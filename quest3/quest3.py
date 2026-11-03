largest = 0
y = 0

stringOfCode = input("Please inout the string of numbers: ").upper()      

i = 0 
start_index = 0
while i < len(stringOfCode) - 1:

        #This is here to ensure that we break on the first 9
        if stringOfCode[i] == '9':
                largest = 9
                start_index = i + 1
                break

        #If there is no 9 we'd still need to find the largest number    
        if int(stringOfCode[i]) > largest:
                largest = int(stringOfCode[i])
                start_index = i

        i += 1

#second loop, starting from the position just after the largest number we found.
i = start_index

while i < len(stringOfCode):
        if int(stringOfCode[i]) > y:
                y = int(stringOfCode[i])
        i += 1

#sep can be set in order to remove the otherwise mandatort space in between largest and y in the print. 
print("The largest possible number is: ", largest,y, sep="")

#in python you could also use a printf statment like this:
#print(f"{largest}{y}")