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
// chân kích rơ le đèn
#define den_san 3
bool trangThaiCua = false;
#define khoaCua 6
#define coi 5
#define nutOnOff 4 //trở
Servo myServo;

void setup() {
  mySerial.begin(9600);
 Serial.begin(9600); 
 SPI.begin();        
 mfrc522.PCD_Init(); 
   pinMode(nutOnOff, INPUT);
     pinMode(den_san, OUTPUT);
  pinMode(khoaCua, OUTPUT);
  pinMode(coi, OUTPUT);
  myServo.attach(khoaCua,500,2500);
 Serial.println("Lectura del UID");
}

void loop() 
{ 
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // lưu giá trị của UID vào biến cardUid dạng unsigned long
    unsigned long cardUid = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUid = (cardUid << 8) | mfrc522.uid.uidByte[i];
    }
    // hiển thị giá trị của UID trên Serial Monitor

    for (byte i = 0; i < mfrc522.uid.size; i++) {
      mfrc522.uid.uidByte[i] < 0x10 ? Serial.print(" 0") : Serial.print(" ");

    }
    Serial.println();
    // hiển thị giá trị của cardUid trên Serial Monitor

    Serial.println(cardUid);
    // đợi cho thẻ được gỡ ra
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  
      if(cardUid==1701653376)//bố
        {
          if (trangThaiCua==false)
          {
            for (int pos =0; pos <= 180; pos +=1) { //Biến pos sẽ chạy từ 0-180
              myServo.write(pos);              //ra lệnh servo quay một góc “pos”
              delay(10);
            }
            cardUid=0;
          }
          else if (trangThaiCua==true){
            for (int pos =180; pos >= 0; pos -= 1) { //Biến pos sẽ chạy từ 0-180
                myServo.write(pos);              //ra lệnh servo quay một góc “pos”
                delay(25); 
            }   
           cardUid=0; 
          }
          trangThaiCua=!trangThaiCua;
        }
          
      else if(cardUid==1388679707)//bố
        {
          if (trangThaiCua==false)
          {
            for (int pos =0; pos <= 180; pos +=1) { //Biến pos sẽ chạy từ 0-180
              myServo.write(pos);              //ra lệnh servo quay một góc “pos”
              delay(10);
            }
            cardUid=0;
          }
          else if (trangThaiCua==true){
            for (int pos =180; pos >= 0; pos -= 1) { //Biến pos sẽ chạy từ 0-180
                myServo.write(pos);              //ra lệnh servo quay một góc “pos”
                delay(25); 
            }   
           cardUid=0; 
          }
          trangThaiCua=!trangThaiCua;
        }
  }
   if(mySerial.available())  
  {
    String Incoming_value = mySerial.readString();
    Serial.println("Incoming_value");
     Serial.println(Incoming_value);
    if (Incoming_value=="open")
    {

 
          for (int pos =0; pos <= 190; pos +=1) { //Biến pos sẽ chạy từ 0-180
          myServo.write(pos);              //ra lệnh servo quay một góc “pos”
          delay(10);
    }}
    else if (Incoming_value=="khoa")
    {
      for (int pos =110; pos >= 0; pos -= 1) { //Biến pos sẽ chạy từ 0-180
            myServo.write(pos);              //ra lệnh servo quay một góc “pos”
            delay(25); 
            }   
    }
    Serial.available()!=Serial.available();}
    // if (digitalRead(nutOnOff)==1)
    // {
    //   if (trangThaiCua==false)
    //     {
    //         trangThaiCua=true;
    //     }
    //   else{
    //         trangThaiCua=false;
    //     }
        
    // }
    
  
}
