#include "mx28.h"
#include <iostream>

MX28::MX28(QObject *parent) :
    QThread(parent)
{
    mStop = false;
    mbRequest_av_change = false;

}

void MX28::request_av_change(int id, int av)
{
    if( id == LEFT_WHEEL)
    {
        this->mCommand_left_av = av;
    }
    else if (id == RIGHT_WHEEL )
    {
        this->mCommand_right_av = av;
    }

    QMutex mutex;
    mutex.lock();
    mbRequest_av_change = true;
    mutex.unlock();
}

void MX28::run()
{
    bool bOpen = dxl_initialize(DEFAULT_PORTNUM, DEFAULT_BAUDNUM);

    if( bOpen == true)
    {
        std::cout << " Succeed to open USB2Dynamixel SDK " << std::endl;
    }
    else
    {
        std::cout << " Fail to open USB2Dynamixel SDK " << std::endl;
        return;
    }

    int nlow1 =0;
    int nhigh1=0;
    int nlow2 =0;
    int nhigh2=0;

    while(!mStop)
    {

        this->msleep(10);
        if(mbRequest_av_change)
        {
            command_av_change(LEFT_WHEEL, mCommand_left_av);
            command_av_change(RIGHT_WHEEL, mCommand_right_av);

            QMutex mutex;
            mutex.lock();
            mbRequest_av_change = false;
            mutex.unlock();
        }

        /*
        //  requset for angular velocity
        nlow1 = dxl_read_byte(1, 38);
        nhigh1 = dxl_read_byte(1, 39);
        int result1 = dxl_get_result();

        nlow2 = dxl_read_byte(2, 38);
        nhigh2 = dxl_read_byte(2,39);
        int result2 = dxl_get_result();

        if( (result1 == COMM_RXSUCCESS) &&
            (result2 == COMM_RXSUCCESS))
        {

            //  received av from MX28
          //  int temp = dxl_makeword(nlow, nhigh);
           // if( std::abs(temp - mCurrent_av) > 3)
            //{
             //   mCurrent_av = temp;
              //  emit signal_received_av(mCurrent_av);
            //}

        }
        */
    }
    dxl_terminate();
}

void MX28::command_av_change(int id, int value)
{
    int nlow= dxl_get_lowbyte(value);
    int nhigh = dxl_get_highbyte(value);
    //	id, address, rpm
    dxl_write_word(id, 32, dxl_makeword(nlow, nhigh));
}

int MX28::make_present_speed(int direction, double rpm)
{
    int result = 0;
    result = (direction == 1) ?  (1<<10) : (0<<10);

    int temp = 0;
    temp = (rpm > MAX_RPM) ? MAX_RPM : rpm;

    result |= (int)(temp/PER_RPM);
    return result;
}

double MX28::make_rpm(int current_speed)
{
    int sign = 0;
    sign = (current_speed>1023) ? 1 : 0 ;

    if( sign == 1)
    {
        return (double)(current_speed-1023)*PER_RPM;
    }
    else
    {
        return (double)current_speed*PER_RPM;
    }

}





























