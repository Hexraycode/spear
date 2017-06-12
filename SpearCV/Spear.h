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
	Mat frame1Color;
	Mat frame2;
	Mat frameResult;
	Mat frameDifference;

	VideoCapture cap;
	pair<int, double> property;

	//vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;
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
				cap.read(frame1Color);
				waitKey(40);
				cap.read(frame2);
				//To grayscale
				cvtColor(frame1Color, frame1, CV_BGR2GRAY);
				cvtColor(frame2, frame2, CV_BGR2GRAY);
				//Difference
				absdiff(frame1, frame2, frameDifference);
				//Threshold
				/*adaptiveThreshold(frameDifference, frameResult, thresholdMaxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,
					thresholdBlockSize, thresholdC);*/
				threshold(frameDifference, frameResult, 10, thresholdMaxValue, CV_THRESH_BINARY);
				erode(frameResult, frameResult, Mat(), Point(-1, -1), 1);
				medianBlur(frameResult, frameResult, 3);
				//Extract contours
				vector<vector<Point>> contours;
				vector<Vec4i> hierarchy;
				findContours(frameResult, contours/*, hierarchy*/, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

				//drawContours(frame1Color, contours, -1, Scalar(0,0,255), 1);

				std::vector<cv::Point> points;
				for (size_t i = 0; i<contours.size(); i++) {
					for (size_t j = 0; j < contours[i].size(); j++) {
						cv::Point p = contours[i][j];
						points.push_back(p);
					}
				}
				if (points.size() > 0) {
					cv::Rect brect = cv::boundingRect(cv::Mat(points).reshape(2));
					cv::rectangle(frame1Color, brect.tl(), brect.br(), cv::Scalar(100, 100, 200), 2, CV_AA);
				}


				//Canny(frameResult, frameResult, 100, 200, 3);
				//Showing images
				imshow("Original", frame1Color);
				imshow("Difference", frameDifference);
				imshow("Processed", frameResult);
			}
			catch (exception ex) {
				cout << ex.what() << endl;
			}
		}
	}
	//vector<Moments> contour_moments(contours.size());
	//vector<Point> mass_centers(contours.size());
	//get centroid of contours
	//for (int i = 0; i < contours.size(); i++) {
	//	contour_moments[i] = moments(contours[i], false);
	//	mass_centers[i] = Point(contour_moments[i].m10 / contour_moments[i].m00, contour_moments[i].m01 / contour_moments[i].m00);
	//}
	//
	//bool objectsDetected = (contours.size() > 0);
	//if (objectsDetected) {
	//	double xPos = 0;
	//	double yPos = 0;
	//	for (int i = 0; i < contours.size(); i++) {
	//		xPos += mass_centers[i].x;
	//		yPos += mass_centers[i].y;
	//	}
	//}
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

