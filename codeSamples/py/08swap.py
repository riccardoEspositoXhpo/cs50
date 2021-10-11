from cs50 import get_int

x = get_int("x: ")
y = get_int("y: ")

print(f"x is {x}, y is {y}")

x, y = y, x

print(f"x is {x}, y is {y}")