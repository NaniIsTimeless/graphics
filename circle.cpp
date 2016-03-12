#include <stdio.h>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void drawpixel(Mat& m,int x,int y,Vec3b color){
	m.at<Vec3b>(x,y) = color;
}

void circlepoints(Mat& m,Point p,int x,int y,Vec3b color){
	int x1 = p.x, y1 = p.y;
	drawpixel(m,x+x1,y+y1,color);drawpixel(m,y+x1,x+y1,color);
	drawpixel(m,-x+x1,y+y1,color);drawpixel(m,y+x1,-x+y1,color);
	drawpixel(m,x+x1,-y+y1,color);drawpixel(m,-y+x1,x+y1,color);
	drawpixel(m,-x+x1,-y+y1,color);drawpixel(m,-y+x1,-x+y1,color);
}

void MidPointCircle(Mat& m,Point center,int r,Vec3b color){
	int x = 0, y = r;
	cout << x << " " << y << endl;
	cout << center.x << " " << center.y << endl;
	double d = 1.25 - r;
	circlepoints(m,center,x,y,color);
	while(x <= y){
		if(d < 0){
			d += 2 * x + 3;
		}else{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		circlepoints(m,center,x,y,color);
	}
}

int main(){ 
	Mat m(600, 800, CV_8UC3, Scalar(255, 255, 255)); 
	MidPointCircle(m,Point(300,400),200,Vec3b(0,0,255));
	imshow("Image", m);
	cvWaitKey();
	return 0;
}