from PIL import Image, ImageFilter


# the . operator
# you can have functions inside of structures
# image "object" contains open function
before = Image.open("bridge.bmp")

after = before.filter(ImageFilter.BoxBlur(1))
after.save("out.bmp")

# dammit I could have written the filter problem in 4 lines of code

