def main():
    mealtime = input("What time is it? ")
    converted_time = convert(mealtime)

    if converted_time >= 7.0 and converted_time <= 8.0:
        print("breakfast time!!")
    elif converted_time >= 12.0 and converted_time <= 13.0:
        print("lunch time!!")
    elif converted_time >= 18.0 and converted_time <= 19.0:
        print('dinner time!!')
    else:
        print("NO EATING")

def convert(time):
    hours, minutes = time.split(":")
    return int(hours) + int(minutes) / 60 

if __name__ == "__main__":
   main()
