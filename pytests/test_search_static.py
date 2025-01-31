import unittest
import io
from pathlib import Path
from game import BaseField, create_field, Game
from ctypes import memmove, byref, sizeof
from ctypes import c_float, c_ubyte, c_int

class TestSearchStatic(unittest.TestCase):

    def test_search(self):
        for path in Path("resources/saved_positions").iterdir():
            with open(path, "rb") as file:
                buffer = file.read()
                base = BaseField()
                memmove(byref(base), buffer, sizeof(base))

            game = Game(base.width, base.height, 3)
            evals = (c_float*base.width)()
            fig = c_ubyte()
            inarow = c_int()
            depth = c_int()

            stream = io.BytesIO(buffer)
            stream.readinto(game.field)
            stream.readinto(fig)
            game.fig = fig.value
            stream.readinto(inarow)
            game.inarow = inarow.value
            stream.readinto(depth)
            stream.readinto(evals)

            nres = game.search(depth.value)
            for key, val in enumerate(evals[:]):
                if val==val:
                    self.assertEqual(val, nres[key])
