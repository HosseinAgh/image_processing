#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int Sort(int *arr, int length);
void salt_pepper(Mat img, float density);
void medfilt2(Mat img, int dim);

int main(){
	
	Mat img = imread("peppers.png", 0); //open source image
	
	//show the source image
	namedWindow("original");
	imshow("original", img);

	//save the original (rgb to gray)
	imwrite("source.png", img);

	//adding noise 
	salt_pepper(img, 0.2);

	//show image with noise
	namedWindow("image with noise");
	imshow("image with noise", img);

	//save image with noise
	imwrite("imageWithNoise.png", img);

	//median flter with dimention of window =3 (3*3)
	medfilt2(img, 3);

	//show image with noise elimination
	namedWindow("filtered Image");
	imshow("filtered Image", img);

	//save the utput image
	imwrite("filteredImage.png", img);
	
	waitKey(0);

}

// sort and return median
int Sort(int *arr, int length) {

	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			if (*(arr + j) < *(arr + i)) {
				int temp = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = temp;
			}
		}
	}
	if (length == 9)
		return *(arr + int(9 / 2));
	else if (length == 25)
		return *(arr + int(25 / 2));
}

//adding noise salt& pepper    2 argument :first img  second density of noise
//density between 0 and 1    0 <= density <= 1
void salt_pepper(Mat img, float density) {
	int x_dim = img.rows;
	int y_dim = img.cols;
	int n = x_dim * y_dim * density;

	for (int i = 0; i < n; i++) {
		int x = rand() % x_dim;
		int y = rand() % y_dim;
		int num = rand() % 100;

		if (num > 50) {
			img.at<uchar>(x, y) = 0;
		}
		else {
			img.at<uchar>(x, y) = 255;
		}
	}
}
//median filter to noise elimination
//2 argument : frist img second dimention of window for example 3(3*3) or 5(5*5) 
void medfilt2(Mat img, int dim) {

	if (dim == 3) {
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				if (i == 0) {
					if (j == 0) {
						img.at<uchar>(i, j) = 0;
					}
					else if (j == img.cols - 1) {
						img.at<uchar>(i, j) = 0;
					}
					else {
						int num[9] = { 0 , 0 , 0 ,
							img.at<uchar>(i ,j - 1),img.at<uchar>(i ,j),img.at<uchar>(i ,j + 1),
							img.at<uchar>(i + 1 ,j - 1),img.at<uchar>(i + 1 ,j),img.at<uchar>(i + 1 ,j + 1) };
						img.at<uchar>(i, j) = uchar(Sort(num, 9));
					}
				}
				else if (i == img.rows - 1) {
					if (j == 0) {
						img.at<uchar>(i, j) = 0;
					}
					else if (j == img.cols - 1) {
						img.at<uchar>(i, j) = 0;
					}
					else {
						int num[9] = { img.at<uchar>(i - 1,j - 1),img.at<uchar>(i - 1,j),img.at<uchar>(i - 1,j + 1),
							img.at<uchar>(i ,j - 1),img.at<uchar>(i ,j),img.at<uchar>(i ,j + 1),
							0 , 0 , 0 };
						img.at<uchar>(i, j) = uchar(Sort(num, 9));
					}
				}
				else if (j == 0) {
					int num[9] = { 0,img.at<uchar>(i - 1,j),img.at<uchar>(i - 1,j + 1),
						0,img.at<uchar>(i ,j),img.at<uchar>(i ,j + 1),
						0,img.at<uchar>(i + 1 ,j),img.at<uchar>(i + 1 ,j + 1) };
					img.at<uchar>(i, j) = uchar(Sort(num, 9));
				}
				else if (j == img.cols - 1) {
					int num[9] = { img.at<uchar>(i - 1,j - 1),img.at<uchar>(i - 1,j),0,
						img.at<uchar>(i ,j - 1),img.at<uchar>(i ,j),0,
						img.at<uchar>(i + 1 ,j - 1),img.at<uchar>(i + 1 ,j),0 };
					img.at<uchar>(i, j) = uchar(Sort(num, 9));
				}
				else {
					int num[9] = { img.at<uchar>(i - 1,j - 1),img.at<uchar>(i - 1,j),img.at<uchar>(i - 1,j + 1),
						img.at<uchar>(i ,j - 1),img.at<uchar>(i ,j),img.at<uchar>(i ,j + 1),
						img.at<uchar>(i + 1 ,j - 1),img.at<uchar>(i + 1 ,j),img.at<uchar>(i + 1 ,j + 1) };
					img.at<uchar>(i, j) = uchar(Sort(num, 9));
				}
			}
		}
	}
	//this in not completed
	if (dim == 5) {
		for (int i = 2; i < img.rows - 2; i++) {
			for (int j = 2; j < img.cols - 2; j++) {
				int num[25] = { img.at<uchar>(i - 2,j - 2),img.at<uchar>(i - 2,j - 1),img.at<uchar>(i - 2,j),img.at<uchar>(i - 2,j + 1),img.at<uchar>(i - 2,j + 2),
					img.at<uchar>(i - 1,j - 2),img.at<uchar>(i - 1,j - 1),img.at<uchar>(i - 1,j),img.at<uchar>(i - 1,j + 1),img.at<uchar>(i - 1,j + 2),
					img.at<uchar>(i    ,j - 2),img.at<uchar>(i    ,j - 1),img.at<uchar>(i    ,j),img.at<uchar>(i    ,j + 1),img.at<uchar>(i    ,j + 2),
					img.at<uchar>(i + 1,j - 2),img.at<uchar>(i + 1,j - 1),img.at<uchar>(i + 1,j),img.at<uchar>(i + 1,j + 1),img.at<uchar>(i + 1,j + 2),
					img.at<uchar>(i + 2,j - 2),img.at<uchar>(i + 2,j - 1),img.at<uchar>(i + 2,j),img.at<uchar>(i + 2,j + 1),img.at<uchar>(i + 2,j + 2) };
				img.at<uchar>(i, j) = uchar(Sort(num, 25));
			}
		}
	}
}
