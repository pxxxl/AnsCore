def gen( key ):
    print("global sendKey{} := false".format(key))
    print("{0}::\nSendInput {{{0}}}{{Enter}}\nreturn\n\n{0} up::".format(key))
    print("SendInput 1{Enter}")
    print("return\n")
    

def main():
    # all characters in the keyboard, put them in a list
    # and then generate the hotkey for each of them
    # use lower case
    for i in range(97, 123):
        gen(chr(i))

if __name__ == "__main__":
    main()