#ifndef AMPLIFICATION_H
#define AMPLIFICATION_H

#include "opencv2/opencv.hpp"
#include "iirfilter.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

Mat ArcCos(Mat m);
Mat Cos(Mat m);
Mat Sin(Mat m);
vector<Mat> DifferencePhaseAmplitude(Mat &c_real, Mat &cRzX, Mat &cRzY, Mat &p_real, Mat &pRzX, Mat &pRzY );
Mat IIRtemporalFilter(IIRFilter &f, Mat phase, vector<Mat> ri);
Mat AmplitudeWeightedblur(Mat img,Mat weighted,Mat kernelx,Mat kernely);
Mat PhaseShiftCoefficientRealPart(Mat laplevel, Mat rieszXLevel, Mat rieszYLevel, Mat phaseMagnifiedCos, Mat phaseMagnifiedSin);


#endif // AMPLIFICATION_H
