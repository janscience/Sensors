#include <ESensors.h>
#include <TemperatureDS18x20.h>
#include <TemperatureDS3231.h>
#include <SenseDHT.h>
#include <SenseBME280.h>
#include <LightTSL2591.h>
#include <LightBH1750.h>
#include <DewPoint.h>
#include <AbsoluteHumidity.h>
#include <SeaLevelPressure.h>

// uncomment the sensors you want to use:
//#define TEMPDS18x20
#define TEMPDS3231
//#define SENSEDHT
#define SENSEBME280
#define LIGHTTSL2591
#define LIGHTBH1750


// settings: -----------------------------------------------------------------

#define DS18x20_PIN 35        // pin for DATA line of DS18x20 themperature sensor
#define DHT_PIN 10            // pin for DATA line of DHTx themperature and humidity sensor
float sensorsInterval = 5.0; // interval between sensor readings in seconds

// ----------------------------------------------------------------------------


ESensors sensors;

#ifdef TEMPDS18x20
TemperatureDS18x20 temp(&sensors);
#endif
#ifdef TEMPDS3231
TemperatureDS3231 temprtc(&sensors);
#endif
#ifdef SENSEDHT
SenseDHT dht(DHT_PIN, DHT_TYPE_22);
TemperatureDHT tempdht(&dht, &sensors);
HumidityDHT humdht(&dht, &sensors);
#endif
#ifdef SENSEBME280
SenseBME280 bme;
TemperatureBME280 tempbme(&bme, &sensors);
HumidityBME280 hum(&bme, &sensors);
//AbsoluteHumidity abshum(&hum, &tempbme, &sensors);
DewPoint dp(&hum, &tempbme, &sensors);
PressureBME280 pres(&bme, &sensors);
//SeaLevelPressure slpres(&pres, &tempbme, 460.0, &sensors);
#endif
#ifdef LIGHTTSL2591
LightTSL2591 tsl;
//Channel0TSL2591 chn0(&tsl, &sensors);
//Channel1TSL2591 chn1(&tsl, &sensors);
//GainTSL2591 gain(&tsl, &sensors);
IRRatioTSL2591 irratio(&tsl, &sensors);
//IrradianceFullTSL2591 irrfull(&tsl, &sensors);
//IrradianceIRTSL2591 irrIR(&tsl, &sensors);
IlluminanceTSL2591 illum(&tsl, &sensors);
#endif
#ifdef LIGHTBH1750
LightBH1750 bh(&sensors);
RawBH1750 bhraw(&bh, &sensors);
QualityBH1750 bhqual(&bh, &sensors);
TimeBH1750 bhtime(&bh, &sensors);
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  sensors.setPrintTime(ESensors::NO_TIME);  // no time column for the serial plotter
  sensors.setInterval(sensorsInterval);
#ifdef TEMPDS18x20
  temp.begin(DS18x20_PIN);
#endif
#ifdef SENSEDHT
  humdht.setPercent();
#endif
  Wire.begin();
#ifdef TEMPDS3231
  temprtc.begin(Wire);
#endif
#ifdef SENSEBME280
  bme.beginI2C(Wire, 0x77);
  hum.setPercent();
  pres.setHecto();
  //slpres.setMilliBar();
#endif
#ifdef LIGHTTSL2591
  tsl.begin(Wire);
  tsl.setGain(LightTSL2591::AUTO_GAIN);
  irratio.setPercent();
#endif
#ifdef LIGHTBH1750
  bh.begin();
  bh.setAutoRanging();
#endif
  Serial.println();
  sensors.reportDevices();  // nice, but confuses the serial plotter
  sensors.report();         // nice, but confuses the serial plotter
  // discard first read:
  sensors.start();
  sensors.read();
  // go:
  sensors.start();
  sensors.printHeader(true);
  #ifdef SENSEDHT
  delay(2100);  // cool down
  #endif
}

void loop(void) {
  if (sensors.update()) {
    sensors.printValues();
#if defined(SENSEBME280) && defined(LIGHTTSL2591)
    tsl.setTemperature(bme.temperature());
#endif
  }
}
