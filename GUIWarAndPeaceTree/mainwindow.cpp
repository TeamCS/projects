#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include "Tokenization.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Atable->setColumnWidth(2, 1000);
    ui->Atable_2->setColumnWidth(2, 1000);
    ui->Atable_3->setColumnWidth(2, 1000);
    ui->Atable_4->setColumnWidth(2, 1000);
    ui->Atable_5->setColumnWidth(2, 1000);
    ui->Atable_6->setColumnWidth(2, 1000);
    ui->Atable_7->setColumnWidth(2, 1000);
    ui->Atable_8->setColumnWidth(2, 1000);
    ui->Atable_9->setColumnWidth(2, 1000);
    ui->Atable_10->setColumnWidth(2, 1000);
    ui->Atable_11->setColumnWidth(2, 1000);
    ui->Atable_12->setColumnWidth(2, 1000);
    ui->Atable_13->setColumnWidth(2, 1000);
    ui->Atable_14->setColumnWidth(2, 1000);
    ui->Atable_15->setColumnWidth(2, 1000);
    ui->Atable_16->setColumnWidth(2, 1000);
    ui->Atable_17->setColumnWidth(2, 1000);
    ui->Atable_18->setColumnWidth(2, 1000);
    ui->Atable_19->setColumnWidth(2, 1000);
    ui->Atable_20->setColumnWidth(2, 1000);
    ui->Atable_21->setColumnWidth(2, 1000);
    ui->Atable_22->setColumnWidth(2, 1000);
    ui->Atable_23->setColumnWidth(2, 1000);
    ui->Atable_24->setColumnWidth(2, 1000);
    ui->Atable_25->setColumnWidth(2, 1000);
    ui->Atable_26->setColumnWidth(2, 1000);
    //set the width for the 3rd column of each table in each tab.

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Tokenization Book;

    QString filename = QFileDialog::getOpenFileName
            (
                this,
                tr("Open File"),
                "C:\\",
                "Text File(*.txt)"

            );
    //default folder path for clicking the button
    //and type that will be displayed

//===================================Choose a file to open===============================================
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "file name: ", file.errorString());
    else
    {
        QTextStream in(&file);

        ui->BookText->setText(in.readAll());   //on text browser "BookText", display the novel.

//=======================================Analysizing the text===========================================

        const char* filenameCstring = filename.toStdString().c_str();


//=====================================Table Modification===============================================
        int posBuffer = 0;
//---------------------------------A--------------------------------

        ui->Summary_27->setText(QString::fromStdString(Book.Tokenize(filenameCstring)));

        for(int i = 0; i<Book.EachLetterCount[0]; i++)             //create enough rows for words starts with A
        {
            const int x = ui->Atable->rowCount();
            ui->Atable->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[0]; i++)            //fill the table with the word, the count, and all locations
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable->setItem(i, 2, location);

            posBuffer++;
        }

//---------------------------------B--------------------------------

        for(int i = 0; i<Book.EachLetterCount[1]; i++)
        {
            const int x = ui->Atable_2->rowCount();
            ui->Atable_2->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[1]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_2->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_2->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_2->setItem(i, 2, location);

            posBuffer++;

        }


