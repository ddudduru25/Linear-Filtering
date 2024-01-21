#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp" // Mat class와 각종 data structure 및 산술 루틴을 포함하는 헤더
#include "opencv2/highgui/highgui.hpp" // GUI와 관련된 요소를 포함하는 헤더(imshow 등)
#include "opencv2/imgproc/imgproc.hpp" // 각종 이미지 처리 함수를 포함하는 헤더
using namespace cv;
using namespace std;

void ex1();
void ex2();
void ex4();
void ex5();
Mat myCopy(Mat srcImg); //1
int myKernelConv3x3(uchar* arr, int kernel[][3], int x, int y, int width, int height);
Mat myGaussianFilter(Mat srcImg);
Mat mySobelFilter(Mat srcImg);
Mat mySampling(Mat srcImg);
vector<Mat> myGaussainPyramid(Mat srcImg); //4
vector<Mat> myLaplacianPyramid(Mat srcImg); //5

int main() {
	ex5();
	return 0;
}void ex1() {
	Mat src_img = imread("gear.jpg", 0);
	Mat dst_img = myCopy(src_img);

	imshow("Source", src_img);
	imshow("Copied", dst_img);
	waitKey(0);
	cvDestroyAllWindows();
}

void ex2() {
	Mat src_img = imread("gear.jpg", 0);
	int width = src_img.cols;
	int height = src_img.rows;
	int kernel[3][3] = { 1, 2, 1,
						2, 4, 2,
						1, 2, 1 };
	Mat dst_img(src_img.size(), CV_8UC1);
	uchar* srcData = src_img.data;
	uchar* dstData = src_img.data;
}

void ex4() {
	Mat src_img = imread("gear.jpg", 0);
	vector<Mat> vec_result = myGaussainPyramid(src_img);
	imshow("0", vec_result[0]);
	imshow("0", vec_result[1]);
	imshow("0", vec_result[2]);
	imshow("0", vec_result[3]);
	imshow("0", vec_result[4]);

	waitKey(0);
	destroyAllWindows();
	
}

void ex5() {
	Mat src_img = imread("landing.jpg", 0);
	Mat dst_img;

	vector<Mat> vecLap = myLaplacianPyramid(src_img);
	reverse(vecLap.begin(), vecLap.end());

	for (int i = 0; i < vecLap.size(); i++) {
		if (i == 0) {
			dst_img = vecLap[i];
		}
		else {
			resize(dst_img, dst_img, vecLap[i].size());
			dst_img = dst_img + vecLap[i] - 128;
		}

		string fname = "ex5_lap_pyr" + to_string(i) + ".jpg";
		imwrite(fname, dst_img);
		imshow(fname, dst_img);
		waitKey(0);
		destroyAllWindows();
	}
	
}

Mat myCopy(Mat srcImg) {
	int width = srcImg.cols;
	int height = srcImg.rows;
	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = srcData[y * width + x];
		}
	}

	return dstImg;
}

int myKernelConv3x3(uchar* arr, int kernel[][3], int x, int y, int width, int height) {
	int sum = 0;
	int sumKernel = 0;

	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + 1) < width) {
				sum += arr[(y + j) * width + (x + i)] * kernel[i + 1][j + 1];
				sumKernel += kernel[i + 1][j + 1];
			}
		}
	}

	if (sumKernel != 0) return sum / sumKernel;
	else return sum;
}

Mat myGaussianFilter(Mat srcImg) {
	int width = srcImg.cols;
	int height = srcImg.rows;
	int kernel[3][3] = { 1, 2, 1,
						2, 4, 2,
						1, 2, 1 };
	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = myKernelConv3x3(srcData, kernel, x, y, width, height);
		}
	}
	return dstImg;
}

Mat mySobelFilter(Mat srcImg) {
	int kernelX[3][3] = { -1, 0, 1,
						-2, 0, 2,
						-1, 0, 1};
	int kernelY[3][3] = { -1, -2, -1,
						0, 0, 0,
						1, 2, 1 };
	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;
	int width = srcImg.cols;
	int height = srcImg.rows;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = (abs(myKernelConv3x3(srcData, kernelX, x, y, width, height)) +
				abs(myKernelConv3x3(srcData, kernelY, x, y, width, height))) / 2;
		}
	}

	return dstImg;
}

Mat mySampling(Mat srcImg) {
	int width = srcImg.cols / 2;
	int height = srcImg.rows / 2;
	Mat dstImg(height, width, CV_8UC1);

	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = srcData[(y * 2) * (width * 2) + (x * 2)];
		}
	}

	return dstImg;

}

vector<Mat> myGaussainPyramid(Mat srcImg) {
	vector<Mat> Vec;
	Vec.push_back(srcImg);
	for (int i = 0; i < 4; i++) {
		srcImg = mySampling(srcImg);
		srcImg = myGaussianFilter(srcImg);
	}

	return Vec;
}

vector<Mat> myLaplacianPyramid(Mat srcImg) {
	vector<Mat>Vec;
	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			Mat highImg = srcImg;
			srcImg = mySampling(srcImg);
			srcImg = myGaussianFilter(srcImg);
		}
		else {
			Vec.push_back(srcImg);
		}
	}

	return Vec;
}