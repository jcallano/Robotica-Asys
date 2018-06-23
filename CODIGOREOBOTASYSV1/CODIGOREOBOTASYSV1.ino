#include <QTRSensors.h>


#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             3  // emitter is controlled by digital pin 2

#define pwma 6
#define ain2 7
#define ain1 8
#define stby 9
#define pwmb 11
#define bin2 10
#define bin1 9




QTRSensorsAnalog qtra((unsigned char[]) {A0, A1, A2, A3, A4, A5,A6,A7}, //Inicializando el objeto sensor para poder manuipularlo
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


void setup() {
  // put your setup code here, to run once:
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();

  pinMode(pwma,OUTPUT);
  pinMode(pwmb,OUTPUT);
  pinMode(ain2,OUTPUT);
  pinMode(ain1,OUTPUT);
  pinMode(bin2,OUTPUT);
  pinMode(bin1,OUTPUT);
  pinMode(stby,OUTPUT);
  digitalWrite(stby,HIGH);
  delay(1000);

}

void motores(int A, int B){


  if (A<0){
    digitalWrite(ain2,HIGH);
    digitalWrite(ain1,LOW);
    analogWrite(pwma,map(A,-100,0,255,0));
   
  }else if (A>0) {
    analogWrite(pwma,map(A,0,100,0,255));
    digitalWrite(ain2,LOW);
    digitalWrite(ain1,HIGH);
    
   
  
  }else{ 
    digitalWrite(ain2,LOW);
    digitalWrite(ain1,LOW);
    analogWrite(pwma,0);
  }

  
  if (B<0){
    digitalWrite(bin2,HIGH);
    digitalWrite(bin1,LOW);
    analogWrite(pwmb,map(B,-100,0,255,0));
   
  }else if (B>0) {
    digitalWrite(bin2,LOW);
    digitalWrite(bin1,HIGH);
    analogWrite(pwmb,map(B,0,100,0,255));
   
  
  }else{ 
    digitalWrite(bin2,LOW);
    digitalWrite(bin1,LOW);
    analogWrite(pwmb,0);
  }
   
  }


void loop() {

unsigned int position = qtra.readLine(sensorValues);
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
    
  }

  Serial.print("->    ");
  Serial.println(position);
  
}
