QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LinderLab1A-master/LinderLab1A/CalculationOfSquareRoot.cpp \
    ../LinderLab1A-master/LinderLab1A/FPolynomialTest.cpp \
    ../LinderLab1A-master/LinderLab1A/FiniteField.cpp \
    ../LinderLab1A-master/LinderLab1A/PolynomialElementTest.cpp \
    ../LinderLab1A-master/LinderLab1A/RPolynomialTest.cpp \
    ../LinderLab1A-master/LinderLab1A/tests.cpp \
    finitefieldwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../LinderLab1A-master/LinderLab1A/Exponent.h \
    ../LinderLab1A-master/LinderLab1A/FPolynomial.h \
    ../LinderLab1A-master/LinderLab1A/Field.h \
    ../LinderLab1A-master/LinderLab1A/FiniteField.h \
    ../LinderLab1A-master/LinderLab1A/FiniteNumber.h \
    ../LinderLab1A-master/LinderLab1A/MillerRabin.h \
    ../LinderLab1A-master/LinderLab1A/Pollard.h \
    ../LinderLab1A-master/LinderLab1A/Polynomial.h \
    ../LinderLab1A-master/LinderLab1A/PolynomialElement.h \
    ../LinderLab1A-master/LinderLab1A/PositiveNumber.h \
    finitefieldwindow.h \
    mainwindow.h

FORMS += \
    FiniteFieldWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
