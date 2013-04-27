/**
  main.cpp

  code to drive project
*/

#include <cv.h>
#include <highgui.h>
#include <sstream>

using namespace cv;

int
main(void)
{
  namedWindow("seq", CV_WINDOW_AUTOSIZE);
  namedWindow("feat", CV_WINDOW_AUTOSIZE);

  for (int fi=7; fi<15; ++fi) {
    std::ostringstream oss;
    oss << "../Walking/frame" << std::setw(2) << std::setfill('0') << fi << ".png";
    std::cout << oss.str() << std::endl;
    Mat image = imread(oss.str());
    imshow("seq", image);
    waitKey(0);
    
    
  } // for fi
  

  return 0;
}