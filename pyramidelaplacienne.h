#ifndef PYRAMIDELAPLACIENNE_H
#define PYRAMIDELAPLACIENNE_H

#include "pyramide.h"

//PyramideLaplacienne继承自类Pyramide
class PyramideLaplacienne:public Pyramide
{
static Mat lowPassFilter;
static Mat highPassFilter;

    void InitFilters();

public :
    PyramideLaplacienne(vector<Mat> &);
    PyramideLaplacienne(Mat &); // construct Laplacian pyramid using http://people.csail.mit.edu/nwadhwa/riesz-pyramid/RieszPyrSupplemental.zip
    Mat Collpase(Pyramide &gauss);
    Mat Collpase();
    vector<Mat> &get();

};




#endif // PYRAMIDELAPLACIENNE_H
