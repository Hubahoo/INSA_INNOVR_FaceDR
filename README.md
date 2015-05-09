# INSA_INNOVR_FaceDR
This project aim to use OpenCV on a Raspberry Pi to do some face detection and recognition.
There is two set of sources available: for compilation on a x86-64 architecture running GNU/Linux and the second one is specifically for the Raspberry Pi.
It was developped and tested on a Raspberry Pi model B+.

Libraries used are:
- openCV for image processing and detection classifiers (openCV 2.4)
- SQLite
- boost
- raspicam to use the camera board with the raspberry pi (raspicam 0.1.3)

To build this project on x86-64:
- install openCV: documentation can be found here: http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation
- use cmake to generate Makefile, it's recommended to do so in a 'Release' folder
- use make to compile the project

To build this project on a rapsberry Pi:
- install openCV: documentation can be found here: http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation
- install raspicam: http://www.uco.es/investiga/grupos/ava/node/40
- use cmake to generate Makefile, it's recommended to do so in a 'Release' folder
- use make to compile the project

