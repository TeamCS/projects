#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QCoreApplication>
#include "Parsing.h"

QString style3 = "QPushButton:pressed{background-color: rgb(204, 255, 255); border-style: inset;border-width: 1px;border-radius: 4px;font: bold 15px;}";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

//--------------------------------------------define window and label and customization-----------------------------------------------
    QString style1 = "QMainWindow { background-color: rgb(0, 0, 204); border-style: outset; border-width: 10px; border-radius: 20px; border-color: beige;}";  //customize mainwindow
    this->setStyleSheet(style1);

    label=new QLabel("0",this);
    label->setGeometry(QRect(QPoint(50, 50), QSize(400, 100)));
    FontSize();


//  label->setStyleSheet("border: 5px solid black");  //different format to customize the label
    QString style2 = "QLabel { background-color: rgb(0, 204, 102);border-style: outset; border-width: 5px; border-radius: 5px; border-color: beige;}";  //customize the label
    label->setStyleSheet(style2);


//-------------------------------------------customize each button and connect to their functionality-----------------------------------------------------------------


    clear_button=new QPushButton("C", this);
    clear_button->setGeometry(QRect(QPoint(230, 200), QSize(50, 50)));
    connect(clear_button, SIGNAL(released()), this, SLOT(clear()));
    clear_button->setStyleSheet(style3);


    add_button=new QPushButton("+", this);
    add_button->setGeometry(QRect(QPoint(280, 400), QSize(50, 50)));
    connect(add_button, SIGNAL(released()), this, SLOT(add()));
    add_button->setStyleSheet(style3);


    sub_button=new QPushButton("-", this);
    sub_button->setGeometry(QRect(QPoint(280, 350), QSize(50, 50)));
    connect(sub_button, SIGNAL(released()), this, SLOT(sub()));
    sub_button->setStyleSheet(style3);

    mul_button=new QPushButton("*", this);
    mul_button->setGeometry(QRect(QPoint(280, 300), QSize(50, 50)));
    connect(mul_button, SIGNAL(released()), this, SLOT(mul()));
    mul_button->setStyleSheet(style3);

    div_button=new QPushButton("/", this);
    div_button->setGeometry(QRect(QPoint(280, 250), QSize(50, 50)));
    connect(div_button, SIGNAL(released()), this, SLOT(div()));
    div_button->setStyleSheet(style3);

    pow_button=new QPushButton("^", this);
    pow_button->setGeometry(QRect(QPoint(330, 250), QSize(50, 50)));
    connect(pow_button, SIGNAL(released()), this, SLOT(pow()));
    pow_button->setStyleSheet(style3);

    leftP_button=new QPushButton("(", this);
    leftP_button->setGeometry(QRect(QPoint(330, 300), QSize(50, 50)));
    connect(leftP_button, SIGNAL(released()), this, SLOT(leftP()));
    leftP_button->setStyleSheet(style3);

    rightP_button=new QPushButton(")", this);
    rightP_button->setGeometry(QRect(QPoint(330, 350), QSize(50, 50)));
    connect(rightP_button, SIGNAL(released()), this, SLOT(rightP()));
    rightP_button->setStyleSheet(style3);

    equal_button=new QPushButton("=", this);
    equal_button->setGeometry(QRect(QPoint(230, 400), QSize(50, 50)));
    connect(equal_button, SIGNAL(released()), this, SLOT(equal()));
    equal_button->setStyleSheet(style3);

    neg_button=new QPushButton("neg", this);
    neg_button->setGeometry(QRect(QPoint(330, 400), QSize(50, 50)));
    connect(neg_button, SIGNAL(released()), this, SLOT(neg()));
    neg_button->setStyleSheet(style3);

    dot_button=new QPushButton(".", this);
    dot_button->setGeometry(QRect(QPoint(130, 400), QSize(50, 50)));
    connect(dot_button, SIGNAL(released()), this, SLOT(dot()));
    dot_button->setStyleSheet(style3);

    del_button=new QPushButton("del", this);
    del_button->setGeometry(QRect(QPoint(280, 200), QSize(50, 50)));
    connect(del_button, SIGNAL(released()), this, SLOT(del()));
    del_button->setStyleSheet(style3);

    fraction_button=new QPushButton("frac", this);
    fraction_button->setGeometry(QRect(QPoint(330, 200), QSize(50, 50)));
    connect(fraction_button, SIGNAL(released()), this, SLOT(fraction()));
    fraction_button->setStyleSheet(style3);


//----------------------------------number button connections----------------------------------

    for(int i=0;i<10;i++)
    {
        QString digit=QString::number(i);
        num_button[i]=new QPushButton(digit, this);
        connect(num_button[i], SIGNAL(released()), this, SLOT(buttonPushed()));

        num_button[i]->setStyleSheet(style3);

    }

    setGeo();

}

