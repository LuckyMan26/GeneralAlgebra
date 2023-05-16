#include "fpolinomialwindow.h"
#include "ui_FPolynomialWindow.h"
#include "../LinderLab1A-master/LinderLab1A/TrueFPolynomial.h".h".h"
#include <QLabel>
#include <regex>

FPolynomialWindow::FPolynomialWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::FPolynomialWindow)
{
    ui->setupUi(this);
    AdditionBtn = new QRadioButton("Додавання", this);
    SubstractionBtn = new QRadioButton("Віднімання", this);
    MultiplicationBtn = new QRadioButton("Множення", this);
    ToIrreducible = new QRadioButton("Розклад кругового многочлена на незвідні множники використовуючи многочлени Ri", this);
    IrreduciblePolynomial = new QRadioButton("Знаходження K незвідних многочленів заданого порядку", this);
    IsIrreducible = new QRadioButton("Перевірка чи є многочлен незвідним ", this);
    NormingBtn = new QRadioButton("Нормування", this);
    PowerBtn = new QRadioButton("Піднесення у степінь", this);
    InverseBtn = new QRadioButton("Обернений", this);
    OrderOfIrreducibleBtn = new QRadioButton("Порядок незвідного", this);
    IsGeneratorBtn = new QRadioButton("Чи є генератором", this);

    ui->RadioButtonLayout->addWidget(AdditionBtn,1,0);
    ui->RadioButtonLayout->addWidget(SubstractionBtn,1,1);
    ui->RadioButtonLayout->addWidget(MultiplicationBtn,1,2);
    ui->RadioButtonLayout->addWidget(ToIrreducible,1,3);
    ui->RadioButtonLayout->addWidget(IrreduciblePolynomial,1,4);
    ui->RadioButtonLayout->addWidget(IsIrreducible,1,5);
    ui->RadioButtonLayout->addWidget(NormingBtn,2,0);
    ui->RadioButtonLayout->addWidget(PowerBtn,2,1);
    ui->RadioButtonLayout->addWidget(InverseBtn,2,2);
    ui->RadioButtonLayout->addWidget(OrderOfIrreducibleBtn,2,3);
    ui->RadioButtonLayout->addWidget(IsGeneratorBtn,2,4);

    FirstPol = new QLineEdit(this);
    QLabel* label1 = new QLabel("Перший многочлен: ", this);
    ui->gridLayout->addWidget(label1,0,1);
    ui->gridLayout->addWidget(FirstPol,0,2);
    SecondPol = new QLineEdit(this);

    QLabel* label2 = new QLabel("Другий многочлен: ", this);
    ui->gridLayout->addWidget(label2,1,1);
    ui->gridLayout->addWidget(SecondPol,1,2);
    QLabel* label3 = new QLabel("Степінь ", this);
    QLabel* label4 = new QLabel("Ri ", this);
    QLabel* label5 = new QLabel("Розмір поля ", this);
    Power = new QLineEdit(this);
    FieldModule  = new QLineEdit(this);
    ui->gridLayout->addWidget(label3,2,1);
    ui->gridLayout->addWidget(Power,2,2);
    ui->gridLayout->addWidget(FieldModule,3,2);
    ui->gridLayout->addWidget(label5,3,1);

    Ri = new QLineEdit(this);
    ui->gridLayout->addWidget(label4,4,1);
    ui->gridLayout->addWidget(Ri,4,2);
    calculateBtn = new QPushButton("Виконати операцію",this);
    ui->btnLayout->addWidget(calculateBtn);
    connect(calculateBtn,&QPushButton::clicked,this,&FPolynomialWindow::proccesOperation);
}
FPolynomialWindow::~FPolynomialWindow()
{
    delete ui;
}
bool FPolynomialWindow::isAlphaNumeric(std::string str) {

    for(int i=0;i<str.length();i++){
        if(!(str[i]>='0' && str[i]<='9')){
            return false;
        }
    }
     return true;
}
bool FPolynomialWindow::processError(QString str){
    if(str.toInt() < 0){
        ui->result->append("Field size < 0");
        return false;
    }
    if(!isAlphaNumeric(str.toStdString())){
        std::cout<<str.toStdString()<<std::endl;
        ui->result->append("Fields size contains non-numerical values");
        return false;
    }
    return true;
}
void FPolynomialWindow::proccesOperation(){
    if(!processError(FieldModule->text())){
        return;
    }
    if(AdditionBtn->isChecked()){

        FPolynomial irreducible(Ri->text().toStdString(), FieldModule->text().toStdString());
        TrueFPolynomial pol1(FirstPol->text().toStdString(), irreducible);
        TrueFPolynomial pol2(SecondPol->text().toStdString(), irreducible);
        TrueFPolynomial res = pol1 + pol2;
        ui->result->append(FirstPol->text() + "+" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(SubstractionBtn->isChecked()){

        FPolynomial irreducible(Ri->text().toStdString(), FieldModule->text().toStdString());
        TrueFPolynomial pol1(FirstPol->text().toStdString(), irreducible);
        TrueFPolynomial pol2(SecondPol->text().toStdString(), irreducible);
        TrueFPolynomial res = pol1 - pol2;
        ui->result->append(FirstPol->text() + "-" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(MultiplicationBtn->isChecked()){

        FPolynomial irreducible(Ri->text().toStdString(), FieldModule->text().toStdString());
        TrueFPolynomial pol1(FirstPol->text().toStdString(), irreducible);
        TrueFPolynomial pol2(SecondPol->text().toStdString(), irreducible);
        TrueFPolynomial res = pol1 * pol2;
        ui->result->append(FirstPol->text() + "*" + SecondPol->text() + "=" + QString::fromStdString(res.toString()));
    }
    else if(NormingBtn->isChecked()){
        FPolynomial irreducible(Ri->text().toStdString(), FieldModule->text().toStdString());
        TrueFPolynomial pol1(FirstPol->text().toStdString(), irreducible);


        TrueFPolynomial res = pol1.Normalized();
        ui->result->append("Normize: " + FirstPol->text() +  "=" + QString::fromStdString(res.toString()));
    }
    else if(PowerBtn->isChecked()){

        FPolynomial irreducible(Ri->text().toStdString(), FieldModule->text().toStdString());
        TrueFPolynomial pol1(FirstPol->text().toStdString(), irreducible);

        PositiveNumber num(Power->text().toStdString());
        TrueFPolynomial res = pol1.fastExponentiation(num);
        ui->result->append( FirstPol->text() + " in " + Power->text() + " power " +  "=" + QString::fromStdString(res.toString()));
    }
    if(InverseBtn->isChecked()){


        ui->result->append("Студент не виконав завдання");
    }
    if(OrderOfIrreducibleBtn->isChecked()){

         ui->result->append("Студент не виконав завдання");
    }
    if(ToIrreducible->isChecked()){
         ui->result->append("Студент не виконав завдання");
    }
    if(IrreduciblePolynomial->isChecked()){
         ui->result->append("Студент не виконав завдання");
    }
    if(IsIrreducible->isChecked()){
         ui->result->append("Студент не виконав завдання");
    }
    if(IsGeneratorBtn->isChecked()){
         ui->result->append("Студент не виконав завдання");
    }
}



