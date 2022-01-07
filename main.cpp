#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;


int erosion_elem = 2;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void *);

void Dilation(int, void *);


cv::Mat erosion(int, void *, cv::Mat img) {

    int erosion_type = 0;
    if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
    else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
    else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
    Mat element = getStructuringElement(erosion_type,
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        Point(erosion_size, erosion_size));
    Mat src = img;
    erode(img, src, element);
    return src;
}

cv::Mat grayedi(string s) {
    Mat graymat = imread(s, 0);
    return graymat;
}

cv::Mat smoothen(cv::Mat img) {
    Mat smooth = img;
    cvtColor(smooth, smooth, COLOR_GRAY2RGB);
    for (int i = 1; i < 31; i = i + 2) {
        bilateralFilter(img, smooth, i, i * 2, i / 2);

    }
    return smooth;
}

cv::Mat invert(string s) {
    Mat mod = imread(s, 1);
    Mat img = imread(s, 1);
    long long cols = img.cols;
    //cout<<cols<<endl;
    long rows = img.rows;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols * 3; c++) {
            mod.at<uint8_t>(r, c) = 255 - img.at<uint8_t>(r, c);
        }
    }
    return mod;
}


cv::Mat thresh(string s) {
    Mat mod = imread(s, 1);
    Mat img = imread(s, 1);
    long long cols = img.cols;
    //cout<<cols<<endl;
    long rows = img.rows;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (img.at<uint8_t>(r, c) < 188)
                mod.at<uint8_t>(r, c) = 0;

        }
    }
    return mod;
}


cv::Mat inc_bright(cv::Mat img) {
    Mat mod = img;
    //Mat img = imread(s, 1);
    long long cols = img.cols;
    long rows = img.rows;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int x = 1.5 * img.at<uint8_t>(r, c);
            x = min(x, 255);
            mod.at<uint8_t>(r, c) = x;
        }
    }
    return mod;
}










cv::Mat adap_thresh(cv::Mat img){
    Mat mod=img;
    adaptiveThreshold(img,mod,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,7,7);
    return mod;
    
}






void disp(cv::Mat t){
    imshow("filtered",t);
}


int main() {
    printf("Please Enter the path to image\n");
    string s;
    cin >> s;
    Mat original = imread(s, 0);
    while (original.empty()) {
        if (original.empty()) {
            cout << "No such Image found,please try again" << endl;
        }
        cin >> s;
        original = imread(s, 0);
    }
    Mat mod=imread(s,0);
    mod=erosion(0,0,original);
    mod=inc_bright(mod);
    mod=smoothen(mod);
    mod=adap_thresh(mod);
    //imshow("original",original);
    imshow("new", mod);
    printf("\nYour image has been saved in PWD by the name filtered.jpg\n");
    imwrite("filtd.jpg", mod);
    waitKey(0);
}
