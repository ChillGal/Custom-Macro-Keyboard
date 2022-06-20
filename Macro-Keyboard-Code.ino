#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HID-Project.h>
#include <SPI.h>
#include <Wire.h>

/*
 * ARDUINO PRO MICRO PINOUT
 * PIN 1  - Button - Top Row - F13
 * PIN 0  - Button - Top Row - F14
 * PIN 2  - I2C - SDA - Display
 * PIN 3  - I2C - SCL - Display
 * PIN 4  - Button - Top Row - F15
 * PIN 5  - Button - Top Row - F16
 * PIN 6  - Button - Top Row - F17
 * PIN 7  - Rotary Encoder - CLK
 * PIN 8  - Rotary Encoder - DT
 * PIN 9  - Rotary Encoder - SW
 * PIN 10 - Button - Bottom Row - F
 * PIN 16 - Button - Bottom Row - F
 * PIN 14 - Button - Bottom Row - F
 * PIN 15 - Button - Bottom Row - F
 * PIN 18 - Button - Bottom Row - F
*/

/*
    KEY_F13 - 0x68
    KEY_F14 - 0x69
    KEY_F15 - 0x6A
    KEY_F16 - 0x6B
    KEY_F17 - 0x6C
    KEY_F18 - 0x6D
    KEY_F19 - 0x6E
    KEY_F20 - 0x6F
    KEY_F21 - 0x70
    KEY_F22 - 0x71
    KEY_F23 - 0x72
    KEY_F24 - 0x73
*/

//Definitions
  //Keyboard layout
#define HID_CUSTOM_LAYOUT
#define LAYOUT_UNITED_KINGDOM
  //Display
#define SCREEN_WIDTH 128 // Screen width
#define SCREEN_HEIGHT 32 //Screen height
#define LOGO_WIDTH 128 // Logo width
#define LOGO_HEIGHT 32 //Logo height
#define OLED_RESET 4 // OLED reset pin
#define SCREEN_ADDRESS 0x3C // I2C address
  //Encoder                                                                  
#define ENC_CLK 7 //Encoder clock
#define ENC_DT 8 //Encoder data
#define ENC_SW 9 // Encoder switch
  //Buttons
#define BTN_F13 1 //F13 @ Pin 1
#define BTN_F14 0 //F14 @ Pin 0
#define BTN_F15 4 //F15 @ Pin 4
#define BTN_F16 5 //F16 @ Pin 5
#define BTN_F17 6 //F17 @ Pin 6
#define BTN_F18 18 //F18 @ Pin 18
#define BTN_F19 15 //F19 @ Pin 15
#define BTN_F20 14 //F20 @ Pin 14
#define BTN_F21 16 //F21 @ Pin 16
#define BTN_F22 10 //F22 @ Pin 10
  //Keys
#define K_F13 KEY_F13
#define K_F14 KEY_F14
#define K_F15 KEY_F15
#define K_F16 KEY_F16
#define K_F17 KEY_F17
#define K_F18 KEY_F18
#define K_F19 KEY_F19
#define K_F20 KEY_F20
#define K_F21 KEY_F21
#define K_F22 KEY_F22

//Bitmap
static const unsigned char PROGMEM Startup_Logo_BMP[] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5,
0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15,
0xAB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5,
0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55,
0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55,
0xAA, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55,
0xAA, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x55,
0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55,
0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x55,
0xAA, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x55,
0xAA, 0xAB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55,
0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55,
0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55,
0xAA, 0xAB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55,
0xAA, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x55,
0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x55,
0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55,
0xAA, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x55,
0xAA, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55,
0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55,
0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55,
0xAB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5,
0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15,
0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5,
0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//Variables
int ENC_PrevState; //Previous encoder state
int ENC_CurrentState; //Current encoder state
int ENC_PBState; //Previous encoder button state
int ENC_CBState; //Current encoder button state
int ENC_Toggle; //Toggle switch to avoid spamming on button hold
int ENC_Mute; //Mute option to disable volume control if muted
unsigned long currentTime = 0; //Current time
unsigned long clearDisplayTime = 0; //Time until display needs clearing
static uint8_t prevNextCode = 0; //Encoder debouncing
static int8_t val; //Encoder value
static uint16_t store=0; //Encoder debouncing

//Display initialisation
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Button class
class button {
  public:
  const KeyboardKeycode key; //HID-Project uses a "KeyboardKeycode" with Enum
  const uint8_t pin;
  button(KeyboardKeycode k, uint8_t p) : key(k), pin(p){}

