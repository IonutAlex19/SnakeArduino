#include "LedControl.h"
#include <LiquidCrystal.h>
#define joyX A0
#define joyY A1

LedControl lc = LedControl(12, 11, 10, 1);

const int rs = 8, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int buttonPin = 6; //pin-ul pentru butonul care porneste jocul
const int lcdPin = 9; // pin-ul pentru luminozitatea LCD-ului


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int xMap, yMap;
int xValue, yValue;
int xDisplay, yDisplay;

int snakeHeadX = 0;
int snakeHeadY = 0;
int snakeBodyX[64] = {0,1,2}; /// pozitia initiala a sarpelui va fi in stanga sus
int snakeBodyY[64] = {0,0,0};
int snakeLength = 3;

bool fruitFound = false;

int fruitX = 0;
int fruitY = 0;

int gameScore = 0;
int gameSpeed = 250;
bool gameOn = false;

int nrButton = 0;
int buttonStatus = 0;
int gameLevel = 0;
int gameLevelCount = 0;
int snakeDirection = 0;

int getFruit()
{
  return random(8);
}

void setFruit() /// cu aceasta functie ma asigur ca fructul va fi asezat random pe matrice, evitand situatia in care este asezat chiar pe sarpe
{
  int ok = 0;
  int verifPoz = 0;
  int i;
  while(ok == 0)
  {
    fruitX = getFruit();
    fruitY = getFruit();
    verifPoz = 1;
    for(i = 0 ; i < snakeLength ; i++)
    {
      if(snakeBodyX[i] == fruitX && snakeBodyY[i] == fruitY)
        verifPoz = 0; 
    }
    if(verifPoz)
      ok = 1;
  }
  
}

void displaySnakeOn() /// functie pentru afisarea sarpelui
{
  for(int i = 0 ; i < snakeLength ; i++)
  {
    lc.setLed(0, snakeBodyX[i], snakeBodyY[i], true);
  }
}
void displaySnakeOff() /// functie pentru stergerea sarpelui
{
  for(int i = 0 ; i < snakeLength ; i++)
  {
    lc.setLed(0, snakeBodyX[i], snakeBodyY[i], false);
  }
}


void snakeMovement()
{
  
  int ok = 0;
  ///directie: 1 = dreapta
  ///          2 = stanga
  ///          3 = sus
  ///          4 = jos
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  xMap = map(xValue, 0, 1023, 0,15); /// mapez valorile generate de joystick astfel: 0-5 =  stanga, 5-10 = sta pe loc, 10-15 =  dreapta;
  yMap = map(yValue, 0, 1023, 0,15); /// mapez valorile generate de joystick astfel: 0-5 = jos, 5-10 sta pe loc, 10-15 sus;

  if(xMap > 10 && ok == 0) //mergem dreapta, folosesc ok-ul pentru a fi sigur ca execut doar o comanda la fiecare loop (evit diagonalizarea)
    {
      snakeHeadY ++;
      if(snakeHeadY > 7)
         snakeHeadY = 0;  /// merg dreapta, daca ajung si trec de margine, sarpele trece prin perete
      for(int i = snakeLength - 1 ; i>0 ; i--)
        {
            snakeBodyX[i] = snakeBodyX[i - 1]; /// la fiecare pas se modifica doar capul sarpelui, restul corpului va urma varful sarpelui
            snakeBodyY[i] = snakeBodyY[i - 1];
        }
      snakeBodyX[0] = snakeHeadX;
      snakeBodyY[0] = snakeHeadY;
      ok = 1;
      snakeDirection = 1;
    }
   /// analog pentru stanga, jos si sus
  if(xMap < 5 && ok == 0)
   {
     snakeHeadY--;
     if(snakeHeadY < 0)
        snakeHeadY = 7;
     for(int i = snakeLength - 1 ; i > 0 ; i--)
       {
          snakeBodyX[i] = snakeBodyX[i - 1];
          snakeBodyY[i] = snakeBodyY[i - 1];
       }
     snakeBodyX[0] = snakeHeadX;
     snakeBodyY[0] = snakeHeadY;
     ok = 1;
     snakeDirection = 2;
   }
  if(yMap > 10 && ok == 0)
    {
      snakeHeadX++;
      if(snakeHeadX > 7)
         snakeHeadX = 0;
      for(int i = snakeLength - 1 ; i > 0 ; i--)
        {
           snakeBodyX[i] = snakeBodyX[i - 1];
           snakeBodyY[i] = snakeBodyY[i - 1];
        }
      snakeBodyX[0] = snakeHeadX;
      snakeBodyY[0] = snakeHeadY;
      ok = 1;
      snakeDirection = 4;
     }
  if(yMap < 5 && ok == 0)
    {
      snakeHeadX--;
      if(snakeHeadX < 0)
         snakeHeadX = 7;
      for(int i = snakeLength - 1; i > 0 ; i--)
        {
           snakeBodyX[i] = snakeBodyX[i - 1];
           snakeBodyY[i] = snakeBodyY[i - 1];
        }
      snakeBodyX[0] = snakeHeadX;
      snakeBodyY[0] = snakeHeadY;
      ok = 1;
      snakeDirection = 3;
    }
  if(xMap  > 5 && xMap < 10 && yMap > 5 && yMap < 10) /// daca player-ul nu efectueaza nicio comanda, sarpele va pastra ultima traiectorie imprimata
    {
       if(snakeDirection == 1)
       {
             snakeHeadY ++;
             if(snakeHeadY > 7)
                snakeHeadY = 0;
             for(int i = snakeLength - 1 ; i > 0 ; i--)
               {
                 snakeBodyX[i] = snakeBodyX[i - 1];
                 snakeBodyY[i] = snakeBodyY[i - 1];
               }
             snakeBodyX[0] = snakeHeadX;
             snakeBodyY[0] = snakeHeadY;
             ok = 1;
             snakeDirection = 1;
       }
       else if(snakeDirection == 2)
        {
            
               snakeHeadY--;
               if(snakeHeadY < 0)
                  snakeHeadY = 7;
               for(int i = snakeLength - 1 ; i > 0 ; i--)
                 {
                    snakeBodyX[i] = snakeBodyX[i - 1];
                    snakeBodyY[i] = snakeBodyY[i - 1];
                 }
               snakeBodyX[0] = snakeHeadX;
               snakeBodyY[0] = snakeHeadY;
               ok = 1;
               snakeDirection = 2;
        }
       else if(snakeDirection == 3)
       {
           
                snakeHeadX--;
                if(snakeHeadX < 0)
                    snakeHeadX = 7;
                for(int i = snakeLength - 1; i > 0 ; i--)
                  {
                      snakeBodyX[i] = snakeBodyX[i - 1];
                      snakeBodyY[i] = snakeBodyY[i - 1];
                  }
               snakeBodyX[0] = snakeHeadX;
               snakeBodyY[0] = snakeHeadY;
               ok = 1;
               snakeDirection = 3;
       }
      else if(snakeDirection == 4)
      {
              snakeHeadX++;
              if(snakeHeadX > 7)
                 snakeHeadX = 0;
              for(int i = snakeLength - 1; i > 0; i--)
                {
                    snakeBodyX[i] = snakeBodyX[i - 1];
                    snakeBodyY[i] = snakeBodyY[i - 1];
                }
              snakeBodyX[0] = snakeHeadX;
              snakeBodyY[0] = snakeHeadY;
              ok = 1;
              snakeDirection = 4;
      }
    }
 
  displaySnakeOn();
  delay(gameSpeed);
  displaySnakeOff();
  
}


