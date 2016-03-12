#include <stdio.h>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const Vec3b BLACK = Vec3b(0,0,0);
const Vec3b RED = Vec3b(0,0,255);
const Vec3b GREEN = Vec3b(0,255,0);

class MyBoundaryFill
{
public:
	MyBoundaryFill(Mat m){
		this->m = m;
	};
	void drawpixel(int x,int y,Vec3b color){
		m.at<Vec3b>(x,y) = color;
	}
	Vec3b getpixel(Point p){
		return m.at<Vec3b>(p.x,p.y);
	}
	bool isSameColor(Point p1,Vec3b colorP2){
		Vec3b colorP1 = getpixel(p1);
		return ( (((int)colorP1[0]) == ((int)colorP2[0])) && 
				(((int)colorP1[1]) == ((int)colorP2[1])) && 
				(((int)colorP1[2]) == ((int)colorP2[2])) );
	}
	void BoundaryFill4(Point p,Vec3b boundaryColor,Vec3b newColor){
		if( (!isSameColor(p,boundaryColor)) && 
			(!isSameColor(p,newColor)) )  {
			drawpixel(p.x,p.y,newColor);
			int x = p.x, y = p.y;
			BoundaryFill4(Point(x,y+1),boundaryColor,newColor);
			BoundaryFill4(Point(x,y-1),boundaryColor,newColor);
			BoundaryFill4(Point(x-1,y),boundaryColor,newColor);
			BoundaryFill4(Point(x+1,y),boundaryColor,newColor);
			
		}
	}
	Mat m;
};
void drawPixel(Mat& m,int x,int y,Vec3b color){
	m.at<Vec3b>(x,y) = color;
}
void drawline(Mat& m,Point p1,Point p2,Vec3b color){
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int ux = ((dx > 0) ? 1 : -1);
	int uy = ((dy > 0) ? 1 : -1);
	int x = p1.x, y = p1.y;
	int eps = 0;

	dx = abs(dx); dy = abs(dy);
	if(dx > dy){
		for(x = p1.x; x != p2.x + ux; x += ux){
			drawPixel(m,x,y,color);
			eps += dy;
			if((eps << 1) >= dx){
				y += uy;
				eps -= dx;
			}
		}
	}else{
		for(y = p1.y; y != p2.y + uy; y += uy){
			drawPixel(m,x,y,color);
			eps += dx;
			if((eps << 1) >= dy){
				x += ux;
				eps -= dy;
			}
		}
	}
}

void drawBoundary(Mat& m){
	drawline(m,Point(100,100),Point(100,300),BLACK);
	drawline(m,Point(100,100),Point(500,100),BLACK);
	drawline(m,Point(500,100),Point(500,300),BLACK);
	drawline(m,Point(100,300),Point(500,300),BLACK);

	drawline(m,Point(100,600),Point(500,500),BLACK);
	drawline(m,Point(100,600),Point(500,700),BLACK);
	drawline(m,Point(500,500),Point(500,700),BLACK);
}

int main(){ 
	Mat m(600, 800, CV_8UC3, Scalar(255, 255, 255)); 
	drawBoundary(m);
	MyBoundaryFill myBF(m);
	cout << myBF.isSameColor(Point(100,300),BLACK) << endl;
	myBF.BoundaryFill4(Point(300,200),BLACK,RED);
	myBF.BoundaryFill4(Point(200,600),BLACK,GREEN);
	imshow("Image", m);
	cvWaitKey();
	return 0;
}