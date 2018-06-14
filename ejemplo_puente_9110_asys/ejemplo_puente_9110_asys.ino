#define a1a 3
#define a1b 5
#define b1a 6
#define b1b 9






void setup() {

  Serial.begin(9600);
  pinMode(a1a,OUTPUT);
  pinMode(a1b,OUTPUT);
  pinMode(b1a,OUTPUT);
  pinMode(b1a,OUTPUT);
  digitalWrite(a1a,LOW);
  digitalWrite(a1b,LOW);
  digitalWrite(b1a,HIGH);
  digitalWrite(b1b,LOW);
  
}

//Esta funcion recibe un entero de -100 a 100 para expresar la velocidad de rotacion de cada canal de max reversa a max delante

void motores(int A, int B){


  if (A<0){
   analogWrite(a1a,0);
   analogWrite(a1b,map(A,-100,0,255,0));
  }else if (A>0) {
   analogWrite(a1a,255);
   analogWrite(a1b,map(A,0,100,255,0));
  }else{ 
   analogWrite(a1b,0);
   analogWrite(a1a,0);
  }

  
  if (B<0){
   analogWrite(b1a,0);
   analogWrite(b1b,map(B,-100,0,255,0));
  
  }else if (B>0) {
   analogWrite(b1a,255);
   analogWrite(b1b,map(B,0,100,255,0));
  
  }else{ 
   analogWrite(b1b,0);
   analogWrite(b1a,0);
   
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
