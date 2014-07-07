#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Software SPI:
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

static const unsigned char PROGMEM logo32[] = 
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
  B11100000, // ###
  B01110000, //  ###
  B00011110, //   #####
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
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B00011100, B00000000, //    ###
  B00011000, B00000000, //    ##
  B00010000, B00000000, //    #
};

static const unsigned char PROGMEM oth714[] = 
{
  B00000000, B00000000, //
  B00000000, B00000000, //
  B11100011, B10001110, //###   ###   ###
  B11100011, B10001110, //###   ###   ###
  B11100011, B10001110, //###   ###   ###
  B00000000, B00000000, //
  B00000000, B00000000, //
};

static const unsigned char PROGMEM incoming2216[] =
{
  B00011000, B00000000, //    ##           
  B00111100, B00000000, //   ####          
  B01111100, B00000000, //  #####          
  B01111110, B00000000, //  ######         
  B11111110, B00010000, // #######    #    
  B11111110, B00001000, // #######     #   
  B11111100, B00100100, // ######    #  #  
  B11111000, B10010010, // #####   #  #  # 
  B01111000, B01001001, //  ####    #  #  #
  B01111001, B00100101, //  ####  #  #  # #
  B01111000, B10010101, //  ####   #  # # #
  B01111100, B00010101, //  #####     # # #
  B00111100, B00000101, //   ####       # #
  B00111110, B00000000, //   #####         
  B00011111, B00000000, //    #####        
  B00001111, B10011000, //     #####  ##   
  B00001111, B11111100, //     ##########  
  B00000111, B11111110, //      ########## 
  B00000011, B11111111, //       ##########
  B00000001, B11111111, //        #########
  B00000000, B01111110, //          ###### 
  B00000000, B00011100, //            ###  
};

int lastRow = 0; 
int rowStartY [4] = {
  11, 19, 27, 35};
int sleepPin = 0;
int batteryMon = 0;
int VSP [8];
//0 = sms
//1 = calls
//2 = email
//3 = oth
//4 = incoming call
//5 = mode
//6 = cell battery
//7 = minutes
//8 = hours

void setup()   {
  pinMode(sleepPin, OUTPUT);
  digitalWrite(sleepPin, HIGH);
  delay(500);  //il tasto va premuto per almeno 500ms (mezzo secondo) per accendere il dispositivo
  digitalWrite(sleepPin, LOW);
  display.begin();
  display.clearDisplay();
  display.setContrast(25);
  display.setTextSize(1);              
  display.setTextColor(BLACK);
  display.setCursor(9, 0);
  display.println("Waiting  for");
  display.setCursor(12, 8);
  display.println("connection");
  display.drawBitmap(20, 26, logo32, 32, 32, BLACK);
  display.display();

  delay(2000);
  display.clearDisplay();
  display.setCursor(12, 0);
  display.println("Connection");
  display.setCursor(11, 8);
  display.println("successful!");
  display.display();
}


void loop() {
  display.clearDisplay();
  batteryMon = map(analogRead(0), 388, 490, 0, 4); //la lettura del partitore (vbat--10k--.--18k--GND) da valori da 388 (3,3v) a 490 (4,4v)
  display.drawRect(0, 2, 6, 3, BLACK);
  display.drawPixel(7, 3, BLACK);
  display.drawRect(11, 2, 6, 3, BLACK);
  display.drawPixel(18, 3, BLACK);
  display.fillRect(0, 2, VSP[6] +1, 3, BLACK);
  display.fillRect(11, 2, batteryMon +1, 3, BLACK);
  display.setCursor(59, 0);
  display.print(VSP[8]);
  display.print(".");
  display.print(VSP[7]);
  display.drawFastHLine(0, 9, 84, BLACK);
  display.display();
  switch(VSP[5]){
  case 1:
    display.drawBitmap(0, 11, incoming2216, 16, 22, BLACK);
    display.setCursor(0, 35);
    display.println("Incoming call");
    if(VSP[4]==0){
      display.print("Unknown");
    }
    else{
      display.print(VSP[4]);
    }
    break;
  case 2:
    digitalWrite(sleepPin, HIGH);
  default: //l'ordine di chiamata delle seguenti funioni determina la loro priorità di visualizzazione sul display
    messages(VSP[0]);
    calls(VSP[1]);
    mail(VSP[2]);
    oth(VSP[3]);
    lastRow = 0;
    break;
  }
  for(int i = 0; i <= 6; i++){
    VSP[i] = 0;
  }
  delay(100);
}

void messages(int numbmsg){
  if (numbmsg != 0){
    display.drawBitmap(0, rowStartY[lastRow], msg716, 16, 7, BLACK);
    display.setCursor(18, rowStartY[lastRow]);
    display.print(numbmsg);
    if(numbmsg==1){
      display.print(" message");
    }
    else {
      display.print(" messages");
    }
    display.display();
    lastRow = lastRow ++;
  }
}

void calls(int numbcall){
  if(numbcall != 0){
    display.drawBitmap(0, rowStartY[lastRow], phone78, 8, 7, BLACK);
    display.setCursor(8, rowStartY[lastRow]);
    display.print(numbcall);
    if(numbcall==1){
      display.print(" call");
    }
    else {
      display.print(" calls");
    }
    display.display();
    lastRow = lastRow ++;
  }
}

void mail(int numbmail){
  if(numbmail != 0){
    display.drawBitmap(0, rowStartY[lastRow], mail710, 14, 7, BLACK);
    display.setCursor(12, rowStartY[lastRow]);
    display.print(numbmail);
    display.print(" mail");
    display.display();
    lastRow = lastRow ++;
  }
}

void oth(int numboth){
  if(numboth != 0){
    display.drawBitmap(0, rowStartY[lastRow], oth714, 15, 7, BLACK);
    display.setCursor(17, rowStartY[lastRow]);
    display.print(numboth);
    if(numboth==1){
      display.print(" other");
    }
    else {
      display.print(" others");
    }
    display.display();
    lastRow = lastRow ++;
  }
}


