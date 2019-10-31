#include "pyramideriesz.h"

//PyramideRiesz::PyramideRiesz()
//{

//}

PyramideRiesz::PyramideRiesz(vector<Mat> &m)
{

        Mat xKernel=(Mat_<float>(3,3) << 0, 0, 0, 0.5, 0, -0.5, 0, 0, 0);
        Mat yKernel=(Mat_<float>(3,3) << 0, .5, 0, 0, 0, 0, 0, -0.5, 0);
    //    Mat yKernel=(Mat_<float>(3,3) << -0.12, -0.34, -0.12, 0,0,0, 0.12, 0.34, 0.12);
    //    Mat xKernel=yKernel.t();

    for (int i = 0; i<m.size()-1;i++)
    {
        Mat tmp1,tmp2;
        filter2D(m[i],tmp1,CV_32F,xKernel);
        xPyr.push_back(tmp1);
        filter2D(m[i],tmp2,CV_32F,yKernel);
        yPyr.push_back(tmp2);
    }

}

Pyramide & PyramideRiesz::get()
{
    return xPyr;
}

Pyramide & PyramideRiesz:: getx()
{
    return xPyr;
}

Pyramide & PyramideRiesz:: gety()
{
    return yPyr;
}
