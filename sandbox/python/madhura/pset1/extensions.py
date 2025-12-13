type = input("File name: ")

if type.find(".") == -1:
    print("application/octet-stream")
else:
    name, extension = type.split(".")

    match extension:
        case "pdf" | "txt" | "zip":
            print(f"application/{extension}")
        case "gif" | "jpg" | "jpeg"| "png":
            print(f"image/{extension}")
        case _:
            print("application/octet-stream")
