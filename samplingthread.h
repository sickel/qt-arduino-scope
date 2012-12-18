#include <qwt_sampling_thread.h>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <qextserialport_global.h>


class SamplingThread: public QwtSamplingThread
{
    Q_OBJECT

public:
    SamplingThread( QObject *parent = NULL );

    double frequency() const;
    double amplitude() const;

public Q_SLOTS:
    void setAmplitude( double );
    void setFrequency( double );

protected:
    virtual void sample( double elapsed );

private:
    virtual double value( double timeStamp );
    double factor;
    double d_frequency;
    double d_amplitude;
    QextSerialPort* port;
    QString buffer;

};
