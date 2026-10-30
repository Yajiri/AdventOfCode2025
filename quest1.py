startpoint = 50
x = 0

while True:
    command = input("Enter commmand: ").upper()
    
    if command == "DONE":
        break
    
    direction = command[0] #if we're doing - or +
    moveSteps = int(command[1:]) #should indicate how many steps I should move.
    if direction == "L":
        startpoint = (startpoint + moveSteps) % 100
        if startpoint == 0:
            x = x + 1

    if direction == "R":
        startpoint = (startpoint - moveSteps) % 100
        if startpoint == 0:
            x = x + 1


print("Stopped at 0", x, "times")
