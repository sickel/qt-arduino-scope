#include "signaldata.h"
#include <qwt_math.h>
#include <math.h>
#include <QDebug>
#include <QString>
#include "samplingthread.h"
#include <QStringList>

#if QT_VERSION < 0x040600
#define qFastSin(x) ::sin(x)
#endif

SamplingThread::SamplingThread( QObject *parent ):
    QwtSamplingThread( parent ),
    d_frequency( 5.0 ),
    d_amplitude( 20.0 )
{
    factor=1.8;
    // http://automon.donaloconnor.net/qt-and-qextserialport/34/
    PortSettings portSettings;
    portSettings.BaudRate = BAUD9600;
    portSettings.DataBits = DATA_8;
    portSettings.Parity = PAR_NONE;
   // portSettings.StopBits = STOP_1;
   // portSettings.FlowControl = FLOW_OFF;
   // portSettings.Timeout_Millisec = 0;
    port = new QextSerialPort("/dev/ttyACM0",portSettings);
    bool res = false;
    res = port->open(QextSerialPort::ReadOnly);
    if(res){
        qDebug("Connected!!\n");
        // Throws away data waiting:
        QByteArray inpt;
        int a = port->bytesAvailable();
        inpt.resize(a);
        port->read(inpt.data(), inpt.size());
    }
    else
        qDebug("Connection failed!!\n");
}

void SamplingThread::setFrequency( double frequency )
{
    d_frequency = frequency;
}

double SamplingThread::frequency() const
{
    return d_frequency;
}

void SamplingThread::setAmplitude( double amplitude )
{
    d_amplitude = amplitude;
}

double SamplingThread::amplitude() const
{
    return d_amplitude;
}

void SamplingThread::sample( double elapsed )
{
    if ( d_frequency > 0.0 )
    {
        const QPointF s( elapsed, value( elapsed ) );
        SignalData::instance().append( s );
    }
}

double SamplingThread::value( double timeStamp )
{
    double v;
    /*const double period = 1.0 / d_frequency;

    const double x = ::fmod( timeStamp, period );
    float r = ((float)rand()-0.5*RAND_MAX)/((float)RAND_MAX);
    double v = d_amplitude * qFastSin( x / period * 2 * M_PI )+r;
    v=v+qFastSin(x/period*4)/2*d_amplitude;
    //const double v=d_amplitude*r*20;
    v=v/factor;
*/
    QByteArray inpt;
    int a = port->bytesAvailable();
    inpt.resize(a);
    port->read(inpt.data(), inpt.size());
    //qDebug() << "bytes read:" << bytes.size();
    // qDebug() << "bytes:" << buffer<<"\n";
     QString strng=buffer+QString::fromAscii(inpt);
     int j=strng.indexOf("\n");
     if(j==1) {
         qDebug() << "-"<<strng <<"-";
         strng=strng.right(1);
     }
     if(j>-1){
         QString s=strng.left(j-1);
         v=s.toFloat();
         buffer=strng.mid(j+1,-1);
         qDebug() << strng<<"=>"<< s << "<="<<j<<">" << buffer << "\n";
         /*buffer.clear();
         buffer.append(s);*/
         return v*d_amplitude/5;
     }

}
