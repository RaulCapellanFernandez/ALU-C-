#ifndef INTERFACEALU_H
#define INTERFACEALU_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <string>
#include <QString>
#include "iostream"

using namespace std;

namespace Ui {
class InterfaceALU;
}

class InterfaceALU : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceALU(QWidget *parent = 0);
    bool esDenormal(unsigned int valor);
    ~InterfaceALU();
    struct numIEEE754
            {
               unsigned int fracc:23;
               unsigned int exp:8;
               unsigned int signo:1;
            };

            unsigned int ayudaEscalar:23;
            unsigned int mantisaAux:24;
            unsigned int mantisa1:24;
            unsigned int mantisa2:24;
            unsigned int p:24;
            unsigned int acarreo:25;
            unsigned int mantisaS:24;
            unsigned int c1:1;
            unsigned int c2:1;
            unsigned int ayuda:24;
            unsigned int mantisaAyuda:24;
            unsigned int c:1;


            //se supone que con esto ya tienes los numeros estructurados??
            union valueU{
                numIEEE754 campos;
                float valorReal;
                unsigned int valorEntero;
            };
            valueU producto;
            valueU x;
            valueU y;
            valueU b;
            valueU r;
            valueU primab;


            void sumaAlu(valueU sumando1,unsigned int mant1 ,valueU sumando2,unsigned int mant2);
            void productoAlu(valueU factor1, unsigned int mant1 , valueU factor2, unsigned int mant2);
            void productoSinSigno(valueU factor1, unsigned int mant1 , valueU factor2, unsigned int mant2);
            void divisionAlu(valueU dividendo,unsigned int mant1, valueU divisor, unsigned int mant2);


private slots:

    void on_pushButton_Calcular_clicked();

    void on_pushButton_AcercaDe_clicked();

private:
    Ui::InterfaceALU *ui;
};

#endif // INTERFACEALU_H
