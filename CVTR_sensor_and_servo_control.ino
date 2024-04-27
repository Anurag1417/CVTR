#include <ESP32Servo.h>
#include <ESP32Firebase.h>
#include <DHT.h>
#define DHTPIN 26  //GPIO                                                            
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Define the servo motor
Servo mg995Servo1;

#define echoPin1 17
#define triggPin1 16

#define echoPin2 19
#define triggPin2 18

long duration1;
int D1;

long duration2;
int D2;

// Define the pin to which the servo signal wire is connected
const int servoPin1 = 23;
 // Change this to the actual pin you are using
#define Soil 33
#define Smoke 32
//#define LED 14
#define _SSID "IQ"          // Your WiFi SSID
#define _PASSWORD "Siddhesh"      // Your WiFi Password
#define REFERENCE_URL "esp32-eef0c-default-rtdb.firebaseio.com" 
Firebase firebase(REFERENCE_URL);

void setup() {
  // Attach the servo to the specified pin
  mg995Servo1.attach(servoPin1);
  pinMode(triggPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  Serial.begin(115200);
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
  //pinMode(LED, OUTPUT);
  //digitalWrite(LED, HIGH);
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int s = analogRead(Smoke);
  int m = analogRead(Soil);
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  firebase.setInt("Smoke", s); 
  firebase.setInt("Soil", m); 
  firebase.setFloat("Humidity", h);     
  firebase.setFloat("Temperature", t);

  Serial.println(s);
  Serial.println(m);
  Serial.println(h);
  Serial.println(t);

  digitalWrite(triggPin1,LOW);
  delayMicroseconds(2);
  digitalWrite(triggPin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggPin1,LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  D1 = duration1 * 0.034/2;
  Serial.print("DISTANCE1 :");
  Serial.print(D1);
  Serial.println("cm");
  delay(50);

  digitalWrite(triggPin2,LOW);
  delayMicroseconds(2);
  digitalWrite(triggPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggPin2,LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  D2 = duration2 * 0.034/2;
  Serial.print("DISTANCE2 :");
  Serial.print(D2);
  Serial.println("cm");
  delay(50); 
  
  int xaxis = firebase.getString("Xaxis").toInt();
  mg995Servo1.write(xaxis);
  Serial.println(xaxis);
 
  firebase.setInt("Distance1", D1); 
  firebase.setInt("Distance2", D2); 
  
  delay(50);                

}