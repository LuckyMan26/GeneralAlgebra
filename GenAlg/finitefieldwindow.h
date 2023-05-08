
#ifndef FINITEFIELDWINDOW_H
#define FINITEFIELDWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
namespace Ui {
class FiniteFieldWindow;
}

class FiniteFieldWindow : public QDialog
{
    Q_OBJECT;

public:
    FiniteFieldWindow(QWidget *parent=0);
    ~FiniteFieldWindow();
public slots:
    void proccesOperation();
private:
    Ui::FiniteFieldWindow *ui;
    QRadioButton *AdditionBtn;
    QRadioButton *SubstractionBtn;
    QRadioButton *MultiplicationBtn;
    QRadioButton *InverseBtn;
    QRadioButton *DividingBtn;
    QRadioButton *PowerBtn;
    QRadioButton *FactorizationNaive;
    QRadioButton *FactorizationRho;
    QRadioButton *SquareRoot;
    QRadioButton *Logarithm;
    QRadioButton *Order;
    QRadioButton *Phi;
    QRadioButton *Lambda;
    QRadioButton *Miller_Rabin;
    QPushButton* calculateBtn;
    QLineEdit* FirstNumber;
    QLineEdit* SecondNumber;
    QLineEdit* Power;
    QLineEdit* FieldModule;
    bool processError(QString);
    bool isAlphaNumeric(std::string str);
};

#endif // FINITEFIELDWINDOW_H
