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
~/catkin_ws/src$git clone git@github.com:mhyangjin/daq.git
```
2. catkin_ws/ 밑에서 컴파일 합니다.

```bash
cd ~/catkin_ws
~/catkin_ws$catkin_make
```

3. 실행파일은 ~catkin_ws/build/daq밑에 있습니다. 
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

### restriction
1. runtime시에 자동으로 rviz node  실행은 아직 적용되지 않았습니다. run으로 node를 실행시켜야 합니다.
2. camera 기능이 아직 구현되지 않았습니다. imageview를 패널 안으로 넣는데 문제가 있어서 확인 중입니다.
3. recored기능이 아직 구현되지 않았습니다. 버튼의 동작만 우선 확인해주십시요.
4. sensor의 run/stop 기능이 아직 구현되지 않았습니다.
5. all view 기능이 아직 구현되지 않았습니다.
6. sensor상태로부터 상태 아이콘 적용 기능이 아직 구현되지 않았습니다.
7. daq 종료 시 core가 발생하는 문제가 있습니다. 보완 예정입니다.
8. menu에서 exit 을 추가할 예정입니다.



