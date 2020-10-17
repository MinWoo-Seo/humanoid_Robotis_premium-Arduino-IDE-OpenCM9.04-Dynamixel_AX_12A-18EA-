#include <DynamixelWorkbench.h>
#include <OLLO.h>

#include <RC100.h>        //블루투스 RC100b 사용하기위한 헤더파일 포함

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif          

#define BAUDRATE  1000000  // 다이나믹셀은 1Mbps가 가장 좋다고 함
#define DXL_ID    1
#define LED 14

  DynamixelWorkbench dxl_wb;  // 다이나믹셀 Class 함수
  OLLO myOLLO;     // 로보티즈 센서 Class 함수
  RC100 Controller; // RC100 Class 함수
  
  uint8_t dxl_id[19] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};  // 숫자를 맞추기 위해서 0을 포함했으나 id_1=1 임  
  int32_t Motion_Value[19] = {0,-96, 96, -71, 71, -13, 13, -43, 43, 0, 0, -37, 37, -40, 40, 18, -18, 0, 0};  // 초기 모션  
  int delay_past=0;// 전역변수로 전에 delay값에서 뺀 값 저장

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  led_14_onoff();
Serial.begin(57600);

 myOLLO.begin(1, IR_SENSOR);//IR Module must be connected at port 1.  // 포트 1번 적외선 센서 동작
 
  Controller.begin(2);//블루투스 RC100b 사용하기 위한 통신 시작함수

  //while(!Serial); // Wait for Opening Serial Monitor // 시리얼 통신해야지만 넘어감

digitalWrite(LED,LOW);//OpenCM9.04의 내부 14핀은 반전됨 = LED: ON
dynamixel_motor_scan();
 ledon();
 delay(3000);
 ledoff();
digitalWrite(LED,HIGH);//OpenCM9.04의 내부 14핀은 반전됨 = LED: ON
delay(500);
Motion_Value_Insult(129,-96, 96, -71, 71, -13, 13, -43, 43, 0, 0, -37, 37, -40, 40, 18, -18, 0, 0);
delay(500);
}

int32_t Anlgle_Value[19];

void loop() {
  // put your main code here, to run repeatedly:
  
  const char *log; // 다이나믹셀에서 보내는 통신 신호 및 메시지를 로그 안에 저장


//dynamixel_position();
//IR_Sensor_ADC();

Controller_bluetooth_RC100b();

}

void humanoid_forward_step(){
  //동보행
  Serial.println(" 동보행 시작 ");
  Motion_Value_Insult(129,-96, 96, -71, 71, -13, 13, -43, 43,    0, 0, -37, 37,      -40, 40, 18, -18, 0, 0);
  delay(70);
  Motion_Value_Insult(139,-96, 96, -71, 71, -13, 13, -43, 43, 0, 0, -74, 37, -77, 40, 28, -31, 0, 0);
  delay(70);
  Motion_Value_Insult(148,-96,96,-71,71,-13,13,-43,43,0,0,-37,37,-40,40,18,-18,0,0);
  delay(70);
  Motion_Value_Insult(159,-96,96,-71,71,-13,13,-43,43,0,0,-37,74,-40,77,31,-28,0,0);
  delay(70);
  Motion_Value_Insult(169,-96,96,-71,71,-13,13,-43,43,0,0,-37,37,-40,40,18,-18,0,0);
  //delay(70);
  //Motion_Value_Insult(125,-81.15,80.86,-68.26,67.97     ,-14.65,14.36     ,-45.12,45.12,-1.46,1.17,-50.1,49.8,-79.69,79.39,39.55,-39.84,-1.46,1.17);
  Serial.println(" 동보행 끝 ");

}


