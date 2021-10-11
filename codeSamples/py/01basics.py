# from cs50 import get_string


answer = input("what's your name man? ")

# option 1
print("hello, " + answer)

# option 2 - the f tells to not interpret the { literally
print(f"hello, {answer}")

x = y = 0

# be careful, python REQUIRES indentation to work properly
if x < y:
    print("x is lower than y")
# else if is called "elif"
elif x > y:
    print("x is greater than y")
else:
    print("x is not less than y")

# infinite loop - the True has a capital T
# while True:
#     print("hello, world")

# finite loop - you can't do i++ in python
i = 0
while i < 3:
    print("hello, world")
    i += 1


# easier way to do for loops if you need to hardcode small values
j = 0
for j in [0, 1, 2]:
    print("hello, world")

# even better way to do loops
for k in range(3):
    print("hello, world")

# python data types - bool, str (string), int, float

# other data types 
# range - range of values
# list - similar to array, but variable size
# tuple - like if you have x , y ,z coordinates
# dict - can store keys and values
# set - collection of values without duplicates

