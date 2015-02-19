/*
We, Jason Chen and Xizhao Deng, do hereby certify that we have derived no assistance for this project
or examination from any sources whatever, whether oral, written, or in print. We also
understand that if it is found that we have received unauthorized assistance, then we
and the individuals involved will receive a failing grade.

Notes:
 1. the GUI of the calculator is written with the help from this follow Youtube
    tutorial series:

    "QT C++ GUI Calculator Tutorial" by EwokHugz
    http://www.youtube.com/watch?v=Zb3QTRWpnJc

 2. customization method mainly comes from the QT Gui Reference:
    http://doc-snapshot.qt-project.org/4.8/stylesheet-examples.html
    http://qt-project.org/doc/qt-4.8/stylesheet-reference.html#list-of-properties

 3. the RPN transformation algorithm is from:
    http://en.wikipedia.org/wiki/Shunting-yard_algorithm

*/

//=========================================================================
/*
    To do:
    1. document your part

*/
//=========================================================================

#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include "include.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//=========================================================================================
    int i=FULL;
    cout << "enum: " <<i <<endl;

    w.showMaximized();
    w.setFixedSize(500, 500);  //set the size of the window
    w.setWindowTitle("Calculator"); //name the window

   // w.setStyleSheet("border: 2px solid yellow"); //the other way to customize window


    w.move(QApplication::desktop()->screen()->rect().center()-w.rect().center()); //initial the window in the center of the screen
    w.show(); //display the window




//=========================================================================================

    return a.exec();
}
