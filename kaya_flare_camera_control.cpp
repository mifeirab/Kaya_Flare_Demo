#include "kaya_flare_camera_control.h"


Kaya_Flare_Camera_control::Kaya_Flare_Camera_control(QObject *parent) : QObject(parent)
{

}
Kaya_Flare_Camera_control::~Kaya_Flare_Camera_control()
{

}
/*
函数：scan_grabber
功能：扫描采集卡
输入参数：无
输出参数：infosize：扫描到采集卡的数量
*/
unsigned int Kaya_Flare_Camera_control::scan_grabber(void)
{
    unsigned int i=0;
    qDebug()<< "Scan Kaya Grabber......";
    unsigned int infosize = 0;
    infosize = KYFG_Scan(0,0);

    qDebug()<<"Number of scan results:"<<infosize;
    for (i = 0; i<infosize; i++)
    {
        qDebug() << "Device:" << i;
        KY_DeviceInfo(i, &ky_Information[i]);							//获取采集卡的信息
        qDebug() << ky_Information[i].szDeviceDisplayName;
        qDebug() << ky_Information[i].DevicePID;
    }
    return infosize;
}
/*
函数：get_div_info
功能：返回采集卡的信息
输入参数：div_info_index：采集卡的序号
输出参数：KY_DEVICE_INFO： 采集卡的信息
*/
KY_DEVICE_INFO Kaya_Flare_Camera_control::get_div_info(unsigned int div_info_index)
{
    return ky_Information[div_info_index];
}
/*
函数：get_grabber_index
功能：获取采集卡当前的序号
输入参数：无
输出参数：unsigned int： 采集卡序号
*/
unsigned int Kaya_Flare_Camera_control::get_grabber_index()
{
    return grabberIndex;
}
/*
函数：get_div_info
功能：返回采集卡的信息
输入参数：div_info_index：采集卡的序号
输出参数：KY_DEVICE_INFO： 采集卡的信息
*/
unsigned int Kaya_Flare_Camera_control::connect_grabber(unsigned int grabber_num)
{
    grabberIndex = grabber_num;
    if ((handle[grabberIndex] = KYFG_Open(grabberIndex)) != -1)										// connect to selected device
    {
        printf("Good connection to grabber #%d, handle=%X\n", grabberIndex, handle[grabberIndex]);
        qDebug() <<"Good connection to grabber #" << grabberIndex<<"handle="<< handle[grabberIndex];
        return 1;
    }
    else
    {
        printf("Could not connect to grabber #%d\n", grabberIndex);
        qDebug() <<"Could not connect to grabber #" << grabberIndex;
        return 2;
    }
}
/*
函数：disconnect_grabber
功能：断开与采集卡的连接
输入参数： grabber_num： 采集卡序号
输出参数：
*/
bool Kaya_Flare_Camera_control::disconnect_grabber(unsigned int grabber_num)
{
    grabberIndex = grabber_num;
    if (FGSTATUS_OK == KYFG_Close(1))
    {
        qDebug()<<"grabber 0 was disconnected successfully";
        return true;
    }
    else
    {
        qDebug()<<"grabber 0 isn't disconnected";
        return false;
    }
}

