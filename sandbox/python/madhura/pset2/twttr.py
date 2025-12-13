text = input("Input: ")
for ch in text:
    if ch not in ["A", "a", "E", "e", "I", "i", "O", "o", "U", "u"]:
        print(ch, end="")
print()