//---------------------------------C--------------------------------

        for(int i = 0; i<Book.EachLetterCount[2]; i++)
        {
            const int x = ui->Atable_3->rowCount();
            ui->Atable_3->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[2]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_3->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_3->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_3->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------D--------------------------------

        for(int i = 0; i<Book.EachLetterCount[3]; i++)
        {
            const int x = ui->Atable_4->rowCount();
            ui->Atable_4->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[3]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_4->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_4->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_4->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------E--------------------------------

        for(int i = 0; i<Book.EachLetterCount[4]; i++)
        {
            const int x = ui->Atable_5->rowCount();
            ui->Atable_5->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[4]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_5->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_5->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_5->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------F--------------------------------

        for(int i = 0; i<Book.EachLetterCount[5]; i++)
        {
            const int x = ui->Atable_6->rowCount();
            ui->Atable_6->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[5]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_6->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_6->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_6->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------G--------------------------------

        for(int i = 0; i<Book.EachLetterCount[6]; i++)
        {
            const int x = ui->Atable_7->rowCount();
            ui->Atable_7->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[6]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_7->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_7->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_7->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------H--------------------------------

        for(int i = 0; i<Book.EachLetterCount[7]; i++)
        {
            const int x = ui->Atable_8->rowCount();
            ui->Atable_8->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[7]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_8->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_8->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_8->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------I--------------------------------

        for(int i = 0; i<Book.EachLetterCount[8]; i++)
        {
            const int x = ui->Atable_9->rowCount();
            ui->Atable_9->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[8]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_9->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_9->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_9->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------J--------------------------------

        for(int i = 0; i<Book.EachLetterCount[9]; i++)
        {
            const int x = ui->Atable_10->rowCount();
            ui->Atable_10->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[9]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_10->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_10->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_10->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------K--------------------------------

        for(int i = 0; i<Book.EachLetterCount[10]; i++)
        {
            const int x = ui->Atable_11->rowCount();
            ui->Atable_11->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[10]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_11->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_11->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_11->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------L--------------------------------

        for(int i = 0; i<Book.EachLetterCount[11]; i++)
        {
            const int x = ui->Atable_12->rowCount();
            ui->Atable_12->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[11]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_12->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_12->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_12->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------M--------------------------------

        for(int i = 0; i<Book.EachLetterCount[12]; i++)
        {
            const int x = ui->Atable_13->rowCount();
            ui->Atable_13->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[12]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_13->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_13->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_13->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------N--------------------------------

        for(int i = 0; i<Book.EachLetterCount[13]; i++)
        {
            const int x = ui->Atable_14->rowCount();
            ui->Atable_14->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[13]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_14->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_14->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_14->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------O--------------------------------

        for(int i = 0; i<Book.EachLetterCount[14]; i++)
        {
            const int x = ui->Atable_15->rowCount();
            ui->Atable_15->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[14]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_15->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_15->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_15->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------P--------------------------------

        for(int i = 0; i<Book.EachLetterCount[15]; i++)
        {
            const int x = ui->Atable_16->rowCount();
            ui->Atable_16->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[15]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_16->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_16->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_16->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------Q--------------------------------

        for(int i = 0; i<Book.EachLetterCount[16]; i++)
        {
            const int x = ui->Atable_17->rowCount();
            ui->Atable_17->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[16]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_17->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_17->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_17->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------R--------------------------------

        for(int i = 0; i<Book.EachLetterCount[17]; i++)
        {
            const int x = ui->Atable_18->rowCount();
            ui->Atable_18->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[17]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_18->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_18->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_18->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------S--------------------------------

        for(int i = 0; i<Book.EachLetterCount[18]; i++)
        {
            const int x = ui->Atable_19->rowCount();
            ui->Atable_19->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[18]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_19->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_19->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_19->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------T--------------------------------

        for(int i = 0; i<Book.EachLetterCount[19]; i++)
        {
            const int x = ui->Atable_20->rowCount();
            ui->Atable_20->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[19]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_20->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_20->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_20->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------U--------------------------------

        for(int i = 0; i<Book.EachLetterCount[20]; i++)
        {
            const int x = ui->Atable_21->rowCount();
            ui->Atable_21->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[20]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_21->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_21->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_21->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------V--------------------------------

        for(int i = 0; i<Book.EachLetterCount[21]; i++)
        {
            const int x = ui->Atable_22->rowCount();
            ui->Atable_22->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[21]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_22->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_22->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_22->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------W--------------------------------

        for(int i = 0; i<Book.EachLetterCount[22]; i++)
        {
            const int x = ui->Atable_23->rowCount();
            ui->Atable_23->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[22]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_23->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_23->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_23->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------X--------------------------------

        for(int i = 0; i<Book.EachLetterCount[23]; i++)
        {
            const int x = ui->Atable_24->rowCount();
            ui->Atable_24->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[23]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_24->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_24->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_24->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------Y--------------------------------

        for(int i = 0; i<Book.EachLetterCount[24]; i++)
        {
            const int x = ui->Atable_25->rowCount();
            ui->Atable_25->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[24]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_25->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_25->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_25->setItem(i, 2, location);

            posBuffer++;

        }
//---------------------------------Z--------------------------------

        for(int i = 0; i<Book.EachLetterCount[25]; i++)
        {
            const int x = ui->Atable_26->rowCount();
            ui->Atable_26->insertRow(x);
        }


        for(int i = 0; i < Book.EachLetterCount[25]; i++)
        {
            QTableWidgetItem *word = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].data));
            ui->Atable_26->setItem(i, 0, word);

            QTableWidgetItem *integer = new QTableWidgetItem(QString::number(Book.WordCount[posBuffer]));
            ui->Atable_26->setItem(i, 1, integer);

            QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(Book.WordList[posBuffer].LinePara));
            ui->Atable_26->setItem(i, 2, location);

            posBuffer++;

        }

//=====================================End of if-else========================================
    }
}
