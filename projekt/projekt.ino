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

//led
int red_light_pin= A1;
int green_light_pin = A2;
int blue_light_pin = A3;

void setup() {
  //display
  lcd.begin(16, 2);
  lcd.print("Hallo Anton du");
  lcd.setCursor(0,1);
  lcd.print("hast heute M SA");

  //rfid
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)

  SPI.begin(); // SPI-Verbindung aufbauen

  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers

  //led
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

}

void loop() {
  RGB_color(255, 0, 0); // Red
  //rfid
  if ( ! mfrc522.PICC_IsNewCardPresent()) // Wenn keine Karte in Reichweite ist...
  
  {
  
  return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  
  }
    
  if ( ! mfrc522.PICC_ReadCardSerial()) // Wenn kein RFID-Sender ausgewählt wurde
  
  {
  
  return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  }
  
  Serial.print("Die ID des RFID-TAGS lautet:"); // "Die ID des RFID-TAGS lautet:" wird auf den Serial Monitor geschrieben.
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  
  {
  
  Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
  
  Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
  
  }
  
  
  Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.

}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
