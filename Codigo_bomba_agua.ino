#include <ESP32Time.h>
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27,lcdColumns, lcdRows);
int pulsadorHora=0;              //almacena el estado del botón
int pulsadorMinutos=0;
int estado=0;                //0=led apagado, 1=led encendido
int horaEditar = 0;
int minutos = 0;
String horaProgramada =  "";
int pulsadores=0;              //almacena el estado del botón
int estados=0;                //0=led apagado, 1=led encendido
int pulsadorAnterior=0;           //almacena el estado anterior del boton

//ESP32Time rtc;
ESP32Time rtc(3600);  // offset in seconds GMT+1

void setup() {
  pinMode(23 , OUTPUT);  //definir pin como salida
lcd.init();
lcd.backlight();
  Serial.begin(115200);
  rtc.setTime(30, 29, 17, 4, 6, 2023);  // 17th Jan 2021 15:24:30
  pinMode(4, INPUT);
  pinMode(18, INPUT); 
  pinMode(19, INPUT);
  horaEditar = rtc.getHour(true);
  minutos = rtc.getMinute();
}

void loop() { 
String hora = rtc.getTime();

 lcd.setCursor(4,0);
 lcd.print(hora);


  pulsadorHora = digitalRead(5); //lee si el botón está pulsado
  pulsadorMinutos = digitalRead(18);

  if( pulsadorMinutos == LOW){
    if( minutos < 59 ){
    minutos++;
        }
    else{
      minutos= 0;
      lcd.clear();
      }

  };

  if( pulsadorHora == LOW){
    if( horaEditar < 23 ){
    horaEditar++;
        }
    else{
  
      horaEditar= 0;
      //lcd.setCursor(2, 1);
      //lcd.print(horaEditar);
      lcd.clear();
      }

  };

  lcd.setCursor(1, 1);
  lcd.print(horaEditar);
  lcd.setCursor(3, 1);
  lcd.print(":");
  lcd.setCursor(4, 1);
  lcd.print(minutos);

String minutosCdna  = String(minutos);
String horaCdna = String( horaEditar );
horaProgramada = horaCdna + ":" + minutos + ":00" ;




  if( hora == horaProgramada ){ 
    digitalWrite( 23, HIGH);
  }



pulsadores = digitalRead(19); //lee si el botón está pulsado
  
  if((pulsadores==HIGH)&&(pulsadorAnterior==LOW)){  //si el boton es pulsado y antes no lo estaba
    estados=1-estados;
    delay(40);               //pausa de 40 ms
  }
  pulsadorAnterior=pulsadores;      //actualiza el nuevo estado del boton        
  
  if(estados==1) {            //si el estado es 1
    Serial.println( "on" ) ;  //se enciende el led
  }
  else{                      //si el estado es 0
     Serial.println( "off" ) ;  //se apaga el led
  }


  delay(150);
}


