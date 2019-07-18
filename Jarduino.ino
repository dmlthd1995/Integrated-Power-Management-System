#include<SoftwareSerial.h>              //시리얼통신 헤더파일
#include <MsTimer2.h>                    //타이머 헤더파일
SoftwareSerial BTSerial(4, 7);          //시리얼통신 포트 4(TX), 7(RX) 설정

byte pre_state = 0;                           //불필요한 재수행을 막기 위한 변수 설정
byte Relay1 = 2;   //Relay 포트 설정
byte Relay2 = 3;
byte Relay3 = 5;
byte Relay4 = 6;
byte Relay5 = 8;
byte Relay6 = 9;
byte Relay7 = 10;
byte Relay8 = 11;
byte buzzer = 12;
unsigned long prev_time;

void Check_connect(void)   //블루투스 연결 확인 함수
{
  BTSerial.write('C');   //블루투스 연결 확인 문자 보내기
}
void setup()
{
  BTSerial.begin(9600);   //블루투스통신 초기화
  //Serial.begin(9600);
  pinMode(Relay1, OUTPUT);    //pinMode 출력 설정
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);
  pinMode(Relay6, OUTPUT);
  pinMode(Relay7, OUTPUT);
  pinMode(Relay8, OUTPUT);
  pinMode(buzzer, OUTPUT);
  MsTimer2::set(100, Check_connect);     //MsTimer2 설정, 타이머2인터럽트를 사용하여 50ms마다 Check_connect함수를 트리거
  MsTimer2::start();                   //MsTimer2 시작
}

void loop()
{
  if (BTSerial.available())
  {
    prev_time = millis();
    digitalWrite(buzzer, LOW);
    char a = BTSerial.read();

    if ( a == '1' && pre_state == 1)
    {
      pre_state = 0;
      digitalWrite(Relay1, LOW);
      digitalWrite(Relay2, LOW);
      digitalWrite(Relay3, LOW);
      digitalWrite(Relay4, LOW);
      digitalWrite(Relay5, LOW);
      digitalWrite(Relay6, LOW);
      digitalWrite(Relay7, LOW);
      digitalWrite(Relay8, LOW);
    }
    else if ( a == '2' && pre_state == 0)
    {
      pre_state = 1;
      digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, HIGH);
      delay(5000);//5
      digitalWrite(Relay6, HIGH);
      digitalWrite(Relay7, HIGH);
      delay(10000);//10
      digitalWrite(Relay5, HIGH);
      digitalWrite(Relay4, HIGH);
      delay(3000);//3
      digitalWrite(Relay3, HIGH);
      digitalWrite(Relay8, HIGH);
    }
  }
  else if (millis() - prev_time >= 1000) // data가 수신이 없으면
  {
    digitalWrite(buzzer, HIGH);
  }
}
