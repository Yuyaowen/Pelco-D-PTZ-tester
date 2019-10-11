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
};

#endif // MAINWINDOW_H
