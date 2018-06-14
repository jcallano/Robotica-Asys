#define pwma 3
#define ain2 2
#define ain1 4
#define stby 5
#define pwmb 6
#define bin2 8
#define bin1 7





void setup() {

  Serial.begin(9600);
  pinMode(pwma,OUTPUT);
  pinMode(pwmb,OUTPUT);
  pinMode(ain2,OUTPUT);
  pinMode(ain1,OUTPUT);
  pinMode(bin2,OUTPUT);
  pinMode(bin1,OUTPUT);
  pinMode(stby,OUTPUT);
  digitalWrite(stby,HIGH);
  
}

//Esta funcion recibe un entero de -100 a 100 para expresar la velocidad de rotacion de cada canal de max reversa a max delante

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
  
  


String readSerialString () {
    String cadena;
    while (Serial.available()) {
      delay(10);
      if (Serial.available() > 0) {
          char c = Serial.read(); // lee uno a uno los bytes en el bufferserial
          cadena += c; // va conformando la cadena de caracteres enla variable cadena
      }
    }

    if (cadena.length() > 0) {
        //Serial.println(cadena); //para depuracion
        return cadena;
     } else {
     return "0";
     }
}

void loop() {
    
    Serial.flush();
    String comando = readSerialString();//leemos el buffer con el comando y lo cargamos en la cadena comando
    int index=0; //donde almacenaremos las posiciones de las comas para saber los diferentes parametros
  if (comando.startsWith("motor")) {//identifica si es comando para activar los motores
       index=comando.indexOf(',')+1;
       String atra = comando.substring(index,comando.length());
       //Serial.println(atra);//depuracion
       
       index=atra.indexOf(',')+1;
       String izq= atra.substring(0,index-1);
       String der= atra.substring(index, atra.length());
       //Serial.print(izq); //para depuracion
       //Serial.print(',');//para depuracion
       //Serial.println(der);// paradepuracion
       
       motores(izq.toInt(),der.toInt());
    }     
  
}
