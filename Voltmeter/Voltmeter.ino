
int sensorValue=0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(57600); // 115200 seems a bit unstable - and 57600 is enough
}

// An arduino uno run this way has a samplingrate of approx 500 Hz
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
   // print out the value you read:
  Serial.println(voltage);
}
