#include <ESP32Firebase.h>
#include <ESP32Servo.h>

Servo mg995Servo;

const int servoPin1 = 4;
const int servoPin2 = 33;

#define M11 13
#define M12 14
#define M21 18
#define M22 19

#define M31 15
#define M32 16
#define M41 17
#define M42 32

#define _SSID "IQ"          // Your WiFi SSID
#define _PASSWORD "Siddhesh"      // Your WiFi Password
#define REFERENCE_URL "esp32-eef0c-default-rtdb.firebaseio.com"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);

void setup() {
  mg995Servo.attach(servoPin1);
  mg995Servo.attach(servoPin2);

  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);

  pinMode(M31, OUTPUT);
  pinMode(M32, OUTPUT);
  pinMode(M41, OUTPUT);
  pinMode(M42, OUTPUT);

  Serial.begin(115200);
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  delay(500);
}

void carstop()
{
  mg995Servo.write(90);
  digitalWrite(M11,LOW);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,LOW);

  digitalWrite(M31,LOW);
  digitalWrite(M32,LOW);
  digitalWrite(M41,LOW);
  digitalWrite(M42,LOW);
}

void movefront()
{
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);

  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
}

void moveback()
{
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);

  digitalWrite(M31,LOW);
  digitalWrite(M32,HIGH);
  digitalWrite(M41,LOW);
  digitalWrite(M42,HIGH);
}

void moveleft()
{
  mg995Servo.write(30);
}

void moveright()
{
  mg995Servo.write(120);
}

void loop()
{
  
  int command = firebase.getInt("Robot");
  int command2 = firebase.getInt("Robot2");
    
    if (command == 1) {
    movefront();
    Serial.println("FRONT");
    }
    if (command == 2) {
    moveback();
    Serial.println("BACK");
    }
    if (command == 0) {
    carstop();
    Serial.println("STOP");
    }
    if (command2 == 3) {
    moveleft();
    Serial.println("LEFT");
    } 
    if (command2 == 4) {
    moveright();
    Serial.println("RIGHT");
    }
}