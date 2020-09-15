void setup(void) {
  Serial.begin(9600);
  
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

delay(100);
}

void loop() {
//
//
// Declare I/O ports
//=====================================
int S1 = analogRead(1);
int S2 = analogRead(2);
int S3 = analogRead(3);
int S4 = analogRead(4);
//
int io_M1 = 12;
int io_M2 = 13;

// Return sensor digital values (Serial.Monitor / Serial.Plotter)
//=================================================================
Serial.print("S1= ");
Serial.print(S1);
Serial.print(", ");
Serial.print("S2= ");
Serial.print(S2);
Serial.print(", ");
Serial.print("S3= ");
Serial.print(S3);
Serial.print(", ");
Serial.print("S4= ");
Serial.print(S4);
Serial.println();

// Sensor calibration: Declare the sensor's reading interval for fine-tunning
//=============================================================================
int S1min = 900;
int S2min = 50;
int S3min = 10;
int S4min = 700;
int S1max = 950;
int S2max = 800;
int S3max = 800;
int S4max = 800;

// Declare the digital variation interval for the output ports
//=============================================================================
int MotMin = 0;
int MotMax = 255;

// Working variables
//=============================
boolean S1Conf = false;
boolean S2Conf = false;
boolean S3Conf = false;
boolean S4Conf = false;
boolean Conf1 = false;
boolean Conf2 = false;
boolean Conf3 = false;
boolean Conf4 = false;
//
int MotVar1, MotVar2, MotVar3, MotVar4;
int MotVar;
int Mot1, Mot2;                             //digital output values = [0,255]


// Full-grip confirmation. E.g.: "S1Conf" => Finger-1 is confirming a solid grip
//===============================================================================
if (S1 > S1max) {
  S1Conf = true;
}
  else {
    S1Conf = false;
  }
if (S2 > S2max) {
  S2Conf = true;
}
  else {
    S2Conf = false;
  }
if (S3 > S3max) {
  S3Conf = true;
}
  else {
    S3Conf = false;
  }
if (S4 > S4max) {
  S4Conf = true;
}
  else {
    S4Conf = false;
  }


// Counting how many fingers are confirming a solid grip. 
// E.g.: "Conf2" => two sensors are confirming a solid grip, and so on..
//================================================================================
if (S1Conf && S2Conf && S3Conf && S4Conf) {
  Conf4 = true;
  Conf1 = false;
  Conf2 = false;
  Conf3 = false;
}
  else if ((S1Conf&&S2Conf&&S3Conf) || (S1Conf&&S2Conf&&S4Conf) || (S1Conf&&S3Conf&&S4Conf) || ((S2Conf&&S3Conf&&S4Conf))) {
    Conf3 = true;
    Conf1 = false;
    Conf2 = false;
    Conf4 = false;
  }
  else if ((S1Conf&&S2Conf) || (S1Conf&&S3Conf) || (S1Conf&&S4Conf) || (S2Conf&&S3Conf) || (S2Conf&&S4Conf) || (S3Conf&&S4Conf)) {
    Conf2 = true;
    Conf1 = false;
    Conf3 = false;
    Conf4 = false;
  }
  else if (S1Conf || S2Conf || S3Conf || S4Conf) {
    Conf1 = true;
    Conf2 = false;
    Conf3 = false;
    Conf4 = false;
  }
  else {
    Conf1 = false;
    Conf2 = false;
    Conf3 = false;
    Conf4 = false;
  }


// Mapping the speed revolution variation for limited grip cases
//===========================================================================
if (!S1Conf) {
  MotVar1 = map(S1, S1min, S1max, MotMin, ((MotMax+1)/2));
}

if (!S2Conf) {
  MotVar2 = map(S2, S2min, S2max, MotMin, ((MotMax+1)/2));
}

if (!S3Conf) {
  MotVar3 = map(S3, S3min, S3max, MotMin, ((MotMax+1)/2));
}

if (!S4Conf) {
  MotVar4 = map(S4, S4min, S4max, MotMin, ((MotMax+1)/2));
}
//
MotVar = MotVar1 + MotVar2 + MotVar3 + MotVar4;


// RPM variation rules
//==========================================
if (Conf3 || Conf4) {
  Mot1 = MotMax;
  Mot2 = MotMax;
  analogWrite(io_M1, Mot1);
  analogWrite(io_M2, Mot2);
  analogWrite(7, Mot1);
  analogWrite(8, Mot2);
}
else if (Conf2) {
  Mot1 = MotMax;
  Mot2 = ((MotMax+1)/2) + MotVar;
  analogWrite(io_M1, Mot1);
  analogWrite(io_M2, Mot2);
  analogWrite(7, Mot1);
  analogWrite(8, Mot2);
}
else if (Conf1) {
  Mot1 = MotMax;
  Mot2 = MotVar;
  analogWrite(io_M1, Mot1);
  analogWrite(io_M2, Mot2);
  analogWrite(7, Mot1);
  analogWrite(8, Mot2);
}
else {
  Mot1 = MotVar;
  Mot2 = MotVar;
  analogWrite(io_M1, Mot1);
  analogWrite(io_M2, Mot2);
  analogWrite(7, Mot1);
  analogWrite(8, Mot2);
}
//
delay(100);
}
//
//
//end of loop