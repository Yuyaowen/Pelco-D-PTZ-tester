#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort>
#include "protocol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    baudRate = ui->baudRate->currentText().toInt();
    dataBit = 8;
    checkBit = 0;
    stopBit = 1;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialPort->addItem(info.portName());
    }
    openSerial();

    if (ui->panTurbo->checkState() == Qt::Checked) {
        pan_speed = 0xff;
    } else {
        pan_speed = ui->panSpeed->value();
    }

    if (ui->tiltTurbo->checkState() == Qt::Checked) {
        tilt_speed = 0xff;
    } else {
        tilt_speed = ui->tiltSpeed->value();
    }

    addr = ui->ptzAddr->value();
}

MainWindow::~MainWindow()
{
    delete ui;
    closeSerial();
    delete comPort;
}

void MainWindow::on_serialPort_currentTextChanged(const QString &arg1)
{
    if (comPort != Q_NULLPTR) {
        comPort->close();
        delete comPort;
        comPort = Q_NULLPTR;
    }
    comPort = new QSerialPort(arg1);

    openSerial();
}

void MainWindow::on_serialOpened_toggled(bool checked)
{
    if (checked) {
        openSerial();
    } else {
        closeSerial();
    }
}

void MainWindow::openSerial(void)
{
    if (comPort->open(QIODevice::ReadWrite) || comPort->isOpen()) {
        comPort->setBaudRate(baudRate);
        switch (dataBit) {
            case 5 : comPort->setDataBits(QSerialPort::Data5); break;
            case 6 : comPort->setDataBits(QSerialPort::Data6); break;
            case 7 : comPort->setDataBits(QSerialPort::Data7); break;
            case 8 : comPort->setDataBits(QSerialPort::Data8); break;
            default : break;
        }

        switch (checkBit) {
            case 0 : comPort->setParity(QSerialPort::NoParity); break;
            case 1 : comPort->setParity(QSerialPort::EvenParity); break;
            case 2 : comPort->setParity(QSerialPort::OddParity); break;
            default : break;
        }

        switch (stopBit) {
            case 0 : comPort->setStopBits(QSerialPort::OneStop); break;
            case 1 : comPort->setStopBits(QSerialPort::OneAndHalfStop); break;
            case 2 : comPort->setStopBits(QSerialPort::TwoStop); break;
            default : break;
        }

        isSerialOpened = true;
        ui->serialOpened->setChecked(true);

        connect(comPort, SIGNAL(readyRead()), this, SLOT(readSerial()), Qt::QueuedConnection);
    } else {
        closeSerial();
        statusBar()->showMessage(tr("打不开串口！"), 3000);
    }
}

void MainWindow::closeSerial()
{
    comPort->close();

    isSerialOpened = false;
    ui->serialOpened->setChecked(false);
}

void MainWindow::readSerial(void)
{
    QByteArray readBuf;

    readBuf = comPort->readAll();
    if (!readBuf.isEmpty()) {
        qDebug() << "Data recv: " << charToHex(readBuf);
    }
}

QByteArray MainWindow::charToHex(QByteArray chr)
{
    QByteArray tempHex = chr.toHex().toUpper();
    QByteArray resultHex;

    for (int i = 0; i < tempHex.length() / 2; i++) {
        resultHex += tempHex.mid(i * 2, 2) + " ";
    }

    return resultHex;
}

void MainWindow::send_cmd(void *dat, unsigned int len)
{
//    unsigned int i;
    unsigned char *data;

    data = (unsigned char *)dat;
//    printf("len: %d -", len);
//    for (i = 0; i < len; i++) {
//        printf(" %02x", data[i]);
//    }
//    printf("\n");
//    fflush(NULL);

    if (! isSerialOpened) {
        openSerial();
    }
    if (isSerialOpened) {
        comPort->write((const char *)data, (qint64)len);
    }
}

void MainWindow::on_up_pressed()
{
    send_cmd((void *)protocol_up(addr, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_leftUp_pressed()
{
    send_cmd((void *)protocol_left_top(addr, pan_speed, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_rightUp_pressed()
{
    send_cmd((void *)protocol_right_top(addr, pan_speed, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_left_pressed()
{
    send_cmd((void *)protocol_left(addr, pan_speed), PELCO_D_LEN);
}

void MainWindow::on_right_pressed()
{
    send_cmd((void *)protocol_right(addr, pan_speed), PELCO_D_LEN);
}

void MainWindow::on_leftDown_pressed()
{
    send_cmd((void *)protocol_left_bottom(addr, pan_speed, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_down_pressed()
{
    send_cmd((void *)protocol_down(addr, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_rightDown_pressed()
{
    send_cmd((void *)protocol_right_bottom(addr, pan_speed, tilt_speed), PELCO_D_LEN);
}

void MainWindow::on_stop_clicked()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_up_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_leftUp_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_rightUp_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_left_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_right_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_leftDown_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_down_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_rightDown_released()
{
    send_cmd((void *)protocol_stop(addr), PELCO_D_LEN);
}

void MainWindow::on_panTurbo_toggled(bool checked)
{
    if (checked) {
        ui->panSpeed->setEnabled(false);
        pan_speed = 0xff;
    } else {
        ui->panSpeed->setEnabled(true);
        pan_speed = ui->panSpeed->value();
    }
}

void MainWindow::on_tiltTurbo_toggled(bool checked)
{
    if (checked) {
        ui->tiltSpeed->setEnabled(false);
        tilt_speed = 0xff;
    } else {
        ui->tiltSpeed->setEnabled(true);
        tilt_speed = ui->tiltSpeed->value();
    }
}

void MainWindow::on_panSpeed_valueChanged(int arg1)
{
    pan_speed = arg1;
}

void MainWindow::on_tiltSpeed_valueChanged(int arg1)
{
    tilt_speed = arg1;
}

void MainWindow::on_ptzAddr_valueChanged(int arg1)
{
    addr = arg1;
}

void MainWindow::on_baudRate_currentTextChanged(const QString &arg1)
{
    baudRate = arg1.toInt();
    comPort->setBaudRate(baudRate);
}
