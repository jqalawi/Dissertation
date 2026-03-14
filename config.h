#ifndef CONFIG_H
#define CONFIG_H

// ── Sampling & Timing ────────────────────────────────────────
#define SAMPLE_RATE         1000        // Hz (target simulation rate)
#define SAMPLE_INTERVAL_US (1000000UL / SAMPLE_RATE)
#define RMS_WINDOW_MS       1000        // 1 second RMS calculation window
#define BLYNK_UPDATE_MS     1000        // Blynk send interval (respect rate limits)

// ── Electrical Parameters (Simulation) ───────────────────────
#define MAINS_FREQUENCY     50.0f       // UK/EU mains (change to 60.0f for US)
#define SIM_VOLTAGE_RMS     230.0f
#define SIM_VOLTAGE_PEAK    (SIM_VOLTAGE_RMS * sqrt(2.0f))   // ≈325.27 V
#define SIM_CURRENT_RMS     5.0f
#define SIM_CURRENT_PEAK    (SIM_CURRENT_RMS * sqrt(2.0f))   // ≈7.07 A
#define PHASE_SHIFT         0.2f        // radians (~11.5° lag, PF ≈ cos(0.2) ≈ 0.980)
#define PHASE_SHIFT_DEG     (PHASE_SHIFT * 180.0f / PI)     // for debug printing

// ── Virtual Pins (Blynk) ─────────────────────────────────────
#define VPIN_VRMS           V0
#define VPIN_IRMS           V1
#define VPIN_POWER          V2
#define VPIN_ENERGY         V3

// ── Misc ─────────────────────────────────────────────────────
#define SERIAL_BAUD         115200
// ── Hardware Pins & Calibration ──────────────────────────────
#define CURRENT_PIN         34          // GPIO34 – change to your actual pin

#endif
