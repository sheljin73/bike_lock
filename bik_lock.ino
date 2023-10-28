#define switch 11
#define bzr 12
#define state 3 
//success
char value;
int statev;
boolean q=false;
boolean bc=true;//bluetooth
boolean ec=false;//engine

void setup() {
  digitalWrite(switch,HIGH);
  digitalWrite(bzr,HIGH);

  Serial.begin(9600);     
  pinMode(switch,OUTPUT);
  pinMode(bzr,OUTPUT);
  pinMode(state,INPUT);

  
}

void loop() {
  if(ec){
    if(q==true){
      statev=digitalRead(state);
      if(statev==LOW){
        for(int i=0;i<1001;i++){
          statev=digitalRead(state);
          if(statev==HIGH) break;
          delay(10);
          if(i%100==0){
            digitalWrite(bzr,LOW);
            delay(1000);
            digitalWrite(bzr,HIGH);
          }
        }
        if(statev==LOW){
          OFF();
          bc=true;
          q=false;
        }
      }
    }
  }

  if(bc==true){
    statev=digitalRead(state);
    if(statev==HIGH){
      digitalWrite(bzr,LOW);
      delay(1000);
      digitalWrite(bzr,HIGH);
      bc=false;
      q=true;
    }
  }
if(bc==false){
    statev=digitalRead(state);
    if(statev==LOW){
      digitalWrite(bzr,LOW);
      delay(1000);
      digitalWrite(bzr,HIGH);
      delay(1000);
      digitalWrite(bzr,LOW);
      delay(1000);
      digitalWrite(bzr,HIGH);
      bc=true;
    }
}

  if(Serial.available()>0){
    value=Serial.read();
    Serial.println(value);
    if(value=='A') ON();
    else if(value=='B') OFF();
  }
}

void ON(){
  digitalWrite(bzr,LOW);
  delay(1000);
  digitalWrite(bzr,HIGH);
  digitalWrite(switch,LOW);
  ec=true;
}

void OFF(){
  digitalWrite(bzr,LOW);
  delay(1000);
  digitalWrite(bzr,HIGH);
  digitalWrite(switch,HIGH);
  ec=false;
}