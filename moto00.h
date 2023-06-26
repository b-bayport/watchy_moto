void WatchyMoto::drawMoto00(bool light, float batt) {


    // ** SETUP **

    int16_t x1, y1;
    uint16_t w, h;
    String textstring, textstringday, texthold;

    

    // draw background
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0,0, moto00_img, 200, 200, GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);
    display.setTextWrap(false);

    // draw date  //////////////////////////////////////////////////////////////// draw date //

    display.setFont(&CFWilliamWallace_Regular14pt7b);

//    textstringday = dayStr(currentTime.Wday);
//    textstringday.toUpperCase();
//    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
//    display.setCursor(3, h + 10); // weekday position
//    display.print(textstringday);
    
    display.setFont(&CFWilliamWallace_Regular10pt7b);
    
    textstring = currentTime.Day;
    textstring += "-";
    textstring += monthShortStr(currentTime.Month);
    textstring.toUpperCase();

    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(199 - w, 197); // date position
    display.print(textstring);
    
    // draw time //////////////////////////////////////////////////////////////// draw time //

    display.setFont(&CFWilliamWallace_Regular30pt7b);
    display.setCursor(6, 197);
    int displayHour;
    if(currentTime.Hour == 0){
      displayHour = 12;
    } else {
      displayHour = currentTime.Hour <=12 ? currentTime.Hour : currentTime.Hour - 12;
    }
    display.print(displayHour);
   
    display.print(":");
    
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.println(currentTime.Minute);
    

    // draw battery  ///////////////////////////////////////////////////////////////// draw battery //
    display.drawBitmap(5, 5, battery, 37, 21, GxEPD_BLACK);
    display.fillRect(10, 10, 27, BATTERY_SEGMENT_HEIGHT, GxEPD_WHITE);//clear battery segments
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        batteryLevel = 3;
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        batteryLevel = 2;
    }
    else if(VBAT > 3.80 && VBAT <= 3.95){
        batteryLevel = 1;
    }
    else if(VBAT <= 3.80){
        batteryLevel = 0;
    }

    for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
        display.fillRect(10 + (batterySegments * BATTERY_SEGMENT_SPACING), 10,BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, GxEPD_BLACK);
    } 

}
