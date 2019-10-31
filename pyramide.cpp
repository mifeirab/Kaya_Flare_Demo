#include "pyramide.h"

Pyramide::Pyramide()
{

}

Pyramide::Pyramide(Pyramide &p, bool zero)
{
    pyr.resize(p.size());
    for (int i = 0; i < p.size(); i++)
    {
        Mat m;
        if (zero)
            m = Mat::zeros(p.get()[i].size(), p.get()[i].type());
        else
            m = p.get()[i].clone();
        pyr[i] = m;
    }
}

vector<Mat>&Pyramide::get()
{
    return pyr;
}

void Pyramide::push_back(Mat m)
{
    pyr.push_back(m);
}	 //添加一个元素


int Pyramide::size()
{
    return pyr.size();
}  //得到当前使用数据的大小
