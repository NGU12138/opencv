#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
void salt(cv::Mat image, int n)
{
	for (int k = 0; k < n; k++)
	{
		int salt_row = std::rand() % image.rows;
		int salt_col = std::rand() % image.cols;
		//根据灰度图像和彩色图像进行不同的处理
		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(salt_row, salt_col) = 255;

		}
		else
		{
			image.at<cv::Vec3b>(salt_row, salt_col)[0] = 255;
			image.at<cv::Vec3b>(salt_row, salt_col)[1] = 255;
			image.at<cv::Vec3b>(salt_row, salt_col)[2] = 255;
		}
	}
}
void main()
{
	cv::namedWindow("image1");
	cv::Mat image = cv::imread("E:\\test\\opencv\\boldt.jpg");
	salt(image, 3000);
	cv::imshow("image1",image);
	cv::waitKey(0);
}
