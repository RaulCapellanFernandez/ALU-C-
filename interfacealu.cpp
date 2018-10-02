#include "interfacealu.h"
#include "ui_interfacealu.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QIcon>
#include <stdio.h>
#include <stdlib.h>
#include <QString>

InterfaceALU::InterfaceALU(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfaceALU)
{
    ui->setupUi(this);

}

 InterfaceALU::~InterfaceALU()
{
    delete ui;
}

void InterfaceALU::on_pushButton_Calcular_clicked()
{

    mantisaAux=100000000000000000000000;
    valueU num1;
    num1.valorReal= ui->lineEdit_N1->text().toFloat();

    valueU num2;
    num2.valorReal= ui->lineEdit_N2->text().toFloat();

    ui->label_HEXA1->setText(QString::number(num1.valorEntero,16));
    ui->label_HEXA2->setText(QString::number(num2.valorEntero,16));
    if(num1.campos.exp == 11111111 && num2.campos.exp == 11111111){
        ui->label_RESULT->setText("NaN");
    }
    else if(num1.campos.exp == 11111111 || num2.campos.exp == 11111111){
        ui->label_RESULT->setText("NaN");
    }
    if(num1.campos.exp == 00000000 || num2.campos.exp == 00000000){
        ui->label_RESULT->setText("NaN");
    }
    else{

        if(esDenormal(num1.campos.exp)){
        num1.campos.exp=-126;
        mantisa1=num1.campos.fracc+mantisaAux;

        }else{
        num1.campos.exp=num1.campos.exp-127;
        mantisa1=num1.campos.fracc+mantisaAux;
        }
        if(esDenormal(num2.campos.exp)){
        num2.campos.exp=-126;
        mantisa2=num2.campos.fracc+mantisaAux;
        }else{
        num2.campos.exp=num2.campos.exp-127;
        mantisa2=num2.campos.fracc+mantisaAux;
        }

        cout<<"*************************"<<endl;
        cout<<"**       paso1         **"<<endl;
        cout<<"*************************"<<endl;

        cout<<"Numero 1 -> signo "<<num1.campos.signo<<" exponente "<<QString::number(num1.campos.exp,2).toStdString()<<" fracc "<<QString::number(num1.campos.fracc,2).toStdString()<<" mantisa "<<QString::number(mantisa1,2).toStdString()<<endl;
        cout<<"Numero 2 -> signo "<<num2.campos.signo<<" exponente "<<QString::number(num2.campos.exp,2).toStdString()<<" fracc "<<QString::number(num2.campos.fracc,2).toStdString()<<" mantisa "<<QString::number(mantisa2,2).toStdString()<<endl;

        //Elige que operacion se va a realizar:
        if(ui->radioButton_Suma->isChecked() == true)
            sumaAlu(num1,mantisa1,num2,mantisa2);
        if(ui->radioButton_Multipliccacion->isChecked() == true)
            productoAlu(num1, mantisa1, num2, mantisa2);
        if(ui->radioButton_Division->isChecked() == true)
            divisionAlu(num1,mantisa1, num2, mantisa2);
    }
}

