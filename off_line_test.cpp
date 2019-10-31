#include "off_line_test.h"

void Off_line_test()
{
    vector<string> listeVideo;						//视频列表
    vector<vector<double> > frequencyBand;			//带宽
    std::vector<double> pb(3);						//[0]:低截止频率，[1]高截止频率，[2]帧率

    //初始化视频列表
    listeVideo.push_back("../Video/baby.avi")		 ;pb[0]=0.2; pb[1]=5;  pb[2]=30;   frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/baby_mp4.mp4")	 ;pb[0]=0.2; pb[1]=5;  pb[2]=30;   frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/baby_blanket.avi");pb[0]=0.2; pb[1]=5;  pb[2]=30;   frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/camera.avi")	     ;pb[0]=6;   pb[1]=30; pb[2]=300;  frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/balance.avi")	 ;pb[0]=1;   pb[1]=7;  pb[2]=300;  frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/drum.avi")		 ;pb[0]=74;  pb[1]=78; pb[2]=1900; frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/guitar.avi")		 ;pb[0]=78;  pb[1]=86; pb[2]=600;  frequencyBand.push_back(pb);
    listeVideo.push_back("../Video/smoke.avi")		 ;pb[0]=9;   pb[1]=15; pb[2]=200;  frequencyBand.push_back(pb);

    //显示视频以及滤波器信息
    for (int i = 0; i<listeVideo.size();i++)
            qDebug() << i << " for " << listeVideo[i] << " with butterworth band pass filter ["<<frequencyBand[i][0]<<","<<frequencyBand[i][1]<<"]\n";

    string nomFichier,codeFichier;
    int fileIndx=-1;
    VideoCapture vid;							//定义一个输入视频对象

    do
      {
          qDebug() << "Video file or number : ";
          cin>>codeFichier;
          if (codeFichier.length() == 1)
          {
              fileIndx = stoi(codeFichier);
              if (fileIndx>=0 && fileIndx<listeVideo.size())
              {
                  nomFichier = listeVideo[fileIndx];
                  pb = frequencyBand[fileIndx];
              }
              else
                  fileIndx=-1;
          }
          else
          {
              nomFichier=codeFichier;
              pb[0]=5;
              pb[1]=0;
              pb[2]=30;
          }
          if (nomFichier.length())
              vid.open(nomFichier);
          if(!vid.isOpened())
              qDebug() << "File not found "<<nomFichier<<"\n";
      }
     while (!vid.isOpened());
     qDebug() << "butterworth band pass filter\n";
     qDebug() << "Example Low pass at 3Hz give 3 for f1 and 0 for f2\n";
     qDebug() << "Example band pass at [3Hz,5hz] give 3 for f1 and 5 for f2\n";
     qDebug() << "Example high pass at [3Hz,15 give 3 for f1 and 15 for f2 (fs=30hz=30images per second)\n";
     qDebug() << "Example high pass at [3Hz,15 give 3 for f1 and 15 for f2 (fs=30hz=30images per second)\n";
     if (fileIndx!=-1)
             qDebug() << "give -1 for f1 for default values\n";
     double x;
        qDebug() << "f1 = ";
        cin>>x;
        if (x!=-1)
            pb[0]=x;
        qDebug() << "f2 = ";
        cin>>x;
        if (x!=-1)
            pb[1]=x;
        qDebug() << "Sampling frequency = ";
        cin>>x;
        if (x!=-1)
            pb[2]=x;
        int ordre;
        qDebug() << "Order filter (more than 3  unstable) = ";
        cin>>ordre;
        if (x!=-1)
            pb[2]=x;
        double fs = pb[2];
        pb.resize(2);
        double amplificationfactor=50;
        double kernelSize, std;
        qDebug() << "Amplification factor = ";
        cin>>amplificationfactor;
        qDebug() << "Kernel size = ";
        cin>>kernelSize;
        qDebug() << "Std value = ";
        cin>>std;

        IIRFilter f("butterworth",ordre,fs,pb);			//定义一个butterworth滤波器

        VideoWriter vidWrite;							//定义一个视频写操作对象

        Mat m,m1;

        vid.read(m1);						//读取视频中的一帧图片
         Mat mc;
         cvtColor(m1,mc,COLOR_BGR2HSV);		//图像空间转换
         vector<Mat> sx;
         split(mc,sx);						//HSV各通道分离
         m = sx[2];
         vidWrite.open("write.avi",CV_FOURCC('P','I','M','1'),30,m.size());

         PyramideLaplacienne plPre(m);			//定义一个Lpalacienne-like 金字塔
         PyramideRiesz prPre(plPre.get());		//定义一个Riesz变换

         Pyramide phaseCos( prPre.getx(), true);
         Pyramide phaseSin(prPre.getx(),true);
         vector<Pyramide> rCos(std::max(f.a.size(),f.b.size()));
         vector<Pyramide> rSin(std::max(f.a.size(),f.b.size()));

         for (int i = 0; i < std::max(f.a.size(), f.b.size()); i++)
            {
                Pyramide r0( prPre.getx(), true);
                Pyramide r1( prPre.getx(), true);
                rCos[i] = r0;
                rSin[i] = r1;
            }

         Pyramide motionMagnified(prPre.getx());
         Mat kernelx,kernely;
         vector<Mat> riCos(std::max(f.a.size(), f.b.size()));
         vector<Mat> riSin(std::max(f.a.size(), f.b.size()));
         kernelx =  getGaussianKernel(kernelSize, std);
         kernely = kernelx.t();
         int numLevels = plPre.size()-1;
         while (vid.read(m1))
         {

             cvtColor(m1,mc,COLOR_BGR2HSV);
             vector<Mat> sx;
             split(mc,sx);
             m = sx[2];
             imshow("video",m);
             PyramideLaplacienne plAct(m);
             PyramideRiesz prAct(plAct.get());
             PyramideLaplacienne prMotionMagnifiedLap(plAct);
             for (int i = 0; i < numLevels; i++)
             {
                 vector<Mat> w=DifferencePhaseAmplitude(plAct[i],prAct.getx()[i],prAct.gety()[i],plPre[i],prPre.getx()[i],prPre.gety()[i]);
                 phaseCos[i] += w[0];
                 phaseSin[i] += w[1];
                 for (int j = 0;j < riCos.size(); j++)
                 {
                     riCos[j] = rCos[j][i];
                     riSin[j] = rSin[j][i];
                 }
                 Mat phaseFilteredCos=IIRtemporalFilter(f,phaseCos[i],riCos);
                 Mat phaseFilteredSin=IIRtemporalFilter(f,phaseSin[i],riSin);


                 phaseFilteredCos = AmplitudeWeightedblur(phaseFilteredCos,w[2],kernelx,kernely);
                 phaseFilteredSin = AmplitudeWeightedblur(phaseFilteredSin,w[2],kernelx,kernely);
                 Mat phaseMagnifiedFilteredCos;
                 Mat phaseMagnifiedFilteredSin;

                 phaseMagnifiedFilteredCos = amplificationfactor*phaseFilteredCos;
                 phaseMagnifiedFilteredSin = amplificationfactor*phaseFilteredSin;
                 prMotionMagnifiedLap[i]=PhaseShiftCoefficientRealPart(plAct[i], prAct.getx()[i], prAct.gety()[i], phaseMagnifiedFilteredCos, phaseMagnifiedFilteredSin);

             }
             prMotionMagnifiedLap[numLevels]=plAct[numLevels];
             Mat x = prMotionMagnifiedLap.Collpase();
             double minVal, maxVal;
             minMaxLoc(x, &minVal, &maxVal);

             Mat uc;
             x.convertTo(uc, CV_8U,255/(maxVal-minVal),-minVal/(maxVal-minVal));
             x.convertTo(uc,CV_8U);
             sx[2]=uc;
             merge(sx,mc);
             Mat mr;
             cvtColor(mc,mr,COLOR_HSV2BGR);
             imshow("Laplacian Motion",uc);
             vidWrite << mr;
             waitKey(1);
             qDebug() << vid.get(CAP_PROP_POS_MSEC)<<endl;
             plPre=plAct;
             prPre=prAct;

         }
}
