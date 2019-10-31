# pragma warning (disable:4819)
#ifndef KAYA_FLARE_CAMERA_CONTROL_H
#define KAYA_FLARE_CAMERA_CONTROL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QDebug>

#include<opencv2/opencv.hpp>


#include "clserkyi.h"
#include "clserkyi_defines.h"
#include "ky_cxp_defines.h"
#include "ky_lib_defines.h"
#include "KYFGcppLib.h"
#include "KYFGLib.h"
#include "KYFGLib_defines.h"

#include "image_parameters.h"

using namespace std;
using namespace cv;

//extern unsigned char* Image_Data_temp_RAM ;

extern int Gb_Flag;
extern unsigned char* Image_pt[32];

extern int Total_Frames_Grabed ;
extern int Allocated_for_Images ;
extern int Gb_number;

class Kaya_Flare_Camera_control : public QObject
{
    Q_OBJECT
public:
    explicit Kaya_Flare_Camera_control(QObject *parent = nullptr);
    ~Kaya_Flare_Camera_control();


    unsigned int scan_grabber();                                //扫描采集卡
    KY_DEVICE_INFO get_div_info(unsigned int div_info_index);   //获取板卡信息
    unsigned int connect_grabber(unsigned int grabber_num);     //连接采集卡
    bool disconnect_grabber(unsigned int grabber_num);  //断开采集卡连接
    unsigned int get_grabber_index(void);                       //获取采集卡的序号
    KYFGCAMERA_INFO connect_camera(unsigned int);               //连接相机
    bool  disconnect_camera(unsigned int);                      //断开相机

    void camera_callbackRegister_Alloc(CameraCallback userFunc,unsigned int buffer_num);        //注册回调函数和分配buffer
    void camera_callbackUnRegister_Alloc(CameraCallback userFunc);        //解注册回调函数
    void start_camera(unsigned int total_frames);               //开始采集
    void stop_camera(void);                                     //停止采集

    //回调函数
    static void Stream_callback_func_preview(void *userContext, STREAM_HANDLE streamHandle);
    static void Stream_callback_func(void* userContext, STREAM_HANDLE streamHandle);            //获取图像
    //内存缓存地址
    static unsigned char* Image_Data_temp_RAM ;
    static unsigned char* Image_Data_temp_RAM_1;
    static unsigned char* Image_Data_temp_RAM_2;


    static int Set_Img_Ram_allocate(long long totalframes,int length,int width);
    static int TotalFrames_grb;
    static int Num_Per_Segment;
    static int Total_Gb;

    int get_total_frames(void);                                 //获取当前采集到的总帧数
    void* get_current_frame(void);                              //获取到当前采集到的图像在内存中的存储地址
    void del_cache(void);
    void set_saving_path(String path);                         //设置保存路径
    String get_saving_path();                                  //获得保存路径

    double get_camera_frame_rate(void);

    int get_camera_ROI_Height(void);                            //获得图像的高度
    int get_camera_ROI_Width(void);                             //获得图像的高度
    int get_camera_ROI_Heigth_Start(void);                      //获得图像的起始点横坐标
    int get_camera_ROI_Width_Start(void);                       //获得图像的起始点纵坐标

    void deleteAll();

    //------------相机操作函数-----------------------------------------//
    int OpenCamera(QString cameraSN);       //打开相机
    int CloseCamera();                      //关闭相机

    //------------模式选择---------------------------------------------//
    void set_camera_mode(bool mode);        //设置相机采集、预览模式
    bool get_camera_mode(void);             //获得相机模式

    //------------设置相机参数-----------------------------------------//
    void set_camera_FrameRate(float camera_framerate);
    void set_camera_ROI(int ROI_H, int ROI_V,int ROI_H_Start, int ROI_V_Start);



    void setExposureTime(double time); // 设置曝光时间
    int getExposureTime();             // 获取曝光时间
    int getExposureTimeMin();          // 最小曝光时间
    int getExposureTimeMax();          // 最大曝光时间

    void set_grabber_handle(unsigned int handle_value);    //设置采集卡句柄
    void select_grabber(unsigned int grabber_index);

signals:
    void totalframesend(int totalframes);


public slots:

private:
    int camera_ROI_VR;                          //相机ROI高度
    int camera_ROI_HR;                          //相机ROI宽度
    float camera_Frame_Rate;                    //相机率

    KY_DEVICE_INFO ky_Information[4];           //采集卡信息数组
    KYFGCAMERA_INFO camera_info[4];             //相机信息数组

    unsigned int grabberIndex;                  //采集卡编号
    int detectedCameras[4];
    FGHANDLE handle[4];                         //定义采集卡句柄
    CAMHANDLE camHandleArray[4][4];             //相机句柄
    STREAM_HANDLE streamHandle = 0;             //图像句柄
    String saving_path;
    int num_single;                             //单块内存存储的图像的数量
    bool camera_mode;                           //模式选择-采集-预览

private:



};

#endif // KAYA_FLARE_CAMERA_CONTROL_H
