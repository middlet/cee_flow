/**
  main.cpp

  code to drive project
*/

#include <cv.h>
#include <highgui.h>
#include <string>
#include <sstream>


using namespace cv;


void 
do_flow(std::string fname) {
  
  namedWindow("seq", CV_WINDOW_AUTOSIZE);
  
  

  // iterate one less than number of frames
  for (int fi=7; fi<14; ++fi) {
    std::ostringstream cfname, nfname;
    cfname << "../Walking/frame" << std::setw(2) << std::setfill('0') << fi << ".png";
    nfname << "../Walking/frame" << std::setw(2) << std::setfill('0') << (fi+1) << ".png";
    // get the current and next frame
    Mat cimage = imread(cfname.str());
    Mat nimage = imread(nfname.str());
    // grayscale image
    Mat cimage_g, nimage_g;
    cvtColor(cimage, cimage_g, CV_RGB2GRAY );
    cvtColor(nimage, nimage_g, CV_RGB2GRAY );
    // get features
    Mat eig_image, temp_image;
    std::vector<Point2f> ccorners, ncorners;
    int max_corners = 1000;
    goodFeaturesToTrack(cimage_g, ccorners, max_corners,
      0.1, 10, noArray(), 3, false
    );
    //goodFeaturesToTrack(nimage_g, ncorners, max_corners,
    //  0.1, 10, noArray(), 3, false
    //);
    // do optical flow
    int winsize = 11;
    int maxlvl = 5;
    vector<uchar> status;
    vector<float> error;
    calcOpticalFlowPyrLK(cimage_g, nimage_g, ccorners,
			 ncorners, status, error, Size(winsize, winsize), maxlvl);
    
    // draw features on image
    for (uint ci=0; ci<ccorners.size(); ci++) {
      circle(cimage, ccorners[ci], 1, Scalar(0,255,0), 1);
    } // for ci
    // draw motion
    for (uint ci=0; ci<ncorners.size(); ci++) {
      line(cimage, ccorners[ci], ncorners[ci], Scalar(0,255,0));
    } // for ci
    
    // show results
    imshow("seq", cimage);
    waitKey(0);
    
    
  } // for fi

  
}

int
main(int argc, char **argv)
{
  std:string path = "../Walking";
  
  if (argc>1) {
    path = argv[1];
  }
  
  do_flow(path);

  return 0;
}