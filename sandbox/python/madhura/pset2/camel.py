def main():
    camel = input("camelCase: ")
    slither(camel)

def slither(camel):
    print("snake_case: ", end="")
    for letters in camel:
        if letters.isupper():
            print("_", end="")
            print(letters.lower(), end="")
        else:
            print(letters, end="")
    print()

main()
