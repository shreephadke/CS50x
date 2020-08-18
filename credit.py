# input
print("Number: ", end="")
num = input()

# 15 digits and first two digits are 34 or 37 -> AMEX
if (len(num) == 15) and (int(num[:2]) in [34, 37]):
    print("AMEX")
# 16 digits and first two digits are between 51 and 56 (not including 56) -> MASTERCARD
elif (len(num) == 16) and (int(num[:2]) in range(51, 56)):
    print("MASTERCARD")
# 13 or 16 digits and first digit is 4 -> VISA
elif (len(num) in [13, 16]) and (int(num[:1]) == 4):
    print("VISA")
# otherwise INVALID
else:
    print("INVALID")