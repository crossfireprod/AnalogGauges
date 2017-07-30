#include "gauge.h"


// Constructor
GAUGE::GAUGE() {
}


// Destructor: Zero Gauge
GAUGE::~GAUGE() {
  analogWrite(gauge_pin, gauge_low);
}


// Initializes gauge on specified pin to minmum value.
void GAUGE::attach(char pin) {
  // Initialize Output
  gauge_pin = pin;
  pinMode(gauge_pin, OUTPUT);

  // Zero Gauge
  analogWrite(gauge_pin, scaled_gauge_value);
}


// Store high and low end hardware limits for driving the gauge.
void GAUGE::calibrate(char l, char h) {
  gauge_low = l;
  gauge_high = h;
}


// Set scale of input values that can be passed into setValue function.
void GAUGE::setScale(int l, int h) {
  scale_low   = l;
  scale_high  = h;
}


// Set gauge needle to specified value.
void GAUGE::setValue(int value) {
  // Force the requested value into within bounds of the specified scale.
  if (value < scale_low) {
    value = scale_low;
  } else if (value > scale_high) {
    value = scale_high;
  }

  // Scale desired value to characteristics of hardware driving the gauge.
  gauge_value = value;
  scaled_gauge_value = (gauge_value - scale_low) * (gauge_high - gauge_low) / (scale_high - scale_low) + gauge_low;

  // Set gauge to desired value.
  analogWrite(gauge_pin, scaled_gauge_value);
}

// Return the gauge's current value.
int GAUGE::getValue() {
  return gauge_value;
}


// Return the gauge's current value, as scaled to the characteristics of hardware driving the gauge.
int GAUGE::getScaledValue() {
  return scaled_gauge_value;
}