/*
函数：get_div_info
功能：返回采集卡的信息
输入参数：div_info_index：采集卡的序号
输出参数：KY_DEVICE_INFO： 采集卡的信息
*/
KYFGCAMERA_INFO Kaya_Flare_Camera_control::connect_camera(unsigned int)
{
    // scan for connected cameras
    if (FGSTATUS_OK != KYFG_CameraScan(handle[grabberIndex], camHandleArray[grabberIndex], &detectedCameras[grabberIndex]))
    {
        qDebug()<< "No cameras were detected!";								// no cameras were detected
    }
    qDebug()<<"Found %d cameras."<<detectedCameras[grabberIndex];
    //显示相机参数信息----2018-9-6
    KYFG_CameraInfo(camHandleArray[grabberIndex][0], &camera_info[0]);
    qDebug()<<"Camera model :"<<camera_info[0].deviceModelName;
    qDebug()<<"Camera manufacturer :"<<camera_info[0].deviceManufacturerInfo;
    qDebug()<<"Camera deviceVersion:" <<camera_info[0].deviceVersion;

    //打开相机
    if (FGSTATUS_OK == KYFG_CameraOpen2(camHandleArray[grabberIndex][0], 0))
    {
        qDebug()<<"Camera 0 was connected successfully";
        //printf("Camera 0 was connected successfully\n");
        //获取相机的XML文件 -----2018-9-6
        //Get_Camera_XML_File(camHandleArray[grabberIndex][0], buffer, isZip, bufferSize, fileOut);
    }
    else
    {
        qDebug()<<"Camera isn't connected";
        //printf("Camera isn't connected\n");

    }

    return camera_info[0];
}
/*
函数：disconnect_camera
功能：断开相机
输入参数：
输出参数：
*/
bool Kaya_Flare_Camera_control::disconnect_camera(unsigned int)
{
    //关闭相机
    if (FGSTATUS_OK == KYFG_CameraClose(camHandleArray[grabberIndex][0]))
    {
        qDebug()<<"Camera 0 was disconnected successfully";
        return true;
    }
    else
    {
        qDebug()<<"Camera isn't disconnected";
        return false;
    }
}
/*
函数：start_camera
功能：开始采集图像
输入参数：total_frames：需要采集的总帧数
输出参数：无
*/
void Kaya_Flare_Camera_control::start_camera(unsigned int total_frames)
{
    if (streamHandle == 0)
    {
        //printf("Stream handle is not valid.\n");
        qDebug()<< "Streaem handle is not valid.";
    }
    else
    {
        KYFG_CameraStart(camHandleArray[grabberIndex][0], streamHandle, total_frames);
    }
}
/*
函数：stop_camera
功能：停止采集图像
输入参数：无
输出参数：无
*/
void Kaya_Flare_Camera_control::stop_camera(void)
{
    KYFG_CameraStop(camHandleArray[grabberIndex][0]);
}
/*
函数：camera_callbackRegister_Alloc
功能：注册回调函数和分配buffer
输入参数：userFunc：回调函数名称   buffer_num：分配的buffer数量
输出参数：无
*/
void Kaya_Flare_Camera_control::camera_callbackRegister_Alloc(CameraCallback userFunc, unsigned int buffer_num)
{
    KYFG_CameraCallbackRegister(camHandleArray[grabberIndex][0], userFunc, 0);
    // allocate buffer large enough to get frames and be able to process this data

    if (FGSTATUS_OK != KYFG_StreamCreateAndAlloc(camHandleArray[grabberIndex][0], &streamHandle, buffer_num, 0))
    {
        qDebug()<<"Failed to allocate buffer.";
    }
    else {
        qDebug()<<"Successed to allocate buffer!";
    }
}
/*
函数：camera_callbackUnRegister_Alloc
功能：解注册回调函数和分配buffer
输入参数：userFunc：回调函数名称   buffer_num：分配的buffer数量
输出参数：无
*/
void Kaya_Flare_Camera_control::camera_callbackUnRegister_Alloc(CameraCallback userFunc)
{
    KYFG_CameraCallbackUnregister(camHandleArray[grabberIndex][0], userFunc);
    // allocate buffer large enough to get frames and be able to process this data
}

