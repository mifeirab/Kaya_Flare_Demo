#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QDir>
#include <QSlider>
#include <QDateTime>
#include "mylabel.h"

# pragma warning (disable:4819)

int  Total_frames = 0;


//函数声明
void Stream_callback_func(void* userContext, STREAM_HANDLE streamHandle);

//创建相机控制对象
Kaya_Flare_Camera_control* m_control =new Kaya_Flare_Camera_control() ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uchar i= 0;

    connect(timer_display,&QTimer::timeout,this,&MainWindow::timer_update);
    connect(timer_count,&QTimer::timeout,this,&MainWindow::timer_count_display);
    //扫描采集卡
     unsigned int grabber_num = m_control->scan_grabber();
    //显示采集卡数量
     ui->lineEdit->setText(QString::number(grabber_num));
    //显示采集卡信息
     for (i = 0; i<grabber_num; i++)
     {
         qDebug() << "Device:" << i;

         qDebug() << m_control->get_div_info(i).szDeviceDisplayName;
         qDebug() << m_control->get_div_info(i).DevicePID;
         ui->Grabber_index_comboBox->setItemText(i,"Device"+QString::number(i)+':'+m_control->get_div_info(i).szDeviceDisplayName);
     }

    //连接相关信号与槽
     connect(this,SIGNAL(dir_path_save(QString)),this,SLOT(get_path(String)));
     connect(this,SIGNAL(record_complete(bool)),this,SLOT(play_racord_Image(bool)));
     //界面对象初始化
        ui->tabWidget->setTabText(0,"Camera Information");
        ui->tabWidget->setTabText(1,"Grabber Information");
        ui->tabWidget->setTabText(2,"Saving Options");
        ui->tabWidget->setTabText(3,"Image to Video Options");
        ui->windoesTabWidget->setTabText(0,"Record");
        ui->windoesTabWidget->setTabText(1,"Preview");
        ui->windoesTabWidget->setTabText(2,"View");
        ui->total_frames_spinBox->setMaximum(9999);
        ui->frames_progressBar->setMinimum(0);
        ui->frames_progressBar->setValue(0);
        ui->saving_progressBar->setValue(0);
        ui->start_camera_pushButton->setEnabled(false);
        ui->connect_camera_pushButton_2->setEnabled(false);
        ui->stop_camera_pushButton->setEnabled(false);
        ui->allocate_Ram_pushButton->setEnabled(false);
        ui->total_frames_spinBox->setEnabled(false);
        ui->radio_doubleSpinBox->setValue(0.28);
        ui->fordword_pushButton->setEnabled(false);
        ui->backword_pushButton->setEnabled(false);
        ui->play_Slider->setEnabled(false);
        ui->tabWidget_param->setTabText(0,"ROI");
        ui->tabWidget_param->setTabText(1,"framrate");
        ui->tabWidget_param->setTabText(2,"Exposure");
        ui->framerate_doubleSpinBox->setMaximum(5000.0);
        ui->savingVideoToorbar->setValue(0);
        ui->radio_doubleSpinBox->setValue(0.5);
        ui->preview_frame_reta_lineEdit->setFocusPolicy(Qt::NoFocus);
        ui->preview_ROI_HR_lineEdit->setFocusPolicy(Qt::NoFocus);
        ui->preview_ROI_VR_lineEdit->setFocusPolicy(Qt::NoFocus);
        ui->preview_roi_HR_start_lineEdit->setFocusPolicy(Qt::NoFocus);
        ui->preview_VR_Start_lineEdit->setFocusPolicy(Qt::NoFocus);
        ui->radioButton_framerate_max->setCheckable(true);
        ui->radioButton_Preview->setChecked(true);
        ui->spinBox_user_roi_V->setMaximum(3072);
        ui->spinBox_user_roi_H->setMaximum(4096);
        ui->spinBox_user_roi_Start_H->setMaximum(3072);
        ui->spinBox_user_roi_Start_V->setMaximum(4096);
        ui->radio_doubleSpinBox->setFocusPolicy(Qt::NoFocus);
        ui->radio_doubleSpinBox->setMinimum(0.1);
        ui->radio_doubleSpinBox->setSingleStep(0.1);
        //显示图像显示边框
        ui->label_preview->setStyleSheet("border:1px solid black;");
        ui->Img_label ->setStyleSheet("border:1px solid black;");
        ui->label_4->setStyleSheet("border:1px solid black;");

        ui->scrollArea->setMaximumSize(881,641);

        QMessageBox message(QMessageBox::Information,"Information","High speed Camera Terminal V1.0. \n\n Copyright By ZhouQian. \n zhouqiansir@163.com",QMessageBox::Ok,NULL);
        message.exec();
        //获取原始label的大小
        Image_Label_size[0] = ui->Img_label->width();       //tab0中显示label的大小获取
        Image_Label_size[1] = ui->Img_label->height();
        Image_live_size[0] = ui->label_4->width();          //tab2中显示label的大小获取
        Image_live_size[1] = ui->label_4->height();

        imageSavingPath = "NULL";

        //退出按钮按下
        connect(ui->actionexit,&QAction::triggered,this,[=](){
            unsigned int current_index =  ui->Grabber_index_comboBox->currentIndex();
            if(true == m_control->disconnect_camera(current_index))
            {
                 this->close();
            }
        });

        //按下菜单栏“打开”按钮，查看采集到的图像
        connect(ui->actionopen,&QAction::triggered,this,[=](){
        //QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\THINK\\Desktop\\");
        imageShowPath =QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()));
            if(imageShowPath.isEmpty())
            {
                QMessageBox::warning(this,tr("warning"),"Fail to open files!");
            }
            else
            {
                QString img_name = imageShowPath + "\\" + "0.bmp";
                qDebug() << img_name ;
                QPixmap image_to_show;
                image_to_show.load(img_name);
                ui->Img_label->setPixmap(image_to_show);

            }
        });
        //按下下一帧按钮后显示下一帧图像
        connect(ui->next_frame_toolButton,&QPushButton::clicked,this,[=](){
            Image_to_show_count++;
            QString img_name = imageShowPath + "\\" + QString::number(Image_to_show_count) + ".bmp";
            qDebug() << img_name ;
            image_to_show.load(img_name);
            ui->Img_label ->setPixmap(image_to_show);
            ui->Image_show_Slider->setValue(Image_to_show_count);
        });
        //按下上一帧按钮后显示上一帧图像
        connect(ui->previous_frame_toolButton,&QPushButton::clicked,this,[=](){
            Image_to_show_count--;
            QString img_name = imageShowPath + "\\" + QString::number(Image_to_show_count) + ".bmp";
            qDebug() << img_name ;
            image_to_show.load(img_name);
            ui->Img_label->setPixmap(image_to_show);
            ui->Image_show_Slider->setValue(Image_to_show_count);
        });
        //滚动条变动时候，按照进度显示图像
        connect(ui->Image_show_Slider,&QSlider::valueChanged,this,[=](){
            Image_to_show_count = ui->Image_show_Slider->value();
            QString img_name = imageShowPath + "\\" + QString::number(Image_to_show_count) + ".bmp";
            qDebug() << img_name ;
            image_to_show.load(img_name);
            ui->Img_label->setPixmap(image_to_show);
        });        
        //保存图像时的进度条滚动
        connect(&thread,&MyThread::imageSavedCount,this,[=](){
            ui->saving_progressBar->setValue(thread.get_image_count_saved()+1);
            ui->saved_image_count_label->setText(QString::number(thread.get_image_count_saved()+1));
        });
        //图像保存结束
        connect(&thread,&MyThread::savingProcessFinished,this,[=](){
            if(thread.isRunning()){
                 thread.stop();
                 thread.terminate();
                 thread.wait();
                 QMessageBox::information(this,"Saving statues","Saving Finished!");
            }
            else {
                QMessageBox::warning(this,"Saving statues","Saving interrupted!");
            }
        });
        //显示系统时间
        timer_sysTIM->start(1000); // 每次发射timeout信号时间间隔为1秒
        connect(timer_sysTIM,SIGNAL(timeout()),this,SLOT(timeUpdate()));
        connect(ui->Img_label,SIGNAL(sendPixel(int*)),this,SLOT(pixel(int*)));
        //图片缩放连接
        connect(this,SIGNAL(send_zoom_coefficient(float)),this,SLOT(zoom_in_Image(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
函数：on_scan_grabber_pushButton_clicked
功能：扫描采集卡
*/
void MainWindow::on_scan_grabber_pushButton_clicked()
{


}
/*
函数：on_connect_grabber_pushButton_clicked()
功能：连接采集卡
*/
void MainWindow::on_connect_grabber_pushButton_clicked()
{
    //获取当前的采集卡的序号
   ui->label_4->setText("Connecting Geabber ...");
   unsigned int current_index =  ui->Grabber_index_comboBox->currentIndex();
   unsigned int connection_statues = m_control->connect_grabber(current_index);
   if(connection_statues == 1)
   {
       qDebug()<< "Good connection to grabber #"<<current_index;
       ui->grb_connect_statue_lineEdit->setText("Good connection to grabber #"+QString::number(m_control->get_grabber_index()));
       ui->label_4->setText("Good Connection!");
       ui->connect_camera_pushButton_2->setEnabled(true);
       QMessageBox message(QMessageBox::Information,"Information","Good connection to grabber!",QMessageBox::Ok,NULL);
       message.exec();
   }
   else {
       qDebug()<< "Can not connect to grabber #"<< current_index;
       ui->grb_connect_statue_lineEdit->setText("Can not connect to grabber # #"+QString::number(m_control->get_grabber_index()));
   }
}

/*
函数：on_connect_grabber_pushButton_clicked()
功能：连接相机 注册回调函数 分配buffer
*/
void MainWindow::on_connect_camera_pushButton_2_clicked()
{
    KYFGCAMERA_INFO caminfo_temp;

    ui->label_4->setText("Connecting Camera ...");
    //获取当前采集卡编号
    unsigned int current_index =  ui->Grabber_index_comboBox->currentIndex();
    //连接相机
    caminfo_temp = m_control->connect_camera(current_index);
    //注册回调函数  分配buffer
    m_control->camera_callbackRegister_Alloc(m_control->Stream_callback_func,15);

     //ui->camera_connect_statue_lineEdit_2->setText(caminfo_temp.deviceModelName);
     ui->label_Camera_Model_Name->setText(caminfo_temp.deviceModelName);
     ui->label_Camera_Version->setText(caminfo_temp.deviceVersion);
     ui->label_Device_ID->setText(caminfo_temp.deviceID);
     ui->label_Manufacture_Information->setText(caminfo_temp.deviceManufacturerInfo);
     ui->label_Vender_name->setText(caminfo_temp.deviceVendorName);

     ui->allocate_Ram_pushButton->setEnabled(true);
     ui->total_frames_spinBox->setEnabled(true);

     //显示分辨率
     ui->Resolution_label->setText(QString::number(m_control->get_camera_ROI_Width())+" X "+QString::number(m_control->get_camera_ROI_Height()) );
     //显示帧率
     ui->frame_rate_label->setText(QString::number(m_control->get_camera_frame_rate()));
     ui->preview_frame_reta_lineEdit->setText(QString::number(m_control->get_camera_frame_rate()));
     QMessageBox message(QMessageBox::Information,"Information","Good connection to Camera!",QMessageBox::Ok,NULL);
     message.exec();

     on_radioButton_Preview_clicked();

     Image_Width = m_control->get_camera_ROI_Width();
     Image_Higth = m_control->get_camera_ROI_Height();

     qDebug() << "Image_Width" << Image_Width;
     qDebug() << "Image_Higth" << Image_Higth;
}
/*
函数：on_start_camera_pushButton_clicked()
功能：开始采集
*/
void MainWindow::on_start_camera_pushButton_clicked()
{
    int totalframes_to_grab;
    totalframes_to_grab = ui->total_frames_spinBox->value();
    ui->frames_progressBar->setMaximum(totalframes_to_grab);

    m_control->start_camera(totalframes_to_grab);         //可以设置采集的数量
    ui->stop_camera_pushButton->setEnabled(true);
    ui->radio_doubleSpinBox->setValue(0.3);
   // id1 = startTimer(20)
    timer_display->start(20);
    timer_count->start(10);                               //打开计数器计数
}
/*
函数：on_start_camera_pushButton_clicked()
功能：停止采集
*/
void MainWindow::on_stop_camera_pushButton_clicked()
{
    //Kaya_Flare_Camera_control::Image_Data_temp_RAM = NULL;
    m_control->stop_camera();
}

/*
函数：on_allocate_Ram_pushButton_clicked()
功能：分配图像存储内存
*/
void MainWindow::on_allocate_Ram_pushButton_clicked()
{
  int statue;
  statue = Kaya_Flare_Camera_control::Set_Img_Ram_allocate(Allocated_for_Images,Image_Higth,Image_Width);
  if(statue)
  {
       ui->start_camera_pushButton->setEnabled(true);
       ui->allocate_Ram_pushButton->setEnabled(false);
  }
  QMessageBox message(QMessageBox::Information,"Information","Successfully allocat RAMs \n Totally "+ QString::number(statue)+" Gb for imagses !",QMessageBox::Ok,NULL);
  message.exec();
  ui->saving_progressBar->setValue(0);
  Gb_number = statue;
}
/*
函数：on_save_image_pushButton_clicked()
功能：存储图像
*/
void MainWindow::on_save_image_pushButton_clicked()
{
//    int i_count_save,Gb_count= 0;
//    int imgCenter = 0;
//    QString saving_path;                                        //定义存储路径

//    saving_path = get_imageSavingPath();                        //获得存储路径
//    qDebug()<<"Image wil be saved to:"+ saving_path;
//    ui->saving_progressBar->setMaximum(Total_Frames_Grabed);     //设置进度条最大值

//    long long size  = Image_Higth*Image_Width;                  //计算一张图像的大小
//    long long total_size = Total_Frames_Grabed*size;            //需要分配的内存的总大小，内存申请按1Gb为单位申请
//    long long resdual_img_num;
//    int total_Gb = (total_size/(1024*1024*1024))+1;             //需要分配的总的Gb数
//    int num_per_seg = (1024*1024*1024)/size;                    //计算内存块数
//    resdual_img_num = Total_Frames_Grabed-(num_per_seg*(total_Gb-1));
//    for(Gb_count = 0; Gb_count < total_Gb;Gb_count++)           //循环存储图像
//    {
//        if(Gb_count < total_Gb-1)                               //全部存储
//        {
//            for (i_count_save = 0; i_count_save < num_per_seg; i_count_save++)
//            {
//                //... Show Image with data ...
//                //创建要存储的当前图像
//                Mat Image_Save(Image_Higth, Image_Width, CV_8UC1,Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width);
//                //static
//                String Img_Name = saving_path.toStdString()+ "\\"+ std::to_string(imgCenter++) + ".bmp";                        //保存路径
//                imwrite(Img_Name, Image_Save);
//                qDebug()<<"total saved :"<<i_count_save+Gb_count*num_per_seg;
//                qDebug()<<"the Address is:" <<Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width;
//                //waitKey(50);
//                //ui->progressBar->setValue(i_count_save);
//                ui->saving_progressBar->setValue(i_count_save+Gb_count*num_per_seg);
//            }
//        }
//        else                        //存储剩下来的部分
//        {
//             for (i_count_save = 0; i_count_save < resdual_img_num; i_count_save++)
//             {
//                 Mat Image_Save(Image_Higth, Image_Width, CV_8UC1,Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width);
//                 //static
//                 String Img_Name = saving_path.toStdString()+ "\\"+ std::to_string(imgCenter++) + ".bmp";                        //保存路径
//                 imwrite(Img_Name, Image_Save);
//                 qDebug()<<"total saved :"<<i_count_save+Gb_count*num_per_seg;
//                 qDebug()<<"the Address is:" <<Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width;
//                 //waitKey(50);
//                 //ui->progressBar->setValue(i_count_save);
//                 ui->saving_progressBar->setValue(i_count_save+Gb_count*num_per_seg);
//             }
//        }
//        if(i_count_save+Gb_count*num_per_seg == Total_Frames_Grabed)         //保存结束，弹出保存结束对话框，并且进度条归零
//            {
//                QMessageBox message(QMessageBox::Information,"Information","Successfully saved images!",QMessageBox::Ok,NULL);
//                message.exec();
//                ui->saving_progressBar->setValue(0);
//            }
//    }
    if(imageSavingPath == "NULL")
    {
        QMessageBox::warning(this,"saving path warning","Please select a new floder for Images!");
    }
    else
    {
        ui->saving_progressBar->setRange(0,ui->total_frames_spinBox->value());
        thread.start();
    }
}

void MainWindow::on_show_image_pushButton_2_clicked()
{
    //id1 = startTimer(20);
}

/*
函数：timerEvent
功能：按一定频率显示采集到的图像
*/
void MainWindow::timer_update()
{
      double radio = ui->radio_doubleSpinBox->value();
      float  radio_fixd = 0;
      float  radio_fixd_preview;
      int width=Image_Width;                                       //获取图像宽度
      int height=Image_Higth;                                      //获取图像高度

      int totalframes = m_control->get_total_frames();             //获取总帧数
      uchar* data24 = new uchar[ width * height*3];                //开辟存储一帧图像的内存空间
      void* current_frame_pt = m_control->get_current_frame();     //获取当前图像的指针

      memcpy(data24,current_frame_pt,width*height);                //将采集到的图像数据拷贝到局部变量中
      //QImage image = QImage(data24, width, height, QImage::Format_RGB888);                //封装QImage

      Mat Image_Show(height, width, CV_8UC1, data24);              //封装Mat图像数据
      Mat dst;                                                     //进行缩放后的图像
      if(width > height)                                            //宽度大于高度，按照宽度显示
      {
            radio_fixd = Image_Label_size[0]/width;                 //计算显示比例
      }
      else                                                         //高度大于宽度，按照高度显示
      {
            radio_fixd = Image_Label_size[1]/height;            //计算显示比例
      }
      //cv::resize(Image_Show, dst, Size(),radio,radio);             //对图像进行缩放
      cv::resize(Image_Show, dst, Size(),radio_fixd,radio_fixd);     //对图像进行缩放
      QImage IMg;
      IMg = QImage((const uchar*)(dst.data), dst.cols, dst.rows, dst.cols*dst.channels(), QImage::Format_Indexed8);   //对图像进行QImage封装
      //在采集窗口label控件中显示
      ui->label_4->setPixmap(QPixmap::fromImage(IMg));

      //在preview窗口label中显示
      QImage IMg_preview = QImage((const uchar*)(Image_Show.data), Image_Show.cols, Image_Show.rows, Image_Show.cols*Image_Show.channels(), QImage::Format_Indexed8);   //对图像进行QImage封装
      QPixmap pixmap = QPixmap::fromImage(IMg_preview);
      int with1 = ui->label_preview->width();
      int height1 = ui->label_preview->height();
      if(width> height)                                     //宽度大于高度，按照宽度显示
      {
            radio_fixd_preview = with1/width;               //计算显示比例
      }
      else                                                  //高度大于宽度，按照高度显示
      {
            radio_fixd_preview = height1/height;            //计算显示比例
      }
      //QPixmap fitpixmap = pixmap.scaled(with1, height1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
      QPixmap fitpixmap = pixmap.scaled(with1, height1, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
      ui->label_preview->setPixmap(fitpixmap);

      //删除空间
      delete data24;

      ui->totelframes_label->setText(QString::number(totalframes));
      ui->totat_frames_label_2->setText(QString::number(totalframes));
      ui->frames_progressBar->setValue(totalframes+1);

      double frame_rate = m_control->get_camera_frame_rate();
      ui->frame_rate_label->setText(QString::number(frame_rate));

      if(m_control->get_camera_mode() == true)
      {
         if(totalframes+1 > Total_Frames_Grabed)
         {
             emit record_complete(true);
             timer_count->stop();
             ui->Del_Cache_pushButton->setEnabled(true);
         }
      }
}
/*
将内存中采集到的图片存储到指定的路径
*/
void MainWindow::on_dict_pushButton_clicked()
{
    QString directory =
            QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        if(ui->dir_comboBox->findText(directory)==-1)
            ui->dir_comboBox->addItem(directory);
        ui->dir_comboBox->setCurrentIndex(ui->dir_comboBox->findText(directory));
    }
    emit dir_path_save(directory);                      //获得存储路径后发送出去
    imageSavingPath = directory;
    thread.set_imageSavingPath(directory);
}
/*
获得保存图片的存储路径
*/
QString MainWindow::get_imageSavingPath()
{
    return imageSavingPath ;
}
/*
清除保存图像的内存中的缓存
*/
void MainWindow::on_Del_Cache_pushButton_clicked()
{
    m_control->del_cache();
    ui->frames_progressBar->setValue(0);
    ui->totelframes_label->setText(QString::number(0));
    ui->allocate_Ram_pushButton->setEnabled(true);
    ui->Del_Cache_pushButton->setEnabled(false);
    ui->play_Slider->setEnabled(false);
    ui->start_camera_pushButton->setEnabled(false);
    ui->stop_camera_pushButton->setEnabled(false);

    QMessageBox message(QMessageBox::Warning,"Critical","Image deleted \n Before starting \n new RAMs must be allocated!!!",QMessageBox::Ok,NULL);
    message.exec();

}

void MainWindow::on_radioButton_clicked()
{
    ui->connect_grabber_pushButton->setEnabled(false);
    ui->connect_camera_pushButton_2->setEnabled(false);
    ui->allocate_Ram_pushButton->setEnabled(false);
}

void MainWindow::play_racord_Image(bool record_statues)
{
    ui->play_Slider->setMaximum(Total_Frames_Grabed);           //设置最大值
    if(record_statues == true)
    {
        ui->fordword_pushButton->setEnabled(true);
        ui->backword_pushButton->setEnabled(true);
        ui->play_Slider->setEnabled(true);
        timer_display->stop();
    }
}
/*
向后显示一帧
*/
void MainWindow::on_backword_pushButton_clicked(void)
{
       --play_frame_count;
       ui->play_Slider->setValue(play_frame_count);
}
/*
向前显示一帧
*/
void MainWindow::on_fordword_pushButton_clicked()
{
    ++play_frame_count;
    ui->play_Slider->setValue(play_frame_count);
}
/*
函数：on_play_Slider_valueChanged()
功能：拉动slider回放图像
*/
void MainWindow::on_play_Slider_valueChanged(int value)
{

    int width = Image_Width;
    int height = Image_Higth;
    float radio_fixed = 0.0;
    double radio = ui->radio_doubleSpinBox->value();
    unsigned char* temp_pt;                                     //临时指针变量
    long long buffSize = width*height;
    int Gb_Index = 0;
    int num_per_seg = (1024*1024*1024)/buffSize;                //没块存储地址可以存放的图片数量

    int count_frames = value;
    play_frame_count = value;
    ui->lineEdit->setText(QString::number(value));
    Gb_Index= (count_frames/num_per_seg)+1;        //计算当前存储的地址块

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

    uchar* data24 = new uchar[ width * height*3];          //开辟存储一帧图像的内存空间
    memcpy(data24,temp_pt,width*height);                   //将采集到的图像数据拷贝到局部变量中

    //Mat Image_Show(width, height, CV_8UC1, data24);        //封装Mat图像数据
    Mat Image_Show(height, width, CV_8UC1, data24);        //封装Mat图像数据
    Mat dst;                                               //进行缩放后的图像
    if(width > height)                                     //宽度大于高度，按照宽度显示
    {
          radio_fixed = Image_Label_size[0]/width;         //计算显示比例
    }
    else                                                    //高度大于宽度，按照高度显示
    {
          radio_fixed = Image_Label_size[1]/height;         //计算显示比例
    }
    cv::resize(Image_Show, dst, Size(),radio_fixed,radio_fixed);       //对图像进行缩放

    QImage IMg;
    IMg = QImage((const uchar*)(dst.data), dst.cols, dst.rows, dst.cols*dst.channels(), QImage::Format_Indexed8);   //对图像进行QImage封装
    //在label控件中显示
    ui->label_4->setPixmap(QPixmap::fromImage(IMg));

    //imshow("CAptured Image", dst);
    //删除空间
    delete data24;
}
/*
显示采集消耗的时间
*/
void MainWindow::timer_count_display()
{
     timer_count_num+=0.01;
     ui->time_label->setText(QString::number(timer_count_num));
}

/*
选择预设的分辨率对相机进行设置
*/
void MainWindow::on_radioButton_3_clicked()
{
    ui->comboBox_ROI_perset->setEnabled(true);
    ui->spinBox_user_roi_H->setEnabled(false);
    ui->spinBox_user_roi_V->setEnabled(false);
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->comboBox_ROI_perset->setEnabled(false);
    ui->spinBox_user_roi_H->setEnabled(true);
    ui->spinBox_user_roi_V->setEnabled(true);
}

void MainWindow::on_comboBox_ROI_perset_currentIndexChanged(int index)
{
    int ROI_V_Val = 0;
    int ROI_H_Val = 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    int ROI_V_Val = 0;
    int ROI_H_Val = 0;

    unsigned char ROI_num_index = ui->comboBox_ROI_perset->currentIndex();

    switch (ROI_num_index) {
    case 0:
        ROI_H_Val = 2048;
        ROI_V_Val = 2048;
        break;
    case 1:
        ROI_H_Val = 1024;
        ROI_V_Val = 1024;
        break;
    case 2:
        ROI_H_Val = 800;
        ROI_V_Val = 800;
        break;
    case 3:
        ROI_H_Val = 700;
        ROI_V_Val = 700;
        break;
    case 4:
        ROI_H_Val = 600;
        ROI_V_Val = 600;
        break;
    case 5:
        ROI_H_Val = 512;
        ROI_V_Val = 512;
        break;
    default:
        break;
    }
    //m_control->set_camera_ROI(ROI_H_Val,ROI_V_Val);             //设置相机ROI
    ui->Resolution_label->setText(QString::number(m_control->get_camera_ROI_Width())+" X "+QString::number(m_control->get_camera_ROI_Height()) );
}

/*
采集模式选择：选择相机为采集模式
*/
void MainWindow::on_radioButton_Record_clicked()
{
    ui->pushButton_preview_start->setEnabled(false);
    ui->pushButton_preview_stop->setEnabled(false);

    m_control->set_camera_mode(true);               //设置相机模式为采集模式

    m_control->camera_callbackRegister_Alloc(m_control->Stream_callback_func,15);           //注册采集模式下的回调函数
    //m_control->camera_callbackUnRegister_Alloc(m_control->Stream_callback_func_preview);    //解注册预览模式下的灰调函数
}
/*
采集模式选择，选择相机为预览模式
*/
void MainWindow::on_radioButton_Preview_clicked()
{
    ui->pushButton_preview_start->setEnabled(true);
    ui->pushButton_preview_stop->setEnabled(true);

    m_control->set_camera_mode(false);      //设置相机模式为预览模式
    m_control->camera_callbackRegister_Alloc(m_control->Stream_callback_func_preview,15);   //注册预览模式下的回调函数
    //m_control->camera_callbackUnRegister_Alloc(m_control->Stream_callback_func);            //解注册采集模式下的回调函数
}

/*
开始预览
*/
void MainWindow::on_pushButton_preview_start_clicked()
{
    //在预览窗口显示参数
    ui->radioButton_Record->setEnabled(false);
    ui->preview_ROI_HR_lineEdit->setText(QString::number(m_control->get_camera_ROI_Width()) );
    ui->preview_ROI_VR_lineEdit->setText(QString::number(m_control->get_camera_ROI_Height()) );
    ui->preview_roi_HR_start_lineEdit->setText(QString::number(m_control->get_camera_ROI_Width_Start()) );
    ui->preview_VR_Start_lineEdit->setText(QString::number(m_control->get_camera_ROI_Heigth_Start()) );

    if(ui->radioButton_Preview->isCheckable() == true)
    {
        Image_pt[0] = new unsigned char [ Image_Higth*Image_Width ];
        m_control->start_camera(0);         // 打开相机
        ui->radio_doubleSpinBox->setValue(0.3);
       // id1 = startTimer(20);
        timer_display->start(20);
        timer_count->start(10);             //打开计数器计数
    }
}
//停止预览
void MainWindow::on_pushButton_preview_stop_clicked()
{
    ui->radioButton_Record->setEnabled(true);
    timer_count_num = 0;
    timer_count->stop();
    m_control->stop_camera();
    ui->frame_rate_label->setText(QString::number(0));
    ui->time_label->setText(QString::number(0));
    ui->totat_frames_label_2->setText(QString::number(0));
    delete [] Image_pt[0];
}

//设置参数
void MainWindow::on_pushButton_setParameters_clicked()
{
    on_connect_camera_pushButton_2_clicked();
    ui->radioButton_Preview->setChecked(true);
    QMessageBox message(QMessageBox::Information,"Information","Test",QMessageBox::Ok,NULL);
    message.exec();
}
//预览窗口开始预览按钮动作
void MainWindow::on_preview_play_pushButton_clicked()
{
   on_pushButton_preview_start_clicked();
}
//预览窗口停止按钮动作
void MainWindow::on_preview_stop_pushButton_clicked()
{
    on_pushButton_preview_stop_clicked();
}

/*
函数名称：on_pushButton_Execute_roi_clicked()
函数功能：更改相机ROI按钮按下的槽函数
输入参数：无
输出参数：无
*/
void MainWindow::on_pushButton_Execute_roi_clicked()
{
    int ROI_H_Temp;
    int ROI_V_Temp;
    int ROI_H_Temp_Start;
    int ROI_V_Temp_Start;
    if(ui->radioButton_ROI_Preset->isChecked() == true)
    {
        switch (ui->comboBox_ROI_perset->currentIndex()) {
        case 0:
            m_control->set_camera_ROI(2048,2048,1,1);
            break;
        case 1:
            m_control->set_camera_ROI(1024,1024,1537,1025);
            break;
        case 2:
            m_control->set_camera_ROI(640,640,1729,1217);
            break;
        case 3:
            m_control->set_camera_ROI(512,512,1793,1281);
        default:
            break;
        }
    }
    else if(ui->radioButton_ROI_User->isChecked() == true) {
        ROI_H_Temp = ui->spinBox_user_roi_H->value();
        ROI_V_Temp = ui->spinBox_user_roi_V->value();
        ROI_H_Temp_Start = ui->spinBox_user_roi_Start_H->value();
        ROI_V_Temp_Start = ui->spinBox_user_roi_Start_V->value();
        if((ROI_H_Temp_Start%2 == 0) && (ROI_V_Temp_Start%2 == 0))   //起始位置数值必须是奇数，输入偶数将出现提醒
        {
            QMessageBox message(QMessageBox::Warning,"Warning","The start position must be odd number!!! ",QMessageBox::Ok,NULL);
            message.exec();
            return;
        }
        else {
          m_control->set_camera_ROI(ROI_H_Temp,ROI_V_Temp,ROI_H_Temp_Start,ROI_V_Temp_Start);
        }
    }
    //重新显示相机帧率
    ui->frame_rate_label->setText(QString::number(m_control->get_camera_frame_rate()));
    //更新ROI显示
    ui->Resolution_label->setText(QString::number(m_control->get_camera_ROI_Width())+" X "+QString::number(m_control->get_camera_ROI_Height()) );

    on_radioButton_Record_clicked();
    on_radioButton_Preview_clicked();

    Image_Width = m_control->get_camera_ROI_Width();
    Image_Higth = m_control->get_camera_ROI_Height();

    qDebug() << "Image_Width" << Image_Width;
    qDebug() << "Image_Higth" << Image_Higth;

}

/*
函数名称：on_pushButton_Execute_frame_rate_clicked()
函数功能：更改相机帧率按钮按下的槽函数
输入参数：无
输出参数：无
*/
void MainWindow::on_pushButton_Execute_frame_rate_clicked()
{
    if(ui->radioButton_framerate_perset->isChecked() == true)
    {
        switch (ui->comboBox_Framerate_perset->currentIndex()) {
        case 0:
            m_control->set_camera_FrameRate(100.0);
            break;
        case 1:
            m_control->set_camera_FrameRate(200.0);
            break;
        case 2:
            m_control->set_camera_FrameRate(300.0);
            break;
        case 3:
            m_control->set_camera_FrameRate(400.0);
            break;
        case 4:
            m_control->set_camera_FrameRate(500.0);
            break;
        case 5:
            m_control->set_camera_FrameRate(600.0);
            break;
        case 6:
            m_control->set_camera_FrameRate(700.0);
            break;
        case 7:
            m_control->set_camera_FrameRate(800.0);
            break;
        case 8:
            m_control->set_camera_FrameRate(900.0);
            break;
        case 9:
            m_control->set_camera_FrameRate(1000.0);
            break;
        case 10:
            m_control->set_camera_FrameRate(1200.0);
            break;
        case 11:
            m_control->set_camera_FrameRate(1400.0);
            break;
        case 12:
            m_control->set_camera_FrameRate(1600.0);
            break;
        case 13:
            m_control->set_camera_FrameRate(1800.0);
            break;
        default:
            break;
        }
    }
    else if(ui->radioButton_framerate_user->isChecked() == true) {
       m_control->set_camera_FrameRate(ui->framerate_doubleSpinBox->value());
    }
    else if(ui->radioButton_framerate_max->isChecked() == true){
         m_control->set_camera_FrameRate(0.0);
    }
//显示帧率
ui->frame_rate_label->setText(QString::number(m_control->get_camera_frame_rate()));
}

//选择预设ROI模式
void MainWindow::on_radioButton_ROI_Preset_clicked()
{

    switch (ui->comboBox_ROI_perset->currentIndex()) {
    case 0:
        ui->spinBox_user_roi_V->setValue(2048);
        ui->spinBox_user_roi_H->setValue(2048);
        ui->spinBox_user_roi_Start_H->setValue(1);
        ui->spinBox_user_roi_Start_V->setValue(1);
        break;
    case 1:
        ui->spinBox_user_roi_V->setValue(1024);
        ui->spinBox_user_roi_H->setValue(1024);
        ui->spinBox_user_roi_Start_H->setValue(1537);
        ui->spinBox_user_roi_Start_V->setValue(1025);
        break;
    case 2:
        ui->spinBox_user_roi_V->setValue(640);
        ui->spinBox_user_roi_H->setValue(640);
        ui->spinBox_user_roi_Start_H->setValue(1729);
        ui->spinBox_user_roi_Start_V->setValue(1217);
        break;
    case 3:
        ui->spinBox_user_roi_V->setValue(512);
        ui->spinBox_user_roi_H->setValue(512);
        ui->spinBox_user_roi_Start_H->setValue(1793);
        ui->spinBox_user_roi_Start_V->setValue(1281);
    default:
        break;
    }
    ui->spinBox_user_roi_V->setEnabled(false);
    ui->spinBox_user_roi_H->setEnabled(false);
    ui->spinBox_user_roi_Start_H->setEnabled(false);
    ui->spinBox_user_roi_Start_V->setEnabled(false);

}

void MainWindow::on_comboBox_ROI_perset_currentIndexChanged(const QString &arg1)
{
    switch (ui->comboBox_ROI_perset->currentIndex()) {
    case 0:
        ui->spinBox_user_roi_V->setValue(2048);
        ui->spinBox_user_roi_H->setValue(2048);
        ui->spinBox_user_roi_Start_H->setValue(1);
        ui->spinBox_user_roi_Start_V->setValue(1);
        break;
    case 1:
        ui->spinBox_user_roi_V->setValue(1024);
        ui->spinBox_user_roi_H->setValue(1024);
        ui->spinBox_user_roi_Start_H->setValue(1537);
        ui->spinBox_user_roi_Start_V->setValue(1025);
        break;
    case 2:
        ui->spinBox_user_roi_V->setValue(640);
        ui->spinBox_user_roi_H->setValue(640);
        ui->spinBox_user_roi_Start_H->setValue(1729);
        ui->spinBox_user_roi_Start_V->setValue(1217);
        break;
    case 3:
        ui->spinBox_user_roi_V->setValue(512);
        ui->spinBox_user_roi_H->setValue(512);
        ui->spinBox_user_roi_Start_H->setValue(1793);
        ui->spinBox_user_roi_Start_V->setValue(1281);
    default:
        break;
    }
}

void MainWindow::on_radioButton_ROI_User_clicked()
{
    ui->spinBox_user_roi_V->setEnabled(true);
    ui->spinBox_user_roi_H->setEnabled(true);
    ui->spinBox_user_roi_Start_H->setEnabled(true);
    ui->spinBox_user_roi_Start_V->setEnabled(true);
    ui->comboBox_ROI_perset->setEnabled(false);
}
//缩放自适应图像大小
void MainWindow::on_pushButton_clicked()
{

}
//输入要采集的图像的数量
void MainWindow::on_total_frames_spinBox_valueChanged(const QString &arg1)
{
    Total_Frames_Grabed = ui->total_frames_spinBox->value();
    Allocated_for_Images = Total_Frames_Grabed*1.2;
}


void MainWindow::on_start_Button_clicked()
{
    ui->saving_progressBar->setRange(0,ui->total_frames_spinBox->value());
    thread.start();
}

void MainWindow::on_stop_Button_clicked()
{
    if(thread.isRunning())
    {
        thread.stop();
    }
}

/*
在状态栏显示时间
*/
void MainWindow::timeUpdate()
{
   QDateTime CurrentTime=QDateTime::currentDateTime();
   QString Timestr=CurrentTime.toString(" yyyy-MM-dd hh:mm:ss "); //设置显示的格式
   currentTimeLabel->setText(Timestr);
   ui->statusBar->addWidget(currentTimeLabel);
}
/*
在状态栏显示图像像素点
*/
void MainWindow::pixel(int* pixel)
{
    int x = *pixel;
    int y = *(++pixel);
    if(ui->windoesTabWidget->currentIndex() == 2)
    {
        QString pixel_pos = "X:" + QString::number(x) + "Y:" + QString::number(y);
        currentImagePixelLabel->setText(pixel_pos);
        ui->statusBar->addWidget(currentImagePixelLabel);
    }
}

//-----------------------------------第三页图像缩放相关函数--------------------------------//
/*
按下“+” 按钮时增加缩放因子
*/
void MainWindow::on_zoom_in_toolButton_clicked()
{
        zoom_coefficient+=0.1;
        emit send_zoom_coefficient(zoom_coefficient);
        //qDebug() << zoom_coefficient;
}
/*
按下“-” 按钮时减少缩放因子
*/
void MainWindow::on_zoom_out_toolButton_clicked()
{
        zoom_coefficient-=0.1;
        emit send_zoom_coefficient(zoom_coefficient);
        //qDebug() << zoom_coefficient;
}
/*
按比例缩放图像
*/
void MainWindow::zoom_in_Image(float coefficent)
{
    float new_width = Image_Label_size[0] * coefficent;
    float new_height = Image_Label_size[1]* coefficent;
    ui->Img_label->resize(new_width,new_height);
    qDebug() << coefficent;
}
