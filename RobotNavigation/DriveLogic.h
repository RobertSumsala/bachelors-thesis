#define PIN_MOTOR_RIGHT_FRONT_DIR1 24 // red
#define PIN_MOTOR_RIGHT_FRONT_DIR2 25 // orange
#define PIN_MOTOR_RIGHT_FRONT_PWM 3 // black

#define PIN_MOTOR_RIGHT_REAR_DIR1 22 // black
#define PIN_MOTOR_RIGHT_REAR_DIR2 23 // khaki
#define PIN_MOTOR_RIGHT_REAR_PWM 2 // orange

#define PIN_MOTOR_LEFT_FRONT_DIR1 28 // purple
#define PIN_MOTOR_LEFT_FRONT_DIR2 29 // blue
#define PIN_MOTOR_LEFT_FRONT_PWM 5 // green

#define PIN_MOTOR_LEFT_REAR_DIR1 26 // white
#define PIN_MOTOR_LEFT_REAR_DIR2 27 // gray
#define PIN_MOTOR_LEFT_REAR_PWM 4 // red

// pwm
#define MOTOR_STOP 0
#define MOTOR_MOVE 110
#define MOTOR_PARK 45   



// speeds at pwm 110 (recommended)
#define TURNING_SPEED 7
#define DRIVING_SPEED 40

// uncomment for faster movement (comment the speeds at pwm 110)
// // speeds at pwm 190 
// #define TURNING_SPEED 12
// #define DRIVING_SPEED 50


// - - - - - - - - - - - - - - - - - CODE - - - - - - - - - - - - - - - 


// run in the setup part of the main code
void configMotorPins(){
	pinMode(PIN_MOTOR_RIGHT_FRONT_DIR1, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_FRONT_DIR2, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_FRONT_PWM, OUTPUT);

	pinMode(PIN_MOTOR_RIGHT_REAR_DIR1, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_REAR_DIR2, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_REAR_PWM, OUTPUT);

	pinMode(PIN_MOTOR_LEFT_FRONT_DIR1, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_FRONT_DIR2, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_FRONT_PWM, OUTPUT);

	pinMode(PIN_MOTOR_LEFT_REAR_DIR1, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_REAR_DIR2, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_REAR_PWM, OUTPUT);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_PWM, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_PWM, LOW);

	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, LOW);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_PWM, LOW);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REAR_PWM, LOW);
}



void setMotorsDirForward(){

	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, HIGH);
}

void setMotorsDirReverse(){

	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, LOW);
}

void setMotorsDirLeft(){
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, HIGH);
}

void setMotorsDirRight() {

	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, HIGH);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, LOW);
}

void setMotorsDirNeutral() {

	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REAR_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FRONT_DIR2, LOW);

	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR1, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REAR_DIR2, LOW);
}

void setMotorPower(byte power){
	analogWrite (PIN_MOTOR_RIGHT_FRONT_PWM, power);
	analogWrite (PIN_MOTOR_LEFT_FRONT_PWM, power);
	analogWrite (PIN_MOTOR_RIGHT_REAR_PWM, power);
	analogWrite (PIN_MOTOR_LEFT_REAR_PWM, power);
}

void turn(int deg){
  //Serial.println("turn" + deg);
  if (deg > 0){
    setMotorsDirRight();
  } else {
    setMotorsDirLeft();
    deg *= -1;
  }

  double s = 3.14 * 20 * ( (double)deg / 360 );
  double t = s / TURNING_SPEED;                             

  setMotorPower(MOTOR_MOVE);
  delay(t*1000);
  setMotorPower(MOTOR_STOP);

}


void drive(double distance){
  Serial.print("            (drive : ");
  Serial.print(distance);
  Serial.println(")");

  if (distance > 0){
    setMotorsDirForward();
  } else {
    setMotorsDirReverse();
    distance *= -1;
  }

  double t = distance / DRIVING_SPEED;              
  
  Serial.print("            (calculated t : ");
  Serial.print(t);
  Serial.println(")");

  setMotorPower(MOTOR_MOVE);
  
  Serial.println("            (Driving)");
  if(t > 400){
    delay(t*1000 - 300);                                      // mind breaking distance
  } else {
    delay(t*1000);                                      // mind breaking distance
  }
  
  setMotorPower(MOTOR_STOP);
  Serial.println("            (Stopping)");
}






// speed and power solves everything :) 