/*
相机预览模式回调函数
*/
void Kaya_Flare_Camera_control::Stream_callback_func_preview(void *userContext, STREAM_HANDLE streamHandle)
{
    static void* data = 0;
    userContext;
    static KYBOOL copyingDataFlag = KYFALSE;
    long long totalFrames = 0, buffSize = 0;
    int buffIndex;
    void* buffData;
    unsigned char* temp_pt = NULL;
    if (0 == streamHandle)		// callback with indicator for acquisition stop
    {
        copyingDataFlag = KYFALSE;
        return;
    }
    totalFrames = KYFG_GetGrabberValueInt(streamHandle, "RXFrameCounter");
    buffSize = KYFG_StreamGetSize(streamHandle);			// get buffer size
    buffIndex = KYFG_StreamGetFrameIndex(streamHandle);
    buffData = KYFG_StreamGetPtr(streamHandle, buffIndex);		// get pointer of buffer data

    if (KYFALSE == copyingDataFlag)
    {
        copyingDataFlag = KYTRUE;
        data = (void*)realloc(data, buffSize); 		// allocate size for local buffer
       // Image_Data_temp_RAM = (unsigned char*)realloc(Image_Data_temp_RAM,buffSize);
        if (0 == data)
        {
            return;
        }
        temp_pt = Image_pt[0];
        memcpy(temp_pt,buffData,buffSize);
        qDebug()<<"Address is:"<<temp_pt;
    }
}
/*
函数：Stream_callback_func
功能：采集到图像时的回调函数
输入参数：*userContext：用户输入选项    streamHandle：streamhandle
输出参数：无
*/
void Kaya_Flare_Camera_control::Stream_callback_func(void *userContext, STREAM_HANDLE streamHandle)
{
    static int count_frames = 0;                    //指针增量
    userContext;
    static void* data = 0;
    static KYBOOL copyingDataFlag = KYFALSE;
    long long totalFrames = 0, buffSize = 0;
    int buffIndex;
    void* buffData;
    unsigned char* temp_pt = NULL;

    if (0 == streamHandle)		// callback with indicator for acquisition stop
    {
        copyingDataFlag = KYFALSE;
        return;
    }

    totalFrames = KYFG_GetGrabberValueInt(streamHandle, "RXFrameCounter");
    buffSize = KYFG_StreamGetSize(streamHandle);			// get buffer size
    buffIndex = KYFG_StreamGetFrameIndex(streamHandle);
    buffData = KYFG_StreamGetPtr(streamHandle, buffIndex);		// get pointer of buffer data

    int num_per_seg = (1024*1024*1024)/buffSize;                //没块存储地址可以存放的图片数量

    if (KYFALSE == copyingDataFlag)
    {
        copyingDataFlag = KYTRUE;
        data = (void*)realloc(data, buffSize); 		// allocate size for local buffer
       // Image_Data_temp_RAM = (unsigned char*)realloc(Image_Data_temp_RAM,buffSize);
        if (0 == data)
        {
            return;
        }
        qDebug()<<"Good callback buffer handle:"<<streamHandle<<"current index:"<<buffIndex<<"total frames:"<<totalFrames;
        TotalFrames_grb = totalFrames;

        int Gb_Index = (count_frames/num_per_seg)+1;        //计算当前存储的地址块

        switch (Gb_Index) {
        case 1:     //No.1
            temp_pt = Image_pt[0]+count_frames*buffSize;
            break;
        case 2:
            temp_pt = Image_pt[1]+(count_frames-num_per_seg)*buffSize;
            break;
        case 3:
            temp_pt = Image_pt[2]+(count_frames-2*num_per_seg)*buffSize;
            break;
        case 4:
            temp_pt = Image_pt[3]+(count_frames-3*num_per_seg)*buffSize;
            break;
        case 5:
            temp_pt = Image_pt[4]+(count_frames-4*num_per_seg)*buffSize;
            break;
        case 6:
            temp_pt = Image_pt[5]+(count_frames-5*num_per_seg)*buffSize;
            break;
        case 7:
            temp_pt = Image_pt[6]+(count_frames-6*num_per_seg)*buffSize;
            break;
        case 8:
            temp_pt = Image_pt[7]+(count_frames-7*num_per_seg)*buffSize;
            break;
        case 9:
            temp_pt = Image_pt[8]+(count_frames-8*num_per_seg)*buffSize;
            break;
        case 10:
            temp_pt = Image_pt[9]+(count_frames-9*num_per_seg)*buffSize;
            break;
        case 11:
            temp_pt = Image_pt[10]+(count_frames-10*num_per_seg)*buffSize;
            break;
        case 12:
            temp_pt = Image_pt[11]+(count_frames-11*num_per_seg)*buffSize;
            break;
        case 13:
            temp_pt = Image_pt[12]+(count_frames-12*num_per_seg)*buffSize;
            break;
        case 14:
            temp_pt = Image_pt[13]+(count_frames-13*num_per_seg)*buffSize;
            break;
        case 15:
            temp_pt = Image_pt[14]+(count_frames-14*num_per_seg)*buffSize;
            break;
        case 16:
            temp_pt = Image_pt[15]+(count_frames-15*num_per_seg)*buffSize;
            break;
        case 17:
            temp_pt = Image_pt[16]+(count_frames-16*num_per_seg)*buffSize;
            break;
        case 18:
            temp_pt = Image_pt[17]+(count_frames-17*num_per_seg)*buffSize;
            break;
        case 19:
            temp_pt = Image_pt[18]+(count_frames-18*num_per_seg)*buffSize;
            break;
        case 20:
            temp_pt = Image_pt[19]+(count_frames-19*num_per_seg)*buffSize;
            break;
        case 21:
            temp_pt = Image_pt[20]+(count_frames-20*num_per_seg)*buffSize;
            break;
        case 22:
            temp_pt = Image_pt[21]+(count_frames-21*num_per_seg)*buffSize;
            break;
        case 23:
            temp_pt = Image_pt[22]+(count_frames-22*num_per_seg)*buffSize;
            break;
        case 24:
            temp_pt = Image_pt[23]+(count_frames-23*num_per_seg)*buffSize;
            break;
        case 25:
            temp_pt = Image_pt[24]+(count_frames-24*num_per_seg)*buffSize;
            break;
        case 26:
            temp_pt = Image_pt[25]+(count_frames-25*num_per_seg)*buffSize;
            break;
        case 27:
            temp_pt = Image_pt[26]+(count_frames-26*num_per_seg)*buffSize;
            break;
        case 28:
            temp_pt = Image_pt[27]+(count_frames-27*num_per_seg)*buffSize;
            break;
        case 29:
            temp_pt = Image_pt[28]+(count_frames-28*num_per_seg)*buffSize;
            break;
        case 30:
            temp_pt = Image_pt[29]+(count_frames-29*num_per_seg)*buffSize;
            break;
        case 31:
            temp_pt = Image_pt[30]+(count_frames-30*num_per_seg)*buffSize;
            break;
        default:
            break;
        }

#ifdef TO_RAM
        //memcpy(Image_Data_temp_RAM+count_frames*buffSize,buffData,buffSize);
        memcpy(temp_pt,buffData,buffSize);
        qDebug()<<"Address is:"<<temp_pt;

        //指针加一
         count_frames++;

         if(count_frames == Total_Frames_Grabed)
             count_frames = 0;
#else
        memcpy(Image_Data_temp_RAM,buffData,buffSize);
        qDebug()<<"Address is:"<<Image_Data_temp_RAM;
#endif
        copyingDataFlag = KYFALSE;
    }
}

