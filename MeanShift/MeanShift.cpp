#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>
#include <features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>
//练习2（简单调用）
using namespace std;
using namespace cv;
int main()
{
	//读取图片
	cv::Mat img1 = cv::imread("E:\\13\\img.png");
	cv::Mat img2 = cv::imread("E:\\13\\template.png");
	cv::imshow("【被查找的图像】", img1);
	cv::imshow("【模版图像】", img2);

	//创建空画布绘制匹配结果
	cv::Mat dstImg;
	dstImg.create(img1.dims, img1.size, img1.type());

	//匹配
	cv::matchTemplate(img1, img2, dstImg, 0);

	//归一化图像矩阵，可省略
	cv::normalize(dstImg, dstImg, 0, 1, 32);

	//获取最大或最小匹配系数
	//首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
	cv::Point minPoint;
	cv::Point maxPoint;
	double *minVal = 0;
	double *maxVal = 0;
	cv::minMaxLoc(dstImg, minVal, maxVal, &minPoint, &maxPoint);//找矩阵的最小位置

	//开始绘制
	cv::rectangle(img1, minPoint, cv::Point(minPoint.x + img2.cols, minPoint.y + img2.rows), cv::Scalar(0, 255, 0), 2, 8);
	cv::imshow("【匹配后的图像】", img1);
	cv::waitKey(0);
	return 0;
}