import sys
import math
import random

def get_command(x, y):
    # A, B, C, D or E
    if y < 0: # y--
        keypress = 'C'
    elif x > 0: # x++
        keypress = 'A'
    elif y > 0: # y++
        keypress = 'D'
    elif x < 0: # x--
        keypress = 'E'
    else:
        keypress = 'B'
    return keypress


first_init_input = int(input())
second_init_input = int(input())
third_init_input = int(input())

print("Init 1: %d" % first_init_input, file=sys.stderr, flush=True)
print("Init 2: %d" % second_init_input, file=sys.stderr, flush=True)
print("Init 3: %d" % third_init_input, file=sys.stderr, flush=True)

map = [[0]*first_init_input]*second_init_input

mx = 0
my = 0
old_mx = 0
old_my = 0
keypress = 'A'
while True:
    first_input = input()
    second_input = input()
    third_input = input()
    fourth_input = input()
    print("%s" % first_input, file=sys.stderr, flush=True)
    print("%s" % second_input, file=sys.stderr, flush=True)
    print("%s" % third_input, file=sys.stderr, flush=True)
    print("%s" % fourth_input, file=sys.stderr, flush=True)
    
    for i in range(third_init_input):
        fifth_input, sixth_input = [int(j) for j in input().split()]
        if i == third_init_input-1:
            old_mx = mx
            old_my = my
            mx = fifth_input
            my = sixth_input
            print("x:%d y:%d" % (mx, my), file=sys.stderr, flush=True)
        else:
            print(" - Arg 5-6: %d %d" % (fifth_input, sixth_input), file=sys.stderr, flush=True)

    if old_mx == mx and old_my == my and keypress != 'B':
        print("ERROR: key %c does work with %s %s %s %s" % (keypress, first_input, second_input, third_input, fourth_input), file=sys.stderr, flush=True)
    
    # Add discovered areas to the map
    map[mx][my] = 1 # 1 = floor
    if first_input == '_':
        map[mx][my-1] = 1
    else:
        map[mx][my-1] = 2

    if second_input == '_':
        map[mx+1][my] = 1
    else:
        map[mx+1][my] = 2
    
    if third_input == '_':
        map[mx][my+1] = 1
    else:
        map[mx][my+1] = 2
    
    if fourth_input == '_':
        map[mx-1][my] = 1
    else:
        map[mx-1][my] = 2

    print(map, file=sys.stderr, flush=True)

    keypress = get_command(1, 1)
    
    print(keypress)