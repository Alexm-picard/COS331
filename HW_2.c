//Alex Picard

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int opcode(char input_line[9]);
int instructions(char instruction[9]);
char* two_char_first(char input_line[9]);
char* two_char_second(char input_line[9]);
int two_int_first(char input_line[9]);
int two_int_second(char input_line[9]);
int four_int(char input_line[9]);
char output[2];
char input_line[9];
int fp, ret;
short int pc = 0;
short int sp = 0; //change to where the memory would actually start
short int p0, p1, p2, p3;
char psw[2];
int acc, r0, r1, r2, r3; 
char ir[6];
char memory[6][100];//For some reason my laptop needs it in this format to properly work
int program_line = 0;
int main(int argc, char** argv) {
  
  fp = open("testProcess", O_RDONLY);
  while(read(fp, input_line, 8)){
    //char opcode[3] = {input_line[8], input_line[7], "\0"};
    memcpy(memory[program_line], input_line,6);
    program_line++;
  }
    
    program_line++;

  program_line = 0;
  
  while(1){

    int test = instructions(memory[program_line]);
    //printf("%d\n", acc);
    if(opcode(memory[program_line]) == 15){
        break;
    }
    program_line++;
  }
  printf("%d %d %d %d %d %s %s\n", p0, p1, r3, r2, acc, memory[20], memory[21]);
  return 0;
}

int opcode(char input_line[9]){
    return (input_line[0] - '0')*10 + (input_line[1] - '0');
}

char* two_char_first(char input_line[9]){
    output[0] = input_line[2];
    output[1] = input_line[3];
    return output;
}
char* two_char_second(char input_line[9]){
    output[0] = input_line[4];
    output[1] = input_line[5];
    return output;
}
int two_int_first(char input_line[9]){
    return (input_line[2] - '0')*10 + (input_line[3] - '0');
}
int two_int_second(char input_line[9]){
    return (input_line[4] - '0')*10 + (input_line[5] - '0');
}

int four_int(char input_line[9]){
    return (input_line[2] - '0')*1000 + (input_line[3] - '0')*100+(input_line[4] - '0')*10 + (input_line[5] - '0');
}

