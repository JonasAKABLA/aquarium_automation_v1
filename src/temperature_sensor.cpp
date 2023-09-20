
#include <OneWire.h>
#include <DallasTemperature.h>

#define TemperatureSensor_PIN  17 // ESP32 GPIO17 腳位連接DS18B20 Data Pin

OneWire oneWire(TemperatureSensor_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC; // 溫度變數tempC，單位為攝氏


//Serial與溫度傳感器初始化
void setup() {
  Serial.begin(115200); 
  DS18B20.begin();    
}
//進行溫度感測
void loop() {
  DS18B20.requestTemperatures();       // 發出溫度偵測請求
  tempC = DS18B20.getTempCByIndex(0);  // 將溫度結果傳回變數tempC

  //輸出結果
  Serial.print("Temperature: ");
  Serial.print(tempC);   
  Serial.print("°C");

  delay(1000);
}
