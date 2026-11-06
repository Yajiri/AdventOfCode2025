startpoint = 50
x = 0

with open("quest1/input.txt", "r") as file:
    for line in file:
        command = line.strip().upper()

        if not command: #just making sure we skip empty lines
            continue


    
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
