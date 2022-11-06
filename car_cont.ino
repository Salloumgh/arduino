#define Ledss 23
unsigned long startMillis;
unsigned long currentMillis;

int interval = 1000;
bool isDriveGranted = false;


const int motora1 = 27;
const int motora2 = 26;
const int motorb2 = 32;
const int motorb1 = 33;
const int sensor = 23;
int drive_state;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps = 0;
float steps_old = 0;
float temp = 0;
float rps = 0;
#define led T0
#define Leds 15

int checkp = 0;
void setup() {

  // put your setup code here, to run once:
  pinMode(motora1, OUTPUT);
  pinMode(motorb2, OUTPUT);
  pinMode(motora2, OUTPUT);
  pinMode(motorb1, OUTPUT);
  pinMode(Leds,OUTPUT);
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  Serial.println("STEPS - 0");
  Serial.println(" RPS - 0.00");
  wifiClient_Setup();
      digitalWrite(Ledss,LOW);

  digitalWrite(Leds,LOW);
  pinMode(Ledss, OUTPUT);

  pinMode(led, OUTPUT);
  startMillis = millis();

}


void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= interval) {
    checkDriveGrant();
    startMillis = currentMillis;
  }

  if (isDriveGranted) {
    //SendData(0);
    digitalWrite(Leds,HIGH);
        digitalWrite(Ledss,HIGH);

    drive_state = GetData();
    switch (drive_state) {
      case 1:
        digitalWrite(motora1, HIGH);
        digitalWrite(motora2, LOW);
        digitalWrite(motorb2, LOW);
        digitalWrite(motorb1, HIGH);
        break;
      case 2:
        digitalWrite(motora2, HIGH);
        digitalWrite(motora1, LOW);
        digitalWrite(motorb1, LOW);
        digitalWrite(motorb2, HIGH);
        break;
      case 3:
        digitalWrite(motora1, HIGH);
        digitalWrite(motora2, LOW);
        digitalWrite(motorb2, HIGH);
        digitalWrite(motorb1, LOW);
        break;
      case 4:
        digitalWrite(motorb2, LOW);
        digitalWrite(motorb1, HIGH);
        digitalWrite(motora1, LOW);
        digitalWrite(motora2, HIGH);
        break;
      case -1:
        digitalWrite(motora1, LOW);
        digitalWrite(motora2, LOW);
        digitalWrite(motorb2, LOW);
        digitalWrite(motorb1, LOW);
        break;
    }
  }

  if (!isDriveGranted) {
    digitalWrite(motora1, LOW);
    digitalWrite(motora2, LOW);
    digitalWrite(motorb2, LOW);
    digitalWrite(motorb1, LOW);
    digitalWrite(Leds,LOW);
        digitalWrite(Ledss,LOW);

    drive_state = -1;

  }

  Serial.print("carDir: ");
  Serial.print(drive_state);
  Serial.print("  -  ");
  Serial.print("grant: ");
  Serial.println(isDriveGranted);
}
