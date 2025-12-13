def main():
  m = input("m: ")
  E = (int(m) * square(300000000))
  print(f"{E:,}")

def square(c):
    return c * c 

main()
