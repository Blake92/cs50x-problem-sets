# TODO

from cs50 import get_string

credit = get_string("Number: ")
len = len(credit)
firstN = int(credit[0]) * 10 + int(credit[1])
credit = credit[::-1]
chksum = 0
for i in range(1, len, 2):
    sum = int(credit[i]) * 2
    if (sum >= 10):
        sum = int((sum % 10)) + int((sum / 10))
    chksum = sum + chksum
for i in range(0, len, 2):
    chksum = chksum + int(credit[i])
if (chksum % 10 == 0):
    if (len == 15):
        if (firstN == 34 or firstN == 37):
            print("AMEX")
        else:
            print("INVALID")
    elif (len == 16):
        if (int(firstN / 10) == 4):
            print("VISA")
        elif (firstN == 51 or firstN == 52 or firstN == 53 or firstN == 54 or firstN == 55):
            print("MASTERCARD")
        else:
            print("INVALID")
    elif (len == 13):
        if (int(firstN / 10) == 4):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")

