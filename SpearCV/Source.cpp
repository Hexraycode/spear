#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>
using namespace cv;
using namespace std;

//#include <opencv2/bioinspired.hpp> // Подключаем модуль

//cv::Ptr<cv::bioinspired::Retina> cvRetina; // Модуль сетчатки глаза

//Definition of prototypes
void imgProcessing(double& thresholdMaxValue);

int main()
{
	double thresholdMaxValue = 20;
	thread t = thread(imgProcessing, std::ref(thresholdMaxValue));
	while (true)
	{
		cin >> thresholdMaxValue;
	}

	return 0;
}

void imgProcessing(double& thresholdMaxValue) {
	Mat frame;
	//--- INITIALIZE VIDEOCAPTURE
	VideoCapture cap;
	// open the default camera using default API
	cap.open(0);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return;
	}
	while (true)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		cvtColor(frame, frame, CV_RGB2GRAY);
		adaptiveThreshold(frame, frame, thresholdMaxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);
		// show live and wait for a key with timeout long enough to show images
		imshow("Live", frame);
		waitKey(50);
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
}