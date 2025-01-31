import unittest
import operator
import random
import itertools

from game import Game
class TestSearchDynamic(unittest.TestCase):
    depths = [2,4,6,8]
    sizes = [(2,2),(4, 3), (4, 5)]
    inarows = [2, 3, 4]
    def setUp(self):
        self.combinations = list(itertools.product(self.inarows, itertools.product(self.sizes, self.depths)))
        self.msg = "Width: {w} Height: {h} Inarow: {i} Depth: {d} Moves: {m}"

    @unittest.skip
    def test_simetric_oponent(self):
        for inarow, ((width, height), depth) in self.combinations:
            steps = list()
            game = Game(width, height, inarow)
            first_nonzero = 0
            while not game.is_done():
                res = game.search(depth)
                if game.fig == 1:
                    best = max(res.values())
                else:
                    best = min(res.values())
                if ((best == 999 and game.fig==1) or (best == -999 and game.fig==2)) and first_nonzero == 0:
                    first_nonzero = int(best)
                move = random.choice([move for move in res.keys() if res[move] == best])
                game.do_move(move)
                steps.append(move)
            fres = 999*game.result()
            if(fres != first_nonzero):
                game.print()
                self.assertEqual(fres, first_nonzero, msg=self.msg.format(w=width,h=height,i=inarow,d=depth,m=steps))
    @unittest.skip
    def test_random_oponent(self):
        for inarow, ((width, height), depth) in self.combinations:
            steps = list()
            game = Game(width, height, inarow)
            first_nonzero = 0
            nonz_fig = 0
            while not game.is_done():
                res = game.search(depth)
                if nonz_fig and nonz_fig != game.fig:
                    move = random.choice(game.get_moves())
                else:
                    if game.fig == 1:
                        best = max(res.values())
                    else:
                        best = min(res.values())
                    move = random.choice([move for move in res.keys() if res[move] == best])
                if ((best == 999 and game.fig==1) or (best == -999 and game.fig==2)) and first_nonzero == 0:
                    first_nonzero = int(best)
                    nonz_fig = game.fig
                game.do_move(move)
                steps.append(move)
            fres = 999*game.result()
            if(fres != first_nonzero):
                game.print()
                self.assertEqual(fres, first_nonzero, msg=self.msg.format(w=width,h=height,i=inarow,d=depth,m=steps))

