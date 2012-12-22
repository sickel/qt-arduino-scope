#include "mainwindow.h"
#include "plot.h"
#include "knob.h"
#include "wheelbox.h"
#include <qwt_scale_engine.h>
#include <qlabel.h>
#include <qlayout.h>
#include <QRadioButton>
#include <QtGui/QPushButton>


MainWindow::MainWindow( QWidget *parent ):
    QWidget( parent )
{
    const double intervalLength = 10; // seconds
    d_plot = new Plot( this );
    d_plot->setIntervalLength( intervalLength );

    d_amplitudeKnob = new Knob( "Amplitude", 0.0, 1000.0, this );
    d_amplitudeKnob->setValue( 400.0);

    d_frequencyKnob = new Knob( "Frequency [Hz]", 0.1, 20.0, this );
    //d_frequencyKnob->setValue( 17.8 );
    d_intervalWheel = new WheelBox( "Displayed [s]", 0.01, 100.0, 0.01, this );
    d_intervalWheel->setValue( intervalLength );

    d_synclock = new QRadioButton("Synclock");

    d_saveImageBtn = new QPushButton("Save Image");
    d_offsetWheel = new WheelBox( "Offset", -200.0, 200.0, 1.0, this );
    d_offsetWheel->setValue(0);


    d_timerWheel = new WheelBox( "Sample Interval [ms]", 0.0, 20.0, 0.001, this );
    d_timerWheel->setValue( 0.9 ); // this value depends on the speed of the serial connection
    d_overloadLed = new Led();


    QVBoxLayout* vLayout1 = new QVBoxLayout();
    QHBoxLayout* vLayout2 = new QHBoxLayout();
    //checkBox = new QCheckBox();
    //        checkBox->setObjectName(QString::fromUtf8("checkBox"));
    // vLayout1->addWidget(checkBox);
    d_overloadLed->setChecked(true);
    vLayout1->addWidget( d_intervalWheel );
    vLayout1->addWidget( d_timerWheel );
    vLayout2->addWidget(d_overloadLed);
    // vLayout1->addLayout(vLayout2);
    vLayout1->addWidget(d_offsetWheel);
    vLayout1->addWidget(d_synclock);
    vLayout1->addStretch( 10 );
    vLayout1->addWidget( d_amplitudeKnob );
    // vLayout1->addWidget( d_frequencyKnob );
    vLayout1->addWidget(d_saveImageBtn);
    QHBoxLayout *layout = new QHBoxLayout( this );
    layout->addWidget( d_plot, 10 );
    layout->addLayout( vLayout1 );

    layout->addLayout( vLayout2 );

    connect( d_amplitudeKnob, SIGNAL( valueChanged( double ) ),
        SIGNAL( amplitudeChanged( double ) ) );
    connect( d_timerWheel, SIGNAL( valueChanged( double ) ),
        SIGNAL( signalIntervalChanged( double ) ) );

    connect( d_intervalWheel, SIGNAL( valueChanged( double ) ),
        d_plot, SLOT( setIntervalLength( double ) ) );
    connect( d_offsetWheel, SIGNAL( valueChanged( double ) ),
        d_plot, SLOT( setOffset( double ) ) );

    connect( d_saveImageBtn, SIGNAL(clicked()),
             d_plot, SLOT(saveImage()));
}

void MainWindow::swoverloadled(bool light)
{
    d_overloadLed->setChecked(light);
}

void MainWindow::start()
{
    d_plot->start();
}

double MainWindow::frequency() const
{
    return d_frequencyKnob->value();
}

double MainWindow::amplitude() const
{
    return d_amplitudeKnob->value();
}

double MainWindow::signalInterval() const
{
    return d_timerWheel->value();
}
