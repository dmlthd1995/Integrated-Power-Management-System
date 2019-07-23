#include<SoftwareSerial.h>                    //시리얼통신 헤더파일
#include <MsTimer2.h>                         //타이머 헤더파일
SoftwareSerial BTSerial(4, 7);                //시리얼통신 포트 4(TX), 7(RX) 설정
byte pre_state = 0;                           //불필요한 재수행을 막기 위한 변수 설정
byte Relay1 = 2;                              //Relay1~8 핀 설정
byte Relay2 = 3;
byte Relay3 = 5;
byte Relay4 = 6;
byte Relay5 = 8;
byte Relay6 = 9;
byte Relay7 = 10;
byte Relay8 = 11;
byte buzzer = 12;                             //buzzer 핀 설정
unsigned long prev_time;                      //통신시간 저장 변수 설정

void Check_connect(void)                      //블루투스 연결 확인 함수
{
  BTSerial.write('C');                        //블루투스 연결 확인 문자 보내기
}
void setup()
{
  BTSerial.begin(9600);                       //블루투스통신 초기화
  pinMode(Relay1, OUTPUT);                    //Relay사용을 위한 pinMode1~8 OUTPUT 설정
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);
  pinMode(Relay6, OUTPUT);
  pinMode(Relay7, OUTPUT);
  pinMode(Relay8, OUTPUT);
  pinMode(buzzer, OUTPUT);
  MsTimer2::set(100, Check_connect);          //MsTimer2 설정, 타이머2인터럽트를 사용하여 50ms마다 Check_connect함수를 트리거
  MsTimer2::start();                          //MsTimer2 시작
}

void loop()
{
  if (BTSerial.available())                   //BTSerial에 입력된 값이 있으면 if문 실행
  {
    prev_time = millis();                     //현재시간을 prev_time 변수에 저장
    digitalWrite(buzzer, LOW);                //버저 끄기
    char Relay_state = BTSerial.read();               

    if ( Relay_state == '1' && pre_state == 1)//Relay_state가 '1'이고 pre_state가 1이면 if문 실행
    {
      pre_state = 0;                          //pre_state = 0
      digitalWrite(Relay1, LOW);              //Relay1~8 LOW
      digitalWrite(Relay2, LOW);
      digitalWrite(Relay3, LOW);
      digitalWrite(Relay4, LOW);
      digitalWrite(Relay5, LOW);
      digitalWrite(Relay6, LOW);
      digitalWrite(Relay7, LOW);
      digitalWrite(Relay8, LOW);
    }
    else if ( Relay_state == '2' && pre_state == 0)//Relay_state가 '2'이고 pre_state가 0이면 if문 실행
    {
      pre_state = 1;                               //pre_state = 1
      digitalWrite(Relay1, HIGH);                  //Relay1, 2 HIGH
      digitalWrite(Relay2, HIGH);
      delay(5000);                                 //5초 딜레이
      digitalWrite(Relay6, HIGH);                  //Relay6, 7 HIGH
      digitalWrite(Relay7, HIGH);
      delay(10000);                                //10초 딜레이
      digitalWrite(Relay5, HIGH);                  //Relay5, 4 HIGH
      digitalWrite(Relay4, HIGH);
      delay(3000);                                 //3초 딜레이
      digitalWrite(Relay3, HIGH);                  //Relay3, 8 HIGH
      digitalWrite(Relay8, HIGH);
    }
  }
  else if (millis() - prev_time >= 1000)           //1초 동안 data 수신이 없으면
  {
    digitalWrite(buzzer, HIGH);                    //버저 켜기
  }
}
