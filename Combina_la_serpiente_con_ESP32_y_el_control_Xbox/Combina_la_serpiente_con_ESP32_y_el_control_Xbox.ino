#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS 5
#define TFT_DC 2
#define TFT_RST 4

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

#define ANCHO 240
#define ALTO 320
#define TAM 10

int snakeX[100], snakeY[100];
int largo = 5;
int dirX = 1, dirY = 0;
int foodX, foodY;

void nuevaComida() {
  foodX = random(0, ANCHO/TAM) * TAM;
  foodY = random(0, ALTO/TAM) * TAM;
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  for (int i=0;i<largo;i++){
    snakeX[i]=100-i*TAM;
    snakeY[i]=100;
  }
  nuevaComida();
}

void leerSerial() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c=='U' && dirY==0){dirX=0;dirY=-1;}
    if (c=='D' && dirY==0){dirX=0;dirY=1;}
    if (c=='L' && dirX==0){dirX=-1;dirY=0;}
    if (c=='R' && dirX==0){dirX=1;dirY=0;}
  }
}

void loop() {
  leerSerial();

  for(int i=largo-1;i>0;i--){
    snakeX[i]=snakeX[i-1];
    snakeY[i]=snakeY[i-1];
  }

  snakeX[0]+=dirX*TAM;
  snakeY[0]+=dirY*TAM;

  if(snakeX[0]<0||snakeX[0]>=ANCHO||snakeY[0]<0||snakeY[0]>=ALTO){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(40,150);
    tft.setTextSize(3);
    tft.print("GAME OVER");
    while(1);
  }

  if(snakeX[0]==foodX&&snakeY[0]==foodY){
    largo++;
    nuevaComida();
  }

  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(foodX,foodY,TAM,TAM,ILI9341_RED);

  for(int i=0;i<largo;i++)
    tft.fillRect(snakeX[i],snakeY[i],TAM,TAM,ILI9341_GREEN);

  delay(120);
}