void Motion_Value_Insult(int32_t A0,int32_t A1,int32_t A2,int32_t A3,int32_t A4,int32_t A5,int32_t A6,int32_t A7,int32_t A8,int32_t A9,int32_t A10,int32_t A11,int32_t A12,int32_t A13,int32_t A14,int32_t A15,int32_t A16,int32_t A17,int32_t A18)
{//1~18까지 다이나믹셀 값 입력  
   const char *log; // 다이나믹셀에서 보내는 통신 신호 및 메시지를 로그 안에 저장
   int32_t Anlgle_Value[19];
   int delay_Value=0;
   int delay_present=0;
   // Value*1024/360+512;
#if 1
    //dxl_wb.jointMode(dxl_id, 0, 0, &log); // 관절모드 (이미 초기값으로 되어있음)
    //delay_Value=A0;//0번째는 delay값 입력
    Anlgle_Value[0]=A0;
    Anlgle_Value[1]=A1;//1부터 18번까지 각도값 저장
    Anlgle_Value[2]=A2;//1부터 18번까지 각도값 저장
    Anlgle_Value[3]=A3;//1부터 18번까지 각도값 저장
    Anlgle_Value[4]=A4;//1부터 18번까지 각도값 저장
    Anlgle_Value[5]=A5;//1부터 18번까지 각도값 저장
    Anlgle_Value[6]=A6;//1부터 18번까지 각도값 저장
    Anlgle_Value[7]=A7;//1부터 18번까지 각도값 저장
    Anlgle_Value[8]=A8;//1부터 18번까지 각도값 저장
    Anlgle_Value[9]=A9;//1부터 18번까지 각도값 저장
    Anlgle_Value[10]=A10;//1부터 18번까지 각도값 저장
    Anlgle_Value[11]=A11;//1부터 18번까지 각도값 저장
    Anlgle_Value[12]=A12;//1부터 18번까지 각도값 저장
    Anlgle_Value[13]=A13;//1부터 18번까지 각도값 저장
    Anlgle_Value[14]=A14;//1부터 18번까지 각도값 저장
    Anlgle_Value[15]=A15;//1부터 18번까지 각도값 저장
    Anlgle_Value[16]=A16;//1부터 18번까지 각도값 저장
    Anlgle_Value[17]=A17;//1부터 18번까지 각도값 저장
    Anlgle_Value[18]=A18;//1부터 18번까지 각도값 저장

    delay_present=A0;//0번째는 delay값 입력 // 현재 스텝(시간) 저장
    delay_Value=delay_present-delay_past;  // 현재 스텝(시간) - 전 스텝(시간)의 차이만큼만 딜레이
    delay_past=A0;// 그 전 스텝(시간)을 저장
    delay_Value=delay_Value*1000/128;  // R+모션은 스텝당 1.28:1초를 기준으로 하기에 곱해줌

    if(delay_Value <0 ){      //토크값을 입력하지 않았을때
     
      delay_Value=1;//delay초기화
      delay_present=0;//delay초기화
      delay_past=0;//delay초기화
      }
    //delay(delay_Value);
      //delay(10);

     for(int cnt=1;cnt<=18;cnt++){  //cnt는 1부터시작(다이나믹셀은 1번부터 시작이기 때문, 번호 맞추기 위해서),cnt가 18이 될 때까지
    Anlgle_Value[cnt]=Anlgle_Value[cnt]*1024/360+512;//R+모션 배율 맞춤 1024:360 이면서, +-중간인 512를 0점으로 맞춤
    //dxl_wb.jointMode(dxl_id[cnt], 0, 0, &log);// 각 모터 포지션 모드 설정 //여기서 시간을 너무 잡아먹음 -> 동작진행이 구분될정도로 시간을 잡아먹음
    dxl_wb.goalPosition(dxl_id[cnt],(int32_t) Anlgle_Value[cnt]); // 각 모터값에 해당하는 포지션 값 입력   
    }
#endif


}

int key_flag=0;  // 한번만 누르기 위한 플래그 (계속 누르고 있더라도 한번만 클릭되도록)
//RC100 Controller; // RC100 Class 함수
int RcvData = 0;  // RC 데이터 변수
void Controller_bluetooth_RC100b(){

   if (Controller.available()) //블루투스 통신 신호 들어옴
  {
    RcvData = Controller.readData(); // 데이터를 저장

       if(key_flag==0){  // 신호가 처음일때
          key_flag=1; 
         Controller_bluetooth_RC100b_keyboard();// 조종기 키보드에 해당하는 버튼 함수들 
          delay(100); //약간의 딜레이를 줌
        //  return;
          }
       else{//key_flag=1 키를 계속 누르고 있을 때
          return;     // 무시
          }
   }
       else{// 통신 신호가 들어오지 않을 때
            if(key_flag==1){ // key_flag=1 계속 누르고 있다는 플래그
               delay(130); //약간의 딜레이를 줌
               key_flag=0;
               }
            else{;}//무시
           }
}
void Controller_bluetooth_RC100b_keyboard(){
  if (RcvData & RC100_BTN_U)
    { Serial.println(" UP버튼 누름");
      humanoid_forward_step();
       Serial.println(" UP버튼 끝");
    }
    else if (RcvData & RC100_BTN_D)
    {Serial.println(" DOWN버튼 누름");
    }
    else if (RcvData & RC100_BTN_L)
    {Serial.println(" LEFT버튼 누름");
    }
    else if (RcvData & RC100_BTN_R)
    {Serial.println(" RIGHT버튼 누름");
    }
    else if (RcvData & RC100_BTN_1)
    {Serial.println(" 1 버튼 누름");
    Walk_Ready_31();
    }
    else if (RcvData & RC100_BTN_2)
    {Serial.println(" 2 버튼 누름");
    F_S_L_32();
    F_S_L_33();
    F_S_R_34();
    F_S_R_35();
    }
    else if (RcvData & RC100_BTN_3)
    {Serial.println(" 3 버튼 누름");
    }
    else if (RcvData & RC100_BTN_4)
    {Serial.println(" 4 버튼 누름");
   }
    else if (RcvData & RC100_BTN_5)
    {Serial.println(" 5 버튼 누름");

    }
    else if (RcvData & RC100_BTN_6)
    {Serial.println(" 6 버튼 누름");
    }
}

