import time  # Para utilizar la instrucción sleep
import logging  # Importamos el módulo de logueo.
from concurrent.futures import ThreadPoolExecutor


logging.basicConfig(level=logging.DEBUG,
                    format='%(thread)d  - %(threadName)s: %(message)s')


# Defino un método responsable de realizar una suma
def un_metodo_que_suma(par1, par2):
    time.sleep(5)

    logging.info(f'La suma de {par1} + {par2} es: {par1 + par2}\n')


# Defino un método responsable de realizar una resta
def un_metodo_que_resta(par1, par2):
    time.sleep(5)

    logging.info(f'La resta de {par1} - {par2} es: {par1 - par2}\n')

# Defino un método responsable de realizar una resta
def un_metodo_con_un_parametro(par1):
    time.sleep(5)

    logging.info(f'Imprimo el valor {par1}\n')



# Trabajamos en el MainThread:
if __name__ == '__main__':

    logging.info("HOLA MUNDO")
    ejecutor =  ThreadPoolExecutor(max_workers=6)

    ejecutor.submit(un_metodo_que_suma, 10, 20)
    ejecutor.submit(un_metodo_que_resta, 10, 20)

    ejecutor.submit(un_metodo_que_suma, 10, 40)
    ejecutor.submit(un_metodo_que_resta, 10, 5)

    ejecutor.submit(un_metodo_con_un_parametro, 10)

    ejecutor.submit(un_metodo_que_suma, 20, 20)
    ejecutor.submit(un_metodo_que_resta, 80, 20)

    ejecutor.submit(un_metodo_que_suma, 40, 20)
    ejecutor.submit(un_metodo_con_un_parametro, 15)
    ejecutor.submit(un_metodo_que_resta, 79, 12)

    ejecutor.submit(un_metodo_que_suma, 10, 20)
    ejecutor.submit(un_metodo_que_resta, 10, 20)



    # with ThreadPoolExecutor(max_workers=2) as ejecutor:

    #     ejecutor.submit(un_metodo_que_suma, 10, 20)
    #     ejecutor.submit(un_metodo_que_resta, 10, 20)

    #     ejecutor.submit(un_metodo_que_suma, 10, 40)
    #     ejecutor.submit(un_metodo_que_resta, 10, 5)

    #     ejecutor.submit(un_metodo_que_suma, 20, 20)
    #     ejecutor.submit(un_metodo_que_resta, 80, 20)

    #     ejecutor.submit(un_metodo_que_suma, 40, 20)
    #     ejecutor.submit(un_metodo_que_resta, 79, 12)

    #     ejecutor.submit(un_metodo_que_suma, 10, 20)
    #     ejecutor.submit(un_metodo_que_resta, 10, 20)

    # Instrucción 1

    # tarea A

    # tarea B
    #
    #
    # LA ULTIMA