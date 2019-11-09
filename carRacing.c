

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
    //deve retornar 1 se houve colisao
    if(matrix[0][0]=='>' && matrix[1][0]!=' '){
        return 1;
    }else if(matrix[0][1]=='>' && matrix[1][1]!=' '){
        return 1;
    }else{
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateMatrix(){
  
//gerar uma matriz de 2x128 onde cada coluna segue o seguinte padrao
//Tipo1: '#' e ' '
//Tipo2: ' ' e '#'
//Tipo3: ' ' e ' '
     // limpa toda a matriz
     for (int j=0;j<130;j++){
        matrix[j][0]=' ';
        matrix[j][1]=' ';
    }
    // inicia a matriz apenas da coluna 14 em diante para que o jogo 
    // não comece com obstaculo em cima do carro e ja encerre
    for (int j=14;j<129;j=j+2){
        int valor = random(2)%2;
        if(valor == 0){
            matrix[j][0]=' ';
            matrix[j][1]='#';
        }else if(valor == 1){
            matrix[j][0]='#';
            matrix[j][1]=' ';
        }
        
    }
    
//Carro inicia em:
     matrix [0][0]=' ';
     matrix [0][1]='>';
// linha de vitoria
     matrix [128][0]='#';
     matrix [128][1]='#';

}       

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moverLeft(){
    //Se o objeto daquela celula for diferente de um carro, deve ser movido para a esquerda
    if(temColisaoFrente()==0){
        for(int linha = 0; linha < 2; linha++) {
            for(int coluna = 0; coluna < 128; coluna++) {
                if(matrix[coluna][linha] != '>') {
                    matrix[coluna][linha] = matrix[coluna + 1][linha];
                }
            }
        }
        need_print=1;

    }else{
        showLose();
    }
    
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moveCarroBaixo(){
    //checa se o carro está na linha de cima e o conteudo da segunda linha
    //caso haja obstaculo, a partida será encerrada
    //caso esteja livre, faz o movimento
    //caso o carro ja esteja na segunda linha, nao faz nada
    if(matrix[0][0] == '>' && matrix[0][1] == '#'){
      showLose();
    } else if(matrix[0][1] == ' ' && matrix[0][0] == '>'){
      matrix[0][0] = ' ';
      matrix[0][1] = '>';
    }
    need_print=1;

}

void moveCarroCima(){
    //checa se o carro está na segunda linha e o conteudo da primeira linha
    //caso haja obstaculo, a partida será encerrada
    //caso esteja livre, faz o movimento
    //caso o carro ja esteja na primeira linha, nao faz nada
    if(matrix[0][1] == '>' && matrix[0][0] == '#'){
      showLose();
    } else if(matrix[0][0] == ' ' && matrix[0][1] == '>'){
      matrix[0][0] = '>';
      matrix[0][1] = ' ';
    }
    need_print=1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPista(){
    //atualiza o LCD
    lcd.clear();
    lcd.setCursor(0,0);

    for(int i = 0; i < 17; i++){
      lcd.print(matrix[i][0]);
    }

    lcd.setCursor(0,1);
    for(int i = 0; i < 16; i++){
      lcd.print(matrix[i][1]);
    }
     need_print=0; 
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//funçoes de inicio e termino do jogo
void showStart(){
    game_control=1;
    need_print=1;
    generateMatrix();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("hello, world!");
    lcd.setCursor(0,1);
    lcd.print("Equipe 7");
    
}

void showWin(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Parabens!");
    lcd.setCursor(0,1);
    lcd.print("Voce ganhou!");
    game_control = 0;

    delay(2000);
}

void showLose(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(":( :( :( :(");
    lcd.setCursor(0,1);
    lcd.print("Voce perdeu");
    game_control=0;
    delay(2000);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {

//inicia o game
  Serial.begin(9600);
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

unsigned long tempoAnterior = millis();

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
//resposta ao teclado
    if(Serial.available()){
        if( Serial.read() == 'a'){
            moveCarroCima();
        }
        if(Serial.read() == 's'){
            moveCarroBaixo();
        }
    }



    if(millis()-tempoAnterior >= 750){
        tempoAnterior=millis();
        if(matrix[1][0]=='#' && matrix[1][1]=='#') {
            showWin();
        }else{
            moverLeft();
        }

    }

 }
 
}

