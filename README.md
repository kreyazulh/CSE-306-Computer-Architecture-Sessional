# CSE-306-Computer-Architecture-Sessional

This repository contains all the assignment resources of group 5/B1 for CSE-306 Computer Architecture Sessional course (July 2022).

## Prerequisites

1. Install [Logisim-ITA](https://github.com/Logisim-Ita/Logisim) for better simulation results.
2. Having Proteus can be an added bonus. You can download the crack version from internet.



# Assignment 1 - 4 Bit ALU Design

In this assignment, we were asked to build a 4-Bit ALU with given opcodes. Go through the [specifications](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%201-%204-Bit%20ALU/CSE%20306%20Assignment%201.pdf) and the [report](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%201-%204-Bit%20ALU/Report/B1_Group5_Report.pdf) to get a better idea..

## Run Simulation

Make sure to include the exact [7400.circ file](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%201-%204-Bit%20ALU/Software%20Simulation/7400-lib.circ) given.


# Assignment 2 - 32 Bit FLoating Point Adder

In this assignment, we were asked to simulate a Floating Point Adder on software. Go through the [specifications](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%202-Floating%20Point%20Adder/CSE%20306%20Assignment%202.pdf) and the [report](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%202-Floating%20Point%20Adder/B1_Group5_Report.pdf) to get a better idea.

## Run Simulation

Just open the .circ file in your Logisim-ITA software.


# Assignment 3 - 4 Bit MIPS Design

In this assignment, we were asked to build a 4-Bit MIPS with different control sequence for each team. Go through the [specifications](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%203-%204%20Bit%20MIPS/Assignment%203.pdf) and the [report](https://github.com/kreyazulh/CSE-306-Computer-Architecture-Sessional/blob/main/Assignment%203-%204%20Bit%20MIPS/Report/B1_Group5_Report.pdf) to get a better idea.

## Run Simulation

Run the assembler to generate machine.txt. For linux platform, simply execute the shell script file. For windows, open the script file with a text editor and execute the commands manually.

```bash
.\run.sh
```
Include the machine.txt file in instructions rom, control_rom.txt in control rom of the logisim circuit. 

## Hardware Design

We have used a d-flip-flop and a switch for CLK. Make sure to avoid [race condition](https://www.techtarget.com/searchstorage/definition/race-condition#:~:text=A%20race%20condition%20is%20an,sequence%20to%20be%20done%20correctly.) when designing the data paths.

## Contributions

The Team :
1. Tareq Ahmed
2. Mehreen Maliha
3. [Kazi Reyazul Hasan](https://github.com/kreyazulh)
4. Wasif Jalal
5. [Mubasshira Musarrat](https://github.com/MubasshiraMusarrat)


## License

[MIT](https://choosealicense.com/licenses/mit/)
