/*
  Project: ESP Hello World
  Project URL: https://github.com/hredan/ESP_HELLO_WORLD
  Description:
  This sketch will send the message "Hello World" as Morse code and using the LED_BUILTIN.
  It is an example of how to share esp projects with the ESPEasyFlasher_2.0 for different platforms.
  The release assets are build for the boards esp8266_d1_mini and esp32_d1_mini32.
  If you need this example for another esp board, you can fork this project and run the manual workflow with settings of your board.
*/
#include <Arduino.h>
#include <Dictionary.h>

#define LED LED_BUILTIN
// #define LED 4
// For my ESP32 mini board, the built-in LED is inverted
#ifdef ESP32
  #define INVERT_LED
#endif

Dictionary *dict = new Dictionary();
String text = "HELLO WORLD";

// https://en.wikipedia.org/wiki/Morse_code#Representation,_timing,_and_speeds
int dit = 80;
int dah = 3 * dit;
int symbol_space = dit;
int letter_space = 3 * dit;
int word_space = 7 * dit;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starts Hello World");
  Serial.printf("Built-in LED on GPIO PIN: %d\n", LED_BUILTIN);
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  dict->insert("H", "....");
  dict->insert("E", ".");
  dict->insert("L", ".-..");
  dict->insert("O", "---");
  dict->insert("W", ".--");
  dict->insert("R", ".-.");
  dict->insert("D", "-..");
  dict->insert(" ", " ");
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Start loop");
  delay(3000);
  for (int i = 0; i < text.length(); i++) {
    String letter = text.substring(i, i + 1);
    String morse = dict->search(letter);

    Serial.printf("Letter: %s -> %s\n", letter.c_str(), morse.c_str());
    for (int j = 0; j < morse.length(); j++) {
      char symbol = morse.charAt(j);
      if (symbol == '.') {
        ledOnForTimespan(dit);
      } else if (symbol == '-') {
        ledOnForTimespan(dah);
      } else if (symbol == ' ') {
        delay(word_space);
      }
    }
    delay(letter_space);
  }
  Serial.println("End loop");
}

void ledOnForTimespan(int timespan) {
  #ifdef INVERT_LED
      digitalWrite(LED, LOW);
  #else
      digitalWrite(LED, HIGH);
  #endif
  delay(timespan);
  #ifdef INVERT_LED
      digitalWrite(LED, HIGH);
  #else
      digitalWrite(LED, LOW);
  #endif
  delay(symbol_space);
}
