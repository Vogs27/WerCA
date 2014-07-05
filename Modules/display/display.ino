#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
 static const unsigned char PROGMEM logo33_glcd_bmp[] =
{
  	B00000000, B00000000, B00000001, B11100000, //                        ####    
	B00000000, B00000000, B00000011, B11000000, //                       ####     
	B00000000, B00000000, B00000011, B11000000, //                       ####     
	B00000000, B00000000, B00000011, B11000000, //                       ####     
	B00000000, B00000000, B00000111, B10000000, //                      ####      
	B00000000, B00000000, B00000111, B00000000, //                      ###       
	B00000000, B00000000, B00001111, B00000000, //                     ####       
	B00000000, B00000000, B00001111, B00000000, //                     ####       
	B00000011, B11111000, B00011110, B00000000, //       #######      ####        
	B00001111, B11111110, B00011110, B00000000, //     ###########    ####        
	B00011111, B11111110, B00111100, B00000000, //    ############   ####         
	B00111110, B00111100, B00111100, B00000000, //   #####   ####    ####         
	B01111100, B00000100, B00111100, B00000000, //  #####       #    ####         
	B01111000, B00000000, B01111000, B01000000, //  ####            ####    #     
	B11110000, B00000000, B01111000, B01000000, // ####             ####    #     
	B11110000, B00000000, B11110000, B11100000, // ####            ####    ###    
	B11110000, B00000000, B11110000, B11100000, // ####            ####    ###    
	B11110000, B00000001, B11100000, B11100000, // ####           ####     ###    
	B11110000, B00000001, B11100000, B11110000, // ####           ####     ####   
	B01111000, B00000011, B11000000, B11110000, //  ####         ####      ####   
	B01111100, B00000011, B11000000, B01111000, //  #####        ####       ####  
	B00111111, B10000011, B11000000, B01111000, //   #######     ####       ####  
	B00011111, B10000111, B10000000, B00111100, //    ######    ####         #### 
	B00001111, B10000111, B10000000, B00111100, //     #####    ####         #### 
	B00000001, B10001111, B00000000, B00011110, //        ##   ####           ####
	B00000000, B00001111, B00000000, B00000000, //             ####               
	B00000000, B00011110, B00000000, B00000000, //            ####                
	B00000000, B00011110, B00000000, B00000000, //            ####                
	B00000000, B00111100, B00000000, B00000000, //           ####                 
	B00000000, B00111100, B00000000, B00000000, //           ####                 
	B00000000, B00111100, B00000000, B00000000, //           ####                 
	B00000000, B01111000, B00000000, B00000000, //          ####                         
};
static const unsigned char PROGMEM phone78[] = 
{
	B11100000, // ###     
	B11110000, // ####
	B11000000, // ##
	B01100000, //  ##
	B00110000, //   ##
	B00011110, //    ####
	B00001111, //     ####


};

static const unsigned char PROGMEM mail710[] = 
{
	B11111111, B11111111,  //################
        B11000000, B00000011,  //##            ##
        B10110000, B00001101,  //# ##        ## #
        B10001100, B00110001,  //#   ##    ##   #
        B10000001, B10000001,  //#      ##      #
        B10000000, B00000001,  //#              #
        B11111111, B11111111,  //################
	};

static const unsigned char PROGMEM msg716[] = 
{
	B00001111, B11100000,	//     #######
	B00110000, B00011000,	//   ##       ## 
	B01000000, B00000100,	//  #           #
	B10000000, B00000010,	// #             #
	B10000000, B00000010,	// #             #
	B01000000, B00000110,	//  #           ##
	B00110000, B00011110,	//   ##       ####
	B00001111, B11100001,	//     #######    # 
	};
static const unsigned char PROGMEM other7[] = 
void setup()   {
  randomSeed(analogRead(0));
  display.begin();
  display.clearDisplay();
  display.setContrast(25);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(9, 0);
  display.println("Waiting  for");
  display.setCursor(12, 8);
  display.println("connection");
  display.drawBitmap(26, 20, logo33_glcd_bmp, 32 , 32, BLACK);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(12, 0);
  display.println("Connection");
  display.setCursor(11, 8);
  display.println("successful!");
  display.drawBitmap(26, 20, logo33_glcd_bmp, 32 , 32, BLACK);
  display.display();
  messages(random(19));
}


void loop() {
  
}

void messages(int numbermsg){
  display.drawBitmap(0,11, msg24, 7, 7, BLACK);
}
