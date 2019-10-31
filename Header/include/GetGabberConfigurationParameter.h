#ifndef GET_GABBER_CONFIGURATION_H_
#define GET_GABBER_CONFIGURATION_H_

#include "KYFGLib_defines.h"
#include "KYFGcppLib.h"
#include <iostream>


void NewParameter(const NodeDescriptor &nodeDescriptor, int grouppingLevel);
void KYFG_CALLCONV ParameterCallbackImpl(void* userContext, NodeDescriptor* pNodeDescriptor, int grouppingLevel);
void PrintParameters();








#endif