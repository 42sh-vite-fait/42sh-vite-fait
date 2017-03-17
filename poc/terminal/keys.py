from __future__ import print_function
import sys, tty, termios, string

def enableRawMode():
    backup = termios.tcgetattr(sys.stdin)
    tty.setraw(sys.stdin)
    return backup

def disableRawMode(backup):
    termios.tcsetattr(sys.stdin, termios.TCSAFLUSH, backup)

def printKeyCode():
    backup = enableRawMode()
    while True:
        char = sys.stdin.read(1)
        if ord(char) == 3: # CTRL-C
            disableRawMode(backup)
            break;
        print('{:3d} | '.format(ord(char)), end='')
        if ord(char) < 32:
            print('^{}'.format(chr(ord(char) + 64)))
        elif ord(char) == 127:
            print('^?')
        else:
            print('{}'.format(char))
        sys.stdout.write("\r")

printKeyCode()
