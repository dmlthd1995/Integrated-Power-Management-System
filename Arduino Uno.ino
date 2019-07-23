#include<SoftwareSerial.h>                    //시리얼통신 헤더파일
SoftwareSerial BTSerial(2, 3);                //시리얼통신 포트 2(TX), 3(RX) 설정
byte buzzer = 12;                             //12번핀 버저 설정
byte ESTOP = 13;                              //13번핀 비상정지 설정
byte ESTOP_state;                             //비상정지 상태값 변수 설정
byte Check_connect;                           //블루투스 연결 확인 변수
unsigned long prev_time;                      //통신시간 저장 변수

void setup()
{
  BTSerial.begin(9600);                       //블루투스통신 초기화
  pinMode(ESTOP, INPUT_PULLUP);               //ESTOP 입력 설정
  pinMode(buzzer, OUTPUT);                    //버저 출력 설정
  BTSerial.flush();                           //통신내용 초기화
}

void loop()
{
  if (BTSerial.available())                   //BTSerial 입력이 있으면 if문 실행
  {
    Check_connect = BTSerial.read();          //BTSerial을 읽어서 Check_connect에 저장
    if ( Check_connect == 'C')                //Check_connect가 'C'이면 if문 실행
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
      noTone(buzzer);                         //버저 끄기
      prev_time = millis();                   //현재 시간을 prev_time 변수에 저장
    }
  }
  else if (millis() - prev_time >= 1000)      // 1초간 data 수신이 없으면 
  {
    tone(buzzer, 659);                        //버저 울림
  }
}
