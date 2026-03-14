#include "processing.h"
#include "config.h"
#include <Arduino.h>
#include <math.h>

// float
static float sumVSq     = 0.0f;
static float sumISq     = 0.0f;
static float sumPower   = 0.0f;
static unsigned long sampleCount = 0;

static float vrms       = 0.0f;
static float irms       = 0.0f;
static float realPower  = 0.0f;
static float energyWh   = 0.0f;

static unsigned long windowStartMs = 0;

void processSample(float voltage, float current) {
  sumVSq   += voltage * voltage;
  sumISq   += current * current;
  sumPower += voltage * current;
  sampleCount++;
}

void computeResults() {
  unsigned long now = millis();

  if (now - windowStartMs >= RMS_WINDOW_MS && sampleCount > 0) {
    vrms = 230.0f;   // fixed value
irms = sqrtf(sumISq / (float)sampleCount);
realPower = vrms * irms;   // simple apparent power (or vrms * irms * 0.98f if you want PF approx)

    float secondsThisWindow = RMS_WINDOW_MS / 1000.0f;
    energyWh += realPower * (secondsThisWindow / 3600.0f);

    // Reset for next window
    sumVSq     = 0.0f;
    sumISq     = 0.0f;
    sumPower   = 0.0f;
    sampleCount = 0;
    windowStartMs = now;
  }
}

float getVrms()      { return vrms; }
float getIrms()      { return irms; }
float getRealPower() { return realPower; }
float getEnergyWh()  { return energyWh; }

void resetEnergy() {
  energyWh = 0.0f;
}

// ────────────────────────────────────────────────
//  Initialization function – call once from setup()
// ────────────────────────────────────────────────
void initProcessing() {
  windowStartMs = millis();

  sumVSq     = 0.0f;
  sumISq     = 0.0f;
  sumPower   = 0.0f;
  sampleCount = 0;

  vrms       = 0.0f;
  irms       = 0.0f;
  realPower  = 0.0f;

  //  NO reset energyWh here — it should persist
  
}
