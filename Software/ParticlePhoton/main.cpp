// Includes
#include "application.h"
#include "gauge.h"

// Definitions
#define GAUGE_PIN_TOP           1
#define GAUGE_PIN_BOTTOM        2

#define GAUGE_PWMLOW_TOP        0
#define GAUGE_PWMHIGH_TOP       193
#define GAUGE_PWMLOW_BOTTOM     0
#define GAUGE_PWMHIGH_BOTTOM    198

#define GAUGE_SCALELOW_TOP      0
#define GAUGE_SCALEHIGH_TOP     100
#define GAUGE_SCALELOW_BOTTOM   0
#define GAUGE_SCALEHIGH_BOTTOM  250


// Declare Gauges
GAUGE top;
GAUGE bottom;


// Function Prototypes
int updateGauge(String);


void setup() {
  // Confirm Particle Cloud Connection
  if (Particle.connected() != true) {
    Particle.connect();
  }

  // Setup Gauges
  top.attach(GAUGE_PIN_TOP);
  top.calibrate(GAUGE_PWMLOW_TOP, GAUGE_PWMHIGH_TOP);
  top.setScale(GAUGE_SCALELOW_TOP, GAUGE_SCALEHIGH_TOP);

  bottom.attach(GAUGE_PIN_BOTTOM);
  bottom.calibrate(GAUGE_PWMLOW_BOTTOM, GAUGE_PWMHIGH_BOTTOM);
  bottom.setScale(GAUGE_SCALELOW_BOTTOM, GAUGE_SCALEHIGH_BOTTOM);

  // Expose Update Function To Particle Cloud
  Particle.function("updateGauge", updateGauge);

  // Set Gauges To Default Value (50%)
  top.setValue((GAUGE_SCALEHIGH_TOP/2));
  bottom.setValue((GAUGE_SCALEHIGH_BOTTOM/2));

  // Disable "breathing" functionality of Photon's onboard LED.
  RGB.control(true);
  RGB.brightness(0);

}


void loop() {


}


int updateGauge(String command_str) {
  /*
    COMMAND STRING FORMAT

    "X;YYY"
    X     = Gauge (0 for top, 1 for bottom.)
    YYY   = Requested Gauge Level

    Ex: "0;75" Will set the top gauge to 75%

    NOTE: Delimiter character (shown as ";" above) is not parsed.
  */

  // Variable Declarations
  int gauge;
  int value;

  // Parse Incoming Request
  command_str.trim();
  gauge = atoi(command_str.substring(0, 1));
  value = atoi(command_str.substring(2, 5));

  // Set Relevant Gauge To Requested Value
  switch(gauge) {
    case 0:
      top.setValue(value);
      break;

    case 1:
      bottom.setValue(value);
      break;

    default:
      return -1;
      break;
  }

  return 1;
}
