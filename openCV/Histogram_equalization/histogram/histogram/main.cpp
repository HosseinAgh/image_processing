#include <iostream>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;

//histogram equalization

int main() {

	int h[256]; //histogram
	for (int i = 0; i < 256; i++) {
		h[i] = 0;
	}

	Mat image = imread("pout.tif", 0); //read the image
	Mat image_out = image.clone();  //copy of original image for output image
	const int r = image.rows; //get  size().height image
	const int c = image.cols; //get size().width image
	//caculate the historam of original image
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			h[int(image.at<uchar>(i, j))] += 1;
		}
	}

	//caculate the Trasnfre function to increase inhancment
	float T[256];
	T[0] = (float)h[0] / (c*r);
	
	for (int i = 1; i < 256; i++) {
		T[i] = T[i - 1] + (float)h[i] / (c*r);
	}
	//set the output image 
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			image_out.at<uchar>(i, j) = uchar(255 * (T[int(image.at<uchar>(i, j))]));
		}
	}
	//show the original image
	namedWindow("original");
	imshow("original",image);
	//show the output image
	namedWindow("contrast");
	imshow("contrast", image_out);
	waitKey(0);

	imwrite("image.tif", image_out); // save the output image

	return 0;
}