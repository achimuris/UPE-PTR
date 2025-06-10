#include <iostream>
#include "misLibrerias\unidad6.cpp"
using namespace std;

/* 
    MI-11 Informar los primeros 100 números naturales y su sumatoria
*/


int mcd(int a, int b)
{
    while (true)
    {
        int resto = a % b;
        if (resto == 0)
        {
            return b;
        }
        else
        {
            a = b;
            b = resto;
        }
    }
}
int main()
{
    int entradausr_1 =  20;
    int entradausr_2  = 54;
    int salida = mcd(entradausr_1, entradausr_2);
    cout << "El máximo común divisor (Version Clase) es " << salida  << endl;
    salida = maximoComunDivisor(entradausr_1, entradausr_2);
    cout << "El máximo común divisor (Version Malena) es " << salida  << endl;
    
    return 0;
}
