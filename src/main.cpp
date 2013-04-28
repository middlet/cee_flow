/**
  main.cpp

  code to drive project
*/

#include <cv.h>
#include <highgui.h>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <iterator>
#include <vector>
#include <algorithm>


using namespace boost::filesystem;
using namespace cv;


void 
do_flow(std::string dname) {
  
  namedWindow("seq", CV_WINDOW_AUTOSIZE);
  
  // get the files in the directory
  path p(dname);
  std::vector<path> files;
  copy(directory_iterator(p), directory_iterator(), back_inserter(files));
  sort(files.begin(), files.end()); 
  
  // iterate one less than number of frames
  for (uint fi=0; fi<files.size()-1; ++fi) {
    std::string cfname = files[fi].string();
    std::string nfname = files[fi+1].string();
    // get the current and next frame
    Mat cimage = imread(cfname);
    Mat nimage = imread(nfname);
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
    waitKey(250);
  } // for fi
  
}

int
main(int argc, char **argv)
{
  std::string path = "../Walking";
  
  if (argc>1) {
    path = argv[1];
  }
  
  do_flow(path);

  return 0;
}