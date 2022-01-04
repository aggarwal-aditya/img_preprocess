#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace cv;

cv::Mat grayedi(string s)
{
    Mat graymat=imread(s,0);
    return graymat;
}

cv::Mat smoothen(string s){
    Mat smooth=imread(s,1);
    Mat img =imread(s,1);
    for ( int i = 1; i < 31; i = i + 2 )
    {
    	bilateralFilter ( img, smooth, i, i*2, i/2 );
       
    }
  return smooth;
}

cv::Mat thresh(string s){
	Mat mod=imread(s,1);
	Mat img=imread(s,1);
	long long cols=img.cols;
	//cout<<cols<<endl;
	long  rows=img.rows;
	  for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols*3; c++){
            mod.at<uint8_t>(r,c)=255-img.at<uint8_t>(r,c);
        }
    }
    return mod;
}

int main()
{
	string s; cin>>s;
	Mat original = imread(s, 1);
   while(original.empty()){
    	if (original.empty()){
        cout << "No such Image found,please try again"<< endl;
    	}
    	cin>>s;
    	 original = imread(s, IMREAD_GRAYSCALE);
    }
    Mat mod=imread(s,1);
//    mod=grayedi(s);
  //  mod=smoothen(s);
   // mod=thresh(s);
    //imshow("original",original);
    imwrite("new.jpg",mod);
    imshow("new", mod);
     waitKey(0);
}
