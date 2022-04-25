/*
  Sensor - Virtual base class for environmental sensors.
  Created by Jan Benda, November 27th, 2021.
*/

#ifndef Sensor_h
#define Sensor_h


#include <Arduino.h>
#include <TimeLib.h>
#include <SensorDevice.h>


class Sensors;


class Sensor : public SensorDevice {

 public:

  float NoValue = -INFINITY;

  // Initialize the sensor.
  Sensor();

  // Initialize the sensor and set name, mathematical symbol, basic unit, and
  // format of sensor readings.
  // The derived unit is also set to unit, the conversion factor
  // is set to one, the offset to zero.
  Sensor(const char *name, const char *symbol, const char *unit,
	 const char *format);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, and format of sensor readings.
  // The derived unit is also set to unit, the conversion factor
  // is set to one, the offset to zero.
  Sensor(Sensors *sensors, const char *name, const char *symbol,
	 const char *unit, const char *format);

  // Return name of environmental sensor reading as character array.
  const char* name() const;

  // Set name of environmental sensor reading to name.
  void setName(const char *name);

  // Set name and mathematical symbol of environmental sensor reading.
  void setName(const char *name, const char *symbol);

  // Return mathematical symbol of environmental sensor reading as
  // character array.
  const char* symbol() const;

  // Set mathematical symbol of environmental sensor reading to name.
  void setSymbol(const char *symbol);

  // Return unit of sensor readings as character array.
  const char* basicUnit() const;

  // Return unit of derived sensor values as character array.
  const char* unit() const;

  // Set unit of environmental sensor reading to unit.
  
  // Optionally, the sensor reading can be mutliplied by factor and
  // offsetted by offset to result in the desired unit.
  void setUnit(const char *unit, float factor=1.0, float offset=0.0);

  // Set unit, conversion factor, offset, and format string of environmental
  // sensor reading.
  void setUnit(const char *unit, float factor, float offset,
	       const char *format);

  // Set unit, conversion factor, and format string of environmental
  // sensor reading. The offset is set to zero.
  void setUnit(const char *unit, float factor, const char *format);

  // Return format string for sensor readings as character array.
  const char* format() const;

  // Set format string for environmental sensor reading to format.
  void setFormat(const char *format);

  // Return resolution of the sensor readings in the current unit.
  // Any implementation should multiply the resolution with Factor
  // before returning the value.
  virtual float resolution() const = 0;
  
  // Print the resolution using format string into string s.
  // Return the number of printed characters.
  int resolutionStr(char *s) const;
  
  // Report properties of sensor on serial monitor.
  virtual void report();

  // The sensor reading in the basic unit.
  // On error, return -INFINITY.
  // Before you can retrieve a sensor reading,
  // you need to call request(), wait for at least delay() milliseconds,
  // and then call read().
  virtual float reading() const = 0;

  // The sensor reading in the current unit.
  // This default implementation multiplies the sensor reading() with Factor
  // and adds Offset.
  virtual float value() const;
  
  // Print the sensor reading using format string into string s.
  // Return the number of printed characters.
  int valueStr(char *s) const;

  
  // Special unit conversions for temperatures measured in degrees celsius:

  // Set unit to Kelvin.
  void setKelvin();

  // Set unit to Fahrenheit.
  void setFahrenheit();
  
  // Special unit conversions for pressures measured in Pascal:
  // https://www.beamex.com/resources/pressure-unit-converter/

  // Set unit to hectopascal.
  void setHectoPascal();

  // Set unit to kilopascal.
  void setKiloPascal();

  // Set unit to megapascal.
  void setMegaPascal();

  // Set unit to bar.
  void setBar();

  // Set unit to mbar.
  void setMilliBar();

  // Set unit to at.
  void setAt();

  // Set unit to atm.
  void setAtm();

  // Set unit to mm Hg.
  void setMMHg();

  // Set unit to psi.
  void setPSI();

  // Set unit to torr.
  void setTorr();

  
protected:

  char Name[50];
  char Symbol[20];
  char BasicUnit[20];
  char Unit[20];
  char Format[10];
  float Factor;
  float Offset;
  
};


#endif