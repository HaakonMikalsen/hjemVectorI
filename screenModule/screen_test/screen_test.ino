/*
 * GC9A01 ROUND LCD DISPLAY
 * 
 *
 * 
 * Pinout: 
 * 
 * CS > Logic level converter > D10
 * DC > Logic level converter > D9
 * RES > Logic level converter > D8
 * SDA > Logic level converter > D11
 * SCL > Logic level converter > D13
 * VCC > 3.3V
 * GND > GND
 * 
 * 240x 240
 * Middle (120,120)
 *
 *Usefull sources https://learn.adafruit.com/adafruit-gfx-graphics-library/overview , https://hjwwalters.com/gc9a01-arduino/ ,
 *
 */

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include <avr/pgmspace.h>

#define TFT_DC 9
#define TFT_CS 10



Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

bool hasDrawnBackgorund = false;

constexpr int notchAmountPerQuadrant = 3;
constexpr float toRadVal = M_PI / 180.0;
constexpr float radPerNotch = (360.0 / (notchAmountPerQuadrant * 4)) * toRadVal;


const byte compassRimWidth = 3;
const byte compassMainNotchLength = 20;
const byte compassSecondaryNotchLength = 10;



const uint16_t backgroundColor = GC9A01A_BLACK;
const uint16_t compassRimColor = GC9A01A_WHITE;
const uint16_t compassSecondaryNotchColor = GC9A01A_BLUE;
const uint16_t compassMainNotchColor = GC9A01A_RED;



const int xMiddle = 120;
const int yMiddle = 120;
const int screenRadius = 120;

int currentRotatedAngleDeg = 0;
int prevRotatedAngleDeg = 0;

void setup() {
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE);
  Serial.begin(9600);
}

void drawCompassBackground() {  //
  if (currentRotatedAngleDeg==prevRotatedAngleDeg) { // fixes exsesive redrawing
    return;
  }
  prevRotatedAngleDeg = currentRotatedAngleDeg;

  //Option 1 Not so smooth, but looks better when still
  // tft.fillCircle(xMiddle, yMiddle, screenRadius, compassRimColor);
  // tft.fillCircle(xMiddle, yMiddle, screenRadius - compassRimWidth, backgroundColor);


  //option 2 More smooth drawing. Fill in circle not perfect
  tft.fillCircle(xMiddle, yMiddle, screenRadius - compassRimWidth, backgroundColor);
  for (int i = 0; i <compassRimWidth;i++){
    tft.drawCircle(xMiddle,yMiddle,screenRadius-i,compassRimColor);
  }

  const float rotateRad = currentRotatedAngleDeg*toRadVal;
  for (int i = 0; i < notchAmountPerQuadrant * 4; i++) {
    uint16_t notchColor = compassSecondaryNotchColor;
    byte notchLenght = compassSecondaryNotchLength;
    if (i == 0) {
      notchLenght = compassMainNotchLength;
      notchColor = compassMainNotchColor;
    }
    if (i == notchAmountPerQuadrant) {
      notchLenght = compassMainNotchLength;
      notchColor = compassMainNotchColor;
    }
    if (i == (notchAmountPerQuadrant*2)) {
      notchLenght = compassMainNotchLength;
      notchColor = compassMainNotchColor;
    }
    if (i ==  (notchAmountPerQuadrant*3)) {
      notchLenght = compassMainNotchLength;
      notchColor = compassMainNotchColor;
    }

    const float rad = radPerNotch * i;
    const float xFactor = cos(rad+rotateRad);
    const float yFactor = sin(rad+rotateRad);
    const float startPointLenght = screenRadius - compassRimWidth - notchLenght;
    const float endPointLenght = screenRadius - compassRimWidth;
    tft.drawLine(xFactor * startPointLenght + xMiddle,
                 yFactor * startPointLenght + yMiddle,
                 xFactor * endPointLenght + xMiddle,
                 yFactor * endPointLenght + yMiddle,
                 notchColor);
  }
}

void loop() {
  drawCompassBackground();
  currentRotatedAngleDeg++;
  // delay(200);
  
}