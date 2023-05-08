#include "finitefieldwindow.h"
#include "ui_FiniteFieldWindow.h"
#include "FiniteNumber.h"
#include "Exponent.h"
#include "Pollard.h"
#include "Euler.h"
#include <QLabel>
FiniteFieldWindow::FiniteFieldWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::FiniteFieldWindow)
{

    ui->setupUi(this);
    AdditionBtn = new QRadioButton("Додавання", this);
    SubstractionBtn = new QRadioButton("Віднімання", this);
    MultiplicationBtn = new QRadioButton("Множення", this);
    InverseBtn = new QRadioButton("Обернений", this);
    DividingBtn = new QRadioButton("Ділення", this);
    PowerBtn = new QRadioButton("Додавання", this);
    FactorizationNaive = new QRadioButton("Віднімання", this);
    FactorizationRho = new QRadioButton("Множення", this);
    SquareRoot = new QRadioButton("Квадратний корінь", this);
    Logarithm = new QRadioButton("Дискретний Логарифм", this);
    Order = new QRadioButton("Порядок Елемента", this);
    Phi = new QRadioButton("Функція Ейлера", this);
    Lambda = new QRadioButton("Функція Кармайкла", this);
    Miller_Rabin = new QRadioButton("Перевірка на простоту(Міллер Рабін)", this);

    ui->RadioButtonLayout->addWidget(AdditionBtn,1,0);
    ui->RadioButtonLayout->addWidget(SubstractionBtn,1,1);
    ui->RadioButtonLayout->addWidget(MultiplicationBtn,1,2);
    ui->RadioButtonLayout->addWidget(InverseBtn,1,3);
    ui->RadioButtonLayout->addWidget(DividingBtn,1,4);
    ui->RadioButtonLayout->addWidget(PowerBtn,1,5);
    ui->RadioButtonLayout->addWidget(FactorizationNaive,1,6);
    ui->RadioButtonLayout->addWidget(FactorizationRho,2,0);
    ui->RadioButtonLayout->addWidget(SquareRoot,2,1);
    ui->RadioButtonLayout->addWidget(Logarithm,2,2);
    ui->RadioButtonLayout->addWidget(Order,2,3);
    ui->RadioButtonLayout->addWidget(Phi,2,4);
    ui->RadioButtonLayout->addWidget(Lambda,2,5);
    ui->RadioButtonLayout->addWidget(Miller_Rabin,2,6);

    FirstNumber = new QLineEdit(this);
    QLabel* label1 = new QLabel("Перше число: ", this);
    ui->gridLayout->addWidget(label1,0,1);
    ui->gridLayout->addWidget(FirstNumber,0,2);
    SecondNumber = new QLineEdit(this);
    QLabel* label2 = new QLabel("Друге число: ", this);
    ui->gridLayout->addWidget(label2,1,1);
    ui->gridLayout->addWidget(SecondNumber,1,2);


    FieldModule = new QLineEdit(this);
    QLabel* label4 = new QLabel("Розмір поля: ", this);
    ui->gridLayout->addWidget(label4,2,1);
    ui->gridLayout->addWidget(FieldModule,2,2);
    calculateBtn = new QPushButton("Виконати операцію",this);
    ui->calculateLayout->addWidget(calculateBtn);
    connect(calculateBtn,&QPushButton::clicked,this,&FiniteFieldWindow::proccesOperation);
}
void FiniteFieldWindow::proccesOperation(){
    if(AdditionBtn->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 + num2;
        ui->result->append(FirstNumber->text() + "+" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(SubstractionBtn->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 - num2;
        ui->result->append(FirstNumber->text() + "-" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(MultiplicationBtn->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 *  num2;
        ui->result->append(FirstNumber->text() + "*" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(InverseBtn->isChecked()){
        FiniteNumber one("1",FieldModule->text().toStdString());
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = one / num1;
        ui->result->append("1/"+ FirstNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(DividingBtn->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 / num2;
        ui->result->append(FirstNumber->text() + "/" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    if(PowerBtn->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        PositiveNumber num2(SecondNumber->text().toStdString());
        Exponentiation exp;
        FiniteNumber res = exp.montgomeryExponention(num1,num2);
        ui->result->append(FirstNumber->text() + "^" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(FactorizationNaive->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());
        std::map<PositiveNumber, int> result = map_factors(num1, naiveFactorization<PositiveNumber>);
        auto it = result.begin();
         ui->result->append(QString::fromStdString(it->first.toString()) + "^" + QString::number(it->second));
        it++;
         for(;it!=result.end();++it){
            ui->result->append("*" + QString::fromStdString(it->first.toString()) + "^" + QString::number(it->second));
        }
    }
    else if(FactorizationRho->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());
        std::map<PositiveNumber,int> result = map_factors(num1, PollardFactorization::pollardRho<PositiveNumber>);
        auto it = result.begin();
        ui->result->append(QString::fromStdString(it->first.toString()) + "^" + QString::number(it->second));
        it++;
        for(;it!=result.end();++it){
            ui->result->append("*" + QString::fromStdString(it->first.toString()) + "^" + QString::number(it->second));
        }
    }
    else if(SquareRoot->isChecked()){


        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber one("1", FieldModule->text().toStdString());

        FiniteNumber res = num1.tonelli_shanks();
        FiniteNumber x(num1.power_mod((stoi(FieldModule->text().toStdString()) - 1) / 2));
        if(x!=one){
            ui->result->append("a is not a quadratic residue mod p");

        }
        else
            ui->result->append("Square root: "+ FirstNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(Logarithm->isChecked()){


        ui->result->append("Автор не зробив завдання");
    }
    else if(Order->isChecked()){

        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        //FiniteNumber res = num1.;
       //ui->result->append("1/"+ FirstNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(Phi->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());

        PositiveNumber res = Euler(num1);
        ui->result->append("Phi: " +  FirstNumber->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(Lambda->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());

        PositiveNumber res = Carmichel(num1);

        ui->result->append("Lambda: " +  FirstNumber->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(Miller_Rabin->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());

        bool res = MillerRabin::miller_rabin(num1);
        if(res)
            ui->result->append(FirstNumber->text() + " is prime");
        if(!res)
            ui->result->append(FirstNumber->text() + " isn`t prime");
    }
}
FiniteFieldWindow::~FiniteFieldWindow()
{
   delete ui;
}
