import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

message = input()

# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr)

message_binary = "".join('{0:07b}'.format(ord(i)) for i in message)

def chuck_convert(binary):
    if binary == "0":
        return "00"
    return "0"

character = message_binary[0]
answer = chuck_convert(character) + " "
for b in message_binary:
    if b != character:
        character = b
        answer = answer + " " + chuck_convert(b) + " "
    answer += "0"

print(answer)