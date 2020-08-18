print("Text: ", end="")
s = input()
letters, words, sent = 0, 1, 0
for i in s:
    if i.isalpha():
        letters += 1
    elif i == " ":
        words += 1
    elif i in [".", "!", "?"]:
        sent += 1

# print(letters)
# print(words)
# print(sent)

L = letters/words * 100
# print(L)
S = sent/words * 100
# print(S)

index = round((0.0588 * L - 0.296 * S - 15.8))

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade: {index}")