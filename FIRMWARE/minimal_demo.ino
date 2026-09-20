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

  delay (300);

  digitalWrite (VBIAS_EN, HIGH);
  Serial.begin(115200);
  delay (8000);    // to make sure I can actually upload a new sketch before it enables HV.
}

void loop() {

  HV_ENABLE();
  delay (4000);

 
  /*
  The electrodes are identified like this:
        6   /   8   /   10   /   12
        5   /   7   /   9    /   13
        4   /   3   /   11   /   14
        2   /   1   /   0    /   15
*/

 // Moving the droplet in circles

  
  moveCell (8);
  moveCell (10);
  moveCell (12);
  moveCell (13);
  moveCell (14);
  moveCell (11);
  moveCell (3);
  moveCell (7);
  }


void shiftData16 (uint16_t data) {
  for (uint8_t b = 0; b < 16; b++) {
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

void activateArrayAC(uint16_t freq, uint32_t duration) {  //ex: duration: 1000ms (1s) freq: 1000Hz (1kHz)
  if (freq == 0 || freq >= 65000) return;
  uint32_t timeStamp = millis();
  uint32_t halfPeriod = (uint32_t) (500000UL / freq);

  while (millis() - timeStamp <= duration) {
    pol = !pol;
    digitalWrite(N_POLARITY, pol);
    delayMicroseconds (halfPeriod);
  }
  digitalWrite(N_POLARITY, HIGH);
}

void moveCell (uint8_t cell) {        // The AC frequency actuation is implemented here directly by constantly changing the register values.
                                      // unlike toggling the POL pin, it doesn't change all the electrodes LOW (0V) to HIGH (168V) 
                                      // drawbacks: The actuation frequency can't be as high as if it was just toggling the POL pin, as the whole register needs to be rewritten
  for (uint16_t i = 0; i < 300; i++) {
      shiftData16 (0x0001 << cell);
      pushDataLatch();
      delay(3);
      shiftData16 (0x0000);
      pushDataLatch();
    }
}
