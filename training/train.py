import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader

from pyloader import PositionDataset

class Model(nn.Module):
    def __init__(self):
        super().__init__()
        width = 6
        height = 5
        self.transformer = nn.Linear(width*height, 512)
        self.l1 = nn.Linear(1024, 256)
        self.l2 = nn.Linear(256, 32)
        self.output = nn.Linear(32, 1)

    def forward(self, us, them):
        #import ipdb; ipdb.set_trace()
        #x = torch.concatenate([us, them],dim=-1)
        #x = self.transformer(x)
        us_x = self.transformer(us)
        them_x = self.transformer(them)
        x = torch.concatenate([us_x, them_x], dim=-1)
        # print(f"Stats: {x.shape} mean: {x.mean()} std: {x.std()}")

        x=F.leaky_relu(x)
        x = self.l1(x)
        ##x = torch.clamp(x, 0, 1)
        x=F.leaky_relu(x)
        #x=F.tanh(x)
        x = self.l2(x)
        x=F.leaky_relu(x)
        #x = torch.clamp(x, 0, 1)
        x = self.output(x)
        return x

datas = "/home/brownie/minimax/tree-search/resources/dataset.bindone"

import torch
import numpy as np
import random
import os

SEED = 42

# Base seeding
torch.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
random.seed(SEED)
np.random.seed(SEED)


import torch.optim as optim


if __name__ == "__main__":
    pd = PositionDataset(datas)
    
    dl = DataLoader(pd, batch_size=4)
    device = "cuda:0"
    model = Model().to(device)
    optimizer = optim.AdamW(model.parameters(), lr=3e-4)

    b1 = next(iter(dl))
    #import ipdb; ipdb.set_trace()

    n = 50
    print(model)
    #for i in range(n):
    epochs = 3
    for ep in range(epochs):
        for i, b in enumerate(dl):
            optimizer.zero_grad()
            us, them, target = b
            target = target[:, None].to(device)
            #for i in range(target.shape[0]):
            #    target[i] = 0
            pred = model(us.to(device), them.to(device))
            cmb = torch.concatenate([pred, pred.sigmoid(), target], dim=-1)
            #if(i==0 or i==n-1):
            loss  = F.binary_cross_entropy(pred.sigmoid(), target.to(device))
            loss.backward()
            optimizer.step()


            t = target
            epsilon = 1e-12
            outcome_entropy = -(t * (t + epsilon).log() + (1.0 - t) * (1.0 - t + epsilon).log())

            print(loss.item() - outcome_entropy.mean().item())
        print(cmb)
    pass

