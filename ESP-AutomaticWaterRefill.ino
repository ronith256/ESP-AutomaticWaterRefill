#define trigPin 5
#define echoPin 18
#define ledPin 12

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
bool onOff;

void setup() {
  Serial.begin(115200); 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode (ledPin, OUTPUT);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  // If water is less than 80% of the Water Tank (1000L) then execute this condition
  // Turn on the LED if water is low. In application an AC switch will be used, which will turn on the Motor.
  if(distanceCm > 100 && !onOff){
    onOff = true;
    digitalWrite(ledPin, HIGH);
  }
  
// When the water is filled to about 95% capacity, turn off the Motor.
  if(distanceCm < 5 && onOff){
    digitalWrite(ledPin, LOW);
  }
  
  // Prints the depth to water in cm
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(1000);
}
