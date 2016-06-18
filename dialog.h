#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <dynamixel.h>
#include "mx28.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    MX28* dxl;

public slots:
    void slot_change_av(int);
    void slot_received_av(int);
private slots:
    void on_button_run_cw_clicked();
    void on_button_run_ccw_clicked();
    void on_button_stop_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
