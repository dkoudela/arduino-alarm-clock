// Hodiny reálného času DS1307

// připojení knihoven
#include <Wire.h>
#include "RTClib.h"

// vytvoření instance DS1307 z knihovny RTClib
RTC_DS1307 DS1307;

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
  DS1307.adjust(DateTime(2018, 6, 22, 14, 13, 00));
}

void loop () {
  // načtení aktuálního času a data do proměnné datumCas
  DateTime datumCas = DS1307.now();
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
  // pauza mezi výpisy
  delay(1000);
}
