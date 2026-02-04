#include <Arduino.h>
#include <PID_v1.h>
#include <ESP32Servo.h>  // ESP32-specific servo library
#include "BluetoothSerial.h"  // Bluetooth Classic library
#include <Preferences.h>  // ESP32 non-volatile storage library

// ===== EMC Type 1 Controller for ESP32 =====
// Hydraulic clutch controller with user-defined parameters,
// automatic sensor inputs, PID control, LED feedback, and Bluetooth Classic communication
//
// Required Libraries for ESP32:
// - PID_v1 (Arduino IDE Library Manager)
// - ESP32Servo (Arduino IDE Library Manager)
// - BluetoothSerial (included with ESP32 Core)
//
// Hardware Requirements:
// - ESP32 development board
// - RPM sensor connected to GPIO19
// - Potentiometers connected to GPIO34 and GPIO35
// - Servo motor connected to GPIO18
// - Arm switch connected to GPIO21
// - LED connected to GPIO2 (or use built-in LED)
//
// Bluetooth Features:
// - Device name: "EMC_Type_1_Controller"
// - Supports all serial commands: setrpm, setpid, arm, disarm, status, help
// - Real-time status feedback over Bluetooth

// ===== Pin Definitions =====
const int rpmSensorPin = 19;        // Digital pin for RPM sensor pulse train (interrupt capable)
const int potentiometerPin = 34;    // Analog input for additional potentiometer (ADC1_CH6)
const int manualPotPin = 35;        // Analog input for manual servo control potentiometer (ADC1_CH7)
const int servoPin = 18;            // PWM pin for servo motor control
const int armLightPin = 2;          // LED pin for arming light (built-in LED on ESP32)
const int armSwitchPin = 21;        // Digital pin for arm switch


// ===== Global Variables =====
// Calibration parameters
int min_position = 0;               // Minimum servo position (0-180)
int max_position = 180;             // Maximum servo position (0-180)
int neutral_position = 90;          // Neutral servo position (0-180)
int preposition = 90;               // Servo preposition when armed (0-180)
bool direction_reversed = false;    // Servo travel direction (false = normal, true = reversed)

// Preferences object for non-volatile storage (ESP32)
Preferences preferences;

// RPM pulse counting variables (volatile for ISR)
volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;
unsigned long lastRPMCalculation = 0;
const unsigned long rpmCalculationInterval = 1000; // Calculate RPM every 1000ms
const int defaultPulsesPerRevolution = 1;          // Default pulses per revolution
int pulsesPerRevolution = defaultPulsesPerRevolution;  // Dynamically adjustable by user

// Sensor readings
int potValue = 0;
int manualPotValue = 0;
bool armSwitch = false;

bool systemArmed = false;

// LED flashing variables for manual mode
unsigned long lastLEDFlash = 0;
const unsigned long ledFlashInterval = 500; // Flash every 500ms
const unsigned long ledFlashIntervalOverride = 250; // Faster flash for safety override (250ms)
bool ledState = false;

// Safety override system variables
int overrideThreshold = 3500;       // Default threshold for potentiometer value (0-4095 for 12-bit ADC)
bool overrideEnabled = false;       // Safety override feature enabled/disabled
bool safetyOverrideActive = false;  // Flag indicating safety override is active (requires rearm toggle)
bool armSwitchPreviousState = false; // Track arm switch state for toggle detection

// PID Control Variables
double setpointRPM = 1000.0;        // Target RPM (user-configurable)
double currentRPM = 0.0;            // Current RPM from sensor
double pidOutput = 0.0;             // PID output (0-255 for PWM)
double Kp = 2.0, Ki = 5.0, Kd = 1.0; // PID constants (user-configurable)

// Servo control
Servo clutchServo;
int servoPosition = 90;             // Servo position (0-180 degrees)

// PID Controller
PID myPID(&currentRPM, &pidOutput, &setpointRPM, Kp, Ki, Kd, DIRECT);

// Serial communication variables
String inputString = "";
bool stringComplete = false;

// Bluetooth communication variables
BluetoothSerial SerialBT;
String btInputString = "";
bool btStringComplete = false;

// Timing variables
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 500; // Print status every 500ms

// ===== Setup Function =====
void setup() {
  Serial.begin(115200); // Higher baud rate for ESP32
  
  // Load calibration data from Preferences
  loadCalibrationData();
  preferences.begin("emc_calibration", false);
pulsesPerRevolution = preferences.getInt("ppr", defaultPulsesPerRevolution);  // Load pulses per revolution
  if (pulsesPerRevolution <= 0) pulsesPerRevolution = defaultPulsesPerRevolution; // Revert to default if invalid
  preferences.end();

  // Initialize Bluetooth Classic
  SerialBT.begin("EMC_Type_1_Controller"); // Bluetooth device name
  Serial.println("Bluetooth initialized. Device name: EMC_Type_1_Controller");
  
  // Initialize pin modes
  pinMode(rpmSensorPin, INPUT_PULLUP); // Digital input with pullup for RPM pulse train
  pinMode(potentiometerPin, INPUT);
  pinMode(manualPotPin, INPUT);
  pinMode(armLightPin, OUTPUT);
  pinMode(armSwitchPin, INPUT_PULLUP);

  // Configure ADC resolution for ESP32 (12-bit by default)
  analogReadResolution(12); // ESP32 supports 12-bit ADC (0-4095)

  // Setup interrupt for RPM pulse counting (falling edge detection)
  attachInterrupt(digitalPinToInterrupt(rpmSensorPin), rpmPulseISR, FALLING);
  
  // Initialize timing variables
  lastRPMCalculation = millis();
  
  // Initialize servo
  clutchServo.attach(servoPin);
  servoPosition = neutral_position;  // Use calibrated neutral position
  clutchServo.write(servoPosition);
  
  // Initialize PID controller
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(min_position, max_position); // Use calibrated range
  
  // Initialize outputs
  digitalWrite(armLightPin, LOW);
  
  // Reserve string space for serial input
  inputString.reserve(200);
  btInputString.reserve(200);

  Serial.println("Pulses per Revolution (PPR): " + String(pulsesPerRevolution));

  Serial.println("Commands: setppr <value>"); // Adding specific new command documentation
  
  printCalibrationStatus();
}

// ===== Updated Functions =====

// RPM calculation uses pulsePerRevolution now
void readSensors() {
  unsigned long currentTime = millis();
  if (currentTime - lastRPMCalculation >= rpmCalculationInterval) {
    unsigned long timeDelta = currentTime - lastRPMCalculation;
    noInterrupts();
    unsigned long currentPulseCount = pulseCount; pulseCount=0; interrupts(); // fixed.
