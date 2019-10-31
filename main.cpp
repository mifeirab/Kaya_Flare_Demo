#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

//unsigned char* Image_Data_temp_RAM ;
int Gb_Flag;

unsigned char* Image_pt[32];
int Image_Width = 1;
int Image_Higth = 1;
int Total_Frames_Grabed ;
int Allocated_for_Images ;
int Gb_number;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setStyle( QStyleFactory::create("fusion") );
    MainWindow w;

    w.setFixedSize(917,817);
    w.setWindowTitle("Flare12M180 V1.0");
    w.show();

    return a.exec();


}
