#include<iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include<vector>


using namespace cv;
using namespace std;

void Detection(Mat img)
{
	blur(img, img, Size(3, 3));
	resize(img, img, Size(img.cols / 5, img.rows / 5), 0, 0, INTER_LINEAR);

	Mat hsv;
	cvtColor(img, hsv, CV_BGR2HSV);

	Mat bw;
	inRange(hsv, Scalar(0, 50, 70), Scalar(20, 150, 255), bw);

	Mat red(img.size(), CV_8UC3, Scalar(255, 0, 0));

	Mat result;
	bitwise_and(red, red, result,bw);	//»Pmask¦X¨Ö

	img += result;

	imshow("src", img);
	imshow("hsv", hsv);
	imshow("dst", bw);
	waitKey(0);
}
int main()
{
	Mat img1 = imread("img1.jpg");
	if (img1.empty())
		return -1;
	Mat img2 = imread("img2.jpg");
	if (img2.empty())
		return -1;
	Mat img3 = imread("img3.jpg");
	if (img3.empty())
		return -1;
	Detection(img1);
	Detection(img2);
	Detection(img3);
	
}