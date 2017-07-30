#ifndef GAUGES_H
#define GAUGES_H

#include "application.h"


class GAUGE {
  public:
    GAUGE();
    ~GAUGE();
    void attach(char);
    void calibrate(char, char);
    void setScale(int, int);
    void setValue(int);
    int getValue(void);
    int getScaledValue(void);
  private:
    // Hardware Characteristics
    char gauge_pin;
    char gauge_low  = 0;
    char gauge_high = 255;

    // Max / Min Input Values
    int scale_low  = 0;
    int scale_high = 255;

    // Current Gauge Value (Both raw and scaled for hardware.)
    int gauge_value        = 0;
    int scaled_gauge_value = 0;
};

#endif
