import time # Para utilizar la función sleep


def un_metodo_que_suma(parte1, parte2):
    time.sleep(2)
    suma = parte1 + parte2
    print("La suma de " + str(parte1) + " + " + str(parte2) + " es de: " + str(suma))

un_metodo_que_suma(4, 4)