#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    stopped= false;
}

void MyThread::run()
{

        int i_count_save,Gb_count= 0;
        int imgCenter = 0;
        QString saving_path;                                        //定义存储路径
        saving_path = get_imageSavingPath();                        //获得存储路径
        qDebug()<<"Image wil be saved to:"+ saving_path;

        long long size  = Image_Higth*Image_Width;                  //计算一张图像的大小
        long long total_size = Total_Frames_Grabed*size;            //需要分配的内存的总大小，内存申请按1Gb为单位申请
        long long resdual_img_num;
        int total_Gb = (total_size/(1024*1024*1024))+1;             //需要分配的总的Gb数
        int num_per_seg = (1024*1024*1024)/size;                    //计算内存块数
        resdual_img_num = Total_Frames_Grabed-(num_per_seg*(total_Gb-1));

        while (!stopped) {
        for(Gb_count = 0; Gb_count < total_Gb;Gb_count++)           //循环存储图像
        {
            if(Gb_count < total_Gb-1)                               //全部存储
            {
                for (i_count_save = 0; i_count_save < num_per_seg; i_count_save++)
                {
                    //... Show Image with data ...
                    //创建要存储的当前图像
                    Mat Image_Save(Image_Higth, Image_Width, CV_8UC1,Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width);
                    //static
                    String Img_Name = saving_path.toStdString()+ "\\"+ std::to_string(imgCenter++) + ".bmp";                        //保存路径
                    imwrite(Img_Name, Image_Save);
                    qDebug()<<"total saved :"<<i_count_save+Gb_count*num_per_seg;
                    qDebug()<<"the Address is:" <<Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width;

                    image_count_saved = i_count_save+Gb_count*num_per_seg;
                    emit imageSavedCount(image_count_saved);
                }
            }
            else                        //存储剩下来的部分
            {
                 for (i_count_save = 0; i_count_save < resdual_img_num; i_count_save++)
                 {
                     Mat Image_Save(Image_Higth, Image_Width, CV_8UC1,Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width);
                     //static
                     String Img_Name = saving_path.toStdString()+ "\\"+ std::to_string(imgCenter++) + ".bmp";                        //保存路径
                     imwrite(Img_Name, Image_Save);
                     qDebug()<<"total saved :"<<i_count_save+Gb_count*num_per_seg;
                     qDebug()<<"the Address is:" <<Image_pt[Gb_count]+i_count_save*Image_Higth*Image_Width;
                     image_count_saved = i_count_save+Gb_count*num_per_seg;
                     emit imageSavedCount(image_count_saved);
                 }
            } 
            if(i_count_save+Gb_count*num_per_seg == Total_Frames_Grabed)         //保存结束，弹出保存结束对话框，并且进度条归零
             {
                     emit savingProcessFinished();
             }
        }
    }
    stopped = false;
}

void MyThread::stop()
{
    stopped = true;
}

QString MyThread::get_imageSavingPath()
{
    return saving_path;
}

void MyThread::set_imageSavingPath(QString path)
{
    saving_path = path;
}

int MyThread::get_image_count_saved()
{
    return image_count_saved;
}

void MyThread::print_process_statue()
{
    if(this->isRunning())
    {
        qDebug() << " is running" ;
    }
    else if(this->isFinished())
    {
        qDebug() << "is finished";
    }
}
