import numpy as np
from ctypes import (
            Structure,
            c_int,
            c_uint,
            sizeof
        )

class GameRecord(Structure):
    _fields_ = [
        ("n_steps", c_int),
        ("res",     c_int),
        ("magic",   c_uint)
    ]


def repack(fname):
    with open(fname, "rb") as f:
        width = int.from_bytes(f.read(4), byteorder='little')
        height = int.from_bytes(f.read(4), byteorder='little')
        sz = width*height
        while True:
            chunk = f.read(sizeof(GameRecord))
            if not chunk:
                break
            game = GameRecord.from_buffer_copy(chunk)
            assert game.magic == 0xdeadbeef, "Magic didnt match"

            print(f"N steps {game.n_steps}")
            data = np.fromfile(f, dtype=np.uint8, count=game.n_steps)
            if game.res == 0:
                continue
            print("new game")
            xplays = np.zeros(sz, dtype=np.float32)
            yplays = np.zeros(sz, dtype=np.float32)
            for i, idx in enumerate(data):
                xplays[idx] = (1-i%2)
                yplays[idx] = i%2
                if game.n_steps-i<8:
                    #buffpt = 0;
                    rsx = xplays#.reshape(height, width)
                    rsy = yplays#.reshape(height, width)
                    if(game.res != 0):
                        if i%2:
                            yield rsx, rsy, np.float32(game.res+1)/2
                        else:
                            yield rsy, rsx, np.float32(-game.res+1)/2


if __name__ == "__main__":
    dl = repack("resources/dataset.bindone")
    i = 0
    for x in dl:
        us, them, res = x
        if(not i%2):
            print(f"{i} {us.astype(np.int32)} {res}")
        i+=1
        pass
