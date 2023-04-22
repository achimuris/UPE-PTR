from ast import Num
import logging
import concurrent.futures
from concurrent.futures import ThreadPoolExecutor

logging.basicConfig(level=logging.DEBUG,
                    format='%(thread)d  - %(threadName)s: %(message)s')

def potencia2(Numero):
    resultado = 0
    auxiliar = 0
    unNumero = int(Numero)
    for i in range(unNumero):
        resultado = pow(2,i)
        if resultado > auxiliar and resultado < unNumero :
            auxiliar = resultado         
    logging.info(f"potencia de 2 mas cercana a " +  str(auxiliar) + "\n")

def potencia3(Numero):
    resultado = 0
    auxiliar = 0
    unNumero = int(Numero)
    for i in range(unNumero):
        resultado = pow(3,i)
        if resultado > auxiliar and resultado < unNumero :
            auxiliar = resultado         
    logging.info(f"potencia de 2 mas cercana a " +  str(auxiliar) + "\n")

# def potencia3(Numero):
#     resultado = 0
#     auxiliar = 0
#     for i in range(Numero):
#         resultado = pow(3,i)
#         if resultado > auxiliar and resultado < Numero:
#             auxiliar = resultado         
#     logging.info(f"potencia de 2 mas cercana a {Numero}:{auxiliar}\n")

# def potencia5(Numero):
#     resultado = 0
#     auxiliar = 0

#     for i in range(Numero):
#         resultado = pow(5,i)
#         if resultado > auxiliar and resultado < Numero:
#             auxiliar = resultado
            
#     logging.info(f"potencia de 2 mas cercana a {Numero}:{auxiliar}\n")

# def potencia7(Numero):
#     resultado = 0
#     auxiliar = 0

#     for i in range(Numero):
#         resultado = pow(7,i)
#         if resultado > auxiliar and resultado > Numero:
#             auxiliar = resultado
            
#     logging.info(f"potencia de 2 mas cercana a {Numero}:{auxiliar}\n")



if __name__ == '__main__':
    Numero = input('ingrese un numero ')

    ejecutor =  ThreadPoolExecutor(max_workers=1)
    ejecutor.submit(potencia2, Numero)
    ejecutor.submit(potencia3, Numero)

    # with concurrent.futures.ThreadPoolExecutor(max_workers = 1) as hilos:        
    #     hilos.submit(potencia2,Numero)
        # hilos.submit(potencia3,Numero)
        # hilos.submit(potencia5,Numero)
        # hilos.submit(potencia7,Numero)



