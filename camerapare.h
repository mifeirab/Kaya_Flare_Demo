#ifndef CAMERAPARE_H
#define CAMERAPARE_H

#include <QObject>

#include "clserkyi.h"
#include "clserkyi_defines.h"
#include "ky_cxp_defines.h"
#include "ky_lib_defines.h"
#include "KYFGcppLib.h"
#include "KYFGLib.h"
#include "KYFGLib_defines.h"

#include <iostream>

using namespace std;

class CameraPare : public QObject
{
    Q_OBJECT
public:
    explicit CameraPare(QObject *parent = 0);

    pair<int,int> get_Camera_ROI();
private:
    int ROI[2];

signals:

public slots:
};

#endif // CAMERAPARE_H
