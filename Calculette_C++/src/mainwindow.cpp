#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusMinus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_mulitply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_mulitply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    QString newLabel;
    double labelNumber;

    if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() || ui->pushButton_mulitply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))
    {
        labelNumber = button->text().right(1).toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g',15);
    }
    else
    {
        if (ui->label->text().contains('.') && button->text().right(1) == "0")
        {
            newLabel = (ui->label->text() + button->text().right(1));
        }
        else
        {
            labelNumber = (ui->label->text() + button->text().right(1)).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }

        ui->label->setText(newLabel);

    }




    ui->label-> setText(newLabel);


}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText(ui->label->text().append("."));
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    QString newLabel;
    double labelNumber;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_mulitply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");
}

void MainWindow::on_pushButton_equals_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        ui->pushButton_add->setChecked(false);

    }
    if(ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->pushButton_subtract->setChecked(false);
    }
    if(ui->pushButton_mulitply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        ui->pushButton_mulitply->setChecked(false);
    }
    if(ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        ui->pushButton_divide->setChecked(false);
    }

    newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);

    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton *) sender();

    firstNum = ui->label->text().toDouble();



    button->setChecked(true);
}
