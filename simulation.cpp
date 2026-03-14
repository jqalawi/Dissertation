#include "simulation.h"
#include "config.h"
#include <Arduino.h>
#include <math.h>

// ────────────────────────────────────────────────
// Persistent state (file scope, static = internal linkage)
// ────────────────────────────────────────────────
static float phase          = 0.0f;
static unsigned long lastMicros = 0;

static float voltageInstant = 0.0f;
static float currentInstant = 0.0f;

void updateSimulation() {
  unsigned long now = micros();

  // Skip very first call to avoid huge initial delta-time
  if (lastMicros == 0) {
    lastMicros = now;
    return;
  }

  float dt = (now - lastMicros) / 1000000.0f;
  lastMicros = now;

  float omega = 2.0f * (float)PI * MAINS_FREQUENCY;

  phase += omega * dt;

  // Wrap phase every full cycle (prevents float drift over long time)
  if (phase >= 2.0f * (float)PI) {
    phase -= 2.0f * (float)PI;
  }

  // Update instantaneous values
  voltageInstant = SIM_VOLTAGE_PEAK * sinf(phase);
  currentInstant = SIM_CURRENT_PEAK * sinf(phase + PHASE_SHIFT);
}

float getSimVoltageInstant() {
  return voltageInstant;
}

float getSimCurrentInstant() {
  return currentInstant;
}
