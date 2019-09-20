2#include <Servo.h>



Servo myServo;

const int s0 = 1;  
const int s1 = 2;  
const int s2 = 3;  
const int s3 = 4;  
const int out = 5;    
int rojo = 0;  
int verde = 0;  
int azul = 0;

bool r=false, g=false, b=false;

void abrir()
{
  
}

 void cerrar()
 {
  
 }

void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  
  if (rojo < azul && verde > azul && rojo < 35){  
    r=true;
    abrir();
    Serial.println("   Rojo");    
  }else if (azul < rojo && azul < verde && verde < rojo){  
    b=true;
    cerrar();
    Serial.println("   Azul");        
  }else{
    
    Serial.print(" azul  ");  
    Serial.print(azul);
     
    Serial.print(" rojo  ");  
    Serial.print(rojo); 
     
    Serial.print(" verde  ");  
    Serial.print(verde);
    Serial.println(" ");
  }
  delay(900);  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(9);
   
myServo.write(90);
   delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:
  color();

}
