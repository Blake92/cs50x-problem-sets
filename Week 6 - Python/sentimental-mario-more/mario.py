# TODO

from cs50 import get_int

hash = get_int("Height: ")
while (hash <= 0 or hash > 8):
    hash = get_int("Height: ")
for x in range(hash):
    print(" " * (hash-(x+1)) + "#" * (x+1) + "  " + "#" * (x+1))

