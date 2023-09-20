
#include "DFRobot_ESP_PH.h"
#include <EEPROM.h>
#include "temperature_sensor.cpp"

DFRobot_ESP_PH ph;
#define ESPADC 4096.0   //定義 ESP-32 ADC 值
#define ESPVOLTAGE 3300 //定義 ESP-32 電壓值
#define PH_PIN 35		//定義 pH Meter Data Pin 位於 ESP-32 GPIO 35
float pH_voltage, phValue, pH_temperature; //宣告電壓,pH值變數，暫時將溫度定為攝氏25度

void setup()
{
	Serial.begin(115200);
	EEPROM.begin(32);//pH Meter 校正值存放於EEPROM中，並分配32bytes
	ph.begin();
}

void loop()
{
	static unsigned long timepoint = millis();//millis()單位為毫秒 1s = 1000ms
	if (millis() - timepoint > 1000U) //time interval: 1s
	{
		timepoint = millis();
		//voltage = rawPinValue / esp32ADC * esp32Vin
		pH_voltage = analogRead(PH_PIN) / ESPADC * ESPVOLTAGE; // 讀取電壓
		Serial.print("voltage:");
		Serial.println(pH_voltage, 4);
		
		//以下為溫度輸出
		pH_temperature = readTemperature();  
		Serial.print("temperature:");
		Serial.print(pH_temperature, 1);
		Serial.println("^C");

		phValue = ph.readPH(pH_voltage, pH_temperature); // 傳入電壓與溫度，並回傳pH值至變數pHValue
		Serial.print("pH:");
		Serial.println(phValue, 4);
	}
	ph.calibration(pH_voltage, pH_temperature); // calibration process by Serail CMD
}

//導入temperature_sensor 變數 tempC
float readTemperature()
{
	return tempC;
}
