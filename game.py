from typing import Literal
import ctypes
import os
gamelib = ctypes.CDLL("./libsearch.so")

class BaseField(ctypes.Structure):
    _fields_ = [
        ("width", ctypes.c_int),
        ("height", ctypes.c_int),
    ]
    def get_cell(self, x, y):
        return self.board[width*y+x]
    def set_cell(self, x, y, val):
        self.board[width*y+x] = val

print_field = gamelib.print_field
print_field.argtypes = [ctypes.POINTER(BaseField)]
do_move = gamelib.do_move
do_move.argtypes = [ctypes.POINTER(BaseField), ctypes.c_int, ctypes.c_ubyte]

def create_field(width, height):
    class Field(BaseField):
        _fields_ = [
            ("board", ctypes.c_ubyte * (width * height)),
        ]
    return Field(width, height)

class Game:
    inarow: int
    field: ctypes.POINTER(BaseField)
    def __init__(self, width, height, inarow):
        self.inarow = inarow
        self.field = create_field(width, height)

    def print(self):
        print_field(ctypes.byref(self.field))

    def do_move(self, pos, fig):
        do_move(ctypes.byref(self.field), pos, fig)
field = Game(4, 3, 3)
field.do_move(1, 2)
field.print()
