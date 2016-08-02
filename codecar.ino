
#include "pitches.h"

#define IN1 8
#define IN2 7
#define IN3 6
#define IN4 5
#define PWM 10
#define PWMValue 50
#define KEYPAD_SCAN0 12
#define KEYPAD_SCAN1 13
#define KEYPAD_SCAN2 A5
#define KEYPAD_SENSE0 A1
#define KEYPAD_SENSE1 A2
#define KEYPAD_SENSE2 A3
#define KEYPAD_SENSE3 A4
#define BUZZER A0

int notes[] = {
  NOTE_B7, NOTE_B5, NOTE_D6, NOTE_F5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6
};

volatile int state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    // initialize serial
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PWM, OUTPUT);
    
  analogWrite(PWM,0);
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
   
  pinMode(KEYPAD_SCAN0, OUTPUT);
  pinMode(KEYPAD_SCAN1, OUTPUT);
  pinMode(KEYPAD_SCAN2, OUTPUT);
  
  pinMode(KEYPAD_SENSE0,INPUT_PULLUP);
  pinMode(KEYPAD_SENSE1,INPUT_PULLUP);
  pinMode(KEYPAD_SENSE2,INPUT_PULLUP);
  pinMode(KEYPAD_SENSE3,INPUT_PULLUP);


//  attachInterrupt(digitalPinToInterrupt(2), blink, FALLING      );
}

int row=0;
int old_key=-1;
int new_key=-1;
int key_pressed=0;
int dummy_count=0;

String commandStr = "";
int lastStrIndex = 0;

int go=-1;
unsigned long time;

