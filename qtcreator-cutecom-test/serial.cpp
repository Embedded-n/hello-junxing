#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    system_init();
}

Serial::~Serial()
{
    delete ui;
}
/* function*/
void Serial::system_init()
{
    //port config
    global_port.setParity(QSerialPort::NoParity);
    global_port.setDataBits(QSerialPort::Data8);
    global_port.setStopBits(QSerialPort::OneStop);

    connect(ui->btn_open,&QPushButton::clicked,this,&Serial::btn_open_port);
    connect(ui->btn_close,&QPushButton::clicked,this,&Serial::btn_close_port);
    connect(ui->btn_send,&QPushButton::clicked,this,&Serial::btn_send_data);
    connect(&global_port,&QSerialPort::readyRead,this,&Serial::receive_data);
}
void Serial::btn_open_port(bool)
{
   // qDebug()<<"ok";
   // int i =10;
   //qDebug("%d",i);
    /**/
    qDebug() << ui->cmb_port_name->currentIndex();//pintf 0
    switch (ui->cmb_port_name->currentIndex()) {
    case 0:
        global_port.setPortName("COM1");
    case 1:
        global_port.setPortName("COM2");
    case 2:
        global_port.setPortName("COM3");
    case 3:
        global_port.setPortName("COM4");
    case 4:
        global_port.setPortName("COM5");
    case 5:
        global_port.setPortName("COM6");
    case 6:
        global_port.setPortName("COM7");
    case 7:
        global_port.setPortName("COM8");
    case 8:
        global_port.setPortName("COM9");
    case 9:
        global_port.setPortName("COM10");
    case 10:
        global_port.setPortName("COM11");
    case 11:
        global_port.setPortName("COM12");
        break;
    default:
    case 12:
        global_port.setPortName("COM13");
        break;
        /*BAUD RATE*/
    }
    switch (ui->cmb_baud_rate->currentIndex()) {
    case 0:
       global_port.setBaudRate(QSerialPort::Baud115200);
    case 1:
       global_port.setBaudRate(QSerialPort::Baud57600);
    case 2:
       global_port.setBaudRate(QSerialPort::Baud38400);
    case 3:
       global_port.setBaudRate(QSerialPort::Baud19200);
    case 4:
       global_port.setBaudRate(QSerialPort::Baud9600);
    case 5:
       global_port.setBaudRate(QSerialPort::Baud4800);
    case 6:
       global_port.setBaudRate(QSerialPort::Baud2400);
        break;
    default:
        global_port.setBaudRate(QSerialPort::Baud1200);
        break;
    }
    //open
    global_port.open(QIODevice::ReadWrite);
    ui->lab_status->setText("Connectted");
    //TEST
   // global_port.write("1");

}
void Serial::btn_close_port(bool)
{
    ui->lab_status->setText("DisConnectted");
    global_port.close();

}
 /*-------------------------*/
void Serial::btn_send_data(bool)
{
   QString data = ui->lint_send_data->text();
   QByteArray array = data.toLatin1();
    global_port.write(array);
}
/*-----------receive data---------------*/
void Serial::receive_data()
{

    QByteArray array = global_port.readAll();
    qDebug()<<array;
    if(ui->checkBox->checkState() == Qt::Checked){
        ui->plainTextEdit->insertPlainText(QString(array.toHex(' ').toUpper().append(' ')));

    }else{

    ui->plainTextEdit->insertPlainText(QString(array));
    }
}
