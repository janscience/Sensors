#include <DewPoint.h>


DewPoint::DewPoint(Sensor *humidity, Sensor *temperature, Sensors *sensors)
  : SensorDerived(temperature, humidity, sensors,
		  "dew point", "Tdp", "ºC", "%5.1f", 0.35) {
}


float DewPoint::compute(float humidity, float temperature,
			float none) const {
  // https://en.wikipedia.org/wiki/Dew_point
  const float b = 17.62;
  const float c = 243.12;
  float gamma = log(0.01*humidity) + (b * temperature)/(c + temperature);
  return c * gamma/(b - gamma);
}
