// QR Code reader

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include <zbar.h>  
#include <iostream>  
#include <string>
#include <time.h>

using namespace cv;  
using namespace std;  
using namespace zbar;  

#define KERNEL 11

int main(int argc, char* argv[])  
{ 
  clock_t t1, t2;
  String imageName("photo_qr.jpg");
  Mat image;

  t1 = clock();
  image = imread(imageName, IMREAD_COLOR);

  ImageScanner scanner;   
  scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);   
  double dWidth = image.cols; //get the width of frames of the video  
  double dHeight = image.rows; //get the height of frames of the video  
  cout << "Frame size: " << dWidth << " x " << dHeight << endl;  
  resize(image, image, Size(dWidth/2, dHeight/2));
  cout << "New size: " << image.cols << " x " << image.rows << endl;
  for (int i = 1; i < KERNEL; i = i + 2) {
    GaussianBlur(image, image, Size(i, i), 0, 0);
  }

  //while (1)  
  //{   
 
    Mat grey;  
    cvtColor(image ,grey, CV_BGR2GRAY);  
    int width = image.cols;   
    int height = image.rows;   
    uchar *raw = (uchar *)grey.data;   
    // wrap image data   
    Image zbarImage(width, height, "Y800", raw, width * height);   
    // scan the image for barcodes   
    int n = scanner.scan(zbarImage);   
    n++;
    // extract results   
    for(Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {   
      vector<Point> vp;   
      // do something useful with results   
      cout << "decoded " << symbol->get_type_name() << endl << "symbol => " << symbol->get_data() << '"' <<" "<< endl;   
      t2 = clock();
      int n = symbol->get_location_size();   
      for(int i=0; i<n; i++) {   
        vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));   
      }   
      RotatedRect r = minAreaRect(vp);   
      Point2f pts[4];   
      r.points(pts);   
      for(int i=0;i<4;i++){   
        line(image, pts[i], pts[(i+1) % 4], Scalar(255, 0, 0), 3);   
      }   
      cout << "Angle: " << r.angle << endl;   
      break;
    } 
    float diff = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
    cout << "Time: " << diff << "s" << endl;
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"  
    imshow("MyVideo", image); //show the frame in "MyVideo" window  
    if (waitKey(0) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop  
    {  
      cout << "esc key is pressed by user" << endl;    
    }  
  //}  
  return 0;  
}  