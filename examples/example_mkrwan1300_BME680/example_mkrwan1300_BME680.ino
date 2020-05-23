
//#include "LoRa-payload-BKU.h"
//#include <LoRa-payload-BKU.h>
//#include "\..\src\LoRa-payload-BKU.h"
#include <Wire.h>
#include <SPI.h>
#include "C:\secrets\secrets.h"
#include <Adafruit_BME680.h>
#include "E:\ReposCode\LoRa-payload-BKU\src\LoRa-payload-BKU.h"
using namespace lora_bku;

//use your secrets.h file or enter appEui & appKey below
//  #include secrets.h

// String appEui = "****************";
// String appKey = "********************************";

//set your frequenze plan values are: (EU868,AS923,AU915,KR920,IN865,US915,US915_HYBRID)
_lora_band frequency = EU868;
Adafruit_BME680 bme;

void setup()
{
    Serial.begin(9600);
    setupLorawan(appEui, appKey, frequency);

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop()
{

    payload testpayload[] = {
                            payload(TYPE_TEMP, bme.temperature),
                            payload(TYPE_PRESSURE, bme.pressure),
                            payload(TYPE_RH,bme.humidity)
                            };
    
    /*                          Blockbefüllung 
    payload testpayload3[] = {
                            {TYPE_RH, 66},
                            {TYPE_TEMP, 20.6},
                            };
    */

    sendPayload(testpayload);
    delay(1000);
    uint8_t *MSG = receiveData();
    if (MSG[0] = 0)
    {
        Serial.println("No downlink message received at this time.");
    }
    printMSG(MSG);

    delay(10000);
}