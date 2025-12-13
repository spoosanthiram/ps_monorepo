problem = input("Expression: ")
# 8 + 9

x, y, z = problem.split(" ")

x = float(x)
z = float(z)

match(y):
    case "+":
        print(x + z)
    case "-":
        print(x - z)
    case "*":
        print(x * z)
    case "z":
        print(x / z)
