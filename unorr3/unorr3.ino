/*
            UNO      
SDA (SS)    10     
SCK         13        
MOSI        11         
MISO        12        
GND         GND        
RST         9        
3.3V        3.3V       
*/
#include <string.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <Servo.h> 
SoftwareSerial mySerial(8,7);
#define RST_PIN 9    
#define SS_PIN 10   // Nếu dùng Arduino Mega 2560 thì đổi 10 thành 53
MFRC522 mfrc522(SS_PIN, RST_PIN); 
#define cam_bien 2
#define den_san 3
bool trangThaiDen=false;
bool trangThaiCua = false;
#define khoaCua 6//////
#define coi 5
#define nutOnOff 4 //trở
Servo myServo;
void cua_nha(){
  
  if (trangThaiCua==false){
    digitalWrite(coi, 1);
    if(digitalRead(cam_bien)==1&&trangThaiDen==false){
      digitalWrite(den_san, 0);
      trangThaiDen=true;
    }
    for (int pos =0; pos <= 100; pos +=1) {
      myServo.write(pos);
      delay(5);
    }
    digitalWrite(coi, 0);
  }
  else if (trangThaiCua==true){
    digitalWrite(coi, 1);
    
    for (int pos =100; pos >= 0; pos -= 1) {
      myServo.write(pos);
      delay(10);
    }
    if(trangThaiDen==true){
      digitalWrite(den_san, 1);
      trangThaiDen=false;
    }
    digitalWrite(coi, 0); 
  }
    trangThaiCua=!trangThaiCua;
}

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600); 
    SPI.begin();        
    mfrc522.PCD_Init(); 
    pinMode(cam_bien, INPUT);
    pinMode(nutOnOff, INPUT);
    pinMode(den_san, OUTPUT);
    pinMode(khoaCua, OUTPUT);
    digitalWrite(den_san, 0);
    digitalWrite(coi,1);
    pinMode(coi, OUTPUT);
    myServo.attach(khoaCua,500,2500);
    if (trangThaiCua==false)myServo.write(0);
    delay(500);
    digitalWrite(den_san, 1);
    digitalWrite(coi,0);
}
void xuly_nfc(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    unsigned long cardUid = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUid = (cardUid << 8) | mfrc522.uid.uidByte[i];
    }
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      mfrc522.uid.uidByte[i] < 0x10 ? Serial.print(" 0") : Serial.print(" ");
    }
    //Serial.println();
    Serial.println(cardUid);
    // đợi cho thẻ được gỡ ra
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  
    if(cardUid==2301937817||cardUid==1388679707){
      // if (trangThaiCua==false){
      //   digitalWrite(coi, 1);
      //   for (int pos =0; pos <= 100; pos +=1) {
      //     myServo.write(pos);
      //     delay(5); 
      //   }
      //   digitalWrite(coi, 0);
      //   cardUid=0;
      // }
      // else if (trangThaiCua==true){
      //   digitalWrite(coi, 1);
      //   for (int pos =100; pos >= 0; pos -= 1) {
      //       myServo.write(pos);
      //       delay(10);
      //   }
      //   digitalWrite(coi, 0);   
      //   cardUid=0; 
      // }
      // trangThaiCua=!trangThaiCua;
      cua_nha();
      cardUid=0;
    }
    else{
      mySerial.print("canhbao");
      for(int i=0;i<10;i++){
        if (i%2==0)
        {
          digitalWrite(coi,1);
          delay(500);
        }
        else
        {
          digitalWrite(coi,0);
          delay(100);
        }
      }
      digitalWrite(coi,0);
    }    
  }
}
void xuly_telegram(){
  if(mySerial.available()){
        String Incoming_value = mySerial.readString();
        //Serial.println(Incoming_value);
        if (Incoming_value=="open"){
          if (trangThaiCua==false){
            digitalWrite(coi, 1);
            if(digitalRead(cam_bien)==1&&trangThaiDen==false){
              digitalWrite(den_san, 0);
              trangThaiDen=true;
            }
            for (int pos =0; pos <= 100; pos +=1) {
              myServo.write(pos);
              delay(5);
            }
            digitalWrite(coi, 0);
            trangThaiCua=!trangThaiCua;
          } 
        }
        else if (Incoming_value=="close")
        {
          if (trangThaiCua==true){
            digitalWrite(coi, 1);
            for (int pos =100; pos >= 0; pos -= 1) {
              myServo.write(pos);
              delay(10);
            }
            if(trangThaiDen==true){
              digitalWrite(den_san, 1);
              trangThaiDen=false;
            }
            digitalWrite(coi, 0);  
            trangThaiCua=!trangThaiCua;  
        } 
        } 
        else if (Incoming_value=="batden")
        {
          digitalWrite(den_san,0);
        }
        else if (Incoming_value=="tatden")
        {
          digitalWrite(den_san,1);
        }
        else if (Incoming_value=="chuong")
        {
          digitalWrite(coi,1);
          delay(500);
          digitalWrite(coi,0);
          delay(500);
          digitalWrite(coi,1);
          delay(500);
          digitalWrite(coi,0);
          delay(500);
          digitalWrite(coi,1);
          delay(500);
          digitalWrite(coi,0);
        }
  }
}
void loop() 
{ 
  xuly_nfc();
  xuly_telegram();
  if (digitalRead(nutOnOff)==1)
  {
    
    cua_nha();
  }
  mfrc522.PCD_SoftPowerUp();
  } 

