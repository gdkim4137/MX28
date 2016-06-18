#include "dialog.h"
#include "ui_dialog.h"

#include <iostream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    dxl = new MX28(this);
    connect(dxl,SIGNAL(signal_received_av(int)),this,SLOT(slot_received_av(int)));

    dxl->start();

    QThread::msleep(100);
    dxl->request_av_change(LEFT_WHEEL,2023);
    dxl->request_av_change(RIGHT_WHEEL,500);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_button_run_cw_clicked()
{
    dxl->mbRequest_av_change = true;

    int rqt_value = dxl->make_present_speed(1,MAX_RPM);
    dxl->request_av_change(LEFT_WHEEL,rqt_value);

    rqt_value = dxl->make_present_speed(0,MAX_RPM);
    dxl->request_av_change(RIGHT_WHEEL,rqt_value);

    std::cout << "request value : " << rqt_value << std::endl;
    ui->lcd_cmd_av->display(MAX_RPM);
}

void Dialog::on_button_run_ccw_clicked()
{
    dxl->mbRequest_av_change = true;

    int rqt_value = dxl->make_present_speed(0,MAX_RPM);
    dxl->request_av_change(LEFT_WHEEL,rqt_value);

    rqt_value = dxl->make_present_speed(1,MAX_RPM);
    dxl->request_av_change(RIGHT_WHEEL,rqt_value);

    std::cout << "request value : " << rqt_value << std::endl;
    ui->lcd_cmd_av->display(-MAX_RPM);
}

void Dialog::on_button_stop_clicked()
{
    dxl->request_av_change(LEFT_WHEEL,0);
    dxl->request_av_change(RIGHT_WHEEL,0);
//    dxl->mStop = true;
}

void Dialog::slot_change_av(int av)
{
    ui->lcd_cmd_av->display(av);
}
void Dialog::slot_received_av(int av)
{
    double rqt_value = dxl->make_rpm(av);
    ui->lcd_curr_av->display(rqt_value);
}
