def main():
    mario(3)

def mario(n):
    for i in range(n):
        print("#")

    for j in range(n):
        #print something horizontally
        print("?", end="")

    print("")

main()