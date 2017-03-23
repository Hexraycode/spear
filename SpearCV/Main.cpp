#include <thread>
#include "Spear.h"

//#include <opencv2/bioinspired.hpp> // Подключаем модуль

//cv::Ptr<cv::bioinspired::Retina> cvRetina; // Модуль сетчатки глаза

int main()
{
	Spear* sp = new Spear();

	thread processingThread = thread(&Spear::imgProcessing, sp);
	sp->runPropertiesManagement();

	return 0;
}