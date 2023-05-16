
#include "prwindow.h"
#include "ui_PRWindow.h"
#include <QLabel>
#include <QPushButton>
#include "../LinderLab1A-master/LinderLab1A/RPolynomial.h"
#include "../LinderLab1A-master/LinderLab1A/FPolynomial.h"
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
    ui->RadioButtonLayout->addWidget(QuatientBtn,2,4);


    FirstPol = new QLineEdit(this);
    FirstPol->setFixedWidth(300);
    QLabel* label1 = new QLabel("Перший многочлен: ", this);
    ui->gridLayout->addWidget(label1,0,1);
    ui->gridLayout->addWidget(FirstPol,0,2);

    SecondPol = new QLineEdit(this);
    SecondPol->setFixedWidth(300);
    QLabel* label2 = new QLabel("Другий многочлен: ", this);
    ui->gridLayout->addWidget(label2,1,1);
    ui->gridLayout->addWidget(SecondPol,1,2);

    Value = new QLineEdit(this);
    Value->setFixedWidth(300);
    QLabel* label3 = new QLabel("Значення або порядок ", this);
    ui->gridLayout->addWidget(label3,2,1);
    ui->gridLayout->addWidget(Value,2,2);

    Modulo = new QLineEdit(this);
    Modulo->setFixedWidth(300);
    QLabel* label4 = new QLabel("Розмір поля ", this);
    ui->gridLayout->addWidget(label4,3,1);
    ui->gridLayout->addWidget(Modulo,3,2);

    calculateBtn = new QPushButton("Виконати операцію",this);
    calculateBtn->setFont(QFont("Arial", 12, QFont::Bold));
    ui->btnLayout->addWidget(calculateBtn);
    connect(calculateBtn,&QPushButton::clicked,this,&PRWindow::proccesOperation);
}
PRWindow::~PRWindow()
{
    delete ui;
}


void PRWindow::proccesOperation(){

    if(AdditionBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = pol1 + pol2;
        ui->result->append(FirstPol->text() + "+" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(SubstractionBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = pol1 - pol2;
        ui->result->append(FirstPol->text() + "-" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(MultiplicationBtn->isChecked()){
        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = pol1 * pol2;
        ui->result->append(FirstPol->text() + "*" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(DerrivitiveBtn->isChecked()){
        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);

        FPolynomial res = pol1.derivative();
        ui->result->append("Derivative: " + FirstPol->text() +  "=" + QString::fromStdString(res.toString()));
    }
    else if(ValueBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FiniteNumber num(Value->text().toStdString(), p);
        FiniteNumber res = pol1.valueAt(num);
        ui->result->append("Value of " +  FirstPol->text() + "at " + Value->text() + +  "=" + QString::fromStdString(res.toString()));
    }
    if(RemainderBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = pol1 % pol2;
        ui->result->append(FirstPol->text() + "%" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    if(GCD->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = FPolynomial::GCD(pol1,pol2);
        ui->result->append("GCD(" + FirstPol->text() + "," + SecondPol->text()+ ")" + "=" + QString::fromStdString(res.toString()));
    }
    if(CyclomiticBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());
        PositiveNumber order(Value->text().toStdString());

        auto f = FiniteField(p);

        FPolynomial res =  FPolynomial::cyclotomic(order, f);
        ui->result->append("Cyclomitic of order " + QString::fromStdString(order.toString()) +  "=" + QString::fromStdString(res.toString()));
    }
    if(QuatientBtn->isChecked()){

        PositiveNumber p(Modulo->text().toStdString());

        FPolynomial pol1(FirstPol->text().toStdString(), p);
        FPolynomial pol2(SecondPol->text().toStdString(), p);
        FPolynomial res = pol1 / pol2;
        ui->result->append(FirstPol->text() + "/" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    }

