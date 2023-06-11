#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h>
#include "moto_img.h"
#include "moto00_img.h"
#include "tintin_img.h"
#include "ghostrider_img.h"
#include "twisties_img.h"
#include "z900rscafe_img.h"
#include "icons.h"
#include "font_cfwilliam/font_CFWilliamWallace.h"
#include "font_cfwilliam/CFWilliamWallace_Regular14pt7b.h"
#include "font_engplot/Engplot4pt7b.h"
#include "font_engplot/Engplot6pt7b.h"
#include "font_engplot/Engplot8pt7b.h"
#include "font_ghost/Ghost_Factory10pt7b.h"
#include "font_ghost/Ghost_Factory12pt7b.h"
#include "font_ghost/Ghost_Factory26pt7b.h"
#include "font_highspeed/High_Speed4pt7b.h"
#include "font_highspeed/High_Speed6pt7b.h"
#include "font_highspeed/High_Speed8pt7b.h"
#include "font_highspeed/High_Speed12pt7b.h"
#include "font_inversionz/Inversionz10pt7b.h"
#include "font_inversionz/Inversionz12pt7b.h"
#include "font_inversionz/Inversionz14pt7b.h"
#include "font_inversionz/Inversionz16pt7b.h"

RTC_DATA_ATTR bool light = true;
RTC_DATA_ATTR int face = 0;

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;

class WatchyMoto : public Watchy {
  using Watchy::Watchy;
  public:
    void drawWatchFace();
    void drawWrapText(String text);
    void drawBattery();
    void drawSteps();
    void drawMoto(bool light, float batt);
    void drawMoto00(bool light, float batt);
    void drawTintin(bool light, float batt);
    void drawGhostRider(bool light, float batt);
    void drawTwisties(bool light, float batt);
    void drawZ900RSCafe(bool light, float batt);
    virtual void handleButtonPress(); //Must also be virtual in Watchy.h
};

#include "moto.h"
#include "moto00.h"
#include "tintin.h"
#include "ghostrider.h"
#include "twisties.h"
#include "z900rscafe.h"

void WatchyMoto::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    //Up and Down switches 
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
    if (wakeupBit & UP_BTN_MASK) {
      face--;
      if (face < 0) {face = 5; } //update face=X based on face qty
        RTC.read(currentTime);
        showWatchFace(true);
        return;
    }
    if (wakeupBit & DOWN_BTN_MASK) {
      face++;
      if (face > 5) {face = 0;} // update face > X  based on face qty
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }
    if (wakeupBit & BACK_BTN_MASK) {
      light = !light;
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }
    if (wakeupBit & MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }
  } else {Watchy::handleButtonPress();}
  return;
}


void WatchyMoto::drawWatchFace() {
  // ** UPDATE **
  // resets step counter at midnight daily
  if (currentTime.Hour == 00 && currentTime.Minute == 00) {
    sensor.resetStepCounter();
  }

  // ** GET BATTERY **
  float batt = (getBatteryVoltage()-3.3);
  if (batt > 1) { batt = 1; } else if (batt < 0) { batt = 0; }

  // ** DRAW WATCHFACE **
  if (face == 0) {
    drawMoto(light, batt);
  }
  if (face == 1) {
    drawMoto00(light, batt);
  }
  if (face == 2) {
    drawTintin(light, batt);
  }
  if (face == 3) {
    drawGhostRider(light, batt);
  }
  if (face == 4) {
    drawTwisties(light, batt);
  }
  if (face ==5) {
    drawZ900RSCafe(light, batt);
  }
}




#endif