# version 1.2.0 - 2022.12.29
1. Lidar side 송출 프레임 버그 수정
2. sensor All view시에만 frame size 적용 하도록 변경
3. sensor All view시 frame define 기능 추가
   src/defines.h 에서 frame size 변경 가능함.
   ```
   const int FRAME_CNT[7] = {
    10, //  FRAME_CNT[F_CAMERA]       :초당 frame 수, default=30으로 세팅하려면 0
    10, //  FRAME_CNT[F_LIDAR_TOP]    :초당 frame 수, default=30으로 세팅하려면 0
    10, //  FRAME_CNT[F_LIDAR_SIDE]   :초당 frame 수, default=30으로 세팅하려면 0
    0, //  FRAME_CNT[F_RADAR]        :signal interval 개수. N개중 1개만 display. 모두 일 경우 0
    0, //  FRAME_CNT[F_GPS]          :signal interval 개수. N개중 1개만 display. 모두 일 경우 0
    0, //  FRAME_CNT[F_CAR]          :signal interval 개수. N개중 1개만 display. 모두 일 경우 0
    0  //  FRAME_CNT[F_IMU]          :signal interval 개수. N개중 1개만 display. 모두 일 경우 0
    };
   ```

# version 1.1.9 - 2022.12.28
1.reduese frame size in all view case. 
   camera : 30 frame per sec --> 1 frame per sec
   Lidar  : 30 frame per sec --> 1 frame per sec
   Text   : reduese 1/30

# version 1.1.8 - 2022.12.28
1. Lidar Side 오류 수정
2. Record button click시 config loading 시점 변경

# version 1.1.7 - 2022.12.27
1. 내부 로직 개선
2. LOG level 수정 (DEBUG->INFO)

# version 1.1.6 - 2022.12.19
1. 내부 로직 개선

# version 1.1.5 - 2022.12.16
1. 종료 스크립트 수정
2. 내부 로직 개선

# version 1.1.4 - 2022.12.13
1. all view 시 비정상 종료 bug fix

# version 1.1.1 - 2022.12.09
1. 버튼 동작 내부 기능 개선
2. kill시 종료 되지 않는 부분 개선
3. 카메라 뷰 전환 개선
4. LOG size 체크

# version 1.1.0 - 2022.12.06
1. 바로가기 아이콘, script, rvizs dir 복사를 위한 install.sh 추가
2. 비정상 종료시 roscore, ros node를 종료기능 추가

# version 1.0.0 - 2022.12.5
1. 카메라 영상 송출 확인
2. 화면 전환 시 이전 화면 clear
3. run, kill script 추가

# version 0.9.5 - 2022.11.30
1. sensor message 우측 정렬
2. daq icon 변경
3. roscore 종료 추가

# version 0.9.0 - 2022.11.28
1. LOG 상세 정보 추가
2. config.yml 없이 default로 로딩. 추후 config가 변경되면 변경 정보로 로딩하도록 수정
3. rviz dir, script dir은 pkg install 에서 제외
4. jiat_diagnostic.py pkg install에 추가

# version 0.8.0 - 2022.11.25
1. daq 종료 시 core가 발생하는 문제 fix
2. Log level 기능,  logger 기능 추가
3. 코드 정리

# version 0.7.0 - 2022.11.25
1. topic msg 송출 문제 
2. LiDar 영상 송출 확인
3. logo icon 표시

# version 0.6.5 - 2022.11.22
1. sensor 상태 메시지 위치 변경
2. config.yml 추가

# Version 0.6.0 - 2022.11.18
1. replay 기능 추가
2. record 오류 수정
3. config dialog 기능 추가
4. title 변경
5. sensor start/stop 기능 구현

# Version 0.5.5 - 2022.11.17
1. sensor, replay radio button 추가
2. seosor와 replay run/stop 동작 분리
3. daq logo 추가
4. buttons 별 동작 순서 설정

# Version 0.5.0 - 2022.11.15
1. camera 기능 구현
2. recorder start/stop 구현
3. all view 기능 구현


# Version 0.4.0 - 2022.11.14
1. record 기능 추가
2. start/stop시 ros launch, kill 기능 추가


# Version 0.3.0 - 2022.11.13
1. sensor 상태 기능 추가
2. topic msgs 연결
3. sensor run/stop 버튼 삭제
4. 코드 정리

# Version: 0.2.0 - 2022.11.11
1. button 순서 변경
2. View 화면에 title 추가