bool InterfaceALU::esDenormal(unsigned int valor){
    if(valor!=0){
        return false;
    }
    return true;
}
void InterfaceALU::sumaAlu(valueU sumando1, unsigned int mantisa1, valueU sumando2, unsigned int mantisa2){
    //paso 1
    valueU suma;
    mantisaAux=100000000000000000000000;
    unsigned int aux, aux1;
    float numAux;
    p=0;
    unsigned int k=0;
    unsigned int g=0,r=0,st=0;
    unsigned int d;


    cout<<"*************************"<<endl;
    cout<<"**       paso 2        **"<<endl;
    cout<<"*************************"<<endl;

    bool operados_intercambiados=false,commplemento_p=false;

        if(sumando1.campos.exp<sumando2.campos.exp){
            //Cambiar los dos numeros
            numAux = sumando1.valorReal;
            sumando1.valorReal = sumando2.valorReal;
            sumando2.valorReal = numAux;

           //intercambiamos mantisa
           aux=mantisa1;
           mantisa1=mantisa2;
           mantisa2=aux;

           operados_intercambiados=true;

       }

    cout<<"Numero 1 -> signo "<<sumando1.campos.signo<<" exponente "<<QString::number(sumando1.campos.exp,2).toStdString()<<" fracc "<<QString::number(sumando1.campos.fracc,2).toStdString()<<" mantisa "<<QString::number(mantisa1,2).toStdString()<<endl;
    cout<<"Numero 2 -> signo "<<sumando2.campos.signo<<" exponente "<<QString::number(sumando2.campos.exp,2).toStdString()<<" fracc "<<QString::number(sumando2.campos.fracc,2).toStdString()<<" mantisa "<<QString::number(mantisa2,2).toStdString()<<endl;
    cout<<"boolean paso 2 ->"<<operados_intercambiados<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 3        **"<<endl;
    cout<<"*************************"<<endl;

    suma.campos.exp=sumando1.campos.exp;
    d=sumando1.campos.exp-sumando2.campos.exp;

    if (d<=0){
        d=0;
    }
    cout<<"Exponente suma->"<< QString::number(suma.campos.exp,2).toStdString()<<endl;
    cout<<"D->"<<d<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 4        **"<<endl;
    cout<<"*************************"<<endl;

    if(sumando1.campos.signo!=sumando2.campos.signo){
        mantisa2=-mantisa2;
    }
    cout<< "Mantisa b negada o no->"<< QString::number(mantisa2,2).toStdString() <<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 5        **"<<endl;
    cout<<"*************************"<<endl;

    p=mantisa2;
    cout<< "p->"<< QString::number(p,2).toStdString() <<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 6        **"<<endl;
    cout<<"*************************"<<endl;
    if (d!=0)
        g=p>>(d-1) & 0x01;

    if (d>1)
        r=p>>(d-2) & 0x01;

    if (d>2){
        for( int i=d-3;i>=0;i--){
            aux1=p>>(i) & 0x01;
            st=st|aux1;

        }
    }
    cout<< "g->"<< QString::number(g,2).toStdString() <<endl;
    cout<< "r->"<< QString::number(r,2).toStdString() <<endl;
    cout<< "st->"<< QString::number(st,2).toStdString() <<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 7        **"<<endl;
    cout<<"*************************"<<endl;

    if(sumando1.campos.signo!=sumando2.campos.signo){
        for(int i=d;i>0;i--){
            p= p>>1;
            p= p+ mantisaAux;
        }
    cout<<"p + mantisaAux->>> "<<QString::number(p,2).toStdString()<<endl;
    }else{
        for(int i=d;i>0;i--){
            p= p>>1;
        }
         cout<<"p >> 1->"<<QString::number(p,2).toStdString()<<endl;
    }
    cout<<"*************************"<<endl;
    cout<<"**       paso 8        **"<<endl;
    cout<<"*************************"<<endl;

    acarreo=p+mantisa1;
    p=p+mantisa1;

    c1=acarreo>>24 & 0x01 ;

    cout<<"c1->"<<QString::number(c1,2).toStdString()<<endl;
    cout<<"p->"<<QString::number(p,2).toStdString()<<endl;

    if(c1==1){
        mantisaAux=100000000000000000000000;
    }else if(c1==0){
        mantisaAux=000000000000000000000000;
    }
    cout<<"Acarreo->"<<QString::number(acarreo,2).toStdString()<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 9        **"<<endl;
    cout<<"*************************"<<endl;

    if ((sumando1.campos.signo!=sumando2.campos.signo)&&((p>>23 & 0x01)==1)&&(c1==0)){
        p=-p;

        commplemento_p=true;
    }
    cout<<"-p ->"<<QString::number(p,2).toStdString()<<endl;
    cout<<"commplemento_p->"<<commplemento_p<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 10       **"<<endl;
    cout<<"*************************"<<endl;

    if ((sumando1.campos.signo==sumando2.campos.signo)&&(c1==1)){
        st=g|r|st;

        r= (p>>0 & 0x01);
        p= (p >> 1)+mantisaAux;
        suma.campos.exp=suma.campos.exp+1;

        cout<<"st->"<<st<<endl;
        cout<<"p->"<<QString::number(p,2).toStdString()<<endl;
        cout<<"Exponente de la suma->"<<QString::number(suma.campos.exp,2).toStdString()<<endl;
    }else{
        unsigned int a = p>>23;
        ayuda = p>>23;
        mantisaAux = p;

        if(ayuda != 1){
            while(ayuda != 1 || k == 23){
                ayuda = mantisaAux >> 23;
                mantisaAux = mantisaAyuda <<1;
                k++;
                cout<<"mantisa Auxiliar->"<<mantisaAyuda<<endl;
            }
        }
        cout<<k<<endl;

        if (k==0){
            st=r|st;
            r=g;
        }else if(k>1){
            r=0;
            st=0;
        }
        //desplazar p g a la izquierda no se si es esto
        if(k > 0){
            for(unsigned int i=0;i<k;i++){
              p = p<<1;

            }
        }

        suma.campos.exp=suma.campos.exp - k;

        cout<<"st->"<<st<<endl;
        cout<<"r->"<<r<<endl;
        cout<<"p->"<<QString::number(p,2).toStdString()<<endl;
        cout<<"Exponente de la suma->"<<QString::number(suma.campos.exp,2).toStdString()<<endl;
    }

    cout<<"*************************"<<endl;
    cout<<"**       paso 11       **"<<endl;
    cout<<"*************************"<<endl;

    if(((r==1)&&(st==1))||((r==1)&&(st==0)&&(p & 0x01==1))){
         acarreo=p+1;
         p=p+1;
         c2=acarreo>>(24) & 0x01;
             if(c2==1){
                 p=(p >> 1);
                 c2=0;
                 suma.campos.exp=suma.campos.exp+1;
             }

         }
     mantisaS=p;

    cout<<"*************************"<<endl;
    cout<<"**       paso 12       **"<<endl;
    cout<<"*************************"<<endl;

    if((operados_intercambiados==false)&&(commplemento_p==true)){
        suma.campos.signo=sumando2.campos.signo;
    }else{
        suma.campos.signo=sumando1.campos.signo;
    }
    cout<<"*************************"<<endl;
    cout<<"**       paso 13       **"<<endl;
    cout<<"*************************"<<endl;

    suma.campos.exp = 127 +suma.campos.exp;
    suma.campos.fracc = mantisaS;
    cout<<"Mantisa Suma->"<<QString::number(mantisaS,2).toStdString()<<endl;
    cout<<"Resultado: "<<suma.campos.signo<<" "<<QString::number(suma.campos.exp,2).toStdString()<<" "<<QString::number(suma.campos.fracc,2).toStdString()<<endl;
    cout<<"Resultado: "<<suma.valorReal<<endl;

    ui->label_RESULT->setNum(suma.valorReal);
    ui->label_HEXARESULT->setText(QString::number(suma.valorEntero,16));


}

