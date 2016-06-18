#ifndef MX28_H
#define MX28_H

#include <QThread>
#include <QMutex>
#include <dynamixel.h>


#define DEFAULT_PORTNUM		0		//	/dev/ttyUSB0
#define DEFAULT_BAUDNUM		16		//	1.15Mbps

#define DEFAULT_RPM_NUM				2023	//	near by 114 rpm
#define DEFAULT_INVERSE_RPM_NUM		500	    //	near by 114 rpm


#define PER_RPM                     0.114
#define MAX_RPM                     50


#define LEFT_WHEEL      1
#define RIGHT_WHEEL     2

class MX28 : public QThread
{
    Q_OBJECT

public:
    explicit MX28(QObject *parent = 0);
    void run();

public:
    int mCommand_left_av;
    int mCommand_right_av;

    int mCurrent_left_av;
    int mCurrent_right_av;

    bool mbRequest_av_change;

public:
    void command_av_change(int id, int value);

public:
    void request_av_change(int,int);

public:
    bool mStop;

public:
    int    make_present_speed(int direction,double rpm );
    double make_rpm(int current_speed);

signals:
    void signal_change_av(int av);
    void signal_received_av(int av);

public slots:

};

#endif // MX28_H
