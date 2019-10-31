#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include "kaya_flare_camera_control.h"
//#include "camerapare.h"

#include "clserkyi.h"
#include "clserkyi_defines.h"
#include "ky_cxp_defines.h"
#include "ky_lib_defines.h"
#include "KYFGcppLib.h"
#include "KYFGLib.h"
#include "KYFGLib_defines.h"

#include "mythread.h"

#include <opencv2/opencv.hpp>
#include "image_parameters.h"

//#include "pyramide.h"
//#include "pyramidegaussienne.h"
//#include "pyramidelaplacienne.h"
//#include "pyramideriesz.h"
//#include "amplification.h"
//#include "off_line_test.h"

using namespace cv;

extern int Image_Width;
extern int Image_Higth;
extern int Total_Frames_Grabed ;
extern int Allocated_for_Images ;
extern int Gb_number;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void on_scan_grabber_pushButton_clicked();
     void on_connect_grabber_pushButton_clicked();
     void on_connect_camera_pushButton_2_clicked();
     void on_start_camera_pushButton_clicked();
     void on_stop_camera_pushButton_clicked();
     void on_allocate_Ram_pushButton_clicked();
     void on_save_image_pushButton_clicked();
     void on_show_image_pushButton_2_clicked();
     void on_dict_pushButton_clicked();
     QString get_imageSavingPath();
     void on_Del_Cache_pushButton_clicked();
     void on_radioButton_clicked();
     void play_racord_Image(bool record_statues);
     void on_backword_pushButton_clicked(void);
     void on_fordword_pushButton_clicked();
     void on_play_Slider_valueChanged(int value);
     void timer_update(void);
     void timer_count_display(void);
     void on_radioButton_3_clicked();
     void on_comboBox_ROI_perset_currentIndexChanged(int index);
     void on_radioButton_4_clicked();
     void on_pushButton_2_clicked();
     void on_radioButton_Record_clicked();
     void on_radioButton_Preview_clicked();
     void on_pushButton_preview_start_clicked();
     void on_pushButton_preview_stop_clicked();
     void on_pushButton_setParameters_clicked();
     void on_preview_play_pushButton_clicked();
     void on_preview_stop_pushButton_clicked();
     void on_pushButton_Execute_roi_clicked();
     void on_pushButton_Execute_frame_rate_clicked();
     void on_radioButton_ROI_Preset_clicked();
     void on_comboBox_ROI_perset_currentIndexChanged(const QString &arg1);
     void on_radioButton_ROI_User_clicked();
     void on_pushButton_clicked();
     void on_total_frames_spinBox_valueChanged(const QString &arg1);
     void on_start_Button_clicked();
     void on_stop_Button_clicked();
     void timeUpdate();                               //显示系统当前时间
     void pixel(int* pixel);
     void on_zoom_in_toolButton_clicked();
     void on_zoom_out_toolButton_clicked();
     void zoom_in_Image(float coefficent);

private:
    Ui::MainWindow *ui;
    int id1;
    int play_frame_count;
    QTimer *timer_display = new QTimer(this);         //新建一个定时器
    QTimer *timer_count =   new QTimer(this);         //新建一个定时器
    double timer_count_num;                           //定时器计数次数
    QString imageSavingPath;                          //图像的存储路径
    QString imageShowPath;                            //图像显示路径
    int Image_to_show_count;                          //需要显示图像的序号
    QPixmap image_to_show;                            //需要显示的图像
    float zoom_coefficient = 1;                       //显示的缩放系数
    MyThread thread;
    QLabel  *currentTimeLabel=new QLabel;             //显示系统当前时间
    QLabel  *currentImagePixelLabel=new QLabel;       //显示系统当前时间
    QTimer  *timer_sysTIM=new QTimer(this);           //系统时间发送计时器
    float   Image_Label_size[2];                      //当前显示图像label大小[0]是width，[1]是heigh
    float   Image_live_size[2];                       //采集窗口显示图像label的大小，[0]是width，[1]是heigh

protected:
    // void timerEvent(QTimerEvent *event);


signals:
    void dir_path_save(QString);                //存储路径发送
    bool record_complete(bool statue);          //采集完成信号
    void send_zoom_coefficient(float);            //发送图片缩放系数
};

#endif // MAINWINDOW_H
