expression = input("Expression: ")

x, expr, y = expression.split(" ")

x = float(x)
y = float(y)

z = 0

match expr:
    case "+":
        z = x + y
    case "-":
        z = x - y
    case "*":
        z = x * y
    case "/":
        z = x / y
print(z)
