#!/usr/bin/env python

import sys

newstring = ""

for line in sys.stdin:
        for char in line:
                if char == ' ':
                        newstring += ' '
                else:
                        newstring += chr(ord(char) - 3)

print newstring
