#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

void initCurrentSensor();
float readCurrentInstant();   // returns instantaneous current in Amps

// For calibration ( tune later with measured measurements)
extern float currentOffset;    // ADC midpoint (usually ~2048 for 12-bit)
extern float currentScale;     // Amps per ADC unit

#endif
