//--------------------------//bibliotecas//-------------------------------------------//

#include <HCSR04.h>
#include <Wire.h>
#include<Servo.h>


//------------------//sensor luminosidade//-------------------------------------------//

#define ldr A0

//------------------//pinagem dos motores//-------------------------------------------//

#define velmotor1 6  //PWM motor 1
#define velmotor2 5 //PWM motor 2
#define m1a 8 //saida a do motor 1
#define m1b 7 //saida b do motor 1
#define m2a 4 //saida a do motor 2
#define m2b 3 //saida b do motor 2


//-----------------------//pinagem dos servos//------------------------------------------//

#define PINservoGARRA 13
#define PINservoBRACOS1 12
#define PINservoBRACOS2 18
#define PINservoGIROCORPO 11
#define PINservoABAIXARCORPO1 2
#define PINservoABAIXARCORPO2 19


Servo servoGARRA;
Servo servoBRACOS1;
Servo servoBRACOS2;
Servo servoGIROCORPO;
Servo servoABAIXARCORPO1;
Servo servoABAIXARCORPO2;
//-----------------//pinagem do sensor ultrosonico//----------------------------------------//

#define p_trigger 10
#define p_echo 9

//-------------------------//pinagem buzzer//----------------------------------------------//

#define buzzer 17
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

//---------------------//definições do PCF8574//--------------------------------------//

//#define qtdeCi  1
//byte enderecosPCF8574[qtdeCi] = {32}; //diz que o o CI está no endereço 32 do 12C

//------------------//pinegem do PCF8574//--------------------------------------------//

//pin 3 do PFC8574  = led//
//pin 4 do PFC8574  = led//
//pin 5 do PFC8574  = led//
//pin 6 do PFC8574  = led//
//pin 7 do PFC8574  = led//


//---------------------------//funções//---------------------------------------------------//

UltraSonicDistanceSensor distanceSensor(p_trigger, p_echo); //função para sensor ultrasonico//

//bool ciPCF8574PinMode(byte pino, int modo = -1);  //PinMode para o PCF8574//
//void ciPCF8574Write(byte pino, bool estado);  //digitalWrite para o PFC8574//
//bool ciPCF8574Read(byte pino);  //digitalRead para o PFC8574//
void melody(); //toca a melodia no buzzer//
//--------------------------//variáveis globais//-------------------------------------------//

int vel = 200; //define velocidade dos motores//
int dist_cm; //sensor ultrasonico//
char c = 'a'; //char que o módulo bluetooth irá receber//
float GRAUa = 0; //define o grau dos servos garra//
float GRAUb = 0; //define o grau dos servos braço1//
float GRAUbb = 0; //define o grau dos servos braço2//
float GRAUc = 0; //define o grau dos servos giro do corpo//
float GRAUd = 0; //define o grau dos servos abaixar corpo1//
float GRAUdd = 0; //define o grau dos servos abaixar corpo2//
int tempo = 144; //parametro para o buzzer//
int valor_LDR = 0; //valor lido sensor luminosidade//
int duracao =  10; //parametro para sirene//
int freq = 0; //parametro para sirene//

//--------------------------//setup//-----------------------------------------------------------//

