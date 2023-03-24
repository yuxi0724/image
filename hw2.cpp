#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{
	Mat img = imread("fig.jpg", IMREAD_GRAYSCALE);	//讀灰階照片
	if (img.empty())	//判斷是否有照片
		return -1;
	Mat img_inv = ~img;	
	GaussianBlur(img, img, Size(3, 3), 0, 0);
	Mat qradX, qradY, sketch;
	Sobel(img, qradX, CV_16S, 1, 0, 3);
	Sobel(img, qradY, CV_16S, 0, 1, 3);
	convertScaleAbs(qradX, qradX);
	convertScaleAbs(qradY, qradY);
	Mat dat;
	addWeighted(qradX, 0.5, qradY, 0.5, 0, dat);
	GaussianBlur(img_inv, img_inv, Size(15, 15), 50, 50);
	divide(img, 255-img_inv, sketch, 280);
	
	imshow("dat", dat);	//圖片展示
	imshow("Img", img);
	imshow("sketch",sketch);
	waitKey(0);	//等待
}