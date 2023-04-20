#include <iostream>
#include <opencv2/opencv.hpp>
#include<cmath>
using namespace std;
using namespace cv;

void DFT(Mat input, Mat& output, Mat& transeform)
{
	//擴展圖像矩陣
	int r = getOptimalDFTSize(input.rows);
	int c = getOptimalDFTSize(input.cols);
	copyMakeBorder(input, input, 0, r - input.rows, 0, c - input.cols, BORDER_CONSTANT, Scalar::all(0));	//將圖像擴大
	
	Mat P[] = { Mat_<float>(input),Mat::zeros(input.size(),CV_32F) };	//儲存複數
	
	merge(P, 2, transeform);
	dft(transeform, transeform);//傅立葉轉換

	Mat angle;

	//計算
	split(transeform, P);	//分開實部跟虛部
	magnitude(P[0], P[1], output);	//計算幅度
	phase(P[0], P[1], angle);

	//轉換成較小數級
	output += Scalar(1);	//防止log0
	log(output, output);
	normalize(output, output, 0, 1, NORM_MINMAX);	

	//重新分布圖像
	output = output(Rect(0, 0, output.cols & -2, output.rows & -2));

	//重新排列傅立葉，使原點位於圖像中心
	int cx = output.cols / 2;
	int cy = output.rows / 2;
	Mat q0(output, Rect(0, 0, cx, cy));	//左上
	Mat q1(output, Rect(cx, 0, cx, cy));	//右上
	Mat q2(output, Rect(0, cy, cx, cy));	//右下
	Mat q3(output, Rect(cx, cy, cx, cy));	//左下

	Mat tmp;
	q0.copyTo(tmp);q3.copyTo(q0);tmp.copyTo(q3);	//左上<->左下
	q1.copyTo(tmp);	q2.copyTo(q1);tmp.copyTo(q2);	//右上<->右下
	
	normalize(angle, angle, 0, 255, NORM_MINMAX);	//方便顯示
	angle.convertTo(angle, CV_8U);
	imshow("phase", angle);
}
int main()
{
	Mat img, img_ouput, transform, IDFT;
	img = imread("image3.png", IMREAD_GRAYSCALE);
	if (img.empty())
		return -1;
	imshow("source",img);
	DFT(img, img_ouput,transform);
	imshow("spectrum", img_ouput);

	//逆傅立葉轉換
	idft(transform, IDFT, DFT_SCALE | DFT_REAL_OUTPUT);
	normalize(IDFT, IDFT, 0, 255, NORM_MINMAX);
	IDFT.convertTo(IDFT, CV_8U);
	imshow("IDFT", IDFT);

	waitKey(0);
}