def get_ints():
    while True:
        try:
            num1 = float(input("Enter number: "))
            return num1
        except ValueError:
            print("Need a number")
        



while True:

    num1 = get_ints()
    num2 = get_ints()
    while True:   
        op = input("Enter your operation (+, -, *, /, ^): ")

        if op == "+":
            print("Your value is: " + str(num1 + num2))
            break
        elif op == "-":
            print("Your value is: " + str(num1 - num2))
            break
        elif op == "*":
            print("Your value is: " + str(num1 * num2))
            break
        elif op == "^":
            print("Your value is: " + str(num1 ** num2))
            break
        elif op == "/":
            if num2 == 0:
                print("Cannot divide by zero")
            else:
                print("Your value is: " + str(num1 // num2) + " R " + str(num1 % num2))
                break
        else:
            print("Not valid operation")
            

    again = input("use again?(y | n) ")
    if again == "n":
        break
    