MainWindow::~MainWindow()
{

}

void MainWindow::FontSize()
{
    //set font size and bold
    QFont font = label->font();
    font.setPointSize(15);
    font.setBold(true);
    label->setFont(font);

}

string MainWindow::getScreenText()
{
    string stdStr;
    stdStr = ScreenText.toStdString();
    return stdStr;
}

void MainWindow::clear()
{
    ScreenText="";
    label->setText("0");
    FontSize();
}

//--------------------------------------------------number buttons---------------------------------------------------------
void MainWindow::buttonPushed()
{
    QPushButton *num_button = (QPushButton *)sender();

    emit numberEmitted(num_button->text()[0].digitValue());  //grabing number emitted from button created above

    ScreenText+=QString::number(num_button->text()[0].digitValue());   //the number from emit is converted to Qstring
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::setGeo()
{
    num_button[0]->setGeometry(QRect(QPoint(180, 400), QSize(50, 50)));


    for(int i=1; i<4;i++)
    {
        num_button[i]->setGeometry(QRect(QPoint(80+50*i, 350), QSize(50, 50)));
    }
    for(int i=4; i<7;i++)
    {
        num_button[i]->setGeometry(QRect(QPoint(80+50*(i-3), 300), QSize(50, 50)));
    }
    for(int i=7; i<10;i++)
    {
        num_button[i]->setGeometry(QRect(QPoint(80+50*(i-6), 250), QSize(50, 50)));
    }
}

//----------------------------------what each button does is specified here----------------------------------------------



void MainWindow::add()
{
    ScreenText=ScreenText+" + ";
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::sub()
{
    ScreenText=ScreenText+" - ";
    label->setText(ScreenText);
    FontSize();

}

void MainWindow::mul()
{
    ScreenText=ScreenText+" * ";
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::div()
{
    ScreenText=ScreenText+" / ";
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::pow()
{
    ScreenText=ScreenText+" ^ ";
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::leftP()
{
    ScreenText=ScreenText+" ( ";
    label->setText(ScreenText);
    FontSize();
}

void MainWindow::rightP()
{
    ScreenText=ScreenText+" ) ";
    label->setText(ScreenText);
    FontSize();

}

void MainWindow::equal()
{
    string equ, RPN, result;
    equ = ScreenText.toStdString();


    Parsing parser;

    try
    {
        parser.ParseString(equ);
        RPN=parser.RPNstring();
        result=parser.calc();


        //ScreenText=ScreenText.fromStdString(RPN);
        //ScreenText=ScreenText+ " = " + ScreenText.fromStdString(result);


        if(result=="")
        {
            ScreenText="";
            label->setText("0");
            FontSize();

        }
        else
        {
            ScreenText=ScreenText.fromStdString(result);
            label->setText(ScreenText);
            FontSize();
        }
    }    
    catch(ERRORS e)       //if an error is catched, the error message will be displayed in the label
    {
        QString text;

        int i=e;

        switch(i)
        {
        case 0:
            text="DATATYPE_MISMATCH";
            break;
        case 1:
            text="INVALID_EQU_FORMAT";
            break;
        case 2:
            text="INVALID_EQU_FORMAT";
            break;
        case 3:
            text="INVALID_EQU_FORMAT";
            break;
        case 4:
            text="INVALID_EQU_FORMAT";
            break;
        case 5:
            text="INVALID_EQU_FORMAT";
            break;
        case 6:
            text="INVALID_EQU_FORMAT";
            break;
        case 7:
            text="DIVIDE_BY_ZERO";
            break;
        case 8:
            text="NO_LEFT_PAREN";
            break;
        case 9:
            text="MIS_MATCH_PATHEN";
            break;
        }


        ScreenText="";
        label->setText(text);
        FontSize();
    }

}

void MainWindow::neg()
{
    ScreenText=ScreenText+"-";
    label->setText(ScreenText);
    FontSize();

}

void MainWindow::dot()
{
    ScreenText=ScreenText+".";
    label->setText(ScreenText);
    FontSize();

}

void MainWindow::del()
{
    int TextSize=ScreenText.size();

    if(ScreenText.size()!=0)
    {
        if(ScreenText[TextSize-1]==' ')
            ScreenText.remove(TextSize-2, 2);
        else
            ScreenText.remove(TextSize-1, 1);

        label->setText(ScreenText);
        FontSize();

    }
    else
        clear();
}

void MainWindow::fraction()
{
    ScreenText=ScreenText+"/";
    label->setText(ScreenText);
    FontSize();

}


//===============================end=====================================
