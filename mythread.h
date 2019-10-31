#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include "kaya_flare_camera_control.h"

using namespace cv;


extern int Image_Width;
extern int Image_Higth;
extern int Total_Frames_Grabed ;
extern int Allocated_for_Images ;
extern int Gb_number;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    void        stop();
    QString     get_imageSavingPath();
    void        set_imageSavingPath(QString path);
    int         get_image_count_saved();
    void        print_process_statue();

signals:
    void        imageSavedCount(int);
    void        savingProcessFinished();

protected:
    void run();

public slots:

private:
    volatile bool stopped;
    QString  saving_path;
    int      image_count_saved;

};

#endif // MYTHREAD_H
