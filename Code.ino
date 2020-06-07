int trigPin = 12;    
int echoPin = 11;   
int N = 25;     //Number of measurements per data point
float duration, instvel;
float cm;
unsigned long CurrentTime = 0;
unsigned long PrevTime = 0;
unsigned long ElapsedTime = 0;
float sumprev = 0;
float velocity = 0;
float cmavg = 0;
float sum = 0;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  cmavg = 0;
  sum = 0;
  // Measurement loop
  for (int i = 0; i < N; i++) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
  
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
   
    // Convert the time into a distance
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    sum = sum + cm;

  }
  cmavg = sum / N;
  PrevTime = CurrentTime;
  CurrentTime = millis();
  ElapsedTime = CurrentTime - PrevTime;
  velocity = 1000 * (((sum - sumprev)/N)/ElapsedTime);
  sumprev = sum;

  //Comment any of the following lines to exclude from the printed message and adjust the delay accordingly
    Serial.print(CurrentTime);
    Serial.print(" ms");
    Serial.print("\t");
    Serial.print(cmavg);
    Serial.print(" cm");
    Serial.print("\t");
    Serial.print(velocity);
    Serial.print(" cm/s");
    Serial.println();
    delay(25);
  
}
