void WatchyMoto::drawZ900RSCafe(bool light, float batt) {
    // draw background
    display.fillScreen(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0, 0, z900rscafe_img, 200, 200, light ? GxEPD_WHITE : GxEPD_BLACK);

    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextWrap(false);

    // Draw Time /////////////////////////////////////////////////////////////////////////////// Draw Time //
    display.setFont(&CFWilliamWallace_Regular26pt7b);
    display.setCursor(25, 199);    
    
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

}
