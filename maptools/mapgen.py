from array import *
from PIL import Image

im = Image.open('./garfmap.bmp')
pix = im.load()

width, height = im.size

black = [0, 0, 0]
white = [255, 255, 255]
red = [255, 0, 0]
green = [0, 255, 33]


for j in range(height):
    for i in range(width):
        if pix[i,j] == tuple(white):
            print("0", sep = '', end = ',')
        elif pix[i,j] == tuple(black):
            print("1", sep = '', end = ',')
        elif pix[i,j] == tuple(red):
            print("2", sep = '', end = ',')
        elif pix[i,j] == tuple(green):
            print("3", sep = '', end = ',')
        else:
            print("ERR:",pix[i,j], sep = '', end = ',')
    print("")
    
