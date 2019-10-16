

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


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int move = 0;
char matrix[2][129];

char carro = '>';
char obstaculo = '#';
char win = '*';


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int temColisao(){
    //deve retornar 1 se houve colisao
    if(matrix[0][0]=='>' && matrix[0][1]!=' '){
        return 1;
    }else if(matrix[1][0]=='>' && matrix[1][1]!=' '){
        return 1;
    }else{
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateMatrix(){


 //Carro inicia em:
     matrix [0][0]=' ';
     matrix [1][0]='>';
// linha de vitoria
     matrix [0][128]='*';
     matrix [1][128]='*';
   
//gerar uma matriz de 2x128 onde cada coluna segue o seguinte padrao
//Tipo1: '#' e ' '
//Tipo2: ' ' e '#'
//Tipo3: ' ' e ' '
     int num, j, z;
     for (z=0;z<129;z++){
        for (j=4;j<7;j++){
           num= random(4) % 4;
           if (num==0){
             
                matrix [0][z]='#';
                matrix [1][z]=' ';}
           else if (num==1){
                  
                  matrix [0][z]=' ';
                  matrix [1][z]='#';}
           else {
               
               matrix [0][z]=' ';
               matrix [1][z]=' ';}
        }
     }
    
    
//Existem basicamente 3 tipos de novas colunas:     
//Tipo 1: Coluna com obstaculo em cima e nada em baixo.   
//Tipo 2: Coluna sem nada em cima e com obstavulo em baixo.
//Tipo 3: Coluna sem nada em cima e com obstaculo embaixo.
     

//Agora verificamos se ha espaço para o carro passar e assim limpamos 1 celula aleatoriamente se n houver:
     int num2,i;
       for (i=0;i<128;i++){
          for (j=4;j<6;j++){
             num2= random(4) % 3;
             for (z=2;z<128;z++){
                if (matrix[0][i]=='#' && matrix[1][i]=='#'){
                  if (num2==1){
                    matrix [0][z]=' ';
                    matrix [1][z]='#';}

                  else {
                      matrix [0][z]='#';
                      matrix [0][z]=' ';}}}
          }
       }

}       

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moverLeft(){
    //Se o objeto daquela celula for diferente de um carro, deve ser movido para a esquerda
    if(temColisao()){
        showLose();
    }else{
        for(int r = 0; r < 2; r++) {
            for(int c = 0; c < 128; c++) {
                if(matrix[r][c] != '>') {
                    matrix[r][c] = matrix[r][c + 1];
                }
            }
        }
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showStart(){
    game_control=1;
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

void moveCarroBaixo(){
    //deve checar se na celula celula da segund alinha tem carro, caso tenha
    if(matrix[1][0] == '#'){
      //deve encerrar a partirda, caso não tenha, deve mover o carro,
      showLose();
    }
    else if(matrix[1][0] == ' '){
      matrix[1][0] = '>';
      matrix[0][0] = ' ';
    }
    //caso o carro ja esteja na segunda linha, nao deve fazer nada
}

void moveCarroCima(){
    // mesma coisa de moveCarroBaixo só que para a linha de cima
    if(matrix[0][0] == '#'){
      showLose();
    }
    else if(matrix[1][0] == ' '){
      matrix[0][0] = '>';
      matrix[1][0] = ' ';
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPista(){
    lcd.clear();
    lcd.setCursor(0,0);

    for(int i = 0; i < 16; i++){
      lcd.print(matrix[0][i]);
    }

    lcd.setCursor(1,0);
    for(int i = 0; i < 16; i++){
      lcd.print(matrix[1][i]);
    }
      
    
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
  
 generateMatrix();
 int controle =1; 
 while(controle){ 
   showStart();
   delay(50);
   if(digitalRead(BUTTON1)==HIGH || digitalRead(BUTTON2)==HIGH)
    controle = 0;
 }  

 while(game_control){
  
  printPista();  
  
//resposta botoes
    
    if(digitalRead(BUTTON1)==HIGH){
      moveCarroCima();
      printPista();
    }
    if(digitalRead(BUTTON2)==HIGH){
      moveCarroBaixo();
      printPista();
    }
    delay(20);


//andar na pista
    if(matrix[0][1]==win && matrix[1][1]==win) {
        showWin();
        }else{
            moverLeft();
        }
 }
 
}

