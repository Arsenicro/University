#define MapFreq(Val) map(Val,MinLight,MaxLight,MinFreq,MaxFreq);

const int LightSensor = 0;
const int Speaker = 9;
const int LeftButton = 5;
const int RightButton = 4;
const int Del=10;

const int MaxRecordLength = 500;
int RecordLength = 0;
int Recorded[MaxRecordLength];
int MinLight;
int MaxLight;
int MinFreq;
int MaxFreq;
int Cycle=0;

bool IsRecorded;
bool SetMin=false;
bool SetMax=false;
bool SetMinFreq=false;
bool SetMaxFreq=false;
bool RecordNow=false;
bool PlayNow=false;

void setup() {
  Serial.begin(9600);
  pinMode(Speaker, OUTPUT);
  Serial.println("Set min and max light:");
}

void loop() {
  if(SetMinFreq && SetMaxFreq){
    termin();
    }
  else{
    setting();
    }
}

void setting(){
  if(!SetMin || !SetMax){
    settingMinMax();
  }else{
    settingFreq();  
  }  
}

int setFreq(int Pin){
  int Freq=30;
  while(digitalRead(Pin)==1){
    Freq+=1;
    Freq=(Freq%3000)+31;
    tone(Speaker,Freq);
    delay(200); 
    
  }
  noTone(Speaker);
  return Freq;
}

void settingFreq(){

  if(!SetMinFreq && digitalRead(LeftButton)){
    MinFreq = setFreq(LeftButton);
    Serial.print("Min frequency set to: ");
    Serial.println(MinFreq);
    SetMinFreq=true;
  }
  
  if(!SetMaxFreq && digitalRead(RightButton)){
    MaxFreq = setFreq(RightButton);
    Serial.print("Max frequency set to: ");
    Serial.println(MaxFreq);
    SetMaxFreq=true;
  }
  
  if(SetMinFreq && SetMaxFreq){
    while(digitalRead(LeftButton) || digitalRead(RightButton)) {}
    Serial.println("***");
    Serial.println("Start Play!");
    
  }
}

void settingMinMax(){
  if(!SetMin && digitalRead(LeftButton)){
    MinLight=analogRead(LightSensor);
    Serial.print("Min light set to: ");
    Serial.println(MinLight);
    SetMin=true;
  }
  if(!SetMax && digitalRead(RightButton)){
    MaxLight=analogRead(LightSensor);
    Serial.print("Max light set to: ");
    Serial.println(MaxLight);
    SetMax=true;
  }

  if(SetMin && SetMax){
    while(digitalRead(LeftButton) || digitalRead(RightButton)) {}
    Serial.println("***");
    Serial.println("Set Min/Max frequency (hold button)");

  }
}

void termin(){
  if(digitalRead(LeftButton)){
    RecordNow=true;
  }
  else if(digitalRead(RightButton)){
     PlayNow=true;
  }
   
  
  if(RecordNow){
    record();
  }
  else if(PlayNow){
    play();
  }
  else{
    int Frequency=MapFreq(analogRead(LightSensor)); 
    tone(Speaker,Frequency);
  }
  delay(Del);
  noTone(Speaker);
    
}

void play(){
  if(Cycle==0){
    Serial.print("Playing record of length: ");
    Serial.println(RecordLength);  
  }
  if(!digitalRead(RightButton) || Cycle==RecordLength){
    PlayNow=false;
    Serial.print("Stopped at: ");
    Serial.println(Cycle);
    Serial.println("***");
    Cycle=0;
  }else{
    tone(Speaker,Recorded[Cycle]);
    Cycle++;  
  }
  
}

void record(){
  if(Cycle==0){
    Serial.println("Recording");
  }
  if(!digitalRead(LeftButton) || Cycle>=MaxRecordLength){
    Serial.print("Record length: ");
    Serial.println(Cycle);
    Serial.println("***");
    RecordNow=false;
    RecordLength=Cycle;
    Cycle=0;
  }else{
    int Frequency=MapFreq(analogRead(LightSensor));
    tone(Speaker,Frequency);
    Recorded[Cycle]=Frequency;
    Cycle++;
    }
}


