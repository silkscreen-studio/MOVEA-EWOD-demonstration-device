//    Minimal function implementation for driving the EWOD device.
//    By Clément G. - Silkscreen Studio - https://github.com/silkscreen-studio/MOVEA-EWOD-demonstration-device
//    Implements the HV509 shift register manipulation, HV boost proper enabling/disabling (including `HV OUT` 0V clamping management), and frequency-driven polarity inversion (AC actuation)

#define BLD_IO 4
#define VBIAS_EN 7
#define HVBOOST_EN 0

#define DATA 5
#define CLOCK 6
#define N_LATCH_EN 1
#define N_POLARITY 3

bool pol = 1;

void setup() {
  pinMode (BLD_IO, INPUT);    // HI-Z, pull up keeping the Bleeding Mosfet conducting

  pinMode (VBIAS_EN, OUTPUT);
  digitalWrite (VBIAS_EN, LOW);

  pinMode (HVBOOST_EN, OUTPUT);
  digitalWrite (HVBOOST_EN, LOW);

  pinMode (DATA, OUTPUT);
  pinMode (CLOCK, OUTPUT);
  pinMode (N_LATCH_EN, OUTPUT);
  pinMode (N_POLARITY, OUTPUT);

  digitalWrite (DATA, LOW);
  digitalWrite (CLOCK, LOW);
  digitalWrite (N_LATCH_EN, HIGH);
  digitalWrite (N_POLARITY, HIGH);

  delay (150);

  digitalWrite (VBIAS_EN, HIGH);

  delay(150);
}

void loop() {
  /* Expected procedure:

  shiftData16 (<16 bit variable>);
  delay (5);
  pushDataLatch();
  delay (5);
  HV_ENABLE();
  activateArrayAC (1000, 1000) actuate the droplet for 1s at 1kHz

  ...

  HV_DISABLE();
  shiftData16 (0b0000000000000000);
  pushDataLatch();

  */

}


void shiftData16 (uint16_t data) {
  for (uint8_t b = 0; b <16; b++) {
    digitalWrite (DATA, (data >> b) & 0b0000000000000001);
    delayMicroseconds (1);
    digitalWrite (CLOCK, HIGH);
    delayMicroseconds (2);
    digitalWrite (CLOCK, LOW);
    delayMicroseconds (1);
  }
}

void pushDataLatch () {
  digitalWrite (CLOCK, LOW);
  delayMicroseconds (2);
  digitalWrite (N_LATCH_EN, LOW);
  delayMicroseconds (2);
  digitalWrite (N_LATCH_EN, HIGH);
}

void HV_ENABLE () {
  digitalWrite (HVBOOST_EN, HIGH);
  delay (750);   // HV output still clamped to GND, to cover the HV boost initial overshoot
  pinMode (BLD_IO, OUTPUT); // disable GND clamping: `HV OUT` rises
  digitalWrite (BLD_IO, LOW); //
}


void HV_DISABLE () {
  pinMode (BLD_IO, INPUT); // clamping `HV OUT` to GND 
  digitalWrite (HVBOOST_EN, LOW); // disabling the HV BOOST
  delay (750); // discharging the HV output capacitors
}

void activateArrayAC(uint16_t freq, uint32_t duration){   //ex: duration: 1000ms (1s) freq: 1000Hz (1kHz)
  if (freq == 0 || freq >=65000) return;
  
  uint32_t timeStamp = millis();
  uint32_t halfPeriod = (uint32_t) (500000UL / freq);

  while (millis() - timeStamp <= duration) {
  pol = !pol;
  digitalWrite(N_POLARITY, pol);
  delayMicroseconds (halfPeriod);
  }
}
