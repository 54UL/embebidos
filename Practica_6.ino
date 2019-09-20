 #include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


const byte filas=4;
const byte columnas=4;
byte pinsFilas[filas] = {28, 30, 32, 34};
byte pinsColumnas[columnas] = {36, 38, 40, 42};

char teclas[filas][columnas]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'},  
};

Keypad teclado = Keypad(makeKeymap(teclas),pinsFilas, pinsColumnas, filas, columnas);

char tecla;
int num;
int  valor=0;
int valor2=0;
int valor1=0;
int led1 = 52;
int led2 = 50;
char key;
int b=0;
int retardo=5;          // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // valor recibido en grados
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor
String leeCadena; 
int cont=0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
pinMode(18, OUTPUT);    // Pin 18 conectar a IN4
pinMode(19, OUTPUT);    // Pin 19 conectar a IN3
pinMode(20, OUTPUT);     // Pin 20 conectar a IN2
pinMode(21, OUTPUT);     // Pin 21 conectar a IN1

  lcd.setCursor(0,0);
  lcd.print("IZQ = 1");
  lcd.setCursor(0,1);
  lcd.print("DER = 2"); 
}
void paso_der(){         // Pasos a la derecha
 digitalWrite(18, LOW); 
 digitalWrite(19, LOW);  
 digitalWrite(20, HIGH);  
 digitalWrite(21, HIGH);  
   delay(retardo); 
   
 digitalWrite(18, LOW); 
 digitalWrite(19, HIGH);  
 digitalWrite(20, HIGH);  
 digitalWrite(21, LOW);  
   delay(retardo); 
   
 digitalWrite(18, HIGH); 
 digitalWrite(19, HIGH);  
 digitalWrite(20, LOW);  
 digitalWrite(21, LOW);  
  delay(retardo); 
 digitalWrite(18, HIGH); 
 digitalWrite(19, LOW);  
 digitalWrite(20, LOW);  
 digitalWrite(21, HIGH);  
  delay(retardo);  
}

void paso_izq() {        // Pasos a la izquierda
 digitalWrite(18, HIGH); 
 digitalWrite(19, HIGH);  
 digitalWrite(20, LOW);  
 digitalWrite(21, LOW);  
  delay(retardo); 
 digitalWrite(18, LOW); 
 digitalWrite(19, HIGH);  
 digitalWrite(20, HIGH);  
 digitalWrite(21, LOW);  
  delay(retardo); 
 digitalWrite(18, LOW); 
 digitalWrite(19, LOW);  
 digitalWrite(20, HIGH);  
 digitalWrite(21, HIGH);  
  delay(retardo); 
 digitalWrite(18, HIGH); 
 digitalWrite(19, LOW);  
 digitalWrite(20, LOW);  
 digitalWrite(21, HIGH);  
  delay(retardo); 
}
        
void apagado() {        
 digitalWrite(18, LOW); 
 digitalWrite(19, LOW);  
 digitalWrite(20, LOW);  
 digitalWrite(21, LOW);  
 }

void loop() {
  delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  tecla = teclado.getKey();
  if(tecla != NO_KEY){
    num = tecla - 48;
  }
    switch(tecla){
      case '1':{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Grados: ");
        do{
          
            tecla = teclado.getKey();
            if(tecla != NO_KEY){
              cont++;
              if (cont == 2){
                valor2 = valor1*10;
                valor1 = valor2;
              }
              if(cont == 3){
                valor1 = valor2 + num;
              }
              if(cont == 4){
                valor = valor1*10;
                valor1 = valor + num;
              }
            if(tecla == '*'){
              b=1;
            }
            else{
            
            lcd.print(tecla);
            num = tecla -48;
            if(cont == 1){
            valor1 = num;
            }
            }
            }
            
        }while(b == 0);
         num = valor1;
        Serial.print(num);             // Convierte Caracteres a cadena de caracteres
        delay(retardo);
        num = (num * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados
   while (num>numero_pasos){   // Girohacia la izquierda en grados
       paso_izq();
       numero_pasos = numero_pasos + 1;
   }
  apagado();         // Apagado del Motor para que no se caliente
     break;   
      };

       case '2':{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Grados: ");
        do{
          
            tecla = teclado.getKey();
            if(tecla != NO_KEY){
              cont++;
              if (cont == 2){
                valor2 = valor1*10;
                valor1 = valor2;
              }
              if(cont == 3){
                valor1 = valor2 + num;
              }
              if(cont == 4){
                valor = valor1*10;
                valor1 = valor + num;
              }
            if(tecla == '*'){
              b=1;
            }
            else{
            
            lcd.print(tecla);
            num = tecla -48;
            if(cont == 1){
            valor1 = num;
            }
            }
            }
            
        }while(b == 0);
         num = valor1;
          num = num * -1;
        delay(retardo);
        num = (num * 1.4222222222);
   while (num<numero_pasos){  
       paso_der();
       numero_pasos = numero_pasos - 1;
   }
  apagado();        
       break;
      };
      
    }
}