/*
分配内存
*/
int Kaya_Flare_Camera_control::Set_Img_Ram_allocate(long long totalframes,int length,int width)
{
    int i_count = 0;

    long long size = length*width;                      //图像大小
    long long total_size = totalframes*size;            //需要分配的内存的总大小，内存申请按1Gb为单位申请
    int total_Gb = (total_size/(1024*1024*1024))+1;     //需要分配的总的Gb数
    Num_Per_Segment = (1024*1024*1024)/size;

    for(i_count = 0;i_count<total_Gb;i_count++)
    {
        Image_pt[i_count] = new unsigned char [1024*1024*1024];
        if(Image_pt[i_count !=NULL])
        {
            qDebug()<<"Succeed to allocate the RAM!";
            qDebug()<<"The address of the"<<i_count<<"segment is:"<<Image_pt[i_count];
        }
        else {
            qDebug()<<"Failed to allocate!";
        }
    }
    qDebug()<<"Total allocated:"<<total_Gb<<"Gb";

    return total_Gb;
}
/*
获取当前采集到的总帧数
*/
int Kaya_Flare_Camera_control::get_total_frames()
{
    int totalframes = KYFG_GetGrabberValueInt(streamHandle, "RXFrameCounter");
    return totalframes;
}

/*
获取到当前采集到图像在内存中的存储首地址
*/
void* Kaya_Flare_Camera_control::get_current_frame()
{
    void* buffData_pt;

   int  buffIndex = KYFG_StreamGetFrameIndex(streamHandle);
    buffData_pt = KYFG_StreamGetPtr(streamHandle, buffIndex);
    return buffData_pt;

}

