# π₯ μμ€ν νλ‘κ·Έλλ°
## Mini Shell

```
You will make a simple, tiny shell
```

### **A naive shell structure would be like:** <br>
β’ (Infinite loop) <br>
β’ - (1) get user input as a string <br>
β’ - (2) parse the string into meaningful pieces (command and its arguments) <br>
β’ - (3) execute the commands using the pieces <br>

<br>

### **Given: skeleton code is given** <br> 
β’ shell.c - current version implements (infinite loop) + (1) <br>
β’ Two functions, main() & user_in(), are complete <br>

<br>

### **Task: you are required to implement (2) + (3)** <br> 
β’ Two functions, parse_cmd() + execute_cmd(), are empty <br>

<br>

### **Execution Example**
```bash
Command> cp source dest
input: cp source dest
output:
arg[0]:
arg[1]:
arg[2]:
arg[3]:
arg[4]:
Command>
```
When executed, <br>
β’ It displays a prompt "Command>"<br>
β’ You gives a cmd by keyboard<br>
β’ user_in() receives the cmd

<br>

>Your parse_cmd() will divide this into three pieces<br>
**cp, source, dest** <br>
> <br>
> Your execute_cmd() will actually execute this copy cmd.<br>
**As a result, dest will be created**<br>
><br>
> Once done, it displays a prompt and is ready for the next cmd