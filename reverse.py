import sys
import math
import random

class Character:
    def init(self):
        first_init_input = int(input())+5
        second_init_input = int(input())+5
        self.third_init_input = int(input())
        print("Init 1: %d" % first_init_input, file=sys.stderr, flush=True)
        print("Init 2: %d" % second_init_input, file=sys.stderr, flush=True)
        print("Init 3: %d" % self.third_init_input, file=sys.stderr, flush=True)
        self.map = [[0]*first_init_input]*second_init_input
        self.mx = 0
        self.my = 0
        self.old_mx = 0
        self.old_my = 0
        self.keypress = 'A'
    def get_command(self, x, y):
        # A, B, C, D or E
        if y < 0: # y--
            print("UP", file=sys.stderr, flush=True)
            self.keypress = 'C'
        elif x > 0: # x++
            print("RIGHT", file=sys.stderr, flush=True)
            self.keypress = 'A'
        elif y > 0: # y++
            print("DOWN", file=sys.stderr, flush=True)
            self.keypress = 'D'
        elif x < 0: # x--
            print("LEFT", file=sys.stderr, flush=True)
            self.keypress = 'E'
        else:
            print("NOP", file=sys.stderr, flush=True)
            self.keypress = 'B'
    def mainLoop(self):
        while True:
            first_input = input()
            second_input = input()
            third_input = input()
            fourth_input = input()
            #print("%s" % first_input, file=sys.stderr, flush=True)
            #print("%s" % second_input, file=sys.stderr, flush=True)
            #print("%s" % third_input, file=sys.stderr, flush=True)
            #print("%s" % fourth_input, file=sys.stderr, flush=True)
            
            for i in range(self.third_init_input):
                fifth_input, sixth_input = [int(j) for j in input().split()]
                if i == self.third_init_input-1:
                    self.old_mx = self.mx
                    self.old_my = self.my
                    self.mx = fifth_input
                    self.my = sixth_input
                    print("x:%d y:%d" % (self.mx, self.my), file=sys.stderr, flush=True)
                else:
                    print(" - Arg 5-6: %d %d" % (fifth_input, sixth_input), file=sys.stderr, flush=True)

            if self.old_mx == self.mx and self.old_my == self.my and self.keypress != 'B':
                print("ERROR: key %c does work with %s %s %s %s" % (self.keypress, first_input, second_input, third_input, fourth_input), file=sys.stderr, flush=True)
            
            # Add discovered areas to the map
            self.map[self.mx][self.my] = 1 # 1 = floor
            if first_input == '_':
                self.map[self.mx][self.my-1] = 1
            else:
                self.map[self.mx][self.my-1] = 2

            if second_input == '_':
                self.map[self.mx+1][self.my] = 1
            else:
                self.map[self.mx+1][self.my] = 2
            
            if third_input == '_':
                self.map[self.mx][self.my+1] = 1
            else:
                self.map[self.mx][self.my+1] = 2
            
            if fourth_input == '_':
                self.map[self.mx-1][self.my] = 1
            else:
                self.map[self.mx-1][self.my] = 2

            print(self.map, file=sys.stderr, flush=True)
            for i in range(-2, 3):
                line = ""
                for z in range(-2, 3):
                    line += "%d " % (self.map[self.mx+z][self.my+i])
                print(line, file=sys.stderr, flush=True)
            

            # if we can can go right and there is something to discover there
            if self.map[self.mx+1][self.my] == 1 and (self.map[self.mx+2][self.my] == 0 or self.map[self.mx+2][self.my+1] == 0 or self.map[self.mx+2][self.my-1] == 0):
                self.get_command(1, 0)
            # if we can go left and there is something to discover there
            elif self.map[self.mx-1][self.my] == 1 and (self.map[self.mx-2][self.my] == 0 or self.map[self.mx-2][self.my+1] == 0 or self.map[self.mx-2][self.my-1] == 0):
                self.get_command(-1, 0)
            # if we can go up and there is something to discover there
            elif self.map[self.mx][self.my-1] == 1 and (self.map[self.mx][self.my-2] == 0 or self.map[self.mx+1][self.my-2] == 0 or self.map[self.mx-1][self.my-2] == 0):
                self.get_command(0, -1)
            # if we can go down and there is something to discover there
            elif self.map[self.mx][self.my+1] == 1 and (self.map[self.mx][self.my+2] == 0 or self.map[self.mx+1][self.my+2] == 0 or self.map[self.mx-1][self.my+2] == 0):
                self.get_command(0, 1)
            
            print("Nothing to discover", file=sys.stderr, flush=True)
            # Trying to go down
            if self.map[self.mx][self.my+1] == 1:
                self.get_command(0, 1)
            elif self.map[self.mx-1][self.my] == 1:
                self.get_command(-1, 0)
            elif self.map[self.mx+1][self.my] == 1:
                self.get_command(1, 0)
            elif self.map[self.mx][self.my-1] == 1:
                self.get_command(0, -1)
            else:
                self.get_command(0, 0)
            
            print(self.keypress)

mPlayer = Character()
mPlayer.init()
mPlayer.mainLoop()