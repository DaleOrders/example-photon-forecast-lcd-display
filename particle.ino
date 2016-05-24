#include "SparkJson/SparkJson.h"
#include "LiquidCrystal_I2C_Spark/LiquidCrystal_I2C_Spark.h"

LiquidCrystal_I2C *lcd;

int setText(String arg) {
    
    Serial.println(arg);
    
    // The text to write to the display is sent as a JSON object with
    // two properties for each line.
    // { L1: "line one text", L2: "line two text" }
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& text = jsonBuffer.parseObject((char*)arg.c_str());
    
    // Clear the screen.
    lcd->clear();
    
    // Move the cursor to the start of the first line and print the text.
    lcd->setCursor(0,0);
    lcd->print(text["L1"].asString());
    
    // Move the cursor to the start of the second line and print the text.
    lcd->setCursor(0,1);
    lcd->print(text["L2"].asString());
    
    return 0;
}

void setup()
{
    Serial.begin(9600);
    
    // The address is typically 0x27.
    lcd = new LiquidCrystal_I2C(0x27 /*address*/, 16 /*columns*/, 2/*rows*/);
    lcd->init();
    lcd->backlight();
    lcd->clear();
    
    // Register a setText function that can be invoked by Losant.
    Particle.function("setText", setText);
}
 
void loop()
{
    
}
