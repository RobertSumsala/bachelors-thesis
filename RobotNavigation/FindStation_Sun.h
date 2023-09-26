#define SCANNING_DISTANCE 35
int CHECK_DRIVE_LENGTH;

// ------------------------ Check Directions
int checkDirections(int& RedAndBlueDist_Right, int& RedAndBlueDist_Left){
  int x_red, x_blue;

  Serial.println("      going to check right");
  turn(80);
  drive(CHECK_DRIVE_LENGTH);
  delay(800);
  turn(-100);
  delay(800);

  Serial.println("      turning towards station");
  turnTowardsStation_UsingCam();
  delay(1000);

 
  getToMeasuringDistance(SCANNING_DISTANCE); 
  
  delay(1000);
  RedAndBlueDist_Right = getDistanceOfBlueAndRed(x_red, x_blue);
  Serial.println("      scanned");
  if(RedAndBlueDist_Right == -1){
    Serial.println("      ERROR -> STOP PROCESS OF check sides");
    return -1;
  }
  if(RedAndBlueDist_Right == 0){
    Serial.println("      either front or back -> STOP PROCESS OF check sides");
    return 0;
  }

  Serial.println("      going left");
  delay(800);
  turn(-80);
  drive(CHECK_DRIVE_LENGTH * 2);
  delay(500);
  turn(100);
  delay(800);

  Serial.println("      turning towards station");
  turnTowardsStation_UsingCam();
  delay(1000);

  
  getToMeasuringDistance(SCANNING_DISTANCE);
  delay(800);
  
  RedAndBlueDist_Left = getDistanceOfBlueAndRed(x_red, x_blue);
  Serial.println("      scanned");
  if(RedAndBlueDist_Left == -1){
    Serial.println("      ERROR -> STOP PROCESS OF check sides");
    return -1;
  }
  if(RedAndBlueDist_Left == 0){
    Serial.println("      either front or back -> STOP PROCESS OF check sides");
    return 0;
  }
  

  delay(800);
  return 1;
}

// ------------------------ Get infront of one of the sides
int getInfront_UsingCam(int x_red, int x_blue, int RedAndBlueDist){
  int RedAndBlueDist_Right, RedAndBlueDist_Left;

  CHECK_DRIVE_LENGTH = 30;    // initialize drive length when checking in each direction (it will get smaller each run, if nescessary)
  Serial.print("  CheckDiveLength init: ");
  Serial.println(CHECK_DRIVE_LENGTH);

  //check which way is the Red and Blue distance decreasing
  while(1){
    Serial.println("    initial front/back check");
  // check if at the front
  if (x_blue == -1 && RedAndBlueDist == 0){
    Serial.println("    FRONT -> returning 0");
    return 0;
  }
  // check if at the back
  if (x_red == -1 && RedAndBlueDist == 0){
    Serial.println("    BACK -> returning 180");
    return 180;
  }  
  Serial.println("    not infront, nor at the back -> trying to get to a btter positon");
  
    Serial.println("    checking directions");
    int cd = checkDirections(RedAndBlueDist_Right, RedAndBlueDist_Left);
    if (cd == -1){
      Serial.println("    ERROR -> returning -1");
      return -1;
    }
    if(cd == 0){
      Serial.println("    directions checked -> back or front");
      getDistanceOfBlueAndRed(x_red, x_blue);
      if(x_red == -1 && x_blue != -1){
        Serial.println("    BACK -> returning 180");
        return 180;
      } else if (x_blue == -1 && x_red != -1){
        Serial.println("    FRONT -> returning 0");
        return 0;
      } else {
        return -1;
      }
    }

    Serial.print("    directions checked -> distance of R&B  Left: ");
    Serial.print(RedAndBlueDist_Left);
    Serial.print(" Right: ");
    Serial.println(RedAndBlueDist_Right);
    
    delay(800);
    if(RedAndBlueDist_Left < RedAndBlueDist && RedAndBlueDist_Right > RedAndBlueDist){
      Serial.println("    left was better -> going farther left");
      turn(-70);
      delay(800);
      drive(CHECK_DRIVE_LENGTH * 1.5);
      delay(800);
      turn(90);
      delay(800);
      Serial.println("    turning towards station");
      turnTowardsStation_UsingCam();
      delay(800);
    } else if (RedAndBlueDist_Left > RedAndBlueDist && RedAndBlueDist_Right < RedAndBlueDist) {
      Serial.println("    right was better -> going back right and a bit farther");
      turn(70);
      delay(800);
      drive(CHECK_DRIVE_LENGTH * 2);
      delay(800);
      drive(CHECK_DRIVE_LENGTH * 1.5);
      delay(800);
      turn(-90);
      delay(800);
      Serial.println("    turning towards station");
      turnTowardsStation_UsingCam();
      delay(800);
    } else if (RedAndBlueDist_Left < RedAndBlueDist && RedAndBlueDist_Right < RedAndBlueDist){
      Serial.println("    left and right are worse -> robot was facing a side -> going back to that pos");
      turn(70);
      drive(CHECK_DRIVE_LENGTH);
      delay(800);
      turn(-90);
      delay(800);
      Serial.println("    turning towards station");
      turnTowardsStation_UsingCam();
      delay(800);
      Serial.println("    facing side, returning 90");
      return 90;
    } else {
      Serial.println("    Error encountered -> returning -1");
      return -1;
    }
    getToMeasuringDistance(SCANNING_DISTANCE);
    Serial.print("    new red and blue distance alteration -> r&bd: ");

    RedAndBlueDist = getDistanceOfBlueAndRed(x_red, x_blue);
    Serial.println(RedAndBlueDist);
    delay(800);

    if(CHECK_DRIVE_LENGTH >= 10){
      // deacrease the length of drive, when checking sides with each run, for accuracy
      CHECK_DRIVE_LENGTH *= 0.7;
      Serial.print("    CheckDiveLength init: ");
      Serial.println(CHECK_DRIVE_LENGTH);
    }

    Serial.println("    ideal position not found, another run about to begin");
    Serial.println();
  }
}


