#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat image = imread("image4.png");
	medianBlur(image, image,30);
	imshow("¤¤­È­°Ä¼", image);
	waitKey(0);
}