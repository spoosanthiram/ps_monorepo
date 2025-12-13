name = input("File Name: ")


if name.endswith(".jpg"):
    print("image/jpg")
elif name.endswith(".jpeg"):
    print("image.jpeg")
elif name.endswith(".txt"):
    print("text/plain")
elif name.endswith(".gif"):
    print("image/gif")
elif name.endswith(".png"):
    print("image/png")
elif name.endswith(".zip"):
    print("application/zip")
else:
    print("application/octet-stre")
