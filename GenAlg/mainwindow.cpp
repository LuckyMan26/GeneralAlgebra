#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finitefieldwindow.h"
#include "prwindow.h"
#include "fpolinomialwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PRBtn_clicked()
{
    PRWindow window(this);
    window.exec();
}


void MainWindow::on_FiniteFieldBtn_clicked()
{
    FiniteFieldWindow window(this);
    window.exec();
}


void MainWindow::on_PFBtn_clicked()
{
    FPolynomialWindow window(this);
    window.exec();
}

