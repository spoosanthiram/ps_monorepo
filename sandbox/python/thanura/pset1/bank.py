greeting = input("Greeting: ")

if greeting == "Hello":
    print("$0")
elif greeting.startswith("H"):
    print("$20")
else:
    print("$100")