void setup(){

  Serial.begin(9600);
  
  
//setup dos motores//

  int vel=255;
  pinMode(velmotor1,OUTPUT);
  pinMode(velmotor2,OUTPUT);
  pinMode(m1a,OUTPUT);
  pinMode(m1b,OUTPUT);
  pinMode(m2a,OUTPUT);
  pinMode(m2b,OUTPUT);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  analogWrite(velmotor1,vel);
  analogWrite(velmotor2,vel);
  
  //setup do PCF8574//
  
//  Wire.begin();
//  ciPCF8574PinMode(3, OUTPUT);
//  ciPCF8574PinMode(4, OUTPUT);
 // ciPCF8574PinMode(5, OUTPUT);
 // ciPCF8574PinMode(6, OUTPUT);
 // ciPCF8574PinMode(7, OUTPUT);
 // ciPCF8574Write(3, LOW);
//  ciPCF8574Write(4, LOW);
//  ciPCF8574Write(5, LOW);
 // ciPCF8574Write(6, LOW);
 // ciPCF8574Write(7, LOW);

  //setup dos servos//

  servoGARRA.attach(PINservoGARRA);
  servoBRACOS1.attach(PINservoBRACOS1);
  servoBRACOS2.attach(PINservoBRACOS2);
  servoGIROCORPO.attach(PINservoGIROCORPO);
  servoABAIXARCORPO1.attach(PINservoABAIXARCORPO1);
  servoABAIXARCORPO2.attach(PINservoABAIXARCORPO2);
  servoGARRA.write(0);
  servoBRACOS1.write(130);
  servoBRACOS2.write(50);
  servoGIROCORPO.write(30);
  servoABAIXARCORPO1.write(130);
  servoABAIXARCORPO2.write(50);

//---------------------//setup do buzzer//--------------------//

 pinMode(ldr, INPUT);
 pinMode(buzzer, OUTPUT);
 valor_LDR = 50;

//--------------------------------------------------------------//

Serial.println("terminou setup");
delay(3000);
}

//================================//COPO DO PROGRAMA//===============================================================//

void loop(){

Serial.println(c);
//-------//controle manual//-----------//
char c = Serial.read();

//garra//
if(c=='A'){
  GRAUa = GRAUa+5;
  servoGARRA.write(GRAUa);
  }
if(c=='E'){
  GRAUa = GRAUa-5;
  servoGARRA.write(GRAUa);
  }

//braço//
 
  if(c=='B'){
  GRAUb = GRAUb+3;
  servoBRACOS1.write(GRAUb);
  GRAUbb = GRAUbb-3;
  servoBRACOS2.write(GRAUbb);
  
  }
if(c=='F'){
  GRAUb = GRAUb+3;
  servoBRACOS2.write(GRAUb);
  GRAUbb = GRAUbb-3;
  servoBRACOS1.write(GRAUbb);
  }

//giro do corpo//
if(c=='C'){
  GRAUc = GRAUc+5;
  servoGIROCORPO.write(GRAUc);
  }
if(c=='G'){
  GRAUc = GRAUc-5;
  servoGIROCORPO.write(GRAUc);
  }

//abaixar corpo//
  if(c=='D'){
  GRAUd = GRAUb+3;
  servoABAIXARCORPO1.write(GRAUd);
  GRAUdd = GRAUbb-3;
  servoABAIXARCORPO2.write(GRAUdd);
  
  }
if(c=='H'){
  GRAUd = GRAUb+3;
  servoABAIXARCORPO2.write(GRAUd);
  GRAUdd = GRAUbb-3;
  servoABAIXARCORPO1.write(GRAUdd);
  }

//motores//
if(c=='K'){
//dois motores para frente//
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  analogWrite(velmotor1,vel);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  analogWrite(velmotor2,vel);
}
if(c=='I'){
//dois motores para trás//
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  analogWrite(velmotor1,vel);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  analogWrite(velmotor2,vel);
}
if(c=='N'){
//virar para direita//
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  analogWrite(velmotor1,vel);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  analogWrite(velmotor2,vel);
}
if(c=='L'){
//virar para esquerda//
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  analogWrite(velmotor1,vel);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  analogWrite(velmotor2,vel);
}

if(c=='i'||c=='k'||c=='n'||c=='l'){
//parar motores//
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  analogWrite(velmotor1,vel);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  analogWrite(velmotor2,vel);
}

//acender e apagar luzes//
//if(c=='M'){
//  ciPCF8574Write(3, HIGH);
//  ciPCF8574Write(4, HIGH);
// ciPCF8574Write(5, HIGH);
//  ciPCF8574Write(6, HIGH);
//  ciPCF8574Write(7, HIGH);
//}

//if(c=='m'){
//  ciPCF8574Write(3, LOW);
//  ciPCF8574Write(4, LOW);
//  ciPCF8574Write(5, LOW);
 // ciPCF8574Write(6, LOW);
 // ciPCF8574Write(7, LOW);  
//}

//sensor ultrasonico//
if(c=='O'){
  for(char c;c!='o';c = Serial.read()){
  dist_cm=distanceSensor.measureDistanceCm();
  if(dist_cm<=25){
    digitalWrite(m1a,LOW);
    digitalWrite(m1b,LOW);
    digitalWrite(m2a,LOW);
    digitalWrite(m2b,LOW);
      delay(500);
    digitalWrite(m1a,LOW);
    digitalWrite(m1b,HIGH);
    analogWrite(velmotor1,vel);
    digitalWrite(m2a,LOW);
    digitalWrite(m2b,HIGH);
    analogWrite(velmotor2,vel);
      delay(200);
    digitalWrite(m1a,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2a,LOW);
    digitalWrite(m2b,HIGH);
      delay(200);
    }

   if(dist_cm>20){
    digitalWrite(m1a,HIGH);
    digitalWrite(m1b,LOW);
    analogWrite(velmotor1,vel);
    digitalWrite(m2a,HIGH);
    digitalWrite(m2b,LOW);
    analogWrite(velmotor2,vel);
    c = Serial.read();
    
   }

   }
  }

//buzzer//

//botão//
if(c=='J'){

  melody();
}

//sirene se apagar luz//
 valor_LDR=analogRead(ldr);
 if(valor_LDR>850){
for (freq = 200; freq < 2000; freq++) 
  {
    tone(buzzer, freq, duracao); 
    delay(1);
    valor_LDR=analogRead(ldr);
    if(valor_LDR<850){
      break;
    }
  }
  
  for (freq = 2000; freq > 200; freq --) 
  {
    tone(buzzer, freq, duracao); 
    delay(1);
    valor_LDR=analogRead(ldr);
    if(valor_LDR<850){
      break;
    }
 }
 }
 else{
  noTone(buzzer);
 }

}




