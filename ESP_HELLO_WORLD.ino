/*
  ESP Hello World
  This sketch will send the message "Hello World" in Morse code using the LED_BUILTIN.
  https://en.wikipedia.org/wiki/Morse_code
*/
#include <Arduino.h>
#include <Dictionary.h>

Dictionary *dict = new Dictionary();
String text = "HELLO WORLD";

int dit = 150;
int dah = 3 * dit;
int symbol_space = dit;
int letter_space = 3 * dit;
int word_space = 7 * dit;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starts Hello World");
  Serial.printf("Built-in LED on GPIO PIN: %d\n", LED_BUILTIN);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

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
        digitalWrite(LED_BUILTIN, LOW);
        delay(dit);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(symbol_space);
      } else if (symbol == '-') {
        digitalWrite(LED_BUILTIN, LOW);
        delay(dah);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(symbol_space);
      } else if (symbol == ' ') {
        delay(word_space);
      }
    }
    delay(letter_space);
  }
  Serial.println("End loop");
}
