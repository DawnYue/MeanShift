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
//课前准备
//https ://blog.csdn.net/lwx309025167/article/details/78434930
using namespace std;
using namespace cv;
//https://blog.csdn.net/qq_41007606/article/details/81870607
void main()
{
	//步骤一：读取图片
	cv::Mat img1 = cv::imread("E:\\1\\1.png");
	cv::Mat img2 = cv::imread("E:\\1\\1.png");
	cv::imshow("【被查找的图像】", img1);
	cv::imshow("【模版图像】", img2);

	//步骤二：创建一个空画布用来绘制匹配结果
	cv::Mat dstImg;
	dstImg.create(img1.dims, img1.size, img1.type());
	cv::imshow("createImg", dstImg);

	//步骤三：匹配，最后一个参数为匹配方式，共有6种，详细请查阅函数介绍
	cv::matchTemplate(img1, img2, dstImg, 0);

	//步骤四：归一化图像矩阵，可省略
	cv::normalize(dstImg, dstImg, 0, 1, 32);

	//步骤五：获取最大或最小匹配系数
	//首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
	//找矩阵的最小位置的函数是 minMaxLoc函数
	cv::Point minPoint;
	cv::Point maxPoint;
	double *minVal = 0;
	double *maxVal = 0;
	cv::minMaxLoc(dstImg, minVal, maxVal, &minPoint, &maxPoint);

	//步骤六：开始正式绘制
	cv::rectangle(img1, minPoint, cv::Point(minPoint.x + img2.cols, minPoint.y + img2.rows), cv::Scalar(0, 255, 0), 2, 8);
	cv::imshow("【匹配后的图像】", img1);
	cv::rectangle(dstImg, minPoint, cv::Point(minPoint.x + img2.cols, minPoint.y + img2.rows), cv::Scalar(0, 0, 0), 3, 8);
	cv::imshow("【匹配后的计算过程图像】", dstImg);
	cv::waitKey(0);
}
/*
Mat src, dst;
int spr = 10, scr = 10, maxPryLevel = 3;
//const Scalar& colorDiff=Scalar::all(1);


void meanshift_seg(int, void *)
{
//调用meanshift图像金字塔进行分割
pyrMeanShiftFiltering(src, dst, spr,scr, maxPryLevel);
RNG rng = theRNG();
Mat mask(dst.rows + 2, dst.cols + 2, CV_8UC1, Scalar::all(0));
for (int i = 0; i<dst.rows; i++)    //opencv图像等矩阵也是基于0索引的
for (int j = 0; j<dst.cols; j++)
if (mask.at<uchar>(i + 1, j + 1) == 0)
{
Scalar newcolor(rng(256), rng(256), rng(256));
floodFill(dst, mask, Point(j, i), newcolor, 0, Scalar::all(1), Scalar::all(1));//注意这里的 Point(j, i)的位置不要搞错，否则滑动条将不能正常化动 

//原因是Point中的参数为x,y，对应到图片的矩阵里是列、行，而这段代码中遍历像素点时用的i,j，表示 //需要调换行、列，因此两者正好相反， 对于Mat的对象src，src.at(y.x)与src.at(Point(x,y))是等价的

//        floodFill(dst,mask,Point(i,j),newcolor,0,colorDiff,colorDiff);
}
imshow("dst", dst);
}






int main(int argc, uchar* argv[])
{


namedWindow("src", WINDOW_AUTOSIZE);
namedWindow("dst", WINDOW_AUTOSIZE);


src = imread("stuff.jpg");
CV_Assert(!src.empty());


spr = 24;
scr = 30;
maxPryLevel = 3;


//虽然createTrackbar函数的参数onChange函数要求其2个参数形式为onChange(int,void*)
//但是这里是系统响应函数，在使用createTrackbar函数时，其调用的函数可以不用写参数，甚至
//括号都不用写，但是其调用函数的实现过程中还是需要满足(int,void*)2个参数类型
createTrackbar("spatialRad", "dst", &spr, 80, meanshift_seg);
createTrackbar("colorRad", "dst", &scr, 80, meanshift_seg);
createTrackbar("maxPryLevel", "dst", &maxPryLevel, 5, meanshift_seg);


//    meanshift_seg(0,0);


imshow("src", src);
//char c=(char)waitKey();
//if(27==c)
//return 0;
imshow("dst", src);
waitKey();//无限等待用户交互响应
//    while(1);//这里不能用while(1)的原因是需要等待用户的交互，而while(1)没有该功能。虽然2者都有无限等待的作用。
return 0;
}



*/