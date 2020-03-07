//display
#include <LiquidCrystal.h>

//rfid
#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

//display
const int rs = 2, en = 3, d4 = 7, d5 = 8, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//rfid
#define SS_PIN 10 // SDA an Pin 10 (bei MEGA anders)

#define RST_PIN 9 // RST an Pin 9 (bei MEGA anders)

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen
MFRC522::MIFARE_Key key;
char number[MFRC522::MF_KEY_SIZE];
//led
int red_light_pin= A1;
int green_light_pin = A2;
int blue_light_pin = A3;
boolean newKey;

void setup() {
  //display
  lcd.begin(16, 2);
  lcd.print("Bitte Karte");
  lcd.setCursor(0,1);
  lcd.print("Scannen");

  //rfid
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)

  SPI.begin(); // SPI-Verbindung aufbauen

  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers

  //led
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  number [MFRC522::MF_KEY_SIZE];
  for (int i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();

}

void loop() {
  delay(500);
  //RGB_color(249, 242, 32); // Red
  //rfid
  // Wenn keine Karte in Reichweite ist...

  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();

  unsigned long card;
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    Serial.print("Felix hat hier ganz viel Hilfe gebraucht!!");
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  }


  newKey = false;
  for(int i = 0;i<MFRC522::MF_KEY_SIZE;i++){
    if(number[i]!=key.keyByte[i]) newKey = true;
    number[i] = key.keyByte[i];
  }
  Serial.print("Neue Karte: "+newKey);

  // Wenn kein RFID-Sender ausgewählt wurde
  if ( ! mfrc522.PICC_ReadCardSerial()){
    
    //RGB_color(255, 255, 255);
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  }
  /*
  Serial.print("Die ID des RFID-TAGS lautet:"); // "Die ID des RFID-TAGS lautet:" wird auf den Serial Monitor geschrieben.
  
  for (byte i = 0; i < mfrc522.uid.size; i++){
  
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
    card = card + mfrc522.uid.uidByte[i];
    Serial.print(" card:");
    Serial.print(card);
    Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
  
  }
  
  Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.
*/
  
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
