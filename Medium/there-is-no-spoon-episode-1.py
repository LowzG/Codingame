import sys
import math

# Don't let the machines win. You are humanity's last hope...

width = int(input())  # the number of cells on the X axis
height = int(input())  # the number of cells on the Y axis

lines = []

for i in range(height):
    line = input() # width characters, each either 0 or .
    lline = list(line)
    lines.append(lline)
    
for yindex in range(height):
    for xindex in range(width):
        x2 = -1
        y2 = -1
        x3 = -1
        y3 = -1
        if lines[yindex][xindex] == '0':
            x1 = xindex
            y1 = yindex
            
            rightnode = x1 + 1
            
            while rightnode < width:
                if lines[yindex][rightnode] == '0':
                    x2 = rightnode
                    y2 = yindex
                    break
                rightnode += 1
                
            bottomnode = y1 + 1
            
            while bottomnode < height:
                if lines[bottomnode][xindex] == '0':
                    x3 = xindex
                    y3 = bottomnode
                    break
                bottomnode += 1
            print(f"{x1} {y1} {x2} {y2} {x3} {y3}")