void InterfaceALU::divisionAlu(valueU A, unsigned int mantisaA, valueU B, unsigned int mantisaB){

    float bEscalado = 0,auxFracc=0;
    float aEscalado = 0, bprima = 0, cierreFor, xmenos;
    int d, n, contador = -1;

    cout<<"*************************"<<endl;
    cout<<"**       paso 0        **"<<endl;
    cout<<"*************************"<<endl;

    mantisaAux=100000000000000000000000;
    mantisaA = A.campos.fracc + mantisaAux;
    mantisaB = B.campos.fracc + mantisaAux;
    cout<<"Mantisa A: "<<QString::number(mantisaA,2).toStdString()<<endl;
    cout<<"Mantisa B: "<<QString::number(mantisaB,2).toStdString()<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 1        **"<<endl;
    cout<<"*************************"<<endl;

    n = mantisaB>>23 & 0x01;
    cout<<"N -> "<<n<<endl;

    ayudaEscalar = mantisaB;

    for(int i  = 22 ; i >= 0; i--){
        auxFracc =auxFracc + (ayudaEscalar>>i &0x01) * pow(2,contador);
        contador--;
    }
    bEscalado = auxFracc;
    cout<<"Valor Escalado ->"<<bEscalado<<endl;

    if(n==1){
        bEscalado++;
    }
    cout<<"Valor Escalado B->"<<bEscalado<<endl;

    d = A.campos.exp - B.campos.exp;
    cout<<"D -> "<<d<<endl;

    auxFracc = 0;
    if(d < 0){
        while(d !=0){
             mantisaA = mantisaA >> 1;
             d++;
        }
        ayudaEscalar = mantisaA;
        contador = -1;

        for(int i  = 22 ; i >= 0; i--){
            auxFracc =auxFracc + (ayudaEscalar>>i &0x01) * pow(2,contador);
            contador--;
        }
        if(n==1){
            aEscalado++;
        }
    }
    else{
        float a = 0;
        auxFracc = 0;
        int q = d;
        for(int i = 23-d ; i < 24; i++){
            if(mantisaA >> i & 0x01 == 1){
                 a = a + pow(2,auxFracc);
            }

            auxFracc ++;
        }
        cout<<"A1 -> "<<a<<endl;

        auxFracc = -1;
        d=23-(d+1);
        for(int i = d ; i > -1; i--){
            if(mantisaA >> i & 0x01 ==1){
                a = a + pow(2,auxFracc);
                cout<<i<<"-"<<pow(2,auxFracc)<<endl;
            }

            auxFracc--;
        }
        cout<<"A2 -> "<<a<<endl;
        auxFracc = a;
    }


    aEscalado = auxFracc;
    cout<<"Valor Escalado ->"<<aEscalado<<endl;

    n = mantisaA>>23 & 0x01;
    cout<<"N -> "<<n<<endl;

    cout<<"Valor Escalado A ->"<<aEscalado<<endl;


    cout<<"*************************"<<endl;
    cout<<"**       paso 2        **"<<endl;
    cout<<"*************************"<<endl;

    if(bEscalado < 1.25)
        bprima=1;
    else
        bprima=0.8;

    cout<<"B prima -> "<<bprima<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 3        **"<<endl;
    cout<<"*************************"<<endl;

    x.valorReal = aEscalado * bprima;
    y.valorReal = bEscalado * bprima;
    cout<<"X ->"<<x.valorReal<<endl;
    cout<<"Y ->"<<y.valorReal<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 4        **"<<endl;
    cout<<"*************************"<<endl;

    cierreFor = pow(10,-4);
    xmenos = 0;
   for(int i =0 ; i < 300 ; i++){
        xmenos = x.valorReal;
        r.valorReal = 2- y.valorReal;
        y.valorReal = y.valorReal * r.valorReal;
        x.valorReal = x.valorReal * r.valorReal;
    }

    cout<<"Resultado r ->"<<r.valorReal<<endl;
    cout<<"Resultado x ->"<<x.valorReal<<endl;
    cout<<"Resultado y ->"<<y.valorReal<<endl;

    ui->label_RESULT->setNum(x.valorReal);
    ui->label_HEXARESULT->setText(QString::number(x.valorEntero,16));

}

