// Pixy is connected to ICSP -> takes up pins 50 - 52
Pixy2 pixy;
#define RED 1
#define BLUE 2
// - - - - - - - - - - - - - - - - - CODE - - - - - - - - - - - - - - - 


// run in the setup part of the main code
void setUpPixy(){
  pixy.init(); 
  pixy.changeProg("color_connected_components");
}


//-------------------------------------- Check blocks
void checkBlocks(bool& redFound, bool& blueFound, int& x_red, int& x_blue){
  if (pixy.ccc.getBlocks()){
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      if (pixy.ccc.blocks[i].m_signature == RED) {
        x_red = pixy.ccc.blocks[i].m_x;
        redFound = true;
      } else if (pixy.ccc.blocks[i].m_signature == BLUE){
        x_blue = pixy.ccc.blocks[i].m_x;
        blueFound = true;
      }
      if (redFound && blueFound){
        break;
      }
    }
  } 
}

//-------------------------------------- Turn to station
void turnTowardsStation_UsingCam(){
  bool redFound = false, blueFound = false;
  int x_red, x_blue;

  Serial.println("    scanning");
  checkBlocks(redFound, blueFound, x_red, x_blue); 
  Serial.println("    scanning done");
  delay(800);
  if (!redFound && !blueFound){
    Serial.println("    no target found");
    return;
  } else if (redFound && !blueFound){
    Serial.println("    red found -> turning till red is in middle");
    if(x_red < pixy.frameWidth / 2){
      setMotorsDirLeft();
    } else {
      setMotorsDirRight();
    }
    setMotorPower(MOTOR_MOVE);
    while (x_red > pixy.frameWidth / 2 + 2 || x_red < pixy.frameWidth / 2 - 2){
      checkBlocks(redFound, blueFound, x_red, x_blue);  
    }
    setMotorPower(MOTOR_STOP);
  } else if (blueFound && !redFound){
    if(x_blue < pixy.frameWidth / 2){
      setMotorsDirLeft();
    } else {
      setMotorsDirRight();
    }
    Serial.println("    blue found -> turning till blue is in middle");
    setMotorPower(MOTOR_MOVE);
    while (x_blue > pixy.frameWidth / 2 + 2 || x_blue < pixy.frameWidth / 2 - 2){
      checkBlocks(redFound, blueFound, x_red, x_blue);  
    }
    setMotorPower(MOTOR_STOP);
  } else {
    Serial.print("    both targets found -> ");
    if (x_red < x_blue){
      if(pixy.frameWidth - x_blue > x_red){
      setMotorsDirLeft();
      } else {
      setMotorsDirRight();
      }
      Serial.println("red is on the left -> getting both targets into the center");
      setMotorPower(MOTOR_MOVE);
      while (pixy.frameWidth - x_blue < x_red - 2 || pixy.frameWidth - x_blue > x_red + 2){
        checkBlocks(redFound, blueFound, x_red, x_blue);  
      }
      setMotorPower(MOTOR_STOP);
    } else {
      if(pixy.frameWidth - x_red > x_blue){
      setMotorsDirLeft();
      } else {
      setMotorsDirRight();
      }
      Serial.println("blue is on the left -> getting both targers into center");
      setMotorPower(MOTOR_MOVE);
      while (pixy.frameWidth - x_red < x_blue - 2 && pixy.frameWidth - x_red > x_blue + 2){
        checkBlocks(redFound, blueFound, x_red, x_blue);  
      }
      setMotorPower(MOTOR_STOP);
    }
  }
}



//---------------------------------------------------- Get distance of the two markers
int getDistanceOfBlueAndRed(int& x_red, int& x_blue){
  bool redFound = false, blueFound = false;
  
  checkBlocks(redFound, blueFound, x_red, x_blue);

  if (redFound && !blueFound){
    Serial.print("FRONT!  ->  red X: ");
    Serial.println(x_red);
    x_blue = -1;
    return 0;
  } else if (!redFound && blueFound){
     Serial.print("BACK!  ->  blue X: ");
     Serial.println(x_blue);
     x_red = -1;
     return 0;
  } else if (redFound && blueFound){
     int distance = x_red - x_blue;
     if(distance < 0){
       distance *= -1;
     }
    Serial.print("distance between Red And Blue:  ");
    Serial.print(distance);
    Serial.print("    ->  red X: ");
    Serial.print(x_red);
    Serial.print(", blue X: ");
    Serial.println(x_blue);
    return distance;
  } else {
    Serial.println("Station not visible");
    return -1;
  }
  Serial.println();

}
