#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

//#include <opencv2/bioinspired.hpp> // Подключаем модуль

//cv::Ptr<cv::bioinspired::Retina> cvRetina; // Модуль сетчатки глаза

using namespace cv;
using namespace std;

int main()
{
	Mat frame;
	//--- INITIALIZE VIDEOCAPTURE
	VideoCapture cap;
	// open the default camera using default API
	cap.open(0);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	while(true)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// show live and wait for a key with timeout long enough to show images
		imshow("Live", frame);
		waitKey(500);
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}