void loop() {
  // put your main code here, to run repeatedly:

  // keyboard scan

  for(row=0;row<3;row++){
    if(row==0){
      digitalWrite(KEYPAD_SCAN2,1);
      digitalWrite(KEYPAD_SCAN1,1);
      digitalWrite(KEYPAD_SCAN0,0);
      for(int i=0;i<100;i++){ 
      if(!digitalRead(KEYPAD_SENSE0)){

        new_key=3;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE1)){

        new_key=6;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE2)){

        new_key=9;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE3)){
        
        new_key=11;
        key_pressed=1;
      }
      }
    }
    if(row == 1){
      digitalWrite(KEYPAD_SCAN0,1);
      digitalWrite(KEYPAD_SCAN2,1);
      digitalWrite(KEYPAD_SCAN1,0);
      for(int i=0;i<100;i++){ 
      if(!digitalRead(KEYPAD_SENSE0)){

        new_key=2;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE1)){

        new_key=5;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE2)){

        new_key=8;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE3)){

        new_key=0;
        key_pressed=1;
      }
      }
    }
    if(row == 2){
      digitalWrite(KEYPAD_SCAN0,1);
      digitalWrite(KEYPAD_SCAN1,1);
      digitalWrite(KEYPAD_SCAN2,0);
      for(int i=0;i<100;i++){ 
      if(!digitalRead(KEYPAD_SENSE0)){

        new_key=1;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE1)){

        new_key=4;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE2)){

        new_key=7;
        key_pressed=1;
      }
      if(!digitalRead(KEYPAD_SENSE3)){

        new_key=10;
        key_pressed=1;
      }
      }
    }
  }

  if(key_pressed){
    key_pressed=0;
    if(old_key != new_key){
      String output = "new_key =" + String(new_key);
      Serial.println(output);
      tone(BUZZER, notes[2], 20);
      old_key = new_key;
      if(new_key == 11){
        tone(BUZZER, notes[0], 100);
      }
      dummy_count++;
      if(dummy_count==10){
        dummy_count = 0;
//        tone(A0, notes[0], 100);
      }
      //
//      if(new_key == 0){
//        digitalWrite(9,0);
//        digitalWrite(10,0);
//      }

//      if(new_key == 1){
//        analogWrite(10,30);
//      }
//      if(new_key == 7){
//        analogWrite(10,65);
//      }
      
//      if(new_key == 3){
//        analogWrite(10,170);
//      }
//      if(new_key == 4){
//        analogWrite(10,175);
//      }
//      if(new_key == 5){
//        analogWrite(10,180);
//      }
//      if(new_key == 6){
//        analogWrite(10,185);
//      }
//      if(new_key == 7){
//        analogWrite(10,190);
//      }
//      if(new_key == 8){
//        digitalWrite(10,200);
//      }
///////////////////////////////
//      if(new_key == 10){
//        tone(A0, notes[4], 50);
//        delay(200);
//        tone(A0, notes[5], 50);
//        delay(200);
//        tone(A0, notes[6], 50);
//        delay(200);
//        tone(A0, notes[7], 50);
//        delay(200);
//      }
//
//      if(new_key == 2){
//        digitalWrite(3,0);
//        analogWrite(11,185);
//        digitalWrite(9,0);
//        analogWrite(10,185);
//      }
//      if(new_key == 8){
//        digitalWrite(11,0);
//        analogWrite(3,185);
//        digitalWrite(10,0);
//        analogWrite(9,185);
//      }
//
//      if(new_key == 5){
//        digitalWrite(3,0);
//        digitalWrite(11,0);
//        digitalWrite(9,0);
//        digitalWrite(10,0);
//      }
///////////////////////////////////////
      if(new_key == 11){
        commandStr += "\n";
        Serial.println(commandStr);
      }else{
        commandStr += new_key;
      }
      if(new_key == 10){
        tone(BUZZER, notes[4], 50);
        delay(80);
        tone(BUZZER, notes[5], 50);
        delay(80);
        tone(BUZZER, notes[6], 50);
        delay(80);
        tone(BUZZER, notes[7], 50);
        delay(80);
        go = 1;
      }
    }
  }else{
    old_key = -1;
    new_key = -1;
  }
  ////////////////
  if(go>0){
    Serial.println("");
    int newStrIndex = commandStr.indexOf("\n",lastStrIndex + 1);
    int nextStrIndex = commandStr.indexOf("\n",newStrIndex + 1);
    //
    if(newStrIndex < 0){
        tone(BUZZER, notes[7], 50);
        delay(80);
        tone(BUZZER, notes[6], 50);
        delay(80);
        tone(BUZZER, notes[5], 50);
        delay(80);
        tone(BUZZER, notes[4], 50);
        delay(80);
      go = -1;
      commandStr = "";
      lastStrIndex = 0;
    }else{
      //////////////////////////////////////////////////
      String oneCommand = commandStr.substring((lastStrIndex>0)?(lastStrIndex + 1):lastStrIndex,newStrIndex);
      String nextCommand = commandStr.substring((newStrIndex>0)?(newStrIndex + 1):newStrIndex,nextStrIndex);
      int intOneCommand = oneCommand.toInt();
      int intNextCommand = nextCommand.toInt();
      static int oldIntOneCommand = 0;
      //
      if(intOneCommand == 2){

        digitalWrite(IN1,1);
        digitalWrite(IN2,0);
        digitalWrite(IN3,1);
        digitalWrite(IN4,0);
        analogWrite(PWM,PWMValue);
        delay(1200);


    
       if(intNextCommand != 2){        
        digitalWrite(IN1,0);
        digitalWrite(IN2,0);
        digitalWrite(IN3,0);
        digitalWrite(IN4,0);
        analogWrite(PWM,0);
       }   
      }
      //
      if(intOneCommand == 4){
        if(oldIntOneCommand != intOneCommand) delay(500);
        digitalWrite(IN1,1);
        digitalWrite(IN2,0);
        digitalWrite(IN3,0);
        digitalWrite(IN4,1);
        analogWrite(PWM,PWMValue);
        delay(1200);
        
       
        digitalWrite(IN1,0);
        digitalWrite(IN2,0);
        digitalWrite(IN3,0);
        digitalWrite(IN4,0);
        analogWrite(PWM,0);

      }
      //
      if(intOneCommand == 6){
        if(oldIntOneCommand != intOneCommand) delay(500);
        digitalWrite(IN1,0);
        digitalWrite(IN2,1);
        digitalWrite(IN3,1);
        digitalWrite(IN4,0);
        analogWrite(PWM,PWMValue);
        delay(1200);
        
        
        digitalWrite(IN1,0);
        digitalWrite(IN2,0);
        digitalWrite(IN3,0);
        digitalWrite(IN4,0);
        analogWrite(PWM,0);
        
      }
      if(intOneCommand == 8){
        digitalWrite(IN1,0);
        digitalWrite(IN2,1);
        digitalWrite(IN3,0);
        digitalWrite(IN4,1);
        analogWrite(PWM,PWMValue);
        delay(1200);


        digitalWrite(IN1,0);
        digitalWrite(IN2,0);
        digitalWrite(IN3,0);
        digitalWrite(IN4,0);
        analogWrite(PWM,0);
      }
      oldIntOneCommand = intOneCommand;
      String strOne = "strIndex=" + String(newStrIndex);
      Serial.println(strOne);
      String output = "oneCommand=" + oneCommand + " nextCommand=" + nextCommand;
      Serial.println(output);
      Serial.println("");
      lastStrIndex = newStrIndex;
    }
  }
  //delay(30);
}

void blink() {
    state = HIGH;
        tone(BUZZER, notes[7], 50);
}
