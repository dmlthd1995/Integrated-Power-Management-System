#include<SoftwareSerial.h>        //시리얼통신 헤더파일
SoftwareSerial BTSerial(2, 3);    //시리얼통신 포트 2(TX), 3(RX) 설정

byte buzzer = 12;                   //12번핀 버저 설정
byte ESTOP = 13;                    //13번핀 비상정지 설정
byte ESTOP_state;                   //비상정지 상태값 변수 설정
byte Check_connect;                 //블루투스 연결 확인 변수
unsigned long prev_time;

void setup()
{
  BTSerial.begin(9600);             //블루투스통신 초기화
  //Serial.begin(9600);
  pinMode(ESTOP, INPUT_PULLUP);            //ESTOP 입력 설정
  pinMode(buzzer, OUTPUT);          //버저 출력 설정
  BTSerial.flush();   //통신내용 초기화
}

void loop()
{
  if (BTSerial.available())
  {
    Check_connect = BTSerial.read();
    Serial.print(Check_connect);
    if ( Check_connect == 'C')
    {
      ESTOP_state = digitalRead(ESTOP);       //ESTOP 입력값을 ESTOP_state에 저장

      if (ESTOP_state == HIGH)                //ESTOP_state가 HIGH이면 시리얼 '1'을 보냄
      {
        BTSerial.write('1');
      }
      else if (ESTOP_state == LOW)            //ESTOP_state가 LOW이면 시리얼 '2'를 보냄
      {
        BTSerial.write('2');
      }
      noTone(buzzer);
      prev_time = millis();
    }
  }
  else if (millis() - prev_time >= 1000) // data가 수신이 없으면
  {
    tone(buzzer, 659);
  }
}
