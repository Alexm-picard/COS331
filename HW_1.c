//Alex Picard

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  char input_line[9];
  int fp, ret;
  short int pc = 0;
  short int sp = 0; //change to where the memory would actually start
  short int p0, p1, p2, p3;
  char psw[2];
  int acc, r0, r1, r2, r3; 
  char ir[6];
  char memory[100][6];
  fp = open("testProcess", O_RDONLY);
  int program_line = 0;
  while(read(fp, input_line, 8)){
    //char opcode[3] = {input_line[8], input_line[7], "\0"};
    memcpy(memory[program_line], input_line,6);
    program_line++;
  }

  program_line = 0;

  while(1){
    int test = output(memory[program_line]);
    program_line++;
  }
  
  return 0;
}

int opcode(char input_line[9]){
    return (input_line[0] - '0')*10 + (input_line[1] - '0');
}

int output(char instruction[9]){
    switch(opcode(instruction)){
        case 0:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 1:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 2:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 3:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 4:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 5:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 6:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 7:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 8:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 9:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 10:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 11:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 12:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 13:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 14:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 15:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 16:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 17:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 18:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 19:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 20:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 21:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 22:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 23:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 24:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 25:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 26:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 27:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 28:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 29:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 30:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 31:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 32:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 33:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 34:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 35:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 50:
            printf("Opcode: %d\n", opcode(instruction));
            break;
        case 99:
            printf("Opcode: %d\n", opcode(instruction));
            exit(0);
            break;
        default:
            printf("Unknown Opcode");
            break;
    }
}