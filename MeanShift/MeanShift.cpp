//练习1
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include <vector>

using namespace cv;
using namespace std;
	

int main(){
	Mat cell = imread("E:\\13\\template.png");
	Mat src = imread("E:\\13\\img.png");
	float  ref_hist[1000000] = {0};


	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	cvtColor(cell, cell, CV_BGR2GRAY);

	float scale = 360 / 8;
	int nX = gray.cols / cell.cols;
	int nY = gray.rows / cell.rows;

	Mat gx, gy;
	Mat mag, angle;
	cv::Sobel(gray, gx, CV_32F, 1, 0, 1);
	cv::Sobel(gray, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	//draw rectangle  
	cv::Rect rect;

	rect.height = cell.cols;
	rect.width = cell.rows;

	int ref1 = 0;
	int ref2 = 0;
	int hog1 = 0;
	int hog2 = 0;
	int c = 0;
	//遍历所有
	for (int a = 0; ((a - 1)*nY) <= gray.rows; a++) {
		for (int b = 0; ((b - 1)*nX) <= gray.cols; b++) {

			//遍历其中一个cell
			for (int j = (a*nY); j <= (a*nY + nY); j++) {
				uchar* mag_row_ptr = mag.ptr <uchar>(j);// 第j行的头指针
				uchar* angle_row_ptr = angle.ptr <uchar>(j);// 第j行的头指针
				for (int i = (b*nX); i <= (b*nX + nX); i++) {
					// 访问位于 x,y 处的像素
					uchar* mag_ptr = &mag_row_ptr[i]; //  指向待访问的像素数据
					uchar* angle_ptr = &angle_row_ptr[i]; //  指向待访问的像素数据

					float data_mag = mag_ptr[0]; // data为I(x,y)第0个通道的值    	梯度
					float data_angle = angle_ptr[0]; // data为I(x,y)第0个通道的值   角度
					ref2 = ref1;
					hog2 = hog1;
					for (int i = 0; i <= 8; i++)
					{
						if (data_angle <= (i*scale))
						{
							int d = i + c;
							ref_hist[d] = ref_hist[d] + data_mag;//遍历像素
							ref1 = ref1+ref_hist[d];
							//cout << "histgram" << ref_hist[d] << endl;
						}
					}							
				}
			}
			hog1 = ref1 - ref2;

			if (hog1 <= hog2) {
			rect.x = a;
			rect.y = b;
			}	
			c = c + 8;
		}
	}



	rectangle(src, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	imshow("src", src);
	waitKey(0);//等待用户按键
	return 0;

}