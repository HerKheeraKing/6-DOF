/****
Required Arduino hardware packages:
https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
https://espressif.github.io/arduino-esp32/package_esp32_index.json

Required Libraries:
Arduino ESP32Servo.h

****/

// includes
#include <ESP32Servo.h>

// macros
#define NUM_SERVOS 6
#define MIN_SERVO_POS 10
#define MID_SERVO_POS 90
#define MAX_SERVOPOS 170
#define TIMESTAMP_PERIOD 500
#define NUM_PLATFORM_STATES 24

// structs
typedef struct
{
  uint8_t pin;
  int8_t trim;
  uint8_t last;
  uint8_t next;
} SERVO_DATA;

// globals
bool calibrate = false;
uint32_t timestamp = 0;
uint8_t platform_state = 0;

/*****************/
/**** TODO #1 ****/
/*****************/

// create/initialize servo offset parameter from Solidworks simulation
float platform_offset = 0;

// create 6x array of servo objects
Servo servos[NUM_SERVOS];

// create/initialize 6x array of SERVO_DATA (pin=?, trim=0, last=90, next=90)
SERVO_DATA sdat[NUM_SERVOS] = {
  // 12, 27, 33, 15, 32, 14
  { 12, -2, 90, 90 },
  { 27, 2, 90, 90 },
  { 33, 6, 90, 90 },
  { 15, -3, 90, 90 },
  { 32, 5, 90, 90 },
  { 14, 7, 90, 90 }
};

// create/initialize 24x6 array of DOF platform positions from Solidworks simulation (heave, surge, sway, yaw, pitch, roll)
float dofs[NUM_PLATFORM_STATES][NUM_SERVOS]{
  { 90, 90, 90, 90, 90, 90 },
  { 150.19, 29.81, 150.19, 29.81, 150.19, 29.81 },
  { 90, 90, 90, 90, 90, 90 },
  { 51.5, 128.5, 51.5, 128.5, 51.5, 128.5 },
  { 90, 90, 90, 90, 90, 90 },
  { 126.44, 53.56, 61.37, 68.73, 111.27, 118.63 },
  { 90, 90, 90, 90, 90, 90 },
  { 75.38, 104.62, 143.02, 94.27, 85.73, 36.98 },
  { 90, 90, 90, 90, 90, 90 },
  { 74.59, 68.15, 90.08, 108.83, 116.89, 82.22 },
  { 90, 90, 90, 90, 90, 90 },
  { 114.13, 106.46, 98.93, 60.1, 69.82, 89.55 },
  { 90, 90, 90, 90, 90, 90 },
  { 63.97, 50.56, 63.97, 50.56, 63.97, 50.56 },
  { 90, 90, 90, 90, 90, 90 },
  { 118.32, 111.03, 118.32, 111.03, 118.32, 111.03 },
  { 90, 90, 90, 90, 90, 90 },
  { 113.08, 66.92, 99.94, 124.57, 55.43, 80.06 },
  { 90, 90, 90, 90, 90, 90 },
  { 67.85, 112.15, 78.97, 54.69, 125.31, 101.03 },
  { 90, 90, 90, 90, 90, 90 },
  { 119.28, 121.69, 50.52, 97.09, 98.48, 48.56 },
  { 90, 90, 90, 90, 90, 90 },
  { 58.62, 60.99, 130.98, 81.59, 82.96, 129.08 }

};

