/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *connect_grabber_pushButton;
    QPushButton *connect_camera_pushButton_2;
    QPushButton *allocate_Ram_pushButton;
    QPushButton *show_image_pushButton_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QSpinBox *total_frames_spinBox;
    QLabel *label_3;
    QPushButton *start_camera_pushButton;
    QPushButton *stop_camera_pushButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLabel *totelframes_label;
    QProgressBar *frames_progressBar;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_Camera_Model_Name_3;
    QLabel *label_Manufacture_Information_3;
    QLabel *label_Camera_Version_3;
    QLabel *label_Device_ID_3;
    QLabel *label_Vender_name_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_Camera_Model_Name;
    QLabel *label_Manufacture_Information;
    QLabel *label_Camera_Version;
    QLabel *label_Device_ID;
    QLabel *label_Vender_name;
    QWidget *tab_2;
    QLabel *label_Camera_Model_Name_4;
    QLabel *grb_connect_statue_lineEdit;
    QWidget *tab_3;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QComboBox *dir_comboBox;
    QPushButton *dict_pushButton;
    QPushButton *save_image_pushButton;
    QProgressBar *saving_progressBar;
    QFrame *line_2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *Grabber_index_comboBox;
    QLineEdit *lineEdit;
    QPushButton *Del_Cache_pushButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QSlider *horizontalSlider;
    QFrame *line_3;
    QDoubleSpinBox *radio_doubleSpinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(659, 772);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 0, 651, 401));
        label_4->setMaximumSize(QSize(651, 401));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 480, 631, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        connect_grabber_pushButton = new QPushButton(horizontalLayoutWidget);
        connect_grabber_pushButton->setObjectName(QStringLiteral("connect_grabber_pushButton"));
        connect_grabber_pushButton->setMinimumSize(QSize(153, 23));

        horizontalLayout->addWidget(connect_grabber_pushButton);

        connect_camera_pushButton_2 = new QPushButton(horizontalLayoutWidget);
        connect_camera_pushButton_2->setObjectName(QStringLiteral("connect_camera_pushButton_2"));

        horizontalLayout->addWidget(connect_camera_pushButton_2);

        allocate_Ram_pushButton = new QPushButton(horizontalLayoutWidget);
        allocate_Ram_pushButton->setObjectName(QStringLiteral("allocate_Ram_pushButton"));

        horizontalLayout->addWidget(allocate_Ram_pushButton);

        show_image_pushButton_2 = new QPushButton(horizontalLayoutWidget);
        show_image_pushButton_2->setObjectName(QStringLiteral("show_image_pushButton_2"));
        show_image_pushButton_2->setMinimumSize(QSize(153, 20));

        horizontalLayout->addWidget(show_image_pushButton_2);

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 510, 471, 61));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        total_frames_spinBox = new QSpinBox(gridLayoutWidget);
        total_frames_spinBox->setObjectName(QStringLiteral("total_frames_spinBox"));
        total_frames_spinBox->setMaximumSize(QSize(152, 16777215));

        gridLayout_3->addWidget(total_frames_spinBox, 0, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(153, 16777215));

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);

        start_camera_pushButton = new QPushButton(gridLayoutWidget);
        start_camera_pushButton->setObjectName(QStringLiteral("start_camera_pushButton"));
        start_camera_pushButton->setMaximumSize(QSize(153, 16777215));

        gridLayout_3->addWidget(start_camera_pushButton, 0, 0, 1, 1);

        stop_camera_pushButton = new QPushButton(gridLayoutWidget);
        stop_camera_pushButton->setObjectName(QStringLiteral("stop_camera_pushButton"));
        stop_camera_pushButton->setMaximumSize(QSize(153, 16777215));

        gridLayout_3->addWidget(stop_camera_pushButton, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        totelframes_label = new QLabel(gridLayoutWidget);
        totelframes_label->setObjectName(QStringLiteral("totelframes_label"));

        horizontalLayout_4->addWidget(totelframes_label);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        frames_progressBar = new QProgressBar(gridLayoutWidget);
        frames_progressBar->setObjectName(QStringLiteral("frames_progressBar"));
        frames_progressBar->setMaximumSize(QSize(152, 16777215));
        frames_progressBar->setValue(24);

        gridLayout_3->addWidget(frames_progressBar, 2, 2, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 570, 641, 141));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayoutWidget_3 = new QWidget(tab);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 10, 141, 100));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_Camera_Model_Name_3 = new QLabel(verticalLayoutWidget_3);
        label_Camera_Model_Name_3->setObjectName(QStringLiteral("label_Camera_Model_Name_3"));

        verticalLayout_3->addWidget(label_Camera_Model_Name_3);

        label_Manufacture_Information_3 = new QLabel(verticalLayoutWidget_3);
        label_Manufacture_Information_3->setObjectName(QStringLiteral("label_Manufacture_Information_3"));

        verticalLayout_3->addWidget(label_Manufacture_Information_3);

        label_Camera_Version_3 = new QLabel(verticalLayoutWidget_3);
        label_Camera_Version_3->setObjectName(QStringLiteral("label_Camera_Version_3"));

        verticalLayout_3->addWidget(label_Camera_Version_3);

        label_Device_ID_3 = new QLabel(verticalLayoutWidget_3);
        label_Device_ID_3->setObjectName(QStringLiteral("label_Device_ID_3"));

        verticalLayout_3->addWidget(label_Device_ID_3);

        label_Vender_name_3 = new QLabel(verticalLayoutWidget_3);
        label_Vender_name_3->setObjectName(QStringLiteral("label_Vender_name_3"));

        verticalLayout_3->addWidget(label_Vender_name_3);

        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(140, 10, 141, 96));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_Camera_Model_Name = new QLabel(verticalLayoutWidget);
        label_Camera_Model_Name->setObjectName(QStringLiteral("label_Camera_Model_Name"));

        verticalLayout->addWidget(label_Camera_Model_Name);

        label_Manufacture_Information = new QLabel(verticalLayoutWidget);
        label_Manufacture_Information->setObjectName(QStringLiteral("label_Manufacture_Information"));

        verticalLayout->addWidget(label_Manufacture_Information);

        label_Camera_Version = new QLabel(verticalLayoutWidget);
        label_Camera_Version->setObjectName(QStringLiteral("label_Camera_Version"));

        verticalLayout->addWidget(label_Camera_Version);

        label_Device_ID = new QLabel(verticalLayoutWidget);
        label_Device_ID->setObjectName(QStringLiteral("label_Device_ID"));

        verticalLayout->addWidget(label_Device_ID);

        label_Vender_name = new QLabel(verticalLayoutWidget);
        label_Vender_name->setObjectName(QStringLiteral("label_Vender_name"));

        verticalLayout->addWidget(label_Vender_name);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_Camera_Model_Name_4 = new QLabel(tab_2);
        label_Camera_Model_Name_4->setObjectName(QStringLiteral("label_Camera_Model_Name_4"));
        label_Camera_Model_Name_4->setGeometry(QRect(10, 10, 191, 16));
        grb_connect_statue_lineEdit = new QLabel(tab_2);
        grb_connect_statue_lineEdit->setObjectName(QStringLiteral("grb_connect_statue_lineEdit"));
        grb_connect_statue_lineEdit->setGeometry(QRect(200, 10, 311, 16));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayoutWidget_2 = new QWidget(tab_3);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 10, 624, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        dir_comboBox = new QComboBox(horizontalLayoutWidget_2);
        dir_comboBox->setObjectName(QStringLiteral("dir_comboBox"));
        dir_comboBox->setMinimumSize(QSize(350, 20));
        dir_comboBox->setMaximumSize(QSize(305, 20));

        horizontalLayout_2->addWidget(dir_comboBox);

        dict_pushButton = new QPushButton(horizontalLayoutWidget_2);
        dict_pushButton->setObjectName(QStringLiteral("dict_pushButton"));
        dict_pushButton->setMinimumSize(QSize(41, 23));
        dict_pushButton->setMaximumSize(QSize(41, 23));

        horizontalLayout_2->addWidget(dict_pushButton);

        save_image_pushButton = new QPushButton(horizontalLayoutWidget_2);
        save_image_pushButton->setObjectName(QStringLiteral("save_image_pushButton"));
        save_image_pushButton->setMinimumSize(QSize(121, 23));
        save_image_pushButton->setMaximumSize(QSize(121, 23));

        horizontalLayout_2->addWidget(save_image_pushButton);

        saving_progressBar = new QProgressBar(tab_3);
        saving_progressBar->setObjectName(QStringLiteral("saving_progressBar"));
        saving_progressBar->setGeometry(QRect(0, 50, 621, 23));
        saving_progressBar->setValue(24);
        tabWidget->addTab(tab_3, QString());
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 560, 631, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 450, 631, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        Grabber_index_comboBox = new QComboBox(horizontalLayoutWidget_3);
        Grabber_index_comboBox->setObjectName(QStringLiteral("Grabber_index_comboBox"));
        Grabber_index_comboBox->setMinimumSize(QSize(441, 21));
        Grabber_index_comboBox->setMaximumSize(QSize(441, 21));

        horizontalLayout_3->addWidget(Grabber_index_comboBox);

        lineEdit = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(31, 20));
        lineEdit->setMaximumSize(QSize(31, 20));

        horizontalLayout_3->addWidget(lineEdit);

        Del_Cache_pushButton = new QPushButton(centralWidget);
        Del_Cache_pushButton->setObjectName(QStringLiteral("Del_Cache_pushButton"));
        Del_Cache_pushButton->setGeometry(QRect(490, 510, 153, 20));
        Del_Cache_pushButton->setMinimumSize(QSize(153, 0));
        Del_Cache_pushButton->setMaximumSize(QSize(153, 16777215));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(490, 540, 91, 18));
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(580, 540, 91, 18));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 420, 631, 35));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(verticalLayoutWidget_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalSlider = new QSlider(verticalLayoutWidget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider);

        line_3 = new QFrame(verticalLayoutWidget_2);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        radio_doubleSpinBox = new QDoubleSpinBox(centralWidget);
        radio_doubleSpinBox->setObjectName(QStringLiteral("radio_doubleSpinBox"));
        radio_doubleSpinBox->setGeometry(QRect(600, 0, 64, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 659, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        connect_grabber_pushButton->setText(QApplication::translate("MainWindow", "Connect Grabber", Q_NULLPTR));
        connect_camera_pushButton_2->setText(QApplication::translate("MainWindow", "Scan&Connect Camera", Q_NULLPTR));
        allocate_Ram_pushButton->setText(QApplication::translate("MainWindow", "Allocate RAM", Q_NULLPTR));
        show_image_pushButton_2->setText(QApplication::translate("MainWindow", "Show Image", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Total to Record:</span></p></body></html>", Q_NULLPTR));
        start_camera_pushButton->setText(QApplication::translate("MainWindow", "START Record", Q_NULLPTR));
        stop_camera_pushButton->setText(QApplication::translate("MainWindow", "STOP Recoed", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Total Frames:</span></p></body></html>", Q_NULLPTR));
        totelframes_label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>1\302\2672</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Camera_Model_Name_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Camera Model Name\357\274\232</span></p></body></html>", Q_NULLPTR));
        label_Manufacture_Information_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Manufacurer Info:</span></p></body></html>", Q_NULLPTR));
        label_Camera_Version_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Camera Version:</span></p></body></html>", Q_NULLPTR));
        label_Device_ID_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Device ID:</span></p></body></html>", Q_NULLPTR));
        label_Vender_name_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Vendor Name:</span></p></body></html>", Q_NULLPTR));
        label_Camera_Model_Name->setText(QApplication::translate("MainWindow", "<html><head/><body><p/></body></html>", Q_NULLPTR));
        label_Manufacture_Information->setText(QApplication::translate("MainWindow", "<html><head/><body><p/></body></html>", Q_NULLPTR));
        label_Camera_Version->setText(QApplication::translate("MainWindow", "<html><head/><body><p/></body></html>", Q_NULLPTR));
        label_Device_ID->setText(QApplication::translate("MainWindow", "<html><head/><body><p/></body></html>", Q_NULLPTR));
        label_Vender_name->setText(QApplication::translate("MainWindow", "<html><head/><body><p/></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        label_Camera_Model_Name_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Grabber Connect Statue:</span></p></body></html>", Q_NULLPTR));
        grb_connect_statue_lineEdit->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Saving Path:</span></p></body></html>", Q_NULLPTR));
        dict_pushButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        save_image_pushButton->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\351\241\265", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Grabber Information:</span></p></body></html>", Q_NULLPTR));
        Grabber_index_comboBox->clear();
        Grabber_index_comboBox->insertItems(0, QStringList()
         << QString()
         << QString()
        );
        Del_Cache_pushButton->setText(QApplication::translate("MainWindow", "Del Cache !", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "Preview", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "Record", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
