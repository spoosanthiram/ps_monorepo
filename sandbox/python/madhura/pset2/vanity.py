def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    if len(s) > 6 or len(s) < 2:
        return False

    i = 0
    for ch in s:
        if ch.isdigit():
            break
        else:
            i = i + 1
    letters = s[0:i]
    numbers = s[i:]

    if numbers.startswith("0"):
        return False

    return True

main()
