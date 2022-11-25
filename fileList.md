# Dir
-----------
* msg
  topic의 msg가 선언된 파일
* scripts
  recore.sh, replay.sh
* src
  C++ source
  - images
    Daq application에서 사용할 image files
  - rvizs
    Daq application내부에서 사용할 rviz config files



# File List
-----------
|파일명| 내용|
|---|:---:|
AcquisitionStatus.cpp | AcquisitionStatus 바의 상태 체크를 위한 클래스|
AcquisitionStatus.h |  |
CameraViewer.cpp | Camera Display를  rendering하여 GUI로 보내기 위한 class |
CameraViewer.h |
ConfigLoader.cpp | config.yml을 읽고 저장하는 클래스
ConfigLoader.h |  |
config.yml | rivz, script들의 기본 dir과 로딩해야하는 launch, node 정보를 저장|
DaqCameraDisplay.cpp | rviz/default_plugin에 포함된 camera_display를 수정한 클래스임. default camera_display는 윈도우 창을 따로 띄움
DaqCameraDisplay.h |  |
daqmain.cpp| DAAQ의 MainWindow   ui상의 controll들의 signal은 모두 여기에서 처리한다   ui상의 signal 별로 ui의 disable, enable 도 여기에서 처리한다.   그 외 로직은 모두 sideButtonActions안에서 처리
daqmain.h | |
daqmain.ui | UI design 파일. QT Creator에서 열어서 디자인을 변경할 수 있다.
DAQViz.cpp | .rviz file을 읽어서 rviz::Config로 만든 후 VisualizationManager를 통해 GUI로 보내기 위한 최상위 class. sensor 별로 이 클래스를 상속받아 하위로 구현한다.
DAQViz.h | |
defines.h | labename, sensor name등 기본 설정 |
DialogConfig.cpp |configration settion을 위한 dialog window |
DialogConfig.h | |
DialogConfig.ui | configration settion을 위한 dialog window의 UI Design file. QT Creator에서 열어서 디자인을 변경할 수 있다.
images.qrc | images dir에 있는 이미지 파일을 사용하기 위한 리소스 파일. QT Creator에서 리소스 추가를 하면 수정된다.
init.h | 공통으로 사용하는 include를 함께 선언한 파일
main.cpp |  DAQ application을 실행하기 위한 메인 파일, application의 start point
RecordPlayer.cpp | Record Player
RecordPlayer.h | |
RecordStarter.cpp | Record start/stop controller
RecordStarter.h| |
RosNode.cpp | node or launcher 를 실행하기 위한 thread
RosNode.h | |
RosRunManager.cpp | ros launchers, node의 start/stop을 관리하는 managers
RosRunManager.h | |
RvizViewer.cpp | Rviz file로부터 영상이미지를 위한 윈도우 콘트롤 클래스
RvizViewer.h | |
sideButtonActions.cpp | side button을 클릭했을 때 수행할 동작들. 윈도우상의 모든 액션과 연결된 동작을 콘트롤한다.
sideButtonActions.h | |
TopicSubscribers.cpp | 모든 topic을 모두 sub하기 위한 클래스 ros::spin() thread를 block하고 대기하여, 여러개의 topic을 함께 sub할 수 없다. multi-thread여야 하기 때문에 ros::spiner를 사용한다.
TopicSubscribers.h | |
TopicsViewer.cpp | 토픽들의 window controll class |
TopicsViewer.h | |
YmlLoader.cpp | yml file loader |
YmlLoader.h | |