void checkFruit() /// functie in care verific daca sarpele gaseste un fruct. 
{
  fruitFound = false;
  if(snakeBodyX[0] == fruitX && snakeBodyY[0] == fruitY)
  {
    fruitFound = true;
    lc.setLed(0, fruitX, fruitY, false);
    setFruit();
    gameScore += 10;  /// maresc scorul daca am gasit
    gameSpeed -= 10; /// maresc viteza daca am gasit
    gameLevelCount+= 10;
    if(gameLevelCount % 50 == 0)
      gameLevel ++;
    displayScore();
  }
  lc.setLed(0, fruitX, fruitY, true); ///afisez noua pozitie a fructului
}

bool growSnake() /// functie cu care cresc dimensiunea sarpelui ( coada sarpelui va fi pozitia fructului)
{
  snakeLength++;
  snakeBodyX[snakeLength - 1] = fruitX; 
  snakeBodyY[snakeLength - 1] = fruitY;
}

bool snakeIsDying() /// verific daca sarpele isi musca coada
{
  int x = snakeBodyX[0];
  int y = snakeBodyY[0];
  int ok = 0;
  for(int i = 1; i < snakeLength; i++)
    if(x == snakeBodyX[i] && y == snakeBodyY[i])
        ok = 1;
  if(ok == 1)
  {
    gameLost();
    gameReset();
    return true;
  }
  return false;
      
}


void gameReset() /// functie activata la apasarea butonului, sarpele reprimeste pozitia si dimensiunea initiala
{
  gameOn = false;
  gameSpeed = 250;
  snakeHeadX = 0;
  snakeHeadY = 0;
  snakeBodyX[0] = 0;
  snakeBodyX[1] = 0;
  snakeBodyX[2] = 0;
  snakeBodyY[0] = 5;
  snakeBodyY[1] = 6;
  snakeBodyY[2] = 7;
  snakeLength = 3;
  gameScore = 0;
  gameLevel = 0;
  gameLevelCount = 0;
  
}

void displayScore() /// functie de afisare a scorului pe ecran
{
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("Scor");
  lcd.setCursor(11, 0);
  lcd.print(gameScore);
  lcd.setCursor(2, 1);
  lcd.print("Nivel");
  lcd.setCursor(11, 1);
  lcd.print(gameLevel); 
}

void gameWon() /// functie ce afiseaza mesajul pentru castigarea jocului
{
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("Ai castigat!");
  lcd.setCursor(1, 1);
  lcd.print("Scor final");
  lcd.setCursor(13, 1);
  lcd.print(gameScore);
}

void gameLost() /// functie ce afiseaza mesajul pentru pierderea jocului
{
  gameOn = false;
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("Ai pierdut");
  lcd.setCursor(0, 1);
  lcd.print("Scor final");
  lcd.setCursor(13, 1);
  lcd.print(gameScore);
  lc.clearDisplay(0);
}

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Jocul Snake");
  lcd.setCursor(1, 1);
  lcd.print("Press to start");
  pinMode(buttonPin, INPUT);
  analogWrite(lcdPin, 60);
  setFruit();
}
void loop()
{
  buttonStatus = digitalRead(buttonPin);

  if(buttonStatus == HIGH) /// jocul porneste cand apas pe buton
      gameOn = true;
    
  if(gameOn)
  {
    snakeMovement();
    checkFruit();
    if(fruitFound)
      growSnake();
    if(snakeIsDying())
      gameOn = false;
    if(gameScore == 640)
        gameWon();
  }
}
 
