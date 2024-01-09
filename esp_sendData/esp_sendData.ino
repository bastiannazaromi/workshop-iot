// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

WiFiClient client;
HTTPClient http;
#define USE_SERIAL Serial

String urlSimpan = "http://192.168.21.55/monitoring/controllers/data.php?simpan=ok&suhu=";

String respon;

#define WIFI_SSID "Bas"
#define WIFI_PASSWORD "12345678"

// Sensor Ultrasonik

#define echoPin D1
#define trigPin D2

// Sensor DHT
#include <DHT.h>

#define DHTPIN D0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(false);

  for(uint8_t t = 4; t > 0; t--) {
      USE_SERIAL.printf("[SETUP] Tunggu %d...\n", t);
      USE_SERIAL.flush();
      delay(1000);
  }

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  dht.begin();

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
  int durasi, jarak;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = (durasi / 2) / 29.1;

  if (jarak < 0) {
    jarak = 0;
  }

  Serial.print("Jarak sensor : ");
  Serial.print(jarak);
  Serial.println(" cm");

  Serial.println();
  
  int suhu = dht.readTemperature();
  int kelembapan = dht.readHumidity();

  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.println();

    if (suhu < 100 || kelembapan < 100) {
      Serial.print("Suhu : ");
      Serial.println(suhu);
      Serial.print("Kelembapan Udara : ");
      Serial.println(kelembapan);
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }

  Serial.println();

  delay(1000);

  simpanDatabase(suhu, kelembapan, jarak);

  delay(1000);
}

void simpanDatabase(int suhu, int kelembapan, int jarak) {
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    USE_SERIAL.print("[HTTP] Memulai...\n");
        http.begin( urlSimpan + (String) suhu + "&kelembapan=" + (String) kelembapan + "&jarak=" + (String) jarak );
    
    USE_SERIAL.print("[HTTP] Simpan data sensor ke database ...\n");
    int httpCode = http.GET();

    if(httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP] kode response GET : %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) // kode 200 
      {
        respon = http.getString();
        USE_SERIAL.println("Respon server : " + respon);
        Serial.println();

        delay(200);
      }
    }
    else
    {
      USE_SERIAL.printf("[HTTP] GET kirim data gagal, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
