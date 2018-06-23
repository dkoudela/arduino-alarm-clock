// Hodiny reálného času DS1307

// připojení knihoven
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

// vytvoření instance DS1307 z knihovny RTClib
RTC_DS1307 DS1307;

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);       

// vytvoření pole seznamDni s názvy jednotlivých dní
char seznamDni[7][8] = {"nedele", "pondeli", "utery", "streda", "ctvrtek", "patek", "sobota"};

void setup () {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // kontrola připojeného obvodu reálného času
  if (! DS1307.begin()) {
    Serial.println("Hodiny nejsou pripojeny!");
    while (1);
  }
  // kontrolu spuštění obvodu reálného času
  if (! DS1307.isrunning()) {
    Serial.println("Hodiny nejsou spusteny! Spoustim nyni..");
  }
  // pro nastavení času v obvodu reálného času použijte jednorázově(!)
  // následující příkaz v pořadí rok, měsíc, den, hodina, minuta, vteřina
  // příklad: 26.4.2016 9:10:11
  //DS1307.adjust(DateTime(2018, 6, 23, 17, 52, 00));

  lcd.begin(16,2);      // set up the LCD's number of columns and rows: 
  lcd.setCursor(0,0);   // set the cursor to column 0, line 0 
}

void loop () {
  // načtení aktuálního času a data do proměnné datumCas
  DateTime datumCas = DS1307.now();

  consoleDateTime(datumCas);
  displayDateTime(datumCas);

  // pauza mezi výpisy
  delay(1000);
}

void consoleDateTime(DateTime datumCas) {
  // vypsání informací o aktuálním času a datu po sériové lince
  Serial.print("Aktualni cas ");
  Serial.print(datumCas.hour());
  Serial.print(':');
  Serial.print(datumCas.minute());
  Serial.print(':');
  Serial.print(datumCas.second());
  Serial.print(", ");
  Serial.print(seznamDni[datumCas.dayOfTheWeek()]);
  Serial.print(" ");
  Serial.print(datumCas.day());
  Serial.print('.');
  Serial.print(datumCas.month());
  Serial.print('.');
  Serial.print(datumCas.year());
  Serial.println();
}

void displayDateTime(DateTime dateTime) {
  lcd.clear();
  lcd.print(seznamDni[dateTime.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(dateTime.day());
  lcd.print('.');
  lcd.print(dateTime.month());
  lcd.print('.');
  lcd.print(dateTime.year());

  lcd.setCursor(4,1);   // set the cursor to column 0, line 1 
  lcd.print(dateTime.hour());
  lcd.print(':');
  lcd.print(dateTime.minute());
  lcd.print(':');
  lcd.print(dateTime.second());
}

