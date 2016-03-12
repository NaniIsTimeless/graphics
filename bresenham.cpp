#include <stdio.h>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void drawpixel(Mat& m,int x,int y,Vec3b color){
	m.at<Vec3b>(x,y) = color;
}
void Bresenhamline(Mat& m,Point p1,Point p2,Vec3b color){
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int ux = ((dx > 0) ? 1 : -1);
	int uy = ((dy > 0) ? 1 : -1);
	int x = p1.x, y = p1.y;
	int eps = 0;

	dx = abs(dx); dy = abs(dy);
	if(dx > dy){
		for(x = p1.x; x != p2.x + ux; x += ux){
			drawpixel(m,x,y,color);
			eps += dy;
			if((eps << 1) >= dx){
				y += uy;
				eps -= dx;
			}
		}
	}else{
		for(y = p1.y; y != p2.y + uy; y += uy){
			drawpixel(m,x,y,color);
			eps += dx;
			if((eps << 1) >= dy){
				x += ux;
				eps -= dy;
			}
		}
	}


}
void draw(Mat& m){
	Point p1,p2;
	p1.x = 300;p1.y = 400;
	
	p2.x = 100;
	for(int i = 0;i <= 8;i++){
		p2.y = 100 * i;
		Bresenhamline(m,p1,p2,Vec3b(0,0,255));
	}

	p2.x = 500;
	for(int i = 0;i <= 8;i++){
		p2.y = 100 * i;
		Bresenhamline(m,p1,p2,Vec3b(255,0,255));
	}

	p2.x = 300;
	p2.y = 100;
	Bresenhamline(m,p1,p2,Vec3b(0,255,0));
	p2.y = 700;
	Bresenhamline(m,p1,p2,Vec3b(255,0,0));

}

int main(){ 
	Mat m(600, 800, CV_8UC3, Scalar(255, 255, 255)); 
	draw(m);
    imshow("Image", m);
    cvWaitKey();
    return 0;
}