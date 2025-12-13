due = 50
while due > 0:
    coin = int(input("Insert Coin: "))
    if coin not in [5, 10, 25]:
        print("Coin Invalid.")
        continue
    due = due - coin
    if due > 0:
        print("Amount Due: ", due)
    else: 
        print("Change Owed: ", abs(due))
