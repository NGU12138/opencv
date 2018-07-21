/*------------------------------------------------------------------------------------------*\
This file contains material supporting chapter 10 of the cookbook:
Computer Vision Programming using the OpenCV Library.
by Robert Laganiere, Packt Publishing, 2011.

This program is free software; permission is hereby granted to use, copy, modify,
and distribute this source code, or portions thereof, for any purpose, without fee,
subject to the restriction that the copyright notice may not be removed
or altered from any source or altered source distribution.
The software is released on an as-is basis and without any warranties of any kind.
In particular, the software is not guaranteed to be fault-tolerant or free from failure.
The author disclaims all warranties with regard to this software, any use,
and any consequent failure, is purely the responsibility of the user.

Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
using namespace std;
using namespace cv;

uchar hlow=0, hhigh=10;
uchar slow = 0, shigh = 40;
void h_low(int value,void *)
{
	hlow = value;
}

void h_high(int value,void *)
{
	hhigh = value;
}
void s_low(int value, void *)
{
	slow = value;
}

void s_high(int value, void *)
{
	shigh = value;
}


class Colordetector {
private :
	int mindist; //最小可接受距离
	Vec3b target;
	Mat result; //结果图像
	uchar targetH;

public:
	Colordetector() :mindist(100) {
	//初始化默认参数
		target[0] = target[1] = target[2] = 0;
		targetH = 2;
	}
	void setColorDistanceThreshold(int distance) {
		if (distance < 0)
			distance = 0;
		mindist = distance;

	}
	int getColorDistanceThreshold() const {
		return mindist;
	}
	void setTargetH(uchar a)
	{
		targetH = a;
	}
	void setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
	{
		target[2] = red;
		target[1] = green;
		target[0] = blue;
	}

	Vec3b getTargetColor() const
	{
		return target;
	}
	int getDistance(const Vec3b &color)const
	{
		return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);
	}

	int getDistance(const uchar color)const
	{
		return abs(color-targetH);
	}

	Mat process(Mat &image)
	{
		Mat result;
		result.create(image.rows, image.cols, CV_8U);
		Mat converted;
		converted.create(image.rows, image.cols, image.type());

		cvtColor(image, converted, CV_BGR2HSV);

		Mat_<Vec3b>::const_iterator it= converted.begin<Vec3b>();
		Mat_<Vec3b>::const_iterator itend= converted.end<Vec3b>();
		Mat_<uchar>::iterator itout= result.begin<uchar>();
		
		for (; it != itend; ++it, ++itout)
		{
			//if (getDistance((*it)[0]) < mindist)
			if ((hlow<(*it)[0])&& ((*it)[0]<hhigh)&& (slow<(*it)[1]) && ((*it)[1]<shigh))
			{
				//printf("%d_%d_%d ", (*it)[0], (*it)[1], (*it)[2]);
				//Mat tmp(1, 1, CV_8UC3);
			   // tmp = *it;
				//cvtColor(tmp, tmp, CV_BGR2HSV);
				//printf("_%d ", tmp.at<Vec3b>(0,0)[0]);
				*itout = 255;
			}
			else
				*itout = 0;
		}
		
		int nl = image.rows;
		int nc = image.cols;
		//创建一个图像向量
		//std::vector<Mat> planes;
		//将一个三通道图像分离为三个单通道图像
		//split(image, planes);

		//图像是连续的吗
		/*
		if (image.isContinuous())
		{
			nc = nc * nl;
			nl = 1;  //一维数组
		}
		/*
		for (int j = 0; j < nl; j++)
		{
			uchar *data = image.ptr<uchar>(j);
			//uchar *dataout = result.ptr<uchar>(j);
			for (int i =0; i < nc; i++)
			{
				printf("%d_%d_%d ", data[3 * i], data[3 * i + 1], data[3 * i + 2]);
				//cout << data[3*i] << data[3*i + 1] << data[3*i + 2];
			}
			cout << endl;
		}
		Sleep(1000);
		*/
		return result;
	}
};


int main()
{
	// Open the video file
	// cv::VideoCapture capture("E:\\UAV Detection\\video\\video.mp4");
	// check if video successfully opened
	cv::VideoCapture capture(0);
	Colordetector cdetect;
	cdetect.setTargetColor(200,100,100);
	cdetect.setColorDistanceThreshold(1);
	cdetect.setTargetH(0);

	namedWindow("New");
	createTrackbar("H low", "New", 0, 255, h_low);
	createTrackbar("H high", "New", 0, 255, h_high);
	createTrackbar("S low", "New", 0, 255, s_low);
	createTrackbar("S high", "New", 0, 255, s_high);

	if (!capture.isOpened())
		return 1;

	// Get the frame rate
	double rate = capture.get(CV_CAP_PROP_FPS);

	bool stop(false);
	cv::Mat frame; // current video frame
	cv::namedWindow("Extracted Frame");

	// Delay between each frame
	// corresponds to video frame rate
	int delay = 1000 / rate;

	// for all frames in video
	while (!stop) {

		// read next frame if any
		if (!capture.read(frame))
			break;
		//cdetect.process(frame);
		cv::imshow("Extracted Frame", cdetect.process(frame));
		// introduce a delay
		// or press key to stop
		//if (cv::waitKey(delay)>=0)
		if (cv::waitKey(30) >= 0)
			stop = true;
	}

	// Close the video file
	capture.release();

	cv::waitKey();
}

