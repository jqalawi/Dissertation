#include "sensors.h"
#include "simulation.h"
#include "current_sensor.h"

#define SIMULATION_MODE   // comment out when using real clamp

#ifdef SIMULATION_MODE
float readVoltage() {
  return getSimVoltageInstant();
}

float readCurrent() {
  return getSimCurrentInstant();
}
#else
float readVoltage() {
  return 230.0f;   // fixed voltage
}

float readCurrent() {
  return readCurrentInstant();   // from real clamp
}
#endif
