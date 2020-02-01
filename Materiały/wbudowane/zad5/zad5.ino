const int buttonPin = 2;
const int ledPin =  9;

int i = 0;
int rememberedState[100] = {0};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9700);
}

void loop() {
  Serial.println(digitalRead(buttonPin));
  digitalWrite(ledPin, rememberedState[i]);
  rememberedState[i] = digitalRead(buttonPin);
  ++i %= 100;
  delay(10);
}
