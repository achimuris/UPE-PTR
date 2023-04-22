#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
DNI
- CUIL
- Si corresponde IVA o no.
- Monto a cobrar
*/
struct ejercicio2
{
    long DNI;
    char CUIL [12];
    short aplicaIVA;
    float montoCobrar;
} typedef dato_cliente;

dato_cliente clienteIngresado;

void InformarAFIP();
void GuardarEnLaBD();
void ImprmirFactura();

int main(int argc, char const *argv[])
{
    pid_t pid_proceso_hijo1, pid_proceso_hijo2;

    clienteIngresado.aplicaIVA = 1;
    clienteIngresado.DNI = 121212;
    sprintf(clienteIngresado.CUIL, "20-121212-5");
    clienteIngresado.montoCobrar = 120;

    pid_proceso_hijo1 = fork();

    if (pid_proceso_hijo1 ==  0)
    {
        GuardarEnLaBD();
        return 1;
    }

    pid_proceso_hijo2 = fork();

    if (pid_proceso_hijo2 ==  0)
    {
        InformarAFIP();
        return 1;
    }

    waitpid(pid_proceso_hijo1, NULL, 0);
    waitpid(pid_proceso_hijo2, NULL, 0);

    //Estoy seguro que es el proceso PADRE ORIGINAL
    ImprmirFactura();


    return 0;
}


void ImprmirFactura()
{
    float  montoAFacturar = 0;

    if (clienteIngresado.aplicaIVA == 1)
        montoAFacturar = clienteIngresado.montoCobrar * 1.21;
    else
        montoAFacturar = clienteIngresado.montoCobrar;

    printf("IMPRIMIENDO FACTURA \n");
    printf("\tDNI: %ld\n", clienteIngresado.DNI);
    printf("\tCUIL: %s\n", clienteIngresado.CUIL);
    printf("\tCUIL EMPRESA: 50-77777777-7\n");
    printf("\tTOTAL A PAGAR: %f\n", montoAFacturar);
    printf("Esto se informo desde %d (parent: %d)\n", getpid(), getppid());

}


void GuardarEnLaBD()
{
    sleep(1);
    printf("Se ha guardado en la base de datos - Desde %d (parent: %d)\n", getpid(), getppid());
}

void InformarAFIP()
{
    sleep(2);
    printf("Se acaba de informar a la AFIP - Desde %d (parent: %d)\n", getpid(), getppid());
}
