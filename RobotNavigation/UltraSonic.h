// Ultrasonic sensor pins
#define US_TrigerPIN 36   // white -> yellow 
#define US_EchoPIN 37     // green

long duration;
int distance, avgDist;




// - - - - - - - - - - - - - - - - - CODE - - - - - - - - - - - - - - - 


void UltraSonicSetUp(){
  pinMode(US_TrigerPIN, OUTPUT);
  pinMode(US_EchoPIN, INPUT);
}

//-------------------------------------- Measure Distance from an object
int measureDistance(){
  int numberOfZeroResults = 0;
  avgDist = 0;
  for (int i = 0; i < 6; i++){
    digitalWrite(US_TrigerPIN, LOW);
    delayMicroseconds(2);

    digitalWrite(US_TrigerPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_TrigerPIN, LOW);

    duration = pulseIn(US_EchoPIN, HIGH);
    distance = duration*0.034/2;   
    
    if(distance != 0){
      avgDist += distance;
    } else {
      numberOfZeroResults++;
    }
  }

  return avgDist / (6 - numberOfZeroResults);
}

//-------------------------------------- Drive to a certain distance from an object 
void driveToObstacle(int stopAt_distanceFromObject, byte power){
  if(stopAt_distanceFromObject > measureDistance()){
    Serial.println("    reversing");
    setMotorsDirReverse();
    setMotorPower(power);
    while(measureDistance() < stopAt_distanceFromObject - 4){   // mind the breaking distance
    }
  } else {
    Serial.println("    driving forward");
    setMotorsDirForward();
    setMotorPower(power);
    while(measureDistance() > stopAt_distanceFromObject + 4){   // mind the breaking distance
    }
  }
  setMotorPower(MOTOR_STOP);
}

//-------------------------------------- Get to measuring distance
void getToMeasuringDistance(int scanningDistance){
  Serial.println("      measuring distance from station");
  int distanceFromStation = measureDistance();
  Serial.print("      distance from station: ");
  Serial.println(distanceFromStation);
  if (distanceFromStation != scanningDistance){
    Serial.println("      driving to scanning distance");
    driveToObstacle(scanningDistance, MOTOR_MOVE);
  }
  Serial.println("      in position");
}



//-------------------------------------- Park
void park(int stopAt_distanceFromObject){
  driveToObstacle(stopAt_distanceFromObject, MOTOR_PARK);
}



