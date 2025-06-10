#include <iostream>
#include "misLibrerias\unidad6.cpp"
using namespace std;

/*
MI-32: Dada una serie de números enteros, informar:
a) su factorial
b) cuantos múltiplos de 3
c) cuantos múltiplos de 5
d) cuantos múltiplos de 3 y de 5
*/
int esMultiplo (int deQueEsMultiplo, int valor);
int main () {
    int desde = 5;
    int hasta = 20;

    int contadorDeMultiplosDe3 = 0;
    int contadorDeMultiplosDe5 = 0;
    int contadorDeMultiplosDe3y5 = 0;

    for (int i = desde; i <= hasta; i++)
    {
        cout << "El factorial de " << i << " es " << factorial(i) << endl;

        if (esMultiplo(3, i))
            contadorDeMultiplosDe3++;
        
        if (esMultiplo(5, i))
            contadorDeMultiplosDe5++;

        if (esMultiplo(5, i) && esMultiplo(3, i))
            contadorDeMultiplosDe3y5++;

    }

    cout << "Cantidad de multiplos de 3 entre  " << desde << " y " << hasta << " es " << contadorDeMultiplosDe3 << endl;

    cout << "Cantidad de multiplos de 5 entre  " << desde << " y " << hasta << " es " << contadorDeMultiplosDe5 << endl;

    cout << "Cantidad de multiplos de 3 y 5 entre  " << desde << " y " << hasta << " es " << contadorDeMultiplosDe3y5 << endl;

    
    return 0;
}

int esMultiplo (int deQueEsMultiplo, int valor)
{

    int resto = valor % deQueEsMultiplo;
    if (resto == 0)
    {
        return 1;
    }else{
        return 0;
    }

}
