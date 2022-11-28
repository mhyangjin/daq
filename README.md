# DAQ Application

## prerequir
1. Ubuntu 20.04 (Focal Fossa)
2. C ++ 11
3. ros
4. qt5

## install
1. catkin_ws/src 밑에서 git 소스를 받습니다. 

```bash
cd ~/catkin_ws/src
~/catkin_ws/src$git clone https://github.com/mhyangjin/daq.git
```
2. catkin_ws/ 밑에서 컴파일 합니다.

```bash
cd ~/catkin_ws
~/catkin_ws$catkin_make
```

3. 실행파일은 ~catkin_ws/build/daq밑에 있습니다. 또는 ~catkin_ws/devel/lib/daq 밑에 있음.
   실행하기에 앞서 .rviz 파일들이 실행 파일이 있는 dir/rvizs 폴더에 있어야 합니다.
   가지고 있는 .rviz file을 복사하거나 소스에 포함된 파일을 복사해 둡니다.
   script/record.sh ,replay.sh가 script 밑에 있어야 합니다.

```bash
cd ~/catkin_ws/build/daq
~/catkin_ws/build/daq$mkdir rvizs
cp ~catkin_ws/src/daq/src/rvizs/* ./rvizs/
```

4. daq를 실행합니다.
```bash
~/catkin_ws/build/daq$./daq
```
### 구현된 기능
1. LiDAR Top 화면 display
2. LiDAR Side 화면 display
3. Radar 화면 display
4. Car Info Display
5. GPS Display
6. IMU Display
7. Data Acquisition 버튼 선택 시 folder 선택 
  - start 시 datetime으로 자동 file name 생성
8. sensor상태로부터 상태 아이콘 적용
9. recored기능
10. runtime시에 자동으로 run, 종료시 kill 기능 적용
11. camera 기능 구현
12. recorder start/stop 구현
13. all view 기능 구현
14. sensor, replay radio button 추가
15. seosor와 replay run/stop 동작 분리
16. daq logo 추가
17. buttons 별 동작 순서 설정
18. menu에서 exit 추가
19. replay 기능 추가
20. record 오류 수정
21. config dialog 기능 추가
22. title 변경
23. sensor start/stop 기능 구현
24. topic log 화면 송출 후 종료안되는 bug fix
25. logo icon 표시
26. daq 종료 시 core가 발생하는 문제 fix.

### restriction
1. 현재 카메라 영상 송출 확인 안됨
2. 상태 메시지 위치 조정 - > 윈도우 사이즈 확인 후 fix
 


