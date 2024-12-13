#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

// Define variables for the PID controller
double setPoint = 10.0;
double input = 0.0;
double output = 0.0;

// PID tuning parameters
double Kp = 1.0, Ki = 0.1, Kd = 0.05;

// Create PID and AutoTune objects
PID myPID(&input, &output, &setPoint, Kp, Ki, Kd, DIRECT);
PID_ATune aTune(&input, &output);

// Define the PWM pin for the solenoid
const int valve2 = 9;

// Define the delay time in milliseconds
unsigned long delayTime = 1000; // Start with 1000 ms

void setup() {
  Serial.begin(9600);
  
  // Initialize the PID controller
  myPID.SetMode(AUTOMATIC);
  
  // Initialize the PWM pin
  pinMode(valve2, OUTPUT);
  
  // Initialize AutoTune parameters
  aTune.SetOutputStep(50);
  aTune.SetControlType(1); // PI control
  aTune.SetLookbackSec(20);
  aTune.SetNoiseBand(1);
}

void loop() {
  // Update the input value from your sensor
  input = // your code to get the measured value

  // Check if the input value is within 20% of the set point
  if (abs(input - setPoint) <= 0.2 * setPoint) {
    // Start AutoTune
    if (aTune.Runtime()) {
      // AutoTune has finished, apply the new tuning parameters
      Kp = aTune.GetKp();
      Ki = aTune.GetKi();
      Kd = aTune.GetKd();
      myPID.SetTunings(Kp, Ki, Kd);
    }
  }

  // Compute the PID output
  myPID.Compute();

  // Use the output value to control the solenoid with PWM
  analogWrite(valve2, output);

  // Print the output for debugging
  Serial.println(output);

  delay(delayTime); // Adjust the delay as needed
}