void Kaya_Flare_Camera_control::del_cache()
{
    //delete []Image_Data_temp_RAM;   //释放分配存储采集图片的缓存
    int i_count = 0;
    for(i_count = 0;i_count < Gb_number;i_count++)
    {
        delete []Image_pt[i_count];
        qDebug()<<"Delete No:"<<i_count<<"Segment!";
    }
}


void Kaya_Flare_Camera_control::set_saving_path(String path)
{
    saving_path = path;
}

String Kaya_Flare_Camera_control::get_saving_path()
{
    return saving_path;
}


/*
获得相机的帧率
*/
double Kaya_Flare_Camera_control::get_camera_frame_rate()
{
    double frame_rates = 0.0;
    frame_rates = KYFG_GetCameraValueFloat(camHandleArray[0][0],"AcquisitionFrameRate");
    return frame_rates;
}
/*
获得图像的高度
输入参数：
返回参数：图像高度
*/
int Kaya_Flare_Camera_control::get_camera_ROI_Height(void)
{
    return KYFG_GetCameraValueInt(camHandleArray[0][0],"ROI_1_VR");
}
/*
获得图像的宽度
输入参数：
输出参数：图像宽度
*/
int Kaya_Flare_Camera_control::get_camera_ROI_Width()
{
    return KYFG_GetCameraValueInt(camHandleArray[0][0],"ROI_HR");
}
/*
获得图像的起始点横坐标
输入参数：
返回参数：起始点横坐标
*/
int Kaya_Flare_Camera_control::get_camera_ROI_Heigth_Start()
{
     return KYFG_GetCameraValueInt(camHandleArray[0][0],"ROI_1_HR_Start");
}
/*
获得图像的起始点的纵坐标
输入参数：
返回参数：起始点的纵坐标
*/
int Kaya_Flare_Camera_control::get_camera_ROI_Width_Start()
{
    return KYFG_GetCameraValueInt(camHandleArray[0][0],"ROI_1_VR_Start");
}


//---------------------------------相机参数设置---------------------------------------//

/*
设置相机帧率
*/
void Kaya_Flare_Camera_control::set_camera_FrameRate(float camera_framerate)
{
    KYFG_SetCameraValueFloat(camHandleArray[0][0],"AcquisitionFrameRate",camera_framerate);
}

/*
设置相机的ROI
输入参数：ROI_H:图像宽度  ROI_V:图像高度
*/

void Kaya_Flare_Camera_control::set_camera_ROI(int ROI_H, int ROI_V,int ROI_H_Start,int ROI_V_Start)
{
    KYFG_SetCameraValueInt(camHandleArray[0][0], "ROI_1_HR_Start", ROI_H_Start);							// set camera width
    KYFG_SetCameraValueInt(camHandleArray[0][0], "ROI_1_VR_Start", ROI_V_Start);
    KYFG_SetCameraValueInt(camHandleArray[0][0], "ROI_HR", ROI_H);							// set camera width
    KYFG_SetCameraValueInt(camHandleArray[0][0], "ROI_1_VR", ROI_V);
    KYFG_SetCameraValueBool(camHandleArray[0][0],"ROI_Set_Windows",KYTRUE);
}
/*
设置相机的曝光时间
*/
//---------------------------------相机模式设置---------------------------------------//
void Kaya_Flare_Camera_control::set_camera_mode(bool mode)
{
    camera_mode = mode;
}

bool Kaya_Flare_Camera_control::get_camera_mode()
{
    return camera_mode;
}

//---------------------------------初始化静态变量------------------------------------//
unsigned char* Kaya_Flare_Camera_control::Image_Data_temp_RAM= NULL;
unsigned char* Kaya_Flare_Camera_control::Image_Data_temp_RAM_1= NULL;
unsigned char* Kaya_Flare_Camera_control::Image_Data_temp_RAM_2 = NULL;


unsigned char* Image_Data_RAM_Pt[32] = {0};

int Kaya_Flare_Camera_control::TotalFrames_grb = 0;

int Kaya_Flare_Camera_control::Num_Per_Segment = 0;
int Kaya_Flare_Camera_control::Total_Gb = 1;