// process KVP (KEY=VAL)
String procKVP(String skvp) {
  String sret;
  bool rv = true;

  if (skvp.length()) {
    skvp.toUpperCase();

    int16_t z = skvp.indexOf("=");
    if (z == -1) z = skvp.length();
    String skey = skvp.substring(0, z);
    String sval = skvp.substring(z + 1);
    uint32_t ival = sval.toInt();
    float fval = sval.toFloat();

    //****************************//
    //***** sval length == 0 *****//
    //****************************//
    if (sval.length() == 0) {
      // set calibration mode
      if (skey == "C") sval = String(calibrate);

      // print trim all servos
      else if (skey == "T") {
        for (uint8_t i = 0; i < NUM_SERVOS; i++) {
          sval += " ";
          sval += String(sdat[i].trim);
        }
      }

      // print trim specific servo
      else if (skey[0] == 'T') {
        int8_t i = skey[1] - 48;
        if ((i < 0) || (i >= NUM_SERVOS)) rv = false;
        else sval = String(sdat[i].trim);
      }

      // print offset all servos
      else if (skey == "O")
        sval = String(platform_offset);

      // else error
      else rv = false;
    }

    //*********************************//
    //***** else sval length != 0 *****//
    //*********************************//

    // set calibration state
    else if (skey == "C")
      calibrate = ival;

    // set trim all servos
    else if (skey == "T") {
      for (uint8_t i = 0; i < NUM_SERVOS; i++) sdat[i].trim = ival;
    }

    // set trim specific servo
    else if (skey[0] == 'T') {
      int8_t i = skey[1] - 48;
      if ((i < 0) || (i >= NUM_SERVOS)) rv = false;
      else sdat[i].trim = ival;
    }

    // set offset all servos
    else if (skey == "O")
      platform_offset = ival;

    // else error
    else rv = false;

    // if command OK
    if (rv == true) {
      if (sval.length()) sret = skey + "=" + sval + " OK";
      else sret = skey + " OK";
    }

    // else command ER
    else
      sret = skvp + " ER";

    Serial.println(sret);
  }

  return (sret);
}

// read KVP
String readKVP(void) {
  bool rv = false;
  static uint8_t x = 0;
  static String sstr = "";

  if (x == 0) sstr = "";

  while (Serial.available()) {
    char c = (char)Serial.read();
    if ((c == '\r') || (c == '\n')) {
      x = 0;
      rv = true;
      break;
    }

    x++;
    sstr += c;
  }

  return (rv ? sstr : String(""));
}

void setup() {

  /*****************/
  /**** TODO #2 ****/
  /*****************/
  Serial.begin(9600);

  // initialize serial object
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(sdat[i].pin);
    servos[i].write(90);
  }


  // for all servos
  // attach servo to corresponding pin
  // set servo position to 90 degrees

  Serial.println("setup() complete");
}

void loop() {
  // capture timenow in milliseconds
  uint32_t now = millis();

  // process commands
  procKVP(readKVP());

  /*****************/
  /**** TODO #3 ****/
  /*****************/

  // if calibrating servo trim
  if (calibrate) {
    // for all servos
    // set servo to 90 degrees plus trim, use contrain() to limit range
    for (int i = 0; i < NUM_SERVOS; i++) 
    {
      servos[i].write(90 + sdat[i].trim);
    }
    return;
  }

  /*****************/
  /**** TODO #5 ****/
  /*****************/

  float ratio = (now - timestamp) / (float)TIMESTAMP_PERIOD;

  for (int i = 0; i < NUM_SERVOS; i++) {
    float newPos = sdat[i].last + (sdat[i].next - sdat[i].last) * ratio;
    servos[i].write(constrain(newPos, MIN_SERVO_POS, MAX_SERVOPOS));
  }

  // calculate ratio of timenow to timestamp relative 500ms period
  // for all servos
  // calculate lerped position between last and next using ratio
  // write servo to lerped position, use contrain() to limit range.


  /*****************/
  /**** TODO #4 ****/
  /*****************/

  if (now - timestamp > TIMESTAMP_PERIOD) {
    timestamp = now;
    Serial.println("Next DOF");
    platform_state = (platform_state + 1) % NUM_PLATFORM_STATES;

    for (int i = 0; i < NUM_SERVOS; i++) {
      sdat[i].last = sdat[i].next;
      sdat[i].next = dofs[platform_state][i] + sdat[i].trim;
    }
  }
  // create timestamp that triggers every 500ms
  // reset timestamp to timenow
  // set next platform state (0..23..etc)
  // for all servos
  // save servo next position to servo last position
  // set servo next position to platform position for state, plus servo trim value
}
