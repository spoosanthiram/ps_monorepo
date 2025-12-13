def main():
    reloj = input("What time is it? ")

    converted_time = convert(reloj)

    if 7.0 <= converted_time <= 8.0:
        print("breakfast time")
    elif 12.0 <= converted_time <= 13.0:
        print("lunch time")
    elif 18.0 <= converted_time <= 19.0:
        print("dinner time")
    else:
        print("")

def convert(time):
    hour, minute = time.split(":")
    return float(hour) + float(minute) / 60

if __name__ == "__main__":
    main()
