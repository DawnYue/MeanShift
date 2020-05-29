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
//练习2
using namespace std;
using namespace cv;
int templateMatching_demo()
{
	VideoCapture cap;
	//cap(0)表示打开本机的第一个摄像头
	cap.open(0);//cap(“D:\\1.avi”)本地视频

	if (!cap.isOpened())
	{
		std::cout << "fail to open video...\n" << std::endl;
		return -1;
	}

	Mat frame;
	Mat tempMat;
	Mat resultMat;
	Mat refMat;
	Mat dispMat;
	int cnt = 0;
	while (1) {//延时，否则黑屏
		cap >> frame;
		if (frame.empty())break;
		if (cnt == 10) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
			break;
		}
		cnt++;
		waitKey(30);
	}
	while (1) {

		cap >> frame;
		

		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);

		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal; double maxVal; Point minLoc; Point maxLoc;
		Point matchLoc;

		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		frame.copyTo(dispMat);
		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);

		cnt++;
		imshow("template", refMat);
		imshow("dispMat", dispMat);
		waitKey(30);
	}
	return 0;
}

int img()
{
	cv::Mat img1 = cv::imread("E:\\13\\img.png");
	Mat tempMat;
	Mat resultMat;
	Mat dispMat;
	int cnt = 0;

	/*/在被查找的图像中选择模板
    Mat refMat;
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(img1, true);
			tempMat = img1(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();}
*/
		cv::Mat refMat = cv::imread("E:\\13\\template.png");

		int match_method = 0;
		matchTemplate(img1, refMat, resultMat, match_method);

		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal; double maxVal; Point minLoc; Point maxLoc;
		Point matchLoc;

		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		img1.copyTo(dispMat);
		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);

		imshow("template", refMat);
		imshow("dispMat", dispMat);
		waitKey(0);

	return 0;
}
int main()
{

	templateMatching_demo();//视频匹配
	//img();//图像匹配
}