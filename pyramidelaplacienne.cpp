#include "pyramidelaplacienne.h"

//PyramideLaplacienne::PyramideLaplacienne()
//{

//}

PyramideLaplacienne::PyramideLaplacienne(vector<Mat> &m)
{
    Mat y;
    for (int i = 1; i<m.size();i++)
    {
        Mat tmp1,tmp2;
        pyrUp(m[i],tmp1);
        subtract(m[i-1],tmp1,tmp2,noArray(),CV_32F);
        pyr.push_back(tmp2);
    }
    Mat x;
    m[m.size() - 1].convertTo(x,CV_32F);
    pyr.push_back(x);

}

PyramideLaplacienne::PyramideLaplacienne(Mat &m)
{
    if (lowPassFilter.empty())
        InitFilters();


    Mat tmp=m;
    while (tmp.rows >= MIN_ROW_COL_PYRAMID && tmp.cols > MIN_ROW_COL_PYRAMID)

    {
    Mat tmpLow,tmpHigh;
        filter2D(tmp,tmpHigh,CV_32F,highPassFilter);
        pyr.push_back(tmpHigh);
        filter2D(tmp,tmpLow,CV_32F,lowPassFilter);
//		resize(tmpLow,tmp,Size(),0.5,0.5);
        pyrDown(tmpLow,tmp);
    }
    pyr.push_back(tmp);
}

Mat PyramideLaplacienne::Collpase(Pyramide &gauss)
{
    Mat x,y;

   y=pyr[pyr.size()-1];
    for (int i = pyr.size()-2; i>=0;i--)
    {
        pyrUp(y,y);
        add(y,pyr[i],y);
    }
    return y;
}

Mat PyramideLaplacienne::Collpase()
{
    Mat x,y;
    if (lowPassFilter.rows == 0)
    {
        y = pyr[pyr.size()-1];
        for (int i = pyr.size()-2; i>=0;i--)
        {
            pyrUp(y,x);
            add(x,pyr[i],y);
        }
        return y;

    }
    else
    {
        y = pyr[pyr.size()-1];
        for (int i = pyr.size()-2; i>=0;i--)
        {
            Mat tmp1,tmp2;
            resize(y,x,pyr[i].size(),-1,-1,CV_INTER_NN);//pyrUp(y,x);
            filter2D(x,tmp1,CV_32F,lowPassFilter);
            filter2D(pyr[i],tmp2,CV_32F,highPassFilter);
            add(tmp1,tmp2,y);
        }
        return y;
    }
}

void PyramideLaplacienne::InitFilters()
{
    // Supplemental for Riesz Pyramid for Fast Phase-Based Video Magnification
    lowPassFilter = (Mat_<float>(9,9)<< -0.0001,   -0.0007,  -0.0023,  -0.0046,  -0.0057,  -0.0046,  -0.0023,  -0.0007,  -0.0001,
                                        -0.0007,   -0.0030,  -0.0047,  -0.0025,  -0.0003,  -0.0025,  -0.0047,  -0.0030,  -0.0007,
                                        -0.0023,   -0.0047,   0.0054,   0.0272,   0.0387,   0.0272,   0.0054,  -0.0047,  -0.0023,
                                        -0.0046,   -0.0025,   0.0272,   0.0706,   0.0910,   0.0706,   0.0272,  -0.0025,  -0.0046,
                                        -0.0057,   -0.0003,   0.0387,   0.0910,   0.1138,   0.0910,   0.0387,  -0.0003,  -0.0057,
                                        -0.0046,   -0.0025,   0.0272,   0.0706,   0.0910,   0.0706,   0.0272,  -0.0025,  -0.0046,
                                        -0.0023,   -0.0047,   0.0054,   0.0272,   0.0387,   0.0272,   0.0054,  -0.0047,  -0.0023,
                                        -0.0007,   -0.0030,  -0.0047,  -0.0025,  -0.0003,  -0.0025,  -0.0047,  -0.0030,  -0.0007,
                                        -0.0001,   -0.0007,  -0.0023,  -0.0046,  -0.0057,  -0.0046,  -0.0023,  -0.0007,  -0.0001);
    highPassFilter=(Mat_<float>(9,9)<<   0.0000,   0.0003,   0.0011,   0.0022,   0.0027,   0.0022,   0.0011,   0.0003,   0.0000,
                                         0.0003,   0.0020,   0.0059,   0.0103,   0.0123,   0.0103,   0.0059,   0.0020,   0.0003,
                                         0.0011,   0.0059,   0.0151,   0.0249,   0.0292,   0.0249,   0.0151,   0.0059,   0.0011,
                                         0.0022,   0.0103,   0.0249,   0.0402,   0.0469,   0.0402,   0.0249,   0.0103,   0.0022,
                                         0.0027,   0.0123,   0.0292,   0.0469,  -0.9455,   0.0469,   0.0292,   0.0123,   0.0027,
                                         0.0022,   0.0103,   0.0249,   0.0402,   0.0469,   0.0402,   0.0249,   0.0103,   0.0022,
                                         0.0011,   0.0059,   0.0151,   0.0249,   0.0292,   0.0249,   0.0151,   0.0059,   0.0011,
                                         0.0003,   0.0020,   0.0059,   0.0103,   0.0123,   0.0103,   0.0059,   0.0020,   0.0003,
                                         0.0000,   0.0003,   0.0011,   0.0022,   0.0027,   0.0022,   0.0011,   0.0003,   0.0000);
}

vector<Mat>& PyramideLaplacienne::get()
{
    return pyr;
}

Mat PyramideLaplacienne::highPassFilter;
Mat PyramideLaplacienne::lowPassFilter;


