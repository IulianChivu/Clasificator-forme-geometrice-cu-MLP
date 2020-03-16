#include<iostream>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

int main(){

	Mat img;
	img = imread("/home/iulian/Desktop/Proiect2/shapes/circles/drawing(1).png");
	
	//
	Vec3b p;
	int blue[img.rows][img.cols],
	green[img.rows][img.cols];
	//red[img.rows][img.cols];	
	float red[img.rows][img.cols];

	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			p = img.at<Vec3b>(i,j);
			blue[i][j] = p.val[0];
			//if(blue[i][j] >= 170) blue[i][j] = 0;
			//else blue[i][j] = 1;

            		green[i][j] = p.val[1];
			if(green[i][j] >= 170) green[i][j] = 0;
			else green[i][j] = 1;

            		red[i][j] = (float)p.val[2]/255;
			//if(red[i][j] == 255) red[i][j] = 0;
			//else red[i][j] = 1;
			//cout<<p<<" ";
		}
		//cout<<endl;
	}

	cout<<"blue:"<<endl;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			cout<<blue[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<"\ngreen:"<<endl;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			cout<<green[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"\nred:"<<endl;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			cout<<setprecision(2)<<red[i][j]<<" ";
		}
		cout<<endl;
	}


	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey();

	return 0;
}
