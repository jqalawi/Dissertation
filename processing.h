#ifndef PROCESSING_H
#define PROCESSING_H

void processSample(float voltage, float current);
void computeResults();          // call this periodically to finalize calculations

float getVrms();
float getIrms();
float getRealPower();           // average real power over the window (W)
float getEnergyWh();            // total accumulated energy (Wh)

void resetEnergy();             // optional: reset accumulated energy to 0
void initProcessing();
#endif
