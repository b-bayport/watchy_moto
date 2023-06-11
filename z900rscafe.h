void WatchyMoto::drawZ900RSCafe(bool light, float batt) {
    // draw background
    display.fillScreen(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0, 0, z900rscafe_img, 200, 200, light ? GxEPD_WHITE : GxEPD_BLACK);

    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextWrap(false);

}