//--------------------//funções//-----------------------------------------------------//

//-----//funções do PCF8574//-----//

//------------------------------------------------//

//bool ciPCF8574PinMode(byte pino, int modo) {
//static byte modoPinos[qtdeCi];

//  if (modo == -1) {
 //    return bitRead(modoPinos[pino / 8], pino % 8); 
//  } else {
 //    bitWrite(modoPinos[pino / 8], (pino % 8), modo);
 //    return modo;
 // }
//}

//------------------------------------------------//

//void ciPCF8574Write(byte pino, bool estado) {
//static bool inicio = true;
//static byte estadoPin[qtdeCi];

//    if (inicio) {
//       byte estadoCI;
//       for (int nL = 0; nL < qtdeCi; nL++) {

//           for (int nM = 0; nM < 8; nM++) {
  //             bitWrite(estadoCI, nM, !ciPCF8574PinMode(nM + (nL * 8)) );  
//           }
 //          estadoPin[nL] = estadoCI;
 //      }
 //      inicio = false;
 //   }

//    bitWrite(estadoPin[pino / 8], pino % 8, estado);
    
//    Wire.beginTransmission(enderecosPCF8574[pino / 8]);    
//    Wire.write(estadoPin[pino / 8]);                            
//    Wire.endTransmission();        
//}

//------------------------------------------------//

//bool ciPCF8574Read(byte pino) {
//byte lido;
//bool estado;

//   Wire.requestFrom(enderecosPCF8574[pino / 8], 1);
//   if(Wire.available()) {   
//      lido = Wire.read();        
//   }
       
//   estado = bitRead(lido, pino % 8);
//   return estado;  
//}

//------------------------------------------------//


//--------------//função para o buzzer//----------------------//
void melody(){
int melody[] = {
  
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10//
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18//
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26//
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)//
// there are two values per note (pitch and duration), so for each note there are four bytes//
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats//
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


  // iterate over the notes of the melody. //
  // Remember, the array is twice the number of notes (notes + durations)//
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note//
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed//
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!//
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes//
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause//
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.//
    delay(noteDuration);
    
    // stop the waveform generation before the next note.//
    noTone(buzzer);
  }
}


//----------------------------------------------------------//
