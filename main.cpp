/*************************************************************
   1: Simulation + Processing
 *************************************************************/

#define BLYNK_TEMPLATE_ID   "TMPL5tIIbVPrB"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN    "X0aiBb1G6yeg0OLL_lc9eg05eVQ6PC7x"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "config.h"
#include "simulation.h"
#include "processing.h"
#include "current_sensor.h"

// WiFi credentials
char ssid[] = "VM0160721";
char pass[] = "kv3hdPztxvp5";

BlynkTimer timer;

// ────────────────────────────────────────────────
//  Send values to Blynk +  Serial output
// ────────────────────────────────────────────────
void updateDisplayAndBlynk() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate < BLYNK_UPDATE_MS) return;
  lastUpdate = millis();

  computeResults();   // finalize any pending window

  float v   = getVrms();
  float i   = getIrms();
  float p   = getRealPower();
  float e   = getEnergyWh();

  // Send to Blynk (V0–V3)
  Blynk.virtualWrite(V0, v);
  Blynk.virtualWrite(V1, i);
  Blynk.virtualWrite(V2, p);
  Blynk.virtualWrite(V3, e);

  // Clean Serial output
  Serial.printf(
    "Vrms: %6.1f V | Irms: %5.3f A | Power: %6.1f W | Energy: %7.3f Wh\n",
    v, i, p, e
  );
}

// ────────────────────────────────────────────────
//  Main sampling loop (called very frequently)
// ────────────────────────────────────────────────
void samplingTask() {
  updateSimulation();                    // advance waveform
  processSample(
    getSimVoltageInstant(),
    getSimCurrentInstant()
  );
  computeResults();                      // check if window is ready
}

// ────────────────────────────────────────────────
//  SETUP
// ────────────────────────────────────────────────
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(150);
  Serial.println("\n=== Energy Monitor - Simulation + Processing ===\n");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Fast sampling (~every 1 ms target, but Arduino loop speed limits it)
  timer.setInterval(1L, samplingTask);

  // Display / Blynk update every 1 second
  timer.setInterval(BLYNK_UPDATE_MS, updateDisplayAndBlynk);

  initProcessing();           // ← add this instead
  Serial.println("Setup complete — collecting samples...");
  initCurrentSensor();   // call this after initProcessing()
}

// ────────────────────────────────────────────────
//  LOOP 
// ────────────────────────────────────────────────
void loop() {
  Blynk.run();
  timer.run();
  static unsigned long last = 0;
if (millis() - last > 1000) {
  last = millis();
  Serial.print("Raw ADC: ");
  Serial.println(analogRead(CURRENT_PIN));
  Serial.print("Current instant: ");
  Serial.println(readCurrentInstant(), 3);
}
}
