//#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat image = imread("E:\\test\\opencv\\abc.jpg");
	imshow("ÏÔÊ¾Í¼Ïñ",image);
	waitKey(0);
	return 0;

}