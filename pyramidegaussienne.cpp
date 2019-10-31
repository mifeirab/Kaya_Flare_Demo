#include "pyramidegaussienne.h"

/*
函数名称：PyramideGaussienne
函数功能：
输入参数：m 类型Mat
输出参数：
*/
PyramideGaussienne::PyramideGaussienne(Mat m):Pyramide()
{
    Mat x=m;
    Mat y;
    pyr.push_back(x);
    while (x.rows >= MIN_ROW_COL_PYRAMID && x.cols > MIN_ROW_COL_PYRAMID)
    {
        pyrDown(x,y);					//
        pyr.push_back(y);
        x=y;
    }

}