//----------------------------------------- main function
int getToDockingPosition_UsingCam(){
  int x_red, x_blue, RedAndBlueDist, distanceFromStation;

  Serial.println("  Turning towards station:");
  turnTowardsStation_UsingCam();
  delay(1000);
  Serial.println("  Facing station, if one was found");
  Serial.println(" Measuring the red and blue distance (first = checking if station is there)");
  RedAndBlueDist = getDistanceOfBlueAndRed(x_red, x_blue);
  Serial.print("    Measured r&b distance: ");
  Serial.println(RedAndBlueDist);

  if (RedAndBlueDist == -1){
    Serial.println(" no station was found, returning with -1");
    return -1;
  }

  Serial.println("  Measuring distance from the station");
  distanceFromStation = measureDistance();
  Serial.print( "   Measured distance from station: ");
  Serial.println(distanceFromStation);

  if (distanceFromStation != SCANNING_DISTANCE){
    Serial.println("  Robot not in scanning distance -> driving to scanning distance");
    driveToObstacle(SCANNING_DISTANCE, MOTOR_MOVE);
    Serial.println("  Robot in scanning position");
  }

  delay(800);

  Serial.println("  Measuring the red and blue distance from a scanning position");
  RedAndBlueDist = getDistanceOfBlueAndRed(x_red, x_blue);
  Serial.print("    Measured r&b distance: ");
  Serial.println(RedAndBlueDist);

  Serial.println("  Getting infront using camera");
  int pos = getInfront_UsingCam(x_red, x_blue, RedAndBlueDist);
  if (pos == -1){
    Serial.println("  Error -> returning -1");
    return -1;
  } else if (pos == 0){
    Serial.println("  FRONT -> returning 0");
    return 0;
  } else if (pos == 180){
    Serial.println("  BACK -> going to front from back");
    getToMeasuringDistance(SCANNING_DISTANCE);
    delay(800);
    distanceFromStation = measureDistance();
    turn(-75);
    delay(500);
    drive(35);
    delay(500);
    turn(75);
    drive(distanceFromStation * 3.3);
    delay(500);
    turn(90);
    delay(500);
    drive(35);
    delay(500);
    turn(90);
    delay(500);
    turnTowardsStation_UsingCam();
    delay(800);
    Serial.println("  FRONT(drived to from back) -> returning 0");
    return 0;
  } else if (pos == 90){
    Serial.println(" ONE OF THE SIDES");
    getToMeasuringDistance(SCANNING_DISTANCE);
    delay(800);
    if (x_red < x_blue){
      Serial.println("  Right side -> going to front");
      distanceFromStation = measureDistance();
      turn(-60);
      delay(500);
      drive(40);
      delay(500);
      turn(75);
      delay(500);
      drive(distanceFromStation + 5);
      delay(500);
      turn(80);
      delay(800);
    } else if (x_red > x_blue){
      Serial.println("  Left side -> going to front");
      distanceFromStation = measureDistance();
      turn(60);
      delay(500);
      drive(40);
      delay(500);
      turn(-75);
      delay(500);
      drive(distanceFromStation + 5);
      delay(500);
      turn(-80);
      delay(800);
    }
    turnTowardsStation_UsingCam();
    Serial.println("  FRONT(drived to from side) -> returning 0");
    return 0;
  }
}