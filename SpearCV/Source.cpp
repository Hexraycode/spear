#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>
using namespace cv;
using namespace std;

//#include <opencv2/bioinspired.hpp> // Подключаем модуль

//cv::Ptr<cv::bioinspired::Retina> cvRetina; // Модуль сетчатки глаза

class Spear {
private:
	double thresholdMaxValue;
	double thresholdC;
	int thresholdBlockSize;


	Mat frame;
	VideoCapture cap;
	pair<int, double> property;
public:
	Spear() {
		thresholdMaxValue = 256;
		thresholdC = 5;
		thresholdBlockSize = 9;
		cap.open(0);
		if (!cap.isOpened()) {
			throw new exception("ERROR! Unable to open camera\n");
		}
	}

	void setThresholdMaxValue(double argThresholdMaxValue) {
		thresholdMaxValue = argThresholdMaxValue;
	}

	void imgProcessing() {
		while (true)
		{
			try {
				// wait for a new frame from camera and store it into 'frame'
				cap.read(frame);
				// check if we succeeded
				if (frame.empty()) {
					cerr << "ERROR! blank frame grabbed\n";
					break;
				}

				cvtColor(frame, frame, CV_RGB2GRAY);


				adaptiveThreshold(frame, frame, thresholdMaxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,
					thresholdBlockSize, thresholdC);
				// show live and wait for a key with timeout long enough to show images
				imshow("Live", frame);
				waitKey(50);
			}
			catch (exception ex) {
				cout << ex.what() << endl;
			}
		}
	}

	void runPropertiesManagement() {
		while (true)
		{
			readOptionAndValue();
			if (property.first == 0) {
				return;
			}
			changePropertyValue();
		}
	}

	~Spear() {
		frame.~Mat();
		cap.~VideoCapture();
	}

private:
	void readOptionAndValue() {
		cout << "Enter a number of the property: " << endl;
		cin >> property.first;
		cout << "Enter a new value of the property: " << endl;
		cin >> property.second;
	}

	void changePropertyValue() {
		if (property.first == 1) {
			thresholdMaxValue = property.second;
		} else if (property.first == 2) {
			thresholdBlockSize = property.second;
		}
		else if (property.first == 3) {
			thresholdC = property.second;
		}
	}
};

int main()
{
	Spear* sp = new Spear();

	thread processingThread = thread(&Spear::imgProcessing, sp);
	sp->runPropertiesManagement();

	return 0;
}