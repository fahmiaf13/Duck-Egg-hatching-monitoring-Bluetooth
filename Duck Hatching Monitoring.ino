#include <DHT.h>
#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

#define DHTPIN 7
#define DHTTYPE DHT22   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
const int relaylampu = 9;
const int relayfan = 10;
const int buzzer = 11;


void setup() {
  Serial.begin(9600);
  pinMode(relaylampu, OUTPUT);
  pinMode(relayfan, OUTPUT);
  pinMode(buzzer, OUTPUT); 
  dht.begin();
    // inisialisasi LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
 
void loop() {
  float h = dht.readHumidity();
  //Pembacaan untuk data kelembapan
  float t = dht.readTemperature();
  //Pembacaan dalam format celcius (c)
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Suhu Tidak Terbaca");
    return;
  }
  Serial.print(t);
  Serial.print("°C-");
  Serial.print(h);
  Serial.print(" %-");
  
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Hum  : ");
  lcd.print(h);
  lcd.print(" %");

       if((t>=27) && (t<=28)){
      Serial.print("Normal-");
      Serial.print("Switch OFF");
        digitalWrite(relaylampu, HIGH);
        digitalWrite(relayfan, HIGH);
      }
      else if(t<27){
      Serial.print("Low-");
      Serial.print("Switch OFF");
      digitalWrite(relaylampu, LOW);
      digitalWrite(relayfan, HIGH);
      dering_pendek();
      
      }
      else if(t>28){
      Serial.print("Hot-");
      Serial.print("Switch ON");
        digitalWrite(relaylampu, LOW);
        digitalWrite(relayfan, LOW);
      }
  Serial.println();

 delay(1000);
}

void dering_pendek(){
digitalWrite(buzzer, HIGH);
delay(400);
digitalWrite(buzzer, LOW);
delay(400);
}
