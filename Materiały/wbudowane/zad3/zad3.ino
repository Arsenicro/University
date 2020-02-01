int randPin;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int i = 0;
int d = 0;
int breathe_speed= 10; 

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

  // We're using a Common Anode RGB LED, colour values are reversed (255 is no light, 0 is full light)
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  analogWrite(redPin, 255);

  // Seeding RNG and picking first colour
  randomSeed(analogRead(0));
  randPin = random(9, 12);
}
 
void loop()
{
  for(i = 255; i >=0; i--){
    analogWrite(randPin, i);
    d  = i/breathe_speed;
    delay(d);
  }
   for(i = 0 ; i <= 255; i++){ 
    analogWrite(randPin, i);
    d  = i/breathe_speed;
    delay(d);
  }
  randPin = random(9, 12);
  delay(970);
}

