#include "finitefieldwindow.h"
#include "ui_FiniteFieldWindow.h"
#include "../LinderLab1A-master/LinderLab1A/FiniteNumber.h"
#include "../LinderLab1A-master/LinderLab1A/Exponent.h"
#include "../LinderLab1A-master/LinderLab1A/Pollard.h"
#include "../LinderLab1A-master/LinderLab1A/Euler.h"
#include <QLabel>
#include <regex>
#include "../LinderLab1A-master/LinderLab1A/CalculationOfSquareRoot.h"
#include "../LinderLab1A-master/LinderLab1A/FiniteGroup.h"
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
    PowerBtn = new QRadioButton("Степінь", this);
    FactorizationNaive = new QRadioButton("Факторизація(наївний алгоритм)", this);
    FactorizationRho = new QRadioButton("Факторизація(ефективний алгоритм)", this);
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
    calculateBtn->setFont(QFont("Arial", 12, QFont::Bold));
    ui->calculateLayout->addWidget(calculateBtn);
    connect(calculateBtn,&QPushButton::clicked,this,&FiniteFieldWindow::proccesOperation);
}
bool FiniteFieldWindow::isAlphaNumeric(std::string str) {
    if(str[0]!='-' && !(str[0]>='0' && str[0]<='9')){
        return false;
    }
    for(int i=1;i<str.length();i++){

        if(!(str[i]>='0' && str[i]<='9')){
            return false;
        }
    }
    return true;
}
bool FiniteFieldWindow::processError(QString str){
    if(str.toInt() < 0){
        ui->result->append("Field size < 0");
        return false;
    }
    if(!isAlphaNumeric(str.toStdString())){
        ui->result->append("Fields size contains non-numerical values");
        return false;
    }
    return true;
}
void FiniteFieldWindow::proccesOperation(){
    if(! processError(FieldModule->text())){
        return;
    }
    if(!isAlphaNumeric(FirstNumber->text().toStdString())){
        ui->result->append("FirstNumber field contains non-numerical values");
        return;
    }
    if(! isAlphaNumeric(SecondNumber->text().toStdString()) && !SecondNumber->text().isEmpty()){
        ui->result->append("SecondNumber field contains non-numerical values");
        return;
    }
    if(AdditionBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 + num2;
        ui->result->append(FirstNumber->text() + "+" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(SubstractionBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 - num2;
        ui->result->append(FirstNumber->text() + "-" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(MultiplicationBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber res = num1 *  num2;
        ui->result->append(FirstNumber->text() + "*" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(InverseBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber one("1",FieldModule->text().toStdString());
        FiniteNumber zero("0",FieldModule->text().toStdString());
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        //FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());

        if(num1==zero){
            ui->result->append("No inverse element for 0");
            return;
        }
        else{
            FiniteNumber res = num1.inverse();
            ui->result->append("1/"+ FirstNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
        }
    }
    else if(DividingBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber num2(SecondNumber->text().toStdString(),FieldModule->text().toStdString());
        FiniteNumber zero("0",FieldModule->text().toStdString());
        if(num2==zero){
            ui->result->append("No inverse element for 0");
            return;
        }
        FiniteNumber res = num1 / num2;
        ui->result->append(FirstNumber->text() + "/" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    if(PowerBtn->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        FiniteNumber num1(FirstNumber->text().toStdString(),FieldModule->text().toStdString());
        PositiveNumber num2(SecondNumber->text().toStdString());
        Exponentiation exp;
        FiniteNumber res = exp.montgomeryExponentiation(num1,num2);

        ui->result->append(FirstNumber->text() + "^" + SecondNumber->text() + "=" + QString::fromStdString(res.toString()) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
    }
    else if(FactorizationNaive->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());
        std::map<PositiveNumber, int> result = map_factors(num1, naiveFactorization<PositiveNumber>);
        auto it = result.begin();
        std::string string  = (it->first.toString()) + "^" + std::to_string(it->second);
        it++;
        for(;it!=result.end();++it) {
            string+= "*" + (it->first.toString()) + "^" + std::to_string(it->second);

        }

        ui->result->setPlainText(QString::fromStdString(string));
    }
    else if(FactorizationRho->isChecked()){

        PositiveNumber num1(FirstNumber->text().toStdString());
        std::map<PositiveNumber,int> result = map_factors(num1, PollardFactorization::pollardRho<PositiveNumber>);
        auto it = result.begin();
        std::string string  = (it->first.toString()) + "^" + std::to_string(it->second);
        it++;
        for(;it!=result.end();++it) {
            string+= "*" + (it->first.toString()) + "^" + std::to_string(it->second);

        }

        ui->result->setPlainText(QString::fromStdString(string));
    }
    else if(SquareRoot->isChecked()){

        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/
        long long num1(FirstNumber->text().toInt());
        int p = FieldModule->text().toInt();

        if (CalculationOfSquareRoot::power_mod(num1, (p - 1) / 2, p) != 1) {
            ui->result->append("a is not a quadratic residue mod p");
        }

        else{
        long long root1 = CalculationOfSquareRoot::tonelli_shanks(num1, p);
            ui->result->append("Square root: "+ FirstNumber->text() + "=" + QString::fromStdString(to_string(root1)) + "(mod " + QString::fromStdString(FieldModule->text().toStdString())+")");
        }
    }
    else if(Logarithm->isChecked()){


        ui->result->append("Автор не зробив завдання");
    }
    else if(Order->isChecked()){
        /*if(!PositiveNumber(FieldModule->text().toStdString()).is_prime()){
            ui->result->append("Field size should be prime");
            return;
        }*/

        FiniteGroup g1(PositiveNumber(FieldModule->text().toStdString()));
        PositiveNumber res = g1.ElementOrder(FiniteNumber(FirstNumber->text().toStdString(),FieldModule->text().toStdString()));
        ui->result->append("Order of "+ FirstNumber->text() + "at group Z" + FieldModule->text()+ "=" + QString::fromStdString(res.toString()));
    }
    else if(Phi->isChecked()){
        /*if(FirstNumber->text()=="0"){
            ui->result->append("Carmichel is undefined");
            return;
        }*/
        PositiveNumber num1(FirstNumber->text().toStdString());

        PositiveNumber res = Euler(num1);
        ui->result->append("Phi: " +  FirstNumber->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(Lambda->isChecked()){
        if(FirstNumber->text()=="0"){
            ui->result->append("Carmichel is undefined");
            return;

        }
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
