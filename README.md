# humanoid_Robotis_premium-Arduino-IDE-OpenCM9.04-Dynamixel_AX_12A-18EA-
(Arduino IDE) OpenCM9.04 + Dynamixel_AX_12A (18EA))

로보 티즈 프리미엄 세트를 이용하여 만들었습니다.
아두 이노 프로그램을 사용하고 싶어서 CM530을 대신해서 OpenCM9.04와 OpenCM485 보드를 사용해서 만들었습니다.

Motion_Value_Insult 함수에 delay, 1 ~ 18 번의 다이나믹 셀값 들어면됩니다. 물론 delay 에 대한 함수는 주석으로 남겨놨습니다.
동작 값은 로보 티즈 R + 모션 프로그램을 메모장으로 값을 알아 낸후 정보를 넣었습니다

다이나믹 셀 AX-12A는 BAUDRATE 값이 1000000으로 설정해야합니다.
다이나믹 셀을 제어하기 위해서는 begin, ping, id 값을 맞춰야 동작합니다.

누군가 휴머노이드 프리이엄을 아두이노로 제어하고 싶으시다면 도움이 되길 바랍니다.
