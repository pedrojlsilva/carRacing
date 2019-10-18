

/*  
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#define BUTTON1 9
#define BUTTON2 10

#include <LiquidCrystal.h>

int game_control = 1;
int need_print = 1;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int move = 0;
char matrix[129][2];

char carro = '>';
char obstaculo = '#';
char win = '*';


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int temColisaoFrente(){

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateMatrix(){


}       

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moverLeft(){

    
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moveCarroBaixo(){


}

void moveCarroCima(){

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPista(){

    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//funçoes de inicio e termino do jogo
void showStart(){

    
}

void showWin(){

}

void showLose(){

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {

//inicia o game

  lcd.begin(16, 2);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  randomSeed(analogRead(0));
  
}

void loop() {
  

 int controle = 1;
 showStart(); 
 while(controle){    
   delay(50);
   if(digitalRead(BUTTON1)==HIGH || digitalRead(BUTTON2)==HIGH)
    controle = 0;
 }

 delay(700);

int tempoAnterior = millis();

 while(game_control){

  if(need_print){
      printPista();
  }
  
//resposta botoes
    
    if(digitalRead(BUTTON1)==HIGH){
      moveCarroCima();
      
    }
    if(digitalRead(BUTTON2)==HIGH){
      moveCarroBaixo();
    }


    if(millis()-tempoAnterior >= 800){
        tempoAnterior=millis();
        if(matrix[1][0]=='#' && matrix[1][1]=='#') {
        showWin();
        }else{
            moverLeft();
        }

    }

 }
 
}

