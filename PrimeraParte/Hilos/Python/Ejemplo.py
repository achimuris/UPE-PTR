import time #Para utilizar la instruccion sleep
import logging # importamos el modulo de logueo
from concurrent.futures import ThreadPoolExecutor

logging.basicConfig(level=logging.DEBUG,
                    format='%(thread)d  - %(threadName)s: %(message)s')
def Suma_Numeros(num,num2):
    suma=int(num+num2)
    # print("\nLa suma de %i + %i es:%i" %(num,num2,suma))
    mensaje = "\nLa suma de " + str(num) + " + " + str(num2) + " es: " + str(suma) + "\n"
    logging.info(mensaje)
#Trabjamos en el MainThread
if __name__ == '__main__':
    Ejecutor=ThreadPoolExecutor(max_workers=2)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,5)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,4,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)
    Ejecutor.submit(Suma_Numeros,5,4)