def main():
    text = input().strip()
    greet, emote = text.split(" ")
    print(greet, apple(emote))

def apple(emote):
    if emote == ":(":
        return "🙁"
    elif emote == ":O":
        return "🤥"
    return "?"

main()
