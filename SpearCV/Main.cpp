#include <thread>
#include "Spear.h"

//#include <opencv2/bioinspired.hpp> // ���������� ������

//cv::Ptr<cv::bioinspired::Retina> cvRetina; // ������ �������� �����

int main()
{
	Spear* sp = new Spear();

	thread processingThread = thread(&Spear::imgProcessing, sp);
	sp->runPropertiesManagement();

	return 0;
}