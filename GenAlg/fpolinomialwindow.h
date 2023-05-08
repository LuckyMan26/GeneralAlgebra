
#ifndef FPOLINOMIALWINDOW_H
#define FPOLINOMIALWINDOW_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>

namespace Ui {
class FPolynomialWindow;
}

class FPolynomialWindow : public QDialog
{
    Q_OBJECT;

public:
    FPolynomialWindow(QWidget *parent=0);
    ~FPolynomialWindow();
public slots:
    void proccesOperation();
private:
    Ui::FPolynomialWindow *ui;
    QRadioButton *ToIrreducible;
    QRadioButton *IrreduciblePolynomial;
    QRadioButton *IsIrreducible;
    QRadioButton *AdditionBtn;
    QRadioButton *SubstractionBtn;
    QRadioButton *MultiplicationBtn;
    QRadioButton *DividingBtn;
    QRadioButton *NormingBtn;
    QRadioButton *PowerBtn;
    QRadioButton *InverseBtn;
    QRadioButton *OrderOfIrreducibleBtn;
    QRadioButton *IsGeneratorBtn;
    QPushButton* calculateBtn;
    QLineEdit* FirstPol;
    QLineEdit* SecondPol;
    QLineEdit* Ri;
    QLineEdit* Power;
    QLineEdit* FieldModule;
    bool processError(QString);
    bool isAlphaNumeric(std::string str);
};
#endif // FPOLINOMIALWINDOW_H
