// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

WiFiClient client;
HTTPClient http;
#define USE_SERIAL Serial

String urlGetKontrol = "http://192.168.21.55/monitoring/controllers/kontrol.php?getKontrol=ok";

String statusRelay;

#define WIFI_SSID "Bas"
#define WIFI_PASSWORD "12345678"

#define pinRelay D5

void setup() {
  Serial.begin(115200);

  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(false);

  for(uint8_t t = 4; t > 0; t--) {
      USE_SERIAL.printf("[SETUP] Tunggu %d...\n", t);
      USE_SERIAL.flush();
      delay(1000);
  }

  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  for (int u = 1; u <= 5; u++)
  {
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
      USE_SERIAL.println("Terhubung ke wifi");
      USE_SERIAL.flush();
      delay(1000);
    }
    else
    {
      Serial.println("Wifi belum terhubung");
      delay(1000);
    }
  }

  delay(1000);
}

void loop() {
  Serial.print("STATUS RELAY : ");
  Serial.println(statusRelay);

  Serial.println();

  delay(1000);

  getKontrol();

  if (statusRelay == "ON") {
    digitalWrite(pinRelay, HIGH);
  } else {
    digitalWrite(pinRelay, LOW);
  }

  delay(1000);
}

void getKontrol() {
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    USE_SERIAL.print("[HTTP] Memulai...\n");
    
    http.begin( urlGetKontrol );
    
    USE_SERIAL.print("[HTTP] Ambil status kontrol dari database ...\n");
    int httpCode = http.GET();

    if(httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP] kode response GET : %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) // kode 200 
      {
        statusRelay = http.getString();
        
        Serial.println();
      }
    }
    else
    {
      USE_SERIAL.printf("[HTTP] GET kirim data gagal, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }

  delay(500);
}
