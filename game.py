from typing import Literal, List, Dict
from ctypes import (
            POINTER,
            Structure,
            c_int,
            c_ubyte,
            c_float
        )
from ctypes import (
        byref,
        cast
    )
import ctypes
import os

gamelib = ctypes.CDLL("./libsearch.so")

class BaseField(Structure):
    _fields_ = [
        ("width", c_int),
        ("height", c_int),
    ]

print_field = gamelib.print_field
print_field.argtypes = [POINTER(BaseField)]

do_move = gamelib.do_move
do_move.argtypes = [POINTER(BaseField), c_int, c_ubyte]

get_winner = gamelib.get_winner
get_winner.argtypes = [POINTER(BaseField), c_int]
get_winner.restype = c_int

any_done = gamelib.any_done
any_done.argtypes = [POINTER(BaseField), c_int]
any_done.restype = c_int

class GameContext(Structure):
    _fields_ = [
        ("field", POINTER(BaseField)),
        ("pic", c_ubyte),
        ("inarow", c_int)
    ]

class SearchContext(Structure):
    _fields_ = [
        ("max_depth", c_int)
    ]

search = gamelib.search
search.argtypes = [POINTER(c_float), GameContext, SearchContext]
search.restype = POINTER(c_float)

def create_field(width, height):
    class Field(BaseField):
        _fields_ = [
            ("board", c_ubyte * (width * height)),
        ]
        def get_cell(self, x, y):
            return self.board[self.width*y+x]
        def set_cell(self, x, y, val):
            self.board[self.width*y+x] = val
    return Field(width, height)

class Game:
    inarow: int
    field: POINTER(BaseField)
    def __init__(self, width, height, inarow):
        self.inarow = inarow
        self.field = create_field(width, height)
        self.field_pointer = byref(self.field)
        self.fig = 1

    def print(self):
        print_field(self.field_pointer)

    def do_move(self, pos):
        do_move(self.field_pointer, pos, self.fig)
        self.fig = 1 if self.fig == 2 else 2

    def is_done(self) -> bool:
        return any_done(self.field_pointer, self.inarow)

    def result(self) -> int:
        assert self.is_done()
        return get_winner(self.field_pointer, self.inarow)

    def get_moves(self) -> List[int]:
        posm = list()
        for i in range(self.field.width):        
            if(self.field.get_cell(i,0) == 0):
                posm.append(i)
        return posm

    def search(self, depth: int) -> Dict[int, float]:
        inres = (c_float * self.field.width)()
        game_context = GameContext(cast(self.field_pointer, POINTER(BaseField)), self.fig, self.inarow)
        search(inres, game_context, SearchContext(depth))
        res = dict()
        for move, value in enumerate(inres):
            if value == value:
                res[move] = value
        return res

