// Define your pin assignments
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

  if (atJunction(sr1, sr2, sm3, sl4, sl5)) {
    left();
    Serial.println("junction, turning left");
  }
   else if (sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 0 && sl5 == 0) {
    forward();
    Serial.println("forward");
  } else if ((sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 0 && sl5 == 0)||(sr1 == 1 && sr2 == 1 && sm3 == 0 && sl4 == 0 && sl5 == 0)){
    right();
    Serial.println("right");
  }
    else if ((sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 1 && sl5 == 1) || 
         (sr1 == 0 && sr2 == 0 && sm3 == 1 && sl4 == 1 && sl5 == 0) || 
         (sr1 == 0 && sr2 == 1 && sm3 == 1 && sl4 == 1 && sl5 == 0)||
         (sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 1 && sl5 == 1)) {
  left();
  Serial.println("left");
}

   else if (sr1 == 0 && sr2 == 1 && sm3 == 0 && sl4 == 0 && sl5 == 0) {
    smoothright();
    Serial.println("smooth right");
  } else if (sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 1 && sl5 == 0) {
    smoothleft();
    Serial.println("smooth left");
  } else if (sr1 == 1 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 == 0) {
    smoothright();
    Serial.println("smooth right");
  } else if (sr1 == 0 && sr2 == 0 && sm3 == 0 && sl4 == 0 && sl5 == 1) {
    smoothleft();
    Serial.println("smooth left");
  } 
  else {
    stopMotors();
    //Serial.println("stop");
  }
}

// Function to detect a junction
bool atJunction(int sr1, int sr2, int sm3, int sl4, int sl5) {
  // Define the conditions that indicate a junction (all sensors detecting junction)
  return sr1 == 1 && sr2 == 1 && sm3 == 1 && sl4 == 1 && sl5 == 1;
}

// ... (rest of your motor control functions remain the same)


// Motor control functions
void forward() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  analogWrite(LMS, 110);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  analogWrite(RMS, 100);
}

void right() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  analogWrite(LMS, 200);

  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  analogWrite(RMS, 200);
}

void smoothright() {
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  analogWrite(LMS, 100);

  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  analogWrite(RMS, 100);
}

void left() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  analogWrite(LMS, 200);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  analogWrite(RMS, 200);
}

void smoothleft() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  analogWrite(LMS, 100);

  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  analogWrite(RMS, 100);
}

void stopMotors() {
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, LOW);
  analogWrite(RMS, 0);
  analogWrite(LMS, 0);
}
