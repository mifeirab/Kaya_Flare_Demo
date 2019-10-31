#include "amplification.h"


/*
函数名称：DisplayImage
函数功能：显示图像
输入参数：x：输入的图像  Mat
          s: 图像名称	 string
返回参数：无
*/
void DisplayImage(Mat x,string s)
{
    return;
    vector<Mat> sx;
    split(x, sx);
    vector<double> minVal(3), maxVal(3);
    for (int i = 0; i < sx.size(); i++)
    {
        minMaxLoc(sx[i], &minVal[i], &maxVal[i]);

    }
    maxVal[0] = *max_element(maxVal.begin(), maxVal.end());
    minVal[0] = *min_element(minVal.begin(), minVal.end());
    Mat uc;
    x.convertTo(uc, CV_8U,255/(maxVal[0]-minVal[0]),-0*minVal[0]/(maxVal[0]-minVal[0]));
    imshow(s, uc);
    waitKey();
}


Mat ArcCos(Mat m)
{
    if (m.depth() != CV_32F )
    {
        cv::Exception e;
        e.code = -1;
        e.msg = "Mat must be real with one channel for ArcCos function";
        throw e;
    }
    vector<double> minMat(m.channels()),maxMat(m.channels());
    minMaxLoc(m,minMat.data(),maxMat.data());
    for (int i = 0; i<m.channels();i++)
        if (abs(minMat[i])>1 || abs(maxMat[i])> 1)
        {
            cv::Exception e;
            e.code = -1;
            e.msg = "mat values must be in range -1 to 1 for ArcCos function";
            throw e;
        }


    Mat t(m.size(),CV_32FC(m.channels()));

    for (int i = 0; i < m.rows; i++)
    {
        float *ptr1 = (float*)m.ptr(i);
        float *ptr2 = (float*)t.ptr(i);
        for (int j=0;j<m.cols*m.channels();j++,ptr1++,ptr2++)
            *ptr2 = acos(*ptr1);
    }

    return t;
}


Mat Cos(Mat m)
{
    if (m.depth() != CV_32F )
    {
        cv::Exception e;
        e.code = -1;
        e.msg = "Mat must be real with one channel for Cos function";
        throw e;
    }

    Mat t(m.size(),CV_32FC(m.channels()));

    for (int i = 0; i < m.rows; i++)
    {
        float *ptr1 = (float*)m.ptr(i);
        float *ptr2 = (float*)t.ptr(i);
        for (int j=0;j<m.cols*m.channels();j++,ptr1++,ptr2++)
            *ptr2 = cos(*ptr1);
    }

    return t;
}

Mat Sin(Mat m)
{
    if (m.depth() != CV_32F )
    {
        cv::Exception e;
        e.code = -1;
        e.msg = "Mat must be real with one channel for Cos function";
        throw e;
    }

    Mat t(m.size(),CV_32FC(m.channels()));

    for (int i = 0; i < m.rows; i++)
    {
        float *ptr1 = (float*)m.ptr(i);
        float *ptr2 = (float*)t.ptr(i);
        for (int j=0;j<m.cols*m.channels();j++,ptr1++,ptr2++)
            *ptr2 = sin(*ptr1);
    }

    return t;
}

vector<Mat> DifferencePhaseAmplitude(Mat &c_real, Mat &cRzX, Mat &cRzY, Mat &p_real, Mat &pRzX, Mat &pRzY )
{
    vector<Mat> v(3);

    {
        Mat qconjReal=c_real.mul(p_real) + cRzX.mul(pRzX) + cRzY.mul(pRzY);
        Mat qconjX= -c_real.mul(pRzX)+p_real.mul(cRzX);
        Mat qconjY= -c_real.mul(pRzY)+p_real.mul(cRzY);

        Mat num=qconjX.mul(qconjX)+qconjY.mul(qconjY);
        Mat qconjAmplitude;
        sqrt(qconjReal.mul(qconjReal)+num,qconjAmplitude);
        Mat ratio;
        divide(qconjReal, qconjAmplitude, ratio);
        Mat diffPhase = ArcCos(ratio);
        Mat cosAngle;
        Mat sinAngle;
        divide(qconjX,num,cosAngle);
        divide(qconjY,num,sinAngle);
        Mat diffPhaseCos=diffPhase.mul(cosAngle);
        Mat diffPhaseSin=diffPhase.mul(sinAngle);

        Mat amplitude;
        sqrt(qconjAmplitude,amplitude);
        v[0]=diffPhaseCos;
        v[1]=diffPhaseSin;
        v[2]=amplitude;
        DisplayImage(c_real, "phasecos");
        DisplayImage(cRzX, "phaseSion");
        DisplayImage(cRzY, "p");
    }
return v;
}

Mat IIRtemporalFilter(IIRFilter &f, Mat phase, vector<Mat> ri)
{
    Mat tmp;
    tmp = f.b[0] * phase + (ri[0]);
    for (int i = 0; i<ri.size()-2;i++)
        ri[i] = f.b[i+1] * phase + (ri[i+1]) + f.a[i+1]*tmp;
    ri[ri.size()-2] = f.b[ri.size()-1] * phase  + f.a[ri.size()-1]*tmp;
    return tmp;
}

Mat AmplitudeWeightedblur(Mat img,Mat weighted,Mat kernelx,Mat kernely)
{
    Mat num,den;
    Mat m;


    sepFilter2D(weighted,den,CV_32F,kernelx,kernely);
    multiply(img,weighted,m);
    sepFilter2D(m,num,CV_32F,kernelx,kernely);
    divide(num,den,m);
    //divide(m,weighted,m);
    return m;
}

Mat PhaseShiftCoefficientRealPart(Mat laplevel, Mat rieszXLevel, Mat rieszYLevel, Mat phaseMagnifiedCos, Mat phaseMagnifiedSin)
{
    Mat r;
    Mat pm,expPhaseReal,expPhaseImag;
    Mat expphix,expphiy,tmp;

    sqrt(phaseMagnifiedCos.mul(phaseMagnifiedCos)+phaseMagnifiedSin.mul(phaseMagnifiedSin),pm);
    expPhaseReal = Cos(pm);
    expPhaseImag = Sin(pm);
    divide(expPhaseImag,pm,tmp);
    expphix = phaseMagnifiedCos.mul(tmp);
    expphiy = phaseMagnifiedSin.mul(tmp);

    r = expPhaseReal.mul(laplevel)-expphix.mul(rieszXLevel)-expphiy.mul(rieszYLevel);

    return r;
}