  //Debouncing and key press handling
  void press(boolean state){ 
    if(state == pressed || (millis() - lastPressed  <= debounceTime)){
      return;
    }
    lastPressed = millis();
    state ? Keyboard.press(key) : Keyboard.release(key);    
    pressed = state;
    if(state == pressed) {
      display.clearDisplay();
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.cp437(true);  
      switch(key){
        case 104:
          display.print("F13");
          break;
        case 105:
          display.print("F14");
          break;
        case 106:
          display.print("F15");
          break;
        case 107:
          display.print("F16");
          break;
        case 108:
          display.print("F17");
          break;
        case 109:
          display.print("F18");
          break;
        case 110:
          display.print("F19");
          break;
        case 111:
          display.print("F20");
          break;
        case 112:
          display.print("F21");
          break;
        case 113:
          display.print("F22");
          break;
      }
      display.display();
      clearDisplayTime = millis();
    }
  }
  //Read digital pin and get inverse
  void update(){
    press(!digitalRead(pin)); 
  }
  private:
  const unsigned long debounceTime = 30;
  unsigned long lastPressed = 0;
  boolean pressed = 0;
};

//Button array
button buttons[] = {
  {K_F13, BTN_F13},
  {K_F14, BTN_F14},
  {K_F15, BTN_F15},
  {K_F16, BTN_F16},
  {K_F17, BTN_F17},
  {K_F18, BTN_F18},
  {K_F19, BTN_F19},
  {K_F20, BTN_F20},
  {K_F21, BTN_F21},
  {K_F22, BTN_F22}
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button); //Number of buttons

void setup() {

  //Initialisation
  Serial.begin(9600);
  Consumer.begin();
	Keyboard.begin();

  //Pins
    //Buttons
    for(int i = 0; i < NumButtons; i++){
      pinMode(buttons[i].pin, INPUT_PULLUP);
    }
    //Rotary Encoder
  pinMode(ENC_CLK,INPUT_PULLUP);
	pinMode(ENC_DT,INPUT_PULLUP);
	pinMode(ENC_SW,INPUT_PULLUP);
    //Turn LEDs off
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
    
  //Check for display
  CheckDisplayExists();

  //Get initial state of encoder
  ENC_PrevState = digitalRead(ENC_CLK);
  ENC_PBState = digitalRead(ENC_SW);
  
  //Display initial image
  StartupBMP();
  delay(2000);
  ClearDisplay();
}

void loop() {
//Get current time
currentTime = millis();
//Check how long since displayed, if over 5 seconds, then clear the display.
if(clearDisplayTime == (currentTime - 5000)) {
  ClearDisplay();
  clearDisplayTime = 0;
}
//Check button presses
  for(int i = 0; i < NumButtons; i++){
    buttons[i].update();
  }
//Rotary Encoder 
 if( val=read_rotary() ) {
    if ( prevNextCode==0x0b) {
      RotaryEncoderLeft();
      clearDisplayTime = millis();
    }
    if ( prevNextCode==0x07) {
      RotaryEncoderRight();
      clearDisplayTime = millis();
    }
  }

//Check encoder button state
  if((digitalRead(ENC_SW) != ENC_PBState) && (ENC_Toggle != 1)) {
    RotaryEncoderPress();
    clearDisplayTime = millis();
    ENC_Toggle = 1;
    }

  if((digitalRead(ENC_SW) == ENC_PBState) && (ENC_Toggle == 1)) {
    ENC_Toggle = 0;
    }
}

//Check for display
void CheckDisplayExists() {
  //Checks if display exists, if not continues checking until display found
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    delay(5000); //5 Seconds between checks
    CheckDisplayExists();
  }
}
//Startup bitmap
void StartupBMP() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.drawBitmap(
    (display.width() - LOGO_WIDTH) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
     Startup_Logo_BMP, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}
//Clear display
void ClearDisplay() {
  display.clearDisplay();
  display.display();
}
//Rotary encoder
void RotaryEncoderRight() {
  //Volume UP
  Consumer.write(MEDIA_VOLUME_UP);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.cp437(true);  
  display.print(F("VOL UP"));
  display.display();
}  
void RotaryEncoderLeft() {
  //Volume DOWN
  Consumer.write(MEDIA_VOLUME_DOWN);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.cp437(true);  
  display.print(F("VOL DOWN"));
  display.display();
}
void RotaryEncoderPress() {
  //Volume MUTE
  Consumer.write(MEDIA_VOL_MUTE);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.cp437(true);  
  display.print("MUTE");
  display.display();
}

//Read noisy input and debounce
int8_t read_rotary() {
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode <<= 2;
  if (digitalRead(ENC_DT)) prevNextCode |= 0x02;
  if (digitalRead(ENC_CLK)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   return 0;
}
