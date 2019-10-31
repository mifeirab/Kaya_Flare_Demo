#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "opencv2/opencv.hpp"
#include "iirfilter.h"
#include<iostream>
#include <vector>

using namespace std;
using namespace cv;

#define MIN_ROW_COL_PYRAMID 32



class Pyramide {
protected:
    vector<Mat> pyr;

public :
    //构造函数
    Pyramide();
    //拷贝构造函数
    Pyramide(Pyramide &p, bool zero);
    vector<Mat> &get();

    void push_back(Mat m);	 //添加一个元素
    int size();		         //得到当前使用数据的大小
    void swap(Pyramide x)						 //交换
    {
        pyr = x.pyr;
    }

    Mat & operator [](int i) {return pyr[i];}
    Pyramide& operator=(Pyramide x)
    {
        swap(x);
        return *this;
    }


    Pyramide& operator+=(Pyramide& a)
    {
        if (pyr.size() != a.size())
        {
            cv::Exception e;
            e.code = -2;
            e.msg = "Pyramide size must be equal";
            throw e;
        }
        if (pyr[0].size() != a.get()[0].size())
        {
            cv::Exception e;
            e.code = -3;
            e.msg = "level 0 size  size must be equal";
            throw e;
        }
        Pyramide p(a, false);
        for (int i = 0; i < pyr.size(); i++)
        {
            p.get()[i] = pyr[i] + a.get()[i];
        }
        return p;
    }
    friend Pyramide operator+(Pyramide a, const Pyramide& b)
    {

    }
};

#endif // PYRAMIDE_H
