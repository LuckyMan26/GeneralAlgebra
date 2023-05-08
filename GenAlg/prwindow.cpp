
#include "prwindow.h"
#include "ui_PRWindow.h"
#include <QLabel>
#include <QPushButton>
#include "../LinderLab1A-master/LinderLab1A/RPolynomial.h"
PRWindow::PRWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::PRWindow)
{
    ui->setupUi(this);
    AdditionBtn = new QRadioButton("Додавання", this);
    SubstractionBtn = new QRadioButton("Віднімання", this);
    MultiplicationBtn = new QRadioButton("Множення", this);
    DerrivitiveBtn = new QRadioButton("Похідна", this);
    ValueBtn = new QRadioButton("Значення в точці", this);
    RemainderBtn = new QRadioButton("Остача", this);
    QuatientBtn = new QRadioButton("Частка", this);
    GCD = new QRadioButton("НСД", this);
    CyclomiticBtn = new QRadioButton("Круговий многочлен заданого порядка", this);


    ui->RadioButtonLayout->addWidget(AdditionBtn,1,0);
    ui->RadioButtonLayout->addWidget(SubstractionBtn,1,1);
    ui->RadioButtonLayout->addWidget(MultiplicationBtn,1,2);
    ui->RadioButtonLayout->addWidget(DerrivitiveBtn,1,3);
    ui->RadioButtonLayout->addWidget(ValueBtn,2,0);
    ui->RadioButtonLayout->addWidget(RemainderBtn,2,1);
    ui->RadioButtonLayout->addWidget(GCD,2,2);
    ui->RadioButtonLayout->addWidget(CyclomiticBtn,2,3);


    FirstPol = new QLineEdit(this);
    QLabel* label1 = new QLabel("Перший многочлен: ", this);
    ui->gridLayout->addWidget(label1,0,1);
    ui->gridLayout->addWidget(FirstPol,0,2);
    SecondPol = new QLineEdit(this);
    QLabel* label2 = new QLabel("Другий многочлен: ", this);
    ui->gridLayout->addWidget(label2,1,1);
    ui->gridLayout->addWidget(SecondPol,1,2);
    QLabel* label3 = new QLabel("Значення або порядок ", this);
    Value = new QLineEdit(this);
    ui->gridLayout->addWidget(label3,2,1);
    ui->gridLayout->addWidget(Value,2,2);

    calculateBtn = new QPushButton("Виконати операцію",this);
    ui->btnLayout->addWidget(calculateBtn);
    connect(calculateBtn,&QPushButton::clicked,this,&PRWindow::proccesOperation);
}
PRWindow::~PRWindow()
{
    delete ui;
}


void PRWindow::proccesOperation(){

    if(AdditionBtn->isChecked()){

        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = pol1 + pol2;
        ui->result->append(FirstPol->text() + "+" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(SubstractionBtn->isChecked()){

        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = pol1 - pol2;
        ui->result->append(FirstPol->text() + "-" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(MultiplicationBtn->isChecked()){

        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = pol1 * pol2;
        ui->result->append(FirstPol->text() + "*" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(DerrivitiveBtn->isChecked()){
        RPolynomial pol1(FirstPol->text().toStdString());

        RPolynomial res = pol1.derivative();
        ui->result->append("Derivative: " + FirstPol->text() +  "=" + QString::fromStdString(res.toString()));
    }
    else if(ValueBtn->isChecked()){

        RPolynomial pol1(FirstPol->text().toStdString());
        SignedNumber num(Value->text().toStdString());
        SignedNumber res = pol1.valueAt(num);
        ui->result->append("Value of " +  FirstPol->text() + "at " + Value->text() + +  "=" + QString::fromStdString(res.toString()));
    }
    if(RemainderBtn->isChecked()){

        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = pol1 % pol2;
        ui->result->append(FirstPol->text() + "%" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    if(GCD->isChecked()){


        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = RPolynomial::GCD(pol1,pol2);
        ui->result->append("GCD(" + FirstPol->text() + "," + SecondPol->text()+ ")" + "=" + QString::fromStdString(res.toString()));
    }
    if(CyclomiticBtn->isChecked()){


        PositiveNumber order(Value->text().toStdString());
        RPolynomial res =  RPolynomial::cyclotomic(order);
        ui->result->append("Cyclomitic of order " + QString::fromStdString(order.toString()) +  "=" + QString::fromStdString(res.toString()));
    }
    if(QuatientBtn->isChecked()){


        RPolynomial pol1(FirstPol->text().toStdString());
        RPolynomial pol2(SecondPol->text().toStdString());
        RPolynomial res = pol1 / pol2;
        ui->result->append(FirstPol->text() + "/" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    }

