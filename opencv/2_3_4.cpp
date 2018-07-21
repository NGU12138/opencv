#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
//using namespace cv;
void colorreduce(const cv::Mat &input_image, cv::Mat  output_image, int div = 64)
{
	//output_image.create(input_image.size(), input_image.type());
	int in_row = input_image.rows;
	int num = input_image.cols*input_image.channels();
	for (int i = 0; i < in_row; i++)
	{
		const uchar * in_data = input_image.ptr<uchar>(i);
		uchar * out_data = output_image.ptr<uchar>(i);
		for (int j = 0; j < num; j++)
		{
			out_data[j] = in_data[j] / div * div + div / 2;
		}
	}

}
/*
void main()
{
	cv::namedWindow("Image_gao");
	cv::Mat image=cv::imread("E:\\test\\opencv\\boldt.jpg");
	cv::Mat image2;
	image2.create(image.size(), image.type());
	colorreduce(image, image2);
	cv::imshow("Image_gao", image2);
	cv::waitKey(0);
}
*/