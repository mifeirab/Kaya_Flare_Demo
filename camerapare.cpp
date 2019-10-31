#include "camerapare.h"

CameraPare::CameraPare(QObject *parent) : QObject(parent)
{

}
/*
Get the ROI of the Camera which was set already
*/
//pair<int,int>  CameraPare::get_Camera_ROI()
//{
//    pair <int,int> roi;
//    CameraPare.ROI[0] = KYFG_GetCameraValueInt(0,"ROI_HR");
//    CameraPare.ROI[1] = KYFG_GetCameraValueInt(0,"ROI_VR");

//    roi.first = KYFG_GetCameraValueInt(0,"ROI_HR");
//    roi.second = KYFG_GetCameraValueInt(0,"ROI_VR");

//    return roi;
//}
