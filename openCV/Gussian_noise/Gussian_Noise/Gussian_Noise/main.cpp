#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;

float avg(int* arr, int length); // calculate the mean of window 
Mat Gussian_noise(Mat img, float density); //adding gussian noise with specefic density
void avrFilter(Mat img, int dim); //avreging filter to noise elimination

int main() {

	Mat img = imread("peppers.png", 0); //read the image
	imshow("src", img); //show the original image
	normalize(img, img, 0, 1.0, CV_MINMAX, CV_64F); //normalize the image each picture value beetween 0 and 1
	img = Gussian_noise(img, 0.05);  //adding gussian noise. density = 0.2
	imshow("guss", img); //show image wwith noise
	avrFilter(img, 3); //averagin filter to noise elimination with window dimention = 3(3*3)

	imshow("filtered", img); //show the output after the filtering
	waitKey(0);
}

float avg(double* arr, int length) {
	float sum = 0;
	for (int i = 0; i < length; i++) {
		sum = sum + *(arr + i);
	}
	return  sum / length;
}

Mat Gussian_noise(Mat img, float density) {

	Mat noise = Mat(img.size(), CV_64F);
	normalize(img, img, 0,1.0, CV_MINMAX,CV_64F);
	randn(noise, 0, density);
	img = noise + img;
	//normalize(img, img, 0, 1.0, CV_MINMAX, CV_64F);
	return img;
}

void avrFilter(Mat img, int dim) {
	cout << img.rows << endl << img.cols << endl;
		for (int i = 1; i < img.rows - 1; i++) {
			for (int j = 1; j < img.cols - 1; j++) {
				double num[9] = {	img.at<double>(i - 1,j - 1) , img.at<double>(i - 1,j) , img.at<double>(i - 1,j + 1),
								img.at<double>(i ,j - 1)    , img.at<double>(i ,j)    , img.at<double>(i ,j + 1),
								img.at<double>(i + 1,j - 1), img.at<double>(i + 1,j )  , img.at<double>(i + 1,j + 1) };
				img.at<double>(i, j) = avg(num, 9);
		}
	}
}