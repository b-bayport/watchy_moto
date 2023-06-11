void WatchyMoto::drawGhostRider(bool light, float batt) {

    // ** SETUP **

    int16_t x1, y1;
    uint16_t w, h;
    String textstring, textstringday, textstringtime, textstringsteps, textstringbatt ;

    // draw background
    display.fillScreen(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0,0, ghostrider_img, 200, 200, light ? GxEPD_WHITE : GxEPD_BLACK);

    

    display.setTextColor(!light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextWrap(false);

    // draw date  //////////////////////////////////////////////////////////////// draw date //

    display.setFont(&Ghost_Factory12pt7b);

    textstringday = dayStr(currentTime.Wday);
    textstringday.toUpperCase();
    display.getTextBounds(textstringday, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(199-w, 52); // weekday position
    display.print(textstringday);
    
    display.setFont(&Ghost_Factory12pt7b);
    
    textstring = currentTime.Day;
    textstring += "-";
    textstring += monthShortStr(currentTime.Month);
    textstring.toUpperCase();

    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(199-w, 70); // date position
    display.print(textstring);
    
    // draw time /////////////////////////////////////////////////////////////////////////////////////////////// TIME 
    
    display.setFont(&Ghost_Factory26pt7b);
    display.setCursor(32, 36);
    int displayHour;
    if(HOUR_12_24==12){
      displayHour = ((currentTime.Hour+11)%12)+1;
    } else {
      displayHour = currentTime.Hour;
    }
    if(displayHour < 10){
        display.print("0");
    }
    display.print(displayHour);
    display.print(":");
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.println(currentTime.Minute);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////// END 7SEG

    // draw battery  ///////////////////////////////////////////////////////////////// draw battery //
 
    display.drawBitmap(176, 02, batteryghost, 21, 12, !light ? GxEPD_BLACK : GxEPD_WHITE);
    display.fillRect(178, 03, 18, 10, !light ? GxEPD_WHITE : GxEPD_BLACK);//clear battery segments
    display.setFont(&Ghost_Factory10pt7b);
    //int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        textstringbatt = "IIII"; 
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        textstringbatt = "III"; 
    }
    else if(VBAT > 3.80 && VBAT <= 3.95){
        textstringbatt = "I"; 
    }
    else if(VBAT <= 3.80){
        textstringbatt = "  X  ";
    }
    display.setCursor(179,13);
    display.print(textstringbatt);

/*
    ////////////// Draw Steps
    // reset step counter at midnight
        
    if (currentTime.Hour == 0 && currentTime.Minute == 0){
      sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    //display.drawBitmap(180, 177, steps, 19, 23, light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setFont(&Tintin_Dialogue8pt7b);
    display.setCursor(160, 184);
    display.print("Steps");
    display.drawFastHLine(159,184, 40, light ? GxEPD_BLACK : GxEPD_WHITE);
    
    display.setFont(&Tintin_Dialogue8pt7b);
    textstringsteps = String(stepCount);
    display.getTextBounds(textstringsteps, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(198 - w, 199);
    display.println(textstringsteps);
    */
}
