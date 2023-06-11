void WatchyMoto::drawMoto(bool light, float batt) {

    // ** SETUP **

    int16_t x1, y1, DecimalDay;
    uint16_t w, h;
    String textstringWatchy, textstringMoto, textstringMPH, textstringRPM, textstringX100;
    String textstringWday, textstringYYMMDD, textstringDecimalDay, textstringYMDlegend;
    String textstringbatt;

    // draw background
    display.fillScreen(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0,0, moto_img, 200, 200, light ? GxEPD_WHITE : GxEPD_BLACK);

    // draw WATCHYMOTO name
    textstringWatchy = "WATCHY";
    display.setFont(&High_Speed4pt7b);
    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.getTextBounds(textstringWatchy, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(197-w, 180);
    display.print(textstringWatchy);

    textstringMoto = "MOTO";
    display.setFont(&High_Speed4pt7b);
    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.getTextBounds(textstringMoto, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(192-w, 190);
    display.print(textstringMoto);

    // draw text elements
    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextWrap(false);

    textstringMPH = "MPH";
    display.setFont(&High_Speed8pt7b);
    display.getTextBounds(textstringMPH, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((200-w)/2, 44);
    display.print(textstringMPH);

    textstringRPM = "RPM";
    display.setFont(&High_Speed8pt7b);
    display.getTextBounds(textstringRPM, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((200-w)/2, 162);
    display.print(textstringRPM);

    textstringX100 = "X100";
    display.setFont(&High_Speed4pt7b);
    display.getTextBounds(textstringX100, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((200-w)/2, 171);
    display.print(textstringX100);

    // draw date  //////////////////////////////////////////////////////////////// draw date //

    display.setFont(&Engplot6pt7b);
    textstringWday = dayShortStr(currentTime.Wday);
    textstringWday.toUpperCase();
    display.getTextBounds(textstringWday, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(60, 80);
    display.print(textstringWday);    
    
    display.setFont(&Inversionz16pt7b);
    display.setTextColor(light ? GxEPD_WHITE : GxEPD_BLACK);
    textstringYYMMDD = tmYearToCalendar(currentTime.Year) - 2000; // offset from 1970, since year is stored in uint8_t
    textstringYYMMDD += currentTime.Month < 10 ? "0" + String(currentTime.Month) : currentTime.Month;
    textstringYYMMDD += currentTime.Day < 10 ? "0" + String(currentTime.Day) : currentTime.Day;
    display.getTextBounds(textstringYYMMDD, 0, 0, &x1, &y1, &w, &h);
    display.fillRect((199-w)/2, 105-h, w+2, h+2, light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setCursor((200-w)/2, 105); // date position
    display.print(textstringYYMMDD);

    // Draw decimal day counter with inverted color
    display.setFont(&Inversionz16pt7b);
    DecimalDay = floor(currentTime.Hour/2.4);
    //display.getTextBounds(textstringDecimalDay, 0, 0, &x1, &y1, &w, &h);
    //display.fillRect(160, 105-h, w+2, h+2, light ? GxEPD_WHITE : GxEPD_BLACK);
    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setCursor(161, 105);
    display.print(DecimalDay);

    display.setFont(&Engplot4pt7b);
    textstringYMDlegend = "Y Y M M D D";
    textstringWday.toUpperCase();
    display.getTextBounds(textstringYMDlegend, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((200-w)/2, 115);
    display.print(textstringYMDlegend);   
    



   // draw time /////////////////////////////////////////////////////////////////////////////////////////////// TIME    

    //minute pointer
    int currentMinute = currentTime.Minute;
    int minuteAngle = currentMinute *3 ; // 3deg/min*60min= 180deg
    double radMinute = minuteAngle * 3.141592653589793/180; // radian = degree * pi/180
    double mx1 = 100 - (cos(radMinute) * 65); 
    double my1 = 123 + (sin(radMinute) * 65);
    display.drawLine(99, 123, (int)mx1, (int)my1, !light ? GxEPD_WHITE : GxEPD_BLACK);
    display.drawLine(100, 123, (int)mx1, (int)my1, light ? GxEPD_WHITE : GxEPD_BLACK);
    display.drawLine(101, 123, (int)mx1, (int)my1, !light ? GxEPD_WHITE : GxEPD_BLACK);

    //hour pointer

    int displayHour;
    if(currentTime.Hour == 12){
      displayHour = 0;
    } else {
    displayHour = currentTime.Hour <=12 ? currentTime.Hour : currentTime.Hour -12;
    }
    
    double hourAngle = (displayHour * 15)+(currentMinute * .1875); // 15deg/hr*12hr = 180 deg
    double radHour = ((hourAngle + 90) * 71) / 4068.0;// phase shift 90
    double hx1 = 100 - (sin(radHour) * 65);
    double hy1 = 77 + (cos(radHour) * 65);
    display.drawLine(99, 77, (int)hx1, (int)hy1, !light ? GxEPD_WHITE : GxEPD_BLACK);  
    display.drawLine(100, 77, (int)hx1, (int)hy1, light ? GxEPD_WHITE : GxEPD_BLACK);  
    display.drawLine(101, 77, (int)hx1, (int)hy1, !light ? GxEPD_WHITE : GxEPD_BLACK);             
  
    //  Draw Battery icon 
//    display.drawBitmap(180, 1, motobatt, 19, 11, light ? GxEPD_BLACK : GxEPD_WHITE);

   float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        display.drawBitmap(179, 5, motobatt3, 17, 30, light ? GxEPD_BLACK : GxEPD_WHITE); 
    }
    else if(VBAT > 3.9 && VBAT <= 4.1){
        display.drawBitmap(187, 17, motobatt2, 9, 18, light ? GxEPD_BLACK : GxEPD_WHITE); 
    }
    else if(VBAT > 3.80 && VBAT <= 3.9){
        display.drawBitmap(191, 29, motobatt1, 5, 6, light ? GxEPD_BLACK : GxEPD_WHITE); 
    }

    //  Draw Temperature icon 
//    display.drawBitmap(3, 3, mototemp, 11, 19, light ? GxEPD_BLACK : GxEPD_WHITE);
//    display.drawBitmap(7, 2, mototemp3, 40, 27, light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(4, 17, mototemp2, 9, 18, light ? GxEPD_BLACK : GxEPD_WHITE);
//    display.drawBitmap(7, 15, mototemp1, 19, 14, light ? GxEPD_BLACK : GxEPD_WHITE);
}
