#include <TinkerKit.h>
#include <Servo.h>

#define buttonPin 13
#define buzzerPin 2
#define electroPin I0
#define ledPin 10
#define tolerance 20 //Z jaką tolerancją mierzyć pole elektromagnetyczne
#define winlast 300 //Jak długo musimy trzymać pozycję "win" by gra została zakończona (w milisekundach)
int val;
unsigned long lasttime=0;
bool ison=false;
bool win=false;
int winstart=0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin,OUTPUT);
  randomSeed(analogRead(0));
  val=random(0,1100);
  Serial.begin(9600);
  delay(1);

}

void loop() {
  int nowval=abs(val-analogRead(electroPin));
  if(nowval<=tolerance){
    if(winstart==0) winstart=millis();
    else if(millis()-winstart>=winlast){
      win=true;
      tone(buzzerPin,300);
      digitalWrite(ledPin,HIGH);
    }
  }else{winstart=0;}
  if(!win) beep(nowval);
  if(digitalRead(buttonPin)){
      noTone(buzzerPin);
      val=random(0,1100);
      win=false;
      digitalWrite(ledPin,LOW);
      lasttime=millis();
      winstart=0;
   }
   Serial.println(analogRead(electroPin));
  

}

void beep(int del){
  unsigned long nowtime=millis();
  if(nowtime-lasttime>=del && !ison){ 
    tone(buzzerPin,300);
    lasttime=nowtime;
    ison=true;
    }
  else if(nowtime-lasttime>=del){
    noTone(buzzerPin);
    lasttime=nowtime;
    ison=false;
    }
  }
