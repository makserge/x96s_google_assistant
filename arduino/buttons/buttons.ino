#include <HID-Project.h>
#include <HID-Settings.h>
#include "OneButton.h"
#include "SimpleTimer.h"
#include <avr/wdt.h>

#define SLEEP_PIN 2
#define BACK_PIN 3
#define VOL_DOWN_PIN 4
#define VOL_UP_PIN 5
#define RIGHT_PIN 6
#define LEFT_PIN 7
#define DOWN_PIN 8
#define UP_PIN 9
#define HOME_PIN 10
#define SELECT_PIN 21

OneButton sleepButton(SLEEP_PIN, false, true);
OneButton backButton(BACK_PIN, false, true);
OneButton volDownButton(VOL_DOWN_PIN, false, true);
OneButton volUpButton(VOL_UP_PIN, false, true);
OneButton rightButton(RIGHT_PIN, true, false);
OneButton leftButton(LEFT_PIN, true, false);
OneButton downButton(DOWN_PIN, true, false);
OneButton upButton(UP_PIN, true, false);
OneButton homeButton(HOME_PIN, false, true);
OneButton selectButton(SELECT_PIN, true, false);

SimpleTimer timer;
const uint16_t VOLUME_INTERVAL = 300;
uint8_t volumeTimerId = 0;
uint8_t volDirection = 0;

void setVolume() {
  Consumer.write(volDirection ? MEDIA_VOLUME_UP : MEDIA_VOLUME_DOWN);
}

void clickVolDownButton() {
  Consumer.write(MEDIA_VOLUME_DOWN);
}

void pressStartVolDownButton() {
  volDirection = 0;
  timer.enable(volumeTimerId);
}

void pressStopVolDownButton() {
  timer.disable(volumeTimerId);
}

void clickVolUpButton() {
  Consumer.write(MEDIA_VOLUME_UP);
}

void pressStartVolUpButton() {
  volDirection = 1;
  timer.enable(volumeTimerId);
}

void pressStopVolUpButton() {
  timer.disable(volumeTimerId);
}

void clickBackButton() {
  Consumer.write(HID_CONSUMER_MENU_ESCAPE);
}

void clickSleepButton() {
  Consumer.write(HID_CONSUMER_SLEEP);
}

void clickRightButton() {
  Consumer.write(HID_CONSUMER_MENU_RIGHT);
}

void clickLeftButton() {
  Consumer.write(HID_CONSUMER_MENU_LEFT);
}

void clickDownButton() {
  Consumer.write(HID_CONSUMER_MENU_DOWN);
}

void clickUpButton() {
  Consumer.write(HID_CONSUMER_MENU_UP);
}

void clickHomeButton() {
  Consumer.write(HID_CONSUMER_AC_HOME);
}

void clickSelectButton() {
  Consumer.write(HID_CONSUMER_MENU_PICK);
}

void setup() {
  Consumer.begin();

  sleepButton.attachClick(clickSleepButton);
  backButton.attachClick(clickBackButton);
  volDownButton.attachClick(clickVolDownButton);
  volDownButton.attachLongPressStart(pressStartVolDownButton);
  volDownButton.attachLongPressStop(pressStopVolDownButton);
  volUpButton.attachClick(clickVolUpButton);
  volUpButton.attachLongPressStart(pressStartVolUpButton);
  volUpButton.attachLongPressStop(pressStopVolUpButton);
  rightButton.attachClick(clickRightButton);
  leftButton.attachClick(clickLeftButton);
  downButton.attachClick(clickDownButton);
  upButton.attachClick(clickUpButton);
  homeButton.attachClick(clickHomeButton);
  selectButton.attachClick(clickSelectButton);

  volumeTimerId = timer.setInterval(VOLUME_INTERVAL, setVolume);
  timer.disable(volumeTimerId);
  
  wdt_enable(WDTO_1S);
}

void loop() {
  sleepButton.tick();
  backButton.tick();
  volDownButton.tick();
  volUpButton.tick();
  rightButton.tick();
  leftButton.tick();
  downButton.tick();
  upButton.tick();
  homeButton.tick();
  selectButton.tick();

  timer.run();
  
  wdt_reset();
}
