# DAQ Application

## prerequired
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

### restriction
1. run/kill은 /home/jiat/script/ 밑의 run.sh kill.sh을 호출합니다. 추후 환경설정으로 변경
2. camera 기능이 아직 구현되지 않았습니다. imageview를 패널 안으로 넣는데 문제가 있어서 확인 중입니다.
3. recored start만 구현됨, stop 되지 않음. 윈도우 종료시 종료됨. 중간 stop은 ros library에서 baglog로 동작하도록 되어 있어 
   다른 node와 별개로 recorder만 종료하는 기능이 안됨. 종료 방법을 찾는 중.
4. all view 기능이 아직 구현되지 않았습니다.
5. daq 종료 시 core가 발생하는 문제가 있습니다. 보완 예정입니다.
6. menu에서 exit 을 추가할 예정입니다.



