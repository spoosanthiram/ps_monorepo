# convert emoticon to emoji

def convert(emote):
    if emote == ":)":
        return "🙂"
    elif emote == ":(":
        return "🙁"
    else:
        return "👺"

text = input()
greet, emoticon = text.split(" ")
emoji = convert(emoticon)
print(f"{greet} {emoji}")