int instructions(char instruction[9]){
    //printf("%d\n", program_line);
    //printf("%d\n", opcode(memory[program_line]));
    
    switch(opcode(memory[program_line])){
        case 0:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                p0 = two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                p1 = two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                p2 = two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                p3 = two_int_second(memory[program_line]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 1:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                p0 += two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                p1 += two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                p2 += two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                p3 += two_int_second(memory[program_line]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 2:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                p0 -= two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                p1 -= two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                p2 -= two_int_second(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                p3 -= two_int_second(memory[program_line]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 3:
            acc = four_int(memory[program_line]);
            break;
        case 4:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                acc = memory[p0][0]* 100000 + memory[p0][1]* 10000 +memory[p0][2] * 1000 + memory[p0][3] * 100 +memory[p0][4] * 10 + memory[p0][5];
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                acc = memory[p1][0]* 100000 + memory[p1][1]* 10000 +memory[p1][2] * 1000 + memory[p1][3] * 100 +memory[p1][4] * 10 + memory[p1][5];
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                acc = memory[p2][0]* 100000 + memory[p2][1]* 10000 +memory[p2][2] * 1000 + memory[p2][3] * 100 +memory[p2][4] * 10 + memory[p2][5];
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                acc = memory[p3][0]* 100000 + memory[p3][1]* 10000 +memory[p3][2] * 1000 + memory[p3][3] * 100 +memory[p3][4] * 10 + memory[p3][5];
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 5:
            acc = memory[two_int_first(memory[program_line])][0]* 100000 + memory[two_int_first(memory[program_line])][1]* 10000 +memory[two_int_first(memory[program_line])][2] * 1000 + memory[two_int_first(memory[program_line])][3] * 100 +memory[two_int_first(memory[program_line])][4] * 10 + memory[two_int_first(memory[program_line])][5];
            break;
        case 6:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                memory[p0][0] = '9';
                memory[p0][1] = '9';
                memory[p0][2] = acc/1000 +'0';
                memory[p0][3] = acc/100 - acc/1000 +'0';
                memory[p0][4] = acc/10 - acc/100 - acc/1000 +'0';
                memory[p0][5] = acc%10 +'0';
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                memory[p1][0] = '9';
                memory[p1][1] = '9';
                memory[p1][2] = acc/1000 +'0';
                memory[p1][3] = acc/100 - acc/1000 +'0';
                memory[p1][4] = acc/10 - acc/100 - acc/1000 +'0';
                memory[p1][5] = acc%10 +'0';
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                memory[p2][0] = '9';
                memory[p2][1] = '9';
                memory[p2][2] = acc/1000 +'0';
                memory[p2][3] = acc/100 - acc/1000 +'0';
                memory[p2][4] = acc/10 - acc/100 - acc/1000 +'0';
                memory[p2][5] = acc%10 +'0';
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                memory[p3][0] = '9';
                memory[p3][1] = '9';
                memory[p3][2] = acc/1000 +'0';
                memory[p3][3] = acc/100 - acc/1000 +'0';
                memory[p3][4] = acc/10 - acc/100 - acc/1000 +'0';
                memory[p3][5] = acc%10 +'0';
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 7:
            memory[two_int_first(memory[program_line])][0] = '9';
            memory[two_int_first(memory[program_line])][1] = '9';
            memory[two_int_first(memory[program_line])][2] = acc/1000 +'0';
            memory[two_int_first(memory[program_line])][3] = acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line])][4] = acc/10 - acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line])][5] = acc%10 +'0';

            break;
        case 8:
            if(strcmp(two_char_second(memory[program_line]), "P0")== 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    *memory[p0] = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    *memory[p0] = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    *memory[p0] = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    *memory[p0] = r3;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P1") == 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    *memory[p1] = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    *memory[p1] = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    *memory[p1] = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    *memory[p1] = r3;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P2") == 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    *memory[p2] = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    *memory[p2] = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    *memory[p2] = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    *memory[p2] = r3;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P3") == 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    *memory[p3] = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    *memory[p3] = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    *memory[p3] = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    *memory[p3] = r3;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 9:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                *memory[two_int_second(memory[program_line])] = r0;
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                *memory[two_int_second(memory[program_line])] = r1;
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                *memory[two_int_second(memory[program_line])] = r2;
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                *memory[two_int_second(memory[program_line])] = r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 10:
            if(strcmp(two_char_second(memory[program_line]), "P0") == 0){
                
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = (memory[p0][2]-'0') * 1000 + (memory[p0][3]-'0') * 100 +(memory[p0][4]-'0') * 10 + (memory[p0][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = (memory[p0][2]-'0') * 1000 + (memory[p0][3]-'0') * 100 +(memory[p0][4]-'0') * 10 + (memory[p0][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = (memory[p0][2]-'0') * 1000 + (memory[p0][3]-'0') * 100 +(memory[p0][4]-'0') * 10 + (memory[p0][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    printf("%d\n", r3);
                    printf("%s\n", memory[p0]);
                    r3 = (memory[p0][2]-'0') * 1000 + (memory[p0][3]-'0') * 100 +(memory[p0][4]-'0') * 10 + (memory[p0][5]-'0');
                    printf("%d\n", r3);
                    printf("%d\n", p0);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
                printf("%d\n", r3);
            }else if(strcmp(two_char_second(memory[program_line]), "P1") == 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = (memory[p1][0] -'0')* 100000 + (memory[p1][1]-'0')* 10000 +(memory[p1][2]-'0') * 1000 + (memory[p1][3]-'0') * 100 +(memory[p1][4]-'0') * 10 + (memory[p1][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = (memory[p1][0] -'0')* 100000 + (memory[p1][1]-'0')* 10000 +(memory[p1][2]-'0') * 1000 + (memory[p1][3]-'0') * 100 +(memory[p1][4]-'0') * 10 + (memory[p1][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = (memory[p1][0] -'0')* 100000 + (memory[p1][1]-'0')* 10000 +(memory[p1][2]-'0') * 1000 + (memory[p1][3]-'0') * 100 +(memory[p1][4]-'0') * 10 + (memory[p1][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = (memory[p1][0] -'0')* 100000 + (memory[p1][1]-'0')* 10000 +(memory[p1][2]-'0') * 1000 + (memory[p1][3]-'0') * 100 +(memory[p1][4]-'0') * 10 + (memory[p1][5]-'0');
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P2")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = (memory[p2][0] -'0')* 100000 + (memory[p2][1]-'0')* 10000 +(memory[p2][2]-'0') * 1000 + (memory[p2][3]-'0') * 100 +(memory[p2][4]-'0') * 10 + (memory[p2][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = (memory[p2][0] -'0')* 100000 + (memory[p2][1]-'0')* 10000 +(memory[p2][2]-'0') * 1000 + (memory[p2][3]-'0') * 100 +(memory[p2][4]-'0') * 10 + (memory[p2][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = (memory[p2][0] -'0')* 100000 + (memory[p2][1]-'0')* 10000 +(memory[p2][2]-'0') * 1000 + (memory[p2][3]-'0') * 100 +(memory[p2][4]-'0') * 10 + (memory[p2][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = (memory[p2][0] -'0')* 100000 + (memory[p2][1]-'0')* 10000 +(memory[p2][2]-'0') * 1000 + (memory[p2][3]-'0') * 100 +(memory[p2][4]-'0') * 10 + (memory[p2][5]-'0');
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P3")==0){
                
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = (memory[p3][0] -'0')* 100000 + (memory[p3][1]-'0')* 10000 +(memory[p3][2]-'0') * 1000 + (memory[p3][3]-'0') * 100 +(memory[p3][4]-'0') * 10 + (memory[p3][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = (memory[p3][0] -'0')* 100000 + (memory[p3][1]-'0')* 10000 +(memory[p3][2]-'0') * 1000 + (memory[p3][3]-'0') * 100 +(memory[p3][4]-'0') * 10 + (memory[p3][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = (memory[p3][0] -'0')* 100000 + (memory[p3][1]-'0')* 10000 +(memory[p3][2]-'0') * 1000 + (memory[p3][3]-'0') * 100 +(memory[p3][4]-'0') * 10 + (memory[p3][5]-'0');
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = (memory[p3][0] -'0')* 100000 + (memory[p3][1]-'0')* 10000 +(memory[p3][2]-'0') * 1000 + (memory[p3][3]-'0') * 100 +(memory[p3][4]-'0') * 10 + (memory[p3][5]-'0');
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 11:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                r0 = (memory[two_int_second(memory[program_line])][0] -'0')* 100000 + (memory[two_int_second(memory[program_line])][1] -'0')* 10000 +(memory[two_int_second(memory[program_line])][2] -'0') * 1000 + (memory[two_int_second(memory[program_line])][3] -'0') * 100 +(memory[two_int_second(memory[program_line])][4] -'0') * 10 + (memory[two_int_second(memory[program_line])][5] -'0');
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                r1 = (memory[two_int_second(memory[program_line])][0] -'0')* 100000 + (memory[two_int_second(memory[program_line])][1] -'0')* 10000 +(memory[two_int_second(memory[program_line])][2] -'0') * 1000 + (memory[two_int_second(memory[program_line])][3] -'0') * 100 +(memory[two_int_second(memory[program_line])][4] -'0') * 10 + (memory[two_int_second(memory[program_line])][5] -'0');
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                r2 = (memory[two_int_second(memory[program_line])][0] -'0')* 100000 + (memory[two_int_second(memory[program_line])][1] -'0')* 10000 +(memory[two_int_second(memory[program_line])][2] -'0') * 1000 + (memory[two_int_second(memory[program_line])][3] -'0') * 100 +(memory[two_int_second(memory[program_line])][4] -'0') * 10 + (memory[two_int_second(memory[program_line])][5] -'0');
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                r3 = (memory[two_int_second(memory[program_line])][0] -'0')* 100000 + (memory[two_int_second(memory[program_line])][1] -'0')* 10000 +(memory[two_int_second(memory[program_line])][2] -'0') * 1000 + (memory[two_int_second(memory[program_line])][3] -'0') * 100 +(memory[two_int_second(memory[program_line])][4] -'0') * 10 + (memory[two_int_second(memory[program_line])][5] -'0');
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 12:
            r0 = four_int(memory[program_line]);
            break;
        case 13:
            if(strcmp(two_char_second(memory[program_line]), "R0")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = memory[r0][0]* 100000 + memory[r0][1]* 10000 +memory[r0][2] * 1000 + memory[r0][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = memory[r1][0]* 100000 + memory[r1][1]* 10000 +memory[r1][2] * 1000 + memory[r1][3] * 100 +memory[r1][4] * 10 + memory[r1][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = memory[r2][0]* 100000 + memory[r2][1]* 10000 +memory[r2][2] * 1000 + memory[r2][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = memory[r3][0]* 100000 + memory[r3][1]* 10000 +memory[r3][2] * 1000 + memory[r3][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R1")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = memory[r0][0]* 100000 + memory[r0][1]* 10000 +memory[r0][2] * 1000 + memory[r0][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = memory[r1][0]* 100000 + memory[r1][1]* 10000 +memory[r1][2] * 1000 + memory[r1][3] * 100 +memory[r1][4] * 10 + memory[r1][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = memory[r2][0]* 100000 + memory[r2][1]* 10000 +memory[r2][2] * 1000 + memory[r2][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = memory[r3][0]* 100000 + memory[r3][1]* 10000 +memory[r3][2] * 1000 + memory[r3][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R2")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = memory[r0][0]* 100000 + memory[r0][1]* 10000 +memory[r0][2] * 1000 + memory[r0][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = memory[r1][0]* 100000 + memory[r1][1]* 10000 +memory[r1][2] * 1000 + memory[r1][3] * 100 +memory[r1][4] * 10 + memory[r1][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = memory[r2][0]* 100000 + memory[r2][1]* 10000 +memory[r2][2] * 1000 + memory[r2][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = memory[r3][0]* 100000 + memory[r3][1]* 10000 +memory[r3][2] * 1000 + memory[r3][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R3")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = memory[r0][0]* 100000 + memory[r0][1]* 10000 +memory[r0][2] * 1000 + memory[r0][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = memory[r1][0]* 100000 + memory[r1][1]* 10000 +memory[r1][2] * 1000 + memory[r1][3] * 100 +memory[r1][4] * 10 + memory[r1][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = memory[r2][0]* 100000 + memory[r2][1]* 10000 +memory[r2][2] * 1000 + memory[r2][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = memory[r3][0]* 100000 + memory[r3][1]* 10000 +memory[r3][2] * 1000 + memory[r3][3] * 100 +memory[r0][4] * 10 + memory[r0][5];
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 14:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                acc = r0;
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                acc = r1;
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                acc = r2;
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                acc = r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 15:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                r0 = acc;
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                r1 = acc;
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                r2 = acc;
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                r3 = acc;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            break;
        case 16:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 17:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 18:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 19:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 20:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 21:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 22:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 23:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 24:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 25:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 26:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 27:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 28:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 29:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 30:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 31:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 32:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 33:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 34:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 35:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 50:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        case 99:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        default:
            printf("Unknown Opcode");
            break;
    }
    return 1;
}