
#ifndef PRWINDOW_H
#define PRWINDOW_H



#include <QDialog>
#include <QRadioButton>
#include <QLineEdit>
namespace Ui {
class PRWindow;
}

class PRWindow : public QDialog
{
    Q_OBJECT;

public:
    PRWindow(QWidget *parent=0);
    ~PRWindow();
public slots:
    void proccesOperation();
private:
    Ui::PRWindow *ui;
    QRadioButton *AdditionBtn;
    QRadioButton *SubstractionBtn;
    QRadioButton *MultiplicationBtn;
    QRadioButton *DerrivitiveBtn;
    QRadioButton *ValueBtn;
    QRadioButton *RemainderBtn;
    QRadioButton *GCD;
    QRadioButton *CyclomiticBtn;
    QRadioButton *QuatientBtn;
    QPushButton* calculateBtn;
    QLineEdit* FirstPol;
    QLineEdit* SecondPol;
    QLineEdit* Value;
};

#endif // PRWINDOW_H
