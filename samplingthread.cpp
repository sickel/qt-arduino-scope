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
  //  d_frequency( 5.0 ),
    d_amplitude( 400.0 )
{
    factor=1.8;
    // http://automon.donaloconnor.net/qt-and-qextserialport/34/
    PortSettings portSettings;
    portSettings.BaudRate = BAUD57600;
    portSettings.DataBits = DATA_8;
    portSettings.Parity = PAR_NONE;
   // portSettings.StopBits = STOP_1;
   // portSettings.FlowControl = FLOW_OFF;
   // portSettings.Timeout_Millisec = 0;
    //
    //
    // Setting port here:
    port = new QextSerialPort("/dev/ttyACM0",portSettings);
    bool res = false;
    res = port->open(QextSerialPort::ReadOnly);
    if(res){
        qDebug("Connected!!\n");
        // Throws away data waiting:
        QByteArray inpt;
        int a = port->bytesAvailable();
        qDebug()<< a << "\n";
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
    traway++;
    emit overload(false); // turns of overload led (in case it was on)
    if(buffer.count("\n")>10){
        buffer=buffer.mid(buffer.lastIndexOf("\n")+1,-1);
        qDebug()<<traway << "overrun\n";
        traway=0;
        emit overload(true); // makes the red "led" flash.
    }
    QByteArray inpt;
    int a = port->bytesAvailable();
    inpt.resize(a);
    port->read(inpt.data(), inpt.size());
    QString strng=buffer+QString::fromAscii(inpt);
    int j=strng.indexOf("\n");
    if(j==1) {
        qDebug() << "-"<<strng <<"-";
        strng=strng.right(1);
    }
    if(j>-1){
        QString s=strng.left(j-1);
        v=s.toFloat();
        // Saves for next time what has so far not been read:
        buffer=strng.mid(j+1,-1);
        return v*d_amplitude/5;
    }

}
