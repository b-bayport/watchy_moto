void WatchyMoto::drawTintin(bool light, float batt) {

    // ** SETUP **

    int16_t x1, y1;
    uint16_t w, h;
    String textstring, textstringday, textstringsteps;

    // draw background
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, tintin_img, 200, 200, GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);
    display.setTextWrap(false);

    // draw date  //////////////////////////////////////////////////////////////// draw date //

    display.setFont(&CFWilliamWallace_Regular10pt7b);

    textstringday = dayStr(currentTime.Wday);
    textstringday.toUpperCase();
    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(5, 175); // weekday position
    display.print(textstringday);
    
    display.setFont(&CFWilliamWallace_Regular16pt7b);
    
    textstring = currentTime.Day;
    textstring += "-";
    textstring += monthShortStr(currentTime.Month);
    textstring.toUpperCase();

    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(5, 200); // date position
    display.print(textstring);
    
    // draw time /////////////////////////////////////////////////////////////////////////////////////////////// TIME 
    
    display.setFont(&CFWilliamWallace_Regular26pt7b);
    display.setCursor(118, 45);
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
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////// END 7SEG

    // draw battery  ///////////////////////////////////////////////////////////////// draw battery //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //  Draw Battery from 7_SEG
    display.drawBitmap(05, 05, battery, 37, 21, GxEPD_BLACK);
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
        display.fillRect(10 + (batterySegments * BATTERY_SEGMENT_SPACING), 10, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, GxEPD_BLACK);
    } //  END OF Draw Battery from 7_SEG

}
