#include "lcd_bsp.h"
#include "cst816.h"
#include "lcd_bl_pwm_bsp.h"
#include "lcd_config.h"
#include "ui.h"
#include "screen_manager.h"
#include "screen_main.h"
#include "rotary_encoder.h"
#include "brightness_control.h"
#include "haptic_feedback.h"
#include "ui_haptic_handler.h"
#include "i2c_scanner.h"
#include <USBHIDKeyboard.h>
#include "USB.h"

// Create global instance of USBHIDKeyboard
USBHIDKeyboard usbKeyboard;

void setup()
{
  Serial.begin(115200);
  delay(1000);  // Give serial time to initialize
  Serial.println("Starting device initialization...");
  
  // Initialize USB HID Keyboard first
  usbKeyboard.begin();
  USB.begin();
  Serial.println("USB HID Keyboard initialized");
  delay(500); // Small delay for USB initialization
  
  Touch_Init();  // This initializes I2C
  Serial.println("Touch controller initialized");
  
  // Scan I2C bus to see what devices are present
  I2CScanner::scan(I2C_NUM_0);
  
  lcd_lvgl_Init();
  lcd_bl_pwm_bsp_init(LCD_PWM_MODE_255);
  
  // Initialize haptic feedback after Touch_Init() to use the same I2C bus
  Serial.println("Initializing haptic feedback...");
  if (!HapticFeedback::init()) {
    Serial.println("WARNING: Haptic feedback initialization failed!");
  } else {
    Serial.println("Haptic feedback initialized successfully");
  }
  
  // Initialize UI after LVGL is ready
  if (get_lvgl_lock(-1)) 
  {   
    ui_init();
    
    // Initialize screen manager and setup gestures
    ScreenManager::getInstance()->init();
    ScreenMain::setupGestures();
    
    // Initialize brightness control
    BrightnessControl::init();
    
    // Initialize UI haptic handler
    UIHapticHandler::init();
    
    release_lvgl_lock();
  }
  
  // Initialize rotary encoder (after LVGL is set up)
  RotaryEncoder::init();
  
  Serial.println("Setup complete.");
}

void loop()
{
}