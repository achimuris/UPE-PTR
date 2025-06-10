int maximoComunDivisor(int valor1, int valor2);
long factorial (int n);


int maximoComunDivisor(int valor1, int valor2)
{
    while (valor2 != 0)
    {
        int resto = valor1 % valor2;
        valor1 = valor2;
        valor2 = resto;
    }
    
    return valor1;
}


//5! = 1 * 2 * 3 * 4 * 5
long factorial (int n)
{ 
    long factorial; 
    factorial = 1; 
    for (int i = 1; i <= n; i++) 
    {
        factorial = factorial * i; 
    }                              
    return factorial;   
}
