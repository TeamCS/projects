/*We, Jason Chen and Xizhao Deng, do hereby certify that we have derived no assistance for this project
or examination from any sources whatever, whether oral, written, or in print. We also
understand that if it is found that we have received unauthorized assistance, then we
and the individuals involved will receive a failing grade.


Notes:
1. To use this program, put the abbrev.txt  abbreviation.txt contrac.txt into the compile folder
2. Make sure the default path for click button is valid on this computer that user has
3. the saved data will be in the compile folder

*/


#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
