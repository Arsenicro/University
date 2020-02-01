#define MINLIGHT 0
#define MAXLIGHT 255

#define photocellPin 0
#define maxButtonPin 2
#define minButtonPin 3
#define ledPin 9

bool setMin = false;
bool setMax = false;
int photocellReading, minLightning, maxLightning;
 
void setup(void) {
  pinMode(photocellPin, INPUT);
  pinMode(maxButtonPin, INPUT);
  pinMode(minButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
 
void loop(void) {
  if (setMin && setMax) {
    photocellReading = analogRead(photocellPin);
    
    if (photocellReading > maxLightning) 
      analogWrite(ledPin, MINLIGHT);
    
    else if (photocellReading < minLightning) 
      analogWrite(ledPin, MAXLIGHT);
    
    else 
      analogWrite(ledPin, MAXLIGHT - (map(photocellReading, minLightning, maxLightning, MINLIGHT, MAXLIGHT)));
  }
  
  else {
    if (digitalRead(minButtonPin)) {
      minLightning = analogRead(photocellPin);
      setMin = true;
    }
    
    if (digitalRead(maxButtonPin)) {
      maxLightning = analogRead(photocellPin);
      setMax = true;
    }
  }
}