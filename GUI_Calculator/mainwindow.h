#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    string getScreenText();  //grab the screentext and return as a string
    void FontSize();  //set font size and bold in the label

    QString ScreenText; //stores the output

signals:
    void numberEmitted(int number); //used for defined number buttons

private slots:   //these void functions specifies what the buttons do once they are pressed
    void clear(); //clear the equation

    void add();
    void sub();
    void mul();
    void div();
    void pow();
    void leftP();
    void rightP();
    void equal();
    void neg();  //enter a negative number
    void dot(); //enter a decimal number

    void del();  //delete an operator or a number
    void fraction(); //enter a fraction separator

    void buttonPushed(); //used for defining number buttons

    void setGeo(); //set the geometry of the number buttons



private:
    QLabel *label;

    //here declears the buttons with QT GUI QPushButton
    QPushButton *clear_button;
    QPushButton *add_button;
    QPushButton *sub_button;
    QPushButton *mul_button;
    QPushButton *div_button;
    QPushButton *pow_button;
    QPushButton *leftP_button;
    QPushButton *rightP_button;
    QPushButton *equal_button;
    QPushButton *neg_button;
    QPushButton *dot_button;

    QPushButton *del_button;
    QPushButton *fraction_button;

    QPushButton *num_button[10]; //stores the number buttons 0-9


};

#endif // MAINWINDOW_H
