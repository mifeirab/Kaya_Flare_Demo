#ifndef PYRAMIDERIESZ_H
#define PYRAMIDERIESZ_H

#include "pyramide.h"
//class PyramideRiesz
//{
//public:
//    PyramideRiesz();
//};

class PyramideRiesz {

    Pyramide xPyr;
    Pyramide yPyr;
    public :
        PyramideRiesz(vector<Mat> &); // construct Riesz pyramid using laplacian pyramid
        Pyramide &get();
        Pyramide &getx();
        Pyramide &gety();

};


#endif // PYRAMIDERIESZ_H
