#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readSerial(void);

    void on_up_pressed();
    void on_leftUp_pressed();
    void on_rightUp_pressed();
    void on_left_pressed();
    void on_right_pressed();
    void on_leftDown_pressed();
    void on_down_pressed();
    void on_rightDown_pressed();
    void on_stop_clicked();
    void on_up_released();
    void on_leftUp_released();
    void on_rightUp_released();
    void on_left_released();
    void on_right_released();
    void on_leftDown_released();
    void on_down_released();
    void on_rightDown_released();
    void on_panTurbo_toggled(bool checked);
    void on_tiltTurbo_toggled(bool checked);
    void on_panSpeed_valueChanged(int arg1);
    void on_tiltSpeed_valueChanged(int arg1);
    void on_ptzAddr_valueChanged(int arg1);
    void on_serialPort_currentTextChanged(const QString &arg1);
    void on_serialOpened_toggled(bool checked);

    void on_baudRate_currentTextChanged(const QString &arg1);
    void on_setPreset_clicked();
    void on_callPreset_clicked();
    void on_delPreset_clicked();
    void on_presetNum_valueChanged(int arg1);
    void on_changeAddr_clicked();
    void on_changeBaud_clicked();
    void on_leftLimit_clicked();
    void on_rightLimit_clicked();
    void on_startLimit_clicked();
    void on_cancelLimit_clicked();
    void on_sixDu_toggled(bool checked);
    void on_twDu_toggled(bool checked);
    void on_twtyDu_toggled(bool checked);
    void on_startCruise_clicked();
    void on_stopCruise_clicked();


    void on_setWatch_clicked();

    void on_startWatch_clicked();

    void on_stopWatch_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort *comPort = Q_NULLPTR;
    bool isSerialOpened;
    int baudRate;
    int dataBit;
    int checkBit;
    int stopBit;
    void openSerial(void);
    void closeSerial(void);
    QByteArray charToHex(QByteArray chr);
    void send_cmd(void *dat, unsigned int len);

    unsigned char addr;
    unsigned char pan_speed;
    unsigned char tilt_speed;
    unsigned char preset_num;
};

#endif // MAINWINDOW_H
