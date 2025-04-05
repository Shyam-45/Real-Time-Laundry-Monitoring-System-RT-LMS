#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi‑Fi Credentials – update these!
const char* ssid = "ssid_name";
const char* password = "ssid_password";

// Server endpoint (update the IP to your laptop’s IP address and port 3000)
const char* serverName = "http://x.x.x.x:3000/api/status";

// Pin Definitions for Vibration Sensors
#define VIB_SENSOR_PIN1 D1   // Washing Machine 1 Sensor
#define VIB_SENSOR_PIN2 D8   // Washing Machine 2 Sensor
#define VIB_SENSOR_PIN3 D5   // Washing Machine 3 Sensor
#define VIB_SENSOR_PIN4 D6   // Washing Machine 4 Sensor

// Buzzer Pin
#define BUZZER_PIN D2        // Buzzer

// Current Sensor Pin
#define CURRENT_SENSOR_PIN A0  // Analog input for the current sensor

// Threshold for current sensor reading (calibrate this based on your setup)
const int currentThreshold = 500; // Example threshold value

// Number of samples to average for the current sensor reading
#define NUM_SAMPLES 10

// Note frequency definitions for melody (in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Define a simple melody and note durations
int melody[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
int noteDurations[] = { 4, 4, 4, 4, 4, 4, 4, 2 };  // Quarter notes and a half note
int melodyLength = sizeof(melody) / sizeof(melody[0]);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Hello");

  // Connect to Wi‑Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi‑Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi‑Fi");

  // Initialize sensor pins
  pinMode(VIB_SENSOR_PIN1, INPUT);
  pinMode(VIB_SENSOR_PIN2, INPUT);
  pinMode(VIB_SENSOR_PIN3, INPUT);
  pinMode(VIB_SENSOR_PIN4, INPUT);
  
  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Optional: Play a startup tone to confirm buzzer operation
  tone(BUZZER_PIN, 1000, 500);
  delay(600);
}

void loop() {
  Serial.println("Loop running...");

  // Read and average current sensor values to reduce noise
  long sumADC = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sumADC += analogRead(CURRENT_SENSOR_PIN);
    delay(10);
  }
  int avgADC = sumADC / NUM_SAMPLES;
  float voltage = avgADC * (1.0 / 1023.0);  // Convert ADC value to voltage

  Serial.print("Average ADC Value: ");
  Serial.print(avgADC);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  // Read vibration sensor values
  int vib1 = digitalRead(VIB_SENSOR_PIN1);
  int vib2 = digitalRead(VIB_SENSOR_PIN2);
  int vib3 = digitalRead(VIB_SENSOR_PIN3);
  int vib4 = digitalRead(VIB_SENSOR_PIN4);

  Serial.print("Vib1: ");
  Serial.print(vib1);
  Serial.print(" | Vib2: ");
  Serial.print(vib2);
  Serial.print(" | Vib3: ");
  Serial.print(vib3);
  Serial.print(" | Vib4: ");
  Serial.println(vib4);

  // Determine machine status for each washing machine
  // Here, we assume a machine is occupied if its vibration sensor is HIGH
  // or if the current sensor value exceeds the threshold.
  bool machine1 = (vib1 == HIGH) || (avgADC > currentThreshold);
  bool machine2 = (vib2 == HIGH) || (avgADC > currentThreshold);
  bool machine3 = (vib3 == HIGH) || (avgADC > currentThreshold);
  bool machine4 = (vib4 == HIGH) || (avgADC > currentThreshold);

  // Print machine status to Serial Monitor
  if (machine1 || machine2 || machine3 || machine4) {
    Serial.println("Machine Status: Occupied");
  } else {
    Serial.println("Machine Status: Available");
    // Play a melody if available
    playMelody();
  }

  // Create JSON payload to send to the server
  String jsonPayload = "{";
  jsonPayload += "\"machine1\": " + String(machine1 ? "true" : "false") + ",";
  jsonPayload += "\"machine2\": " + String(machine2 ? "true" : "false") + ",";
  jsonPayload += "\"machine3\": " + String(machine3 ? "true" : "false") + ",";
  jsonPayload += "\"machine4\": " + String(machine4 ? "true" : "false");
  jsonPayload += "}";

  // Send JSON data via HTTP POST to the backend if connected
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, serverName);  // Updated call with WiFiClient parameter
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonPayload);
    Serial.print("POST response code: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  
  delay(1000);  // Delay before next reading
}

// Function to play a melody on the buzzer
void playMelody() {
  for (int i = 0; i < melodyLength; i++) {
    int noteDuration = 1000 / noteDurations[i];  // Duration in milliseconds
    tone(BUZZER_PIN, melody[i], noteDuration);     // Play the note
    delay(noteDuration * 1.30);                    // Wait for the note to finish plus a pause
    noTone(BUZZER_PIN);                            // Stop the note
  }
}