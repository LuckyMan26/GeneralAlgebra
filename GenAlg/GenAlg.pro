QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    finitefieldwindow.cpp \
    fpolinomialwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    prwindow.cpp

HEADERS += \
    ../LinderLab1A-master/LinderLab1A/CalculationOfSquareRoot.h \
    ../LinderLab1A-master/LinderLab1A/Euler.h \
    ../LinderLab1A-master/LinderLab1A/Exponent.h \
    ../LinderLab1A-master/LinderLab1A/FPolynomial.h \
    ../LinderLab1A-master/LinderLab1A/Field.h \
    ../LinderLab1A-master/LinderLab1A/FiniteField.h \
    ../LinderLab1A-master/LinderLab1A/FiniteNumber.h \
    ../LinderLab1A-master/LinderLab1A/MillerRabin.h \
    ../LinderLab1A-master/LinderLab1A/Pollard.h \
    ../LinderLab1A-master/LinderLab1A/Polynomial.h \
    ../LinderLab1A-master/LinderLab1A/PolynomialElement.h \
    ../LinderLab1A-master/LinderLab1A/RPolynomial.h \
    ../LinderLab1A-master/LinderLab1A/SignedNumber.h \
    finitefieldwindow.h \
    fpolinomialwindow.h \
    mainwindow.h \
    prwindow.h

FORMS += \
    FPolynomialWindow.ui \
    FiniteFieldWindow.ui \
    PRWindow.ui \
    mainwindow.ui