void IR_Sensor_ADC(){
  Serial.print("IR Sensor ADC = ");
  Serial.println(myOLLO.read(1, IR_SENSOR)); //read ADC value from OLLO port 1
  delay(60);
  }


void dynamixel_motor_scan(){
  
  const char *log; // 다이나믹셀에서 보내는 통신 신호 및 메시지를 로그 안에 저장
  
dxl_wb.begin(DEVICE_NAME, BAUDRATE, &log);   // begin=init // 다이나믹셀 통신 시작 및 통신속도(1000000) 설정
  uint8_t scanned_id[16]; // 검사된 총 개수
  uint8_t dxl_cnt = 0;   //다이나믹셀 개수
  uint8_t range = 100;  //100개 검사
  bool result = false;
while(!dxl_cnt){ // 1개이상 검색 되면 승인
    dxl_wb.scan(scanned_id, &dxl_cnt, range, &log);  // 스캔 함수
    Serial.println(dxl_cnt); //다이나믹셀 개수
    Serial.println(log);  // 다이나믹셀 통신 메시지
    Serial.println("Failed to scan");
    delay(300);
  }
   Serial.print("Find ");
    Serial.print(dxl_cnt); //다이나믹셀 개수
    Serial.println(" Dynamixels");

    for (int cnt = 0; cnt < dxl_cnt; cnt++)  // 다이나믹셀 몇개 스캔 했는지 판단
    {
      Serial.print("id : ");
      Serial.print(scanned_id[cnt]);
      Serial.print(" model name : ");
      Serial.println(dxl_wb.getModelName(scanned_id[cnt]));
      
      dxl_wb.ping(dxl_id[scanned_id[cnt]], &log);  //ping은 잘 모르겠으나 begin 및 ping은 설정해야 움직임
      Serial.print(scanned_id[cnt]);
      Serial.println("ping 확인");
    }
 }
void led_14_onoff(){
  for(int i=0;i<=5;i++){
  digitalWrite(LED,LOW);//OpenCM9.04의 내부 14핀은 반전됨 = LED: ON
  delay(500);
  digitalWrite(LED,HIGH);//OpenCM9.04의 내부 14핀은 반전됨 = LED: LOW
  delay(500);
  }
  } 
void ledon(){
  const char *log;
    for(int cnt=1;cnt<=18;cnt++){  //cnt는 1부터시작(다이나믹셀은 1번부터 시작이기 때문, 번호 맞추기 위해서),cnt가 18이 될 때까지
    dxl_wb.ledOn(dxl_id[cnt],&log);    
  }Serial.println("All_LED : ON");}
void ledoff(){
  const char *log;
    for(int cnt=1;cnt<=18;cnt++){  //cnt는 1부터시작(다이나믹셀은 1번부터 시작이기 때문, 번호 맞추기 위해서),cnt가 18이 될 때까지
    dxl_wb.ledOff(dxl_id[cnt],&log);    
  }Serial.println("All_LED : OFF");}



void Walk_Ready_31(){
Motion_Value_Insult(125,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-1.46,1.17,-50.1,49.8,-79.69,79.39,39.55,-39.84,-1.46,1.17);
}

