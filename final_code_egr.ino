#include <Adafruit_NeoPixel.h>
 
#define PIN        1  // Pin 
#define NUM_LEDS  16  //Number of led in total strips
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN);
 
uint8_t  mode   = 0,        // Current animation effect
         offset = 0;        // Position of spinner animation
uint32_t prevTime;          // Time of last animation mode switch

int rStep=0;//Variation of red
int gStep=0;//Variation of green
int bStep=0;//Variation of blue

void setup() {
  pixels.begin();
  pixels.setBrightness(60); // ~1/3 brightness
  prevTime = millis();      // Starting time
}
 
void calcColors() //Calculate components of the color
{
  //Random Color
  int red=random(255);//Component of red
  int green=random(255);//Component of green
  int blue=random(255);//Component of Blue
  rStep=red/(NUM_LEDS-1);
  gStep=green/(NUM_LEDS-1);
  bStep=blue/(NUM_LEDS-1);
}

void FadeIn()
{
 
  uint16_t i;//Initializing counter for pixel number 0-16
  uint16_t j;//Initializing counter for brightness
  for (j=50; j<255; j++)
  {
    for (i=0; i<NUM_LEDS; i++)
    {
      pixels.setPixelColor(i,j,0,0,0);//The rgbw color has been set to red
      }
  }
  pixels.show();
  delay(100);
}
 
void FadeOut()
{
  uint16_t i;//Re-initializing counter i for fade out effect
  uint16_t j;//Re-initializing counter j for fade out effect
  for (j=255; j>50; j--)
  {
    for (i=0; i<NUM_LEDS; i++)
    {
    pixels.setPixelColor(i,j,0,0,0);//The rgbw color has been set to red
    }
  }
  pixels.show();
  delay(100);
}

void loop() {
  uint8_t  purple[]= {1,3,5,7,9,11,13,15};
  uint8_t  orange[] = {0,2,4,6,8,10,12,14};
  uint32_t t;

  switch(mode){
    
    case 0: // Sanya
    calcColors();//Calculate colors before going to loop;
    pixels.clear();   // Set all pixels to 'off' state
    uint8_t  i;
    uint32_t t;
    for(i=0; i<NUM_LEDS; i++) {    // For each LED...
    int pos=(i+offset)%NUM_LEDS; 
    pixels.setPixelColor(pos, rStep*i, gStep*i, bStep*i);  //Increase component of color step by step
    }
    pixels.show();                 // Refresh LED states
    delay(50);                     // 50 millisecond delay
    offset++;                      // Shift animation by 1 pixel on next frame
    if (offset >= 12){
        offset = 0;
      }
    break;

    case 1: // Sandy
    FadeIn();
    FadeOut();
    delay(500);
    break;

    case 2: // Sanaye
     for(int i =0; i<16;i++) {
     
      pixels.setPixelColor(i, 0xEB4034); // Set it to current color
   
      }
     pixels.show();
      delay(1000); // 10 millisecond delay
      pixels.clear ();
      pixels.show();
      delay(1000);
      break;

     case 3: // Nolan
     for (int count = 0; count < 8; count++){ //Set even LEDs to off
      pixels.setPixelColor(orange[count], 0);
    }

    for (int count = 0; count < 8 ; count++){ //Set odd LEDs to purple

         pixels.setPixelColor(purple[count], 0x6A0DAD);

    }

    pixels.show();
    delay(500);
    
     for (int count = 0; count < 8 ; count++){ //Set odd LEDs to off

         pixels.setPixelColor(purple[count], 0);

    }

    for (int count = 0; count < 8; count++){ //Set even LEDs to orange

      pixels.setPixelColor(orange[count], 0xFF8E00);

    }

    pixels.show();
    delay(500);   
    } // End of switch case

    t = millis();                    // Current time in milliseconds
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Advance to next animation mode

    if(mode > 3) {                 // End of modes?
      mode = 0;                    // Start over from beginning
    }

    pixels.clear();                // Set all pixels to 'off' state
    prevTime = t;                  // Record the time of the last mode change

  } // End of an 8 second cycle
                
} // End of loop()
