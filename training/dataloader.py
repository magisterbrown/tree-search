import ctypes
from ctypes import Structure, POINTER, c_int, c_float
import numpy as np
import torch

impl = ctypes.CDLL("./loader.so")

class Loader(Structure):
    _fields_ = [
                ("width", c_int),
                ("height", c_int),
            ]

class Position(Structure):
    _fields_ = [
                ("result", c_int),
                ("moves_left", c_int),
                ("attacker", POINTER(c_float)),
                ("deffender", POINTER(c_float)),
            ]

init = impl.init
init.restype = POINTER(Loader)

get_next = impl.get_next
get_next.argtypes = [POINTER(Loader)]
get_next.restype = POINTER(Position) 


def eat_file():
    loader = init()
    w = loader.contents.width
    h = loader.contents.height
    sz = w * h

    while True:
        pos = get_next(loader).contents

        us = np.ctypeslib.as_array(pos.attacker, (sz,)).copy()
        them = np.ctypeslib.as_array(pos.deffender, (sz,)).copy()

        yield pos.result, pos.moves_left, us, them  

get = eat_file()

for i in range(8):
    if(i%2==0):
        vl = next(get)
        us = vl[2]
        sq = np.reshape(us, shape=(5,6))
        print(sq)


