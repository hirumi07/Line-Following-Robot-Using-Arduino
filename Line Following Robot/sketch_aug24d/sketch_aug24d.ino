// Define your constants for PID control
double kp = 1.0; // Proportional gain
double ki = 0.1; // Integral gain
double kd = 0.01; // Derivative gain

double targetSpeed = 100; // Desired motor speed

double leftIntegral = 0;
double rightIntegral = 0;
double leftLastError = 0;
double rightLastError = 0;

#define LMS 3
#define LMB 7
#define LMF 5

#define RMS 6
#define RMB 4
#define RMF 13

#define SR1 8
#define SR2 9
#define SM3 10
#define SL4 11
#define SL5 12

void setup() {
pinMode(LMF, OUTPUT);
pinMode(LMB, OUTPUT);
pinMode(LMS, OUTPUT);

pinMode(RMF, OUTPUT);
pinMode(RMB, OUTPUT);
pinMode(RMS, OUTPUT);

pinMode(SR1, INPUT);
pinMode(SR2, INPUT);
pinMode(SM3, INPUT);
pinMode(SL4, INPUT);
pinMode(SL5, INPUT);

Serial.begin(9600);

}

void loop() {
  int sr1 = digitalRead(SR1);
  int sr2 = digitalRead(SR2);
  int sm3 = digitalRead(SM3);
  int sl4 = digitalRead(SL4);
  int sl5 = digitalRead(SL5);

  
    if (sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 0 && sl5 == 0) {
    forward();
    Serial.println("forward");
  } else if ((sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 0 && sl5 == 0) ||
             (sr1 == 1 && sr2 == 1 && sm3 == 0 && sl4 == 0 && sl5 == 0)) {
               delay(300);
               forward();
               if(sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 == 0){
                  right();
                  Serial.println("right");
               }
               else if(sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 0 && sl5 == 0)  
               {
                 forward();
               }
    

    
  } else if ((sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 1 && sl5 == 1) ||
             (sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 1 && sl5 == 1))
              {
                delay(300);
                forward();
                if(sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 ==0 ){
                  left();
                  Serial.println(" left");
                }
                else if(sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 0 && sl5 ==0){
                  left();
                  Serial.println(" left");

                }else if(sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 1 && sl5 ==1)
                {
                  delay(300);
                  forward();
                  if(sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 1 && sl5 ==1){
                    stopMotors();
                  }
                  else{
                    left();
                  }
                }
    
    
  } else if (sr1 == 0 && sr2 == 1 && sm3 == 0 && sl4 == 0 && sl5 == 0) {
    smoothRight();
    Serial.println("smooth right");
  } else if (sr1 == 1 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 == 0) {
    smoothRight();
    Serial.println("smooth right");
  } else if (sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 1 && sl5 == 0) {
    
    
      smoothLeft();
      Serial.println("smooth left");
    }
    else if(sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 == 1){
      smoothLeft();
      Serial.println("smooth left");
    }

    
   else {
    //stopMotors();
    //Serial.println("stop");
  }
  // Calculate the errors
  double leftError = targetSpeed - digitalRead(LMS);
  double rightError = targetSpeed - digitalRead(RMS);
  
  // Update the integrals
  leftIntegral += leftError;
  rightIntegral += rightError;
  
  // Calculate the derivatives
  double leftDerivative = leftError - leftLastError;
  double rightDerivative = rightError - rightLastError;
  
  // Calculate the PID outputs
  double leftOutput = kp * leftError + ki * leftIntegral + kd * leftDerivative;
  double rightOutput = kp * rightError + ki * rightIntegral + kd * rightDerivative;
  
  // Store errors for the next iteration
  leftLastError = leftError;
  rightLastError = rightError;
  
  // Apply the outputs to motor control
  controlMotors(leftOutput, rightOutput);

  
}

// Function to detect a junction
//bool atJunction(int sr1, int sr2, int sm3, int sl4, int sl5) {
  // Define the conditions that indicate a junction (all sensors detecting junction)
  //return sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 1 && sl5 == 1;
//}

void controlMotors(double leftOutput, double rightOutput) {
  // Map the PID outputs to the motor control range (-255 to 255);
  int leftMotorSpeed = map(leftOutput, -255, 255, -255, 255);
  int rightMotorSpeed = map(rightOutput, -255, 255, -255, 255);

  // Apply the mapped outputs to motor control
  int leftMotorPWM = constrain(targetSpeed + leftMotorSpeed, 0, 255);
  int rightMotorPWM = constrain(targetSpeed - rightMotorSpeed, 0, 255);

  analogWrite(LMS, leftMotorPWM);
  analogWrite(RMS, rightMotorPWM);

  
}

void forward() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  digitalWrite(LMS, 100);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(RMS, 100);
}

void right() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  digitalWrite(LMS, 150);

  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  digitalWrite(RMS, 150);
}

void smoothRight() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  digitalWrite(LMS, 100);

  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  digitalWrite(RMS, 100);
}

void left() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  digitalWrite(LMS, 150);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(RMS, 150);
}

void smoothLeft() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  digitalWrite(LMS, 100);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(RMS, 100);
}

void stopMotors() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, LOW);
  digitalWrite(RMS, 0);
  digitalWrite(LMS, 0);
}