void InterfaceALU::productoAlu(valueU factor1, unsigned int mantisa1, valueU factor2, unsigned int mantisa2){
    unsigned int r, st;

    cout<<"*************************"<<endl;
    cout<<"**       paso 1        **"<<endl;
    cout<<"*************************"<<endl;
    producto.campos.signo = factor1.campos.signo + factor2.campos.signo;
    cout<<"Signo producto ->"<<producto.campos.signo<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 2        **"<<endl;
    cout<<"*************************"<<endl;
    producto.campos.exp = factor1.campos.exp + factor2.campos.exp;
    cout<<"Exponente  ->"<<QString::number(producto.campos.exp,2).toStdString()<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 3        **"<<endl;
    cout<<"*************************"<<endl;
    productoSinSigno(factor1, mantisa1, factor2, mantisa2);

    if((p >> 23 & 0x01) == 0){
        p = p << 1;
        mantisa1 = mantisa1 << 1;
    }else
        producto.campos.exp = producto.campos.exp + 1;

    cout<<"p ->"<<QString::number(p,2).toStdString()<<endl;
    cout<<"Mantisa 1 ->"<<QString::number(mantisa1,2).toStdString()<<endl;
    cout<<"Exponente ->"<<QString::number(producto.campos.exp,2).toStdString()<<endl;


    r = mantisa1 >> 23 & 0x01;
    for(int i = 22; i < 0; i--){
        st = mantisa1 >> i & 0x01 | mantisa1 >> (i-1) & 0x01;
    }

    cout<<"r ->"<<QString::number(r,2).toStdString()<<endl;
    cout<<"st ->"<<QString::number(st,2).toStdString()<<endl;

    mantisaAux = 000000000000000000000001;
    if((r == 1)&&(st ==1))
        p = p + mantisaAux;
    else if((r == 1)&&(st==0)&&(p & 0x01 ==1))
        p = p + mantisaAux;

    producto.campos.exp = 127 + producto.campos.exp;
    producto.campos.fracc = p;

    cout<<"*************************"<<endl;
    cout<<"**   Desbordamientos   **"<<endl;
    cout<<"*************************"<<endl;

    if(producto.campos.exp == 11111111){
        ui->label_RESULT->setText("OverFlow");
    }
    if(producto.campos.exp == 00000000){
        ui->label_RESULT->setText("UndeFlow");
    }
    else{
        ui->label_RESULT->setNum(producto.valorReal);
        ui->label_HEXARESULT->setText(QString::number(producto.valorEntero,16));
    }
}

