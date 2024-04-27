#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP32Firebase.h>


#define RX_PIN 16  // Connect GPS module TX to this pin on ESP32
#define TX_PIN 17  // Connect GPS module RX to this pin on ESP32

SoftwareSerial ss(RX_PIN, TX_PIN);  // Create a SoftwareSerial object
TinyGPSPlus gps;  // Create a TinyGPS++ object

#define _SSID "VINOD"          // Your WiFi SSID
#define _PASSWORD "01971972"      // Your WiFi Password
#define REFERENCE_URL "esp32-eef0c-default-rtdb.firebaseio.com"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);


void setup() {
  Serial.begin(115200);
  ss.begin(9600);

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
  delay(2000);
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isUpdated()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

         Serial.print("latitude = ");
         Serial.println(latitude);
         Serial.print("longitude = ");
         Serial.println(longitude);


         firebase.setFloat("latitude", latitude );                                  //setup path and send readings
         firebase.setFloat("longitude", longitude);

         delay(5000); 

      }
    }
  }
}