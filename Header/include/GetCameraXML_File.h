#ifndef GET_CAMERA_XML_FILE_H_
#define GET_CAMERA_XML_FILE_H_

#define _CRT_SECURE_NO_WARNINGS


#include "KYFGLib_defines.h"
#include "KYFGcppLib.h"
#include <iostream>

void Get_Camera_XML_File(CAMHANDLE camHandle, char * buffer, KYBOOL isZip, unsigned long long bufferSize, FILE *fileOut);

#endif