void InterfaceALU::productoSinSigno(valueU factor1, unsigned int mantisa1, valueU factor2, unsigned int mantisa2){
    mantisaAux = 100000000000000000000000;
    mantisa1 = factor1.campos.fracc+mantisaAux;
    mantisa2 = factor2.campos.fracc+mantisaAux;

    cout<<"*************************"<<endl;
    cout<<"**       paso 1        **"<<endl;
    cout<<"*************************"<<endl;
    p = 0;
    cout<<"p ->"<<p<<endl;

    cout<<"*************************"<<endl;
    cout<<"**       paso 2        **"<<endl;
    cout<<"*************************"<<endl;
    for(int i = 0; i < 24; i++){
        if(mantisa1 & 0x01 == 1){
            acarreo = p + mantisa2;
            p = p + mantisa2;
            c = acarreo>> 24 & 0x01;
        }else{
            p= p + 0;
        }

        mantisa1 = mantisa1 >> 1;
        if(p & 0x01 == 1)
            mantisa1 = mantisa1 + mantisaAux;

        p = p >> 1;
        if(c == 1)
            p = p + mantisaAux;

        c = 0;
    }
    cout<<"p ->"<<QString::number(p,2).toStdString()<<endl;
    cout<<"Mantisa A ->"<<QString::number(mantisa1,2).toStdString()<<endl;
}

void InterfaceALU::on_pushButton_AcercaDe_clicked()
{
    QMessageBox messageBox;
    messageBox.information(0,"Hecha por Raul Capellan Fernandez","Introuce dos numeros en los cuadros verdes elige una operacion y pulsa calcular");
    messageBox.setFixedSize(500,200);
}