void F_S_L_32(){
Motion_Value_Insult(10,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,0.29,2.93,-49.8,49.51,-79.39,78.81,39.26,-39.55,0.29,2.93);
//Motion_Value_Insult(20,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,2.05,4.69,-49.22,48.63,-78.22,77.34,38.67,-38.67,2.05,4.69);
//Motion_Value_Insult(30,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,3.52,6.15,-48.63,47.75,-76.76,75.59,38.09,-37.79,3.52,6.15);
Motion_Value_Insult(40,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,4.69,7.32,-47.75,46.88,-75,73.54,37.21,-36.91,4.69,7.32);
//Motion_Value_Insult(50,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,2.64,9.38,-46.88,48.93,-73.24,77.93,36.33,-38.96,5.57,8.5);
//Motion_Value_Insult(60,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-2.64,12.6,-46.29,53.91,-72.07,87.6,35.74,-43.95,6.15,9.38);
Motion_Value_Insult(70,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-5.27,14.06,-46,55.96,-71.48,91.99,35.45,-46,6.45,9.96);
}
void F_S_L_33(){
//Motion_Value_Insult(10,-81.74,80.27,-68.26,67.97,-14.65,14.36,-45.12,45.12,-2.64,12.6,-46.58,62.4,-71.78,86.43,37.79,-36.91,6.15,9.38);
//Motion_Value_Insult(20,-77.34,84.67,-68.26,67.97,-14.65,14.36,-45.12,45.12,2.64,9.38,-45.41,60.35,-72.66,74.12,39.84,-26.66,5.57,8.5);
//Motion_Value_Insult(30,-72.95,89.06,-68.26,67.97,-14.65,14.36,-45.12,45.12,4.69,7.32,-46,58.89,-74.12,67.97,41.02,-21.97,4.69,7.32);
Motion_Value_Insult(40,-69.14,92.87,-68.26,67.97,-14.65,14.36,-45.12,45.12,3.52,6.15,-46.88,60.35,-76.17,70.02,41.89,-22.85,3.52,6.15);
//Motion_Value_Insult(50,-65.92,96.09,-68.26,67.97,-14.65,14.36,-45.12,45.12,2.05,4.69,-46.58,60.94,-77.34,72.66,43.36,-24.9,2.05,4.69);
//Motion_Value_Insult(60,-63.57,98.44,-68.26,67.97,-14.65,14.36,-45.12,45.12,0.29,2.93,-45.41,60.64,-77.93,75.29,45.12,-27.54,0.29,2.93);
Motion_Value_Insult(70,-61.82,100.2,-68.26,67.97,-14.65,14.36,-45.12,45.12,-1.46,1.17,-43.36,59.77,-77.34,77.05,46.58,-30.18,-1.46,1.17);
}
void F_S_R_34(){
//Motion_Value_Insult(10,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-3.22,-0.59,-49.8,49.51,-79.1,79.1,39.26,-39.55,-3.22,-0.59);
//Motion_Value_Insult(20,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-4.98,-2.34,-48.93,48.93,-77.64,77.93,38.38,-38.96,-4.98,-2.34);
//Motion_Value_Insult(30,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-6.45,-3.81,-48.05,48.34,-75.88,76.46,37.5,-38.38,-6.45,-3.81);
Motion_Value_Insult(40,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-7.62,-4.98,-47.17,47.46,-73.83,74.71,36.62,-37.5,-7.62,-4.98);
//Motion_Value_Insult(50,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-9.67,-2.93,-49.22,46.58,-78.22,72.95,38.67,-36.62,-8.79,-5.86);
//Motion_Value_Insult(60,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-12.89,2.34,-54.2,46,-87.89,71.78,43.65,-36.04,-9.67,-6.45);
Motion_Value_Insult(70,-81.15,80.86,-68.26,67.97,-14.65,14.36,-45.12,45.12,-14.36,4.98,-56.25,45.7,-92.29,71.19,45.7,-35.74,-10.25,-6.74);
}
void F_S_R_35(){
//Motion_Value_Insult(10,-80.86,81.15,-68.26,67.97,-14.65,14.36,-45.12,45.12,-12.89,2.34,-62.7,46.29,-86.72,71.48,36.62,-38.09,-9.67,-6.45);
//Motion_Value_Insult(20,-85.25,76.76,-68.26,67.97,-14.65,14.36,-45.12,45.12,-9.67,-2.93,-60.64,45.12,-74.41,72.36,26.37,-40.14,-8.79,-5.86);
//Motion_Value_Insult(30,-89.65,72.36,-68.26,67.97,-14.65,14.36,-45.12,45.12,-7.62,-4.98,-59.18,45.7,-68.26,73.83,21.68,-41.31,-7.62,-4.98);
Motion_Value_Insult(40,-93.46,68.55,-68.26,67.97,-14.65,14.36,-45.12,45.12,-6.45,-3.81,-60.64,46.58,-70.31,75.88,22.56,-42.19,-6.45,-3.81);
//Motion_Value_Insult(50,-96.68,65.33,-68.26,67.97,-14.65,14.36,-45.12,45.12,-4.98,-2.34,-61.23,46.29,-72.95,77.05,24.61,-43.65,-4.98,-2.34);
//Motion_Value_Insult(60,-99.02,62.99,-68.26,67.97,-14.65,14.36,-45.12,45.12,-3.22,-0.59,-60.94,45.12,-75.59,77.64,27.25,-45.41,-3.22,-0.59);
Motion_Value_Insult(70,-100.78,61.23,-68.26,67.97,-14.65,14.36,-45.12,45.12,-1.46,1.17,-60.06,43.07,-77.34,77.05,29.88,-46.88,-1.46,1.17);
}
