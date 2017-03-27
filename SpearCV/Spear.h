#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
//#include <cstdlib>
//#include <stdio.h>

using namespace cv;
using namespace std;

class Spear {
private:
	double thresholdMaxValue;
	double thresholdC;
	int thresholdBlockSize;

	Mat frame1;
	Mat frame2;
	Mat frameResult;

	VideoCapture cap;
	pair<int, double> property;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
public:
	Spear() {
		thresholdMaxValue = 255;
		thresholdC = 5;
		thresholdBlockSize = 7;
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
				cap.read(frame1);
				waitKey(10);
				cap.read(frame2);
				//To grayscale
				cvtColor(frame1, frame1, CV_BGR2GRAY);
				cvtColor(frame2, frame2, CV_BGR2GRAY);
				//Difference
				absdiff(frame1, frame2, frameResult);
				//Threshold
				adaptiveThreshold(frameResult, frameResult, thresholdMaxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,
					thresholdBlockSize, thresholdC);
				//blur(frameResult, frameResult, Size(5, 5));
				//medianBlur(frameResult, frameResult, 3);

				Canny(frame1, frameResult, 100, 200, 3);

				//RNG rng(12345);
				//findContours(frameResult, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

				//Mat drawing = Mat::zeros(frameResult.size(), CV_8UC3);
				//for (int i = 0; i< contours.size(); i++)
				//{
				//	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				//	drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, Point());
				//}


				//adaptiveThreshold(frameResult, frameResult, thresholdMaxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,
				//	thresholdBlockSize, thresholdC);

				// show live and wait for a key with timeout long enough to show images
				imshow("Original", frame1);
				imshow("Processed", frameResult);
				//imshow("Contours", drawing);
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
			system("cls");
			printOptions();
			readOptionAndValue();
			if (property.first == 0) {
				return;
			}
			changePropertyValue();
		}
	}

	~Spear() {
		frame1.~Mat();
		frame2.~Mat();
		frameResult.~Mat();
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
		}
		else if (property.first == 2) {
			thresholdBlockSize = property.second;
		}
		else if (property.first == 3) {
			thresholdC = property.second;
		}
	}

	void printOptions() {
		cout.precision(5);
		cout << "Threshold maximal value: 1, current: " << thresholdMaxValue << endl;
		cout << "Threshold block sizee: 2, current: " << thresholdBlockSize << endl;
		cout << "Threshold C value: 3, current: " << thresholdC << endl;
	}
};

