from ctypes import Structure, c_int, sizeof
import numpy as np
import torch
from torch.utils.data import DataLoader
import random

datas = "/home/brownie/minimax/tree-search/resources/dataset.bindone"

class GameRecord(Structure):
    _fields_ = [
                ("n_steps", c_int),
                ("res", c_int),
            ]

def repack(fname):
    with open(fname, "rb") as f:
        width = int.from_bytes(f.read(4), byteorder='little')
        height = int.from_bytes(f.read(4), byteorder='little')
        sz = width*height
        xplays = np.zeros(sz, dtype=np.float32)
        yplays = np.zeros(sz, dtype=np.float32)
        while True:
            chunk = f.read(sizeof(GameRecord))
            if not chunk:
                break
            game = GameRecord.from_buffer_copy(chunk)
            data = np.fromfile(f, dtype=np.uint8, count=game.n_steps)
            for i, idx in enumerate(data):
                xplays[idx] = (1-i%2)
                yplays[idx] = i%2
                if game.n_steps-i<8:
                    rsx = xplays#.reshape(height, width)
                    rsy = yplays#.reshape(height, width)
                    if(game.res != 0):
                        if i%2:
                            yield rsx, rsy, np.float32(game.res+1)/2
                        else:
                            yield rsy, rsx, np.float32(-game.res+1)/2

    
class PositionDataset(torch.utils.data.IterableDataset):
    def __init__(self, fname, sz_buff=40):
        super().__init__()
        self.fname = fname
        self.sz_buff = sz_buff

    def __iter__(self):
        buffer = list()
        ct = 0
        for el in repack(self.fname):
            if(len(buffer)<self.sz_buff):
                buffer.append(el)
            else:
                rep = np.random.randint(0, len(buffer))
                yield buffer[rep]
                buffer[rep] = el

        for el in buffer:
            yield el

if __name__ == "__main__":
    pd = PositionDataset(datas)
    import ipdb;ipdb.set_trace()
    
    dl = DataLoader(pd, batch_size=16)
    for batch in dl:
        print(batch[0].shape)
        print(batch[1])


