//Alex Picard

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int opcode(char input_line[9]);
void instructions(char instruction[9]);
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
int temp;
int main(int argc, char* argv[]) {

  FILE *file = fopen(argv[1], "r");
  if(file == NULL){
    print("Cannot find file");
    exit(0);
  }
  while(fgets(input_line, 9, file)!= NULL){
    int i;
    for(i = 0; i < 6; i++){
        memory[program_line][i] = input_line[i];
    } 
    program_line++;
  }
  program_line = 0;

  while(1){
    instructions(memory[program_line]);
    if(opcode(memory[program_line]) == 99){
        break;
    }
  }

  printf("%d\n", four_int(memory[21]));

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

void instructions(char instruction[9]){
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
            program_line++;
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
            program_line++;
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
            program_line++;
            break;
        case 3:
            acc = four_int(memory[program_line]);
            program_line++;
            break;
        case 4:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                acc = four_int(memory[p0]);
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                acc = four_int(memory[p1]);
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                acc = four_int(memory[p2]);
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                acc = four_int(memory[p3]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 5:
            acc = memory[two_int_first(memory[program_line])][0]* 100000 + memory[two_int_first(memory[program_line])][1]* 10000 +memory[two_int_first(memory[program_line])][2] * 1000 + memory[two_int_first(memory[program_line])][3] * 100 +memory[two_int_first(memory[program_line])][4] * 10 + memory[two_int_first(memory[program_line])][5];
            program_line++;
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
            program_line++;
            break;
        case 7:
            memory[two_int_first(memory[program_line])][0] = '9';
            memory[two_int_first(memory[program_line])][1] = '9';
            memory[two_int_first(memory[program_line])][2] = acc/1000 +'0';
            memory[two_int_first(memory[program_line])][3] = acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line])][4] = acc/10 - acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line])][5] = acc%10 +'0';
            program_line++;
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
            program_line++;
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
            program_line++;
            break;
        case 10:
            if(strcmp(two_char_second(memory[program_line]), "P0") == 0){
                
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = four_int(memory[p0]);
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = four_int(memory[p0]);
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = four_int(memory[p0]);
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = four_int(memory[p0]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
                printf("%d\n", r3);
            }else if(strcmp(two_char_second(memory[program_line]), "P1") == 0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = four_int(memory[p1]);
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = four_int(memory[p1]);
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = four_int(memory[p1]);
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = four_int(memory[p1]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P2")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = four_int(memory[p2]);
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = four_int(memory[p2]);
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = four_int(memory[p2]);
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = four_int(memory[p2]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "P3")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = four_int(memory[p3]);
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = four_int(memory[p3]);
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = four_int(memory[p3]);
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = four_int(memory[p3]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 11:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                r0 = four_int(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                r1 = four_int(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                r2 = four_int(memory[program_line]);
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                r3 = four_int(memory[program_line]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 12:
            r0 = four_int(memory[program_line]);
            program_line++;
            break;
        case 13:
            if(strcmp(two_char_second(memory[program_line]), "R0")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = r0;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = r0;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R1")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = r1;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = r1;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R2")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = r2;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = r2;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line]), "R3")==0){
                if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                    r0 = r3;
                }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                    r1 = r3;
                }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                    r2 = r3;
                }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                    r3 = r3;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
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
            program_line++;
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
            program_line++;
            break;
        case 16:
            acc += four_int(instruction);
            program_line++;
            break;
        case 17:
            acc -= four_int(instruction);
            program_line++;
            break;
        case 18:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                acc += r0;
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                acc += r1;
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                acc += r2;
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                acc += r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 19:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                acc -= r0;
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                acc -= r1;
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                acc -= r2;
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                acc -= r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 20:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                acc += four_int(memory[p0]);
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                acc += four_int(memory[p1]);
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                acc += four_int(memory[p2]);
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                acc += four_int(memory[p3]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 21:
            temp = two_int_first(memory[program_line]);
            acc += (memory[temp][2]-'0') * 1000 + (memory[temp][3]-'0') * 100 +(memory[temp][4]-'0') * 10 + (memory[temp][5]-'0');
            program_line++;
            break;
        case 22:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                acc -= (memory[p0][2]-'0') * 1000 + (memory[p0][3]-'0') * 100 +(memory[p0][4]-'0') * 10 + (memory[p0][5]-'0');
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                acc -= (memory[p1][2]-'0') * 1000 + (memory[p1][3]-'0') * 100 +(memory[p1][4]-'0') * 10 + (memory[p1][5]-'0');
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                acc -= (memory[p2][2]-'0') * 1000 + (memory[p2][3]-'0') * 100 +(memory[p2][4]-'0') * 10 + (memory[p2][5]-'0');;
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                acc -= (memory[p3][2]-'0') * 1000 + (memory[p3][3]-'0') * 100 +(memory[p3][4]-'0') * 10 + (memory[p3][5]-'0');;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 23:
            temp = two_int_first(memory[program_line]);
            acc -= (memory[temp][2]-'0') * 1000 + (memory[temp][3]-'0') * 100 +(memory[temp][4]-'0') * 10 + (memory[temp][5]-'0');
            program_line++;
            break;
        case 24:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                if(acc == four_int(memory[p0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                if(acc == four_int(memory[p1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                if(acc == four_int(memory[p2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                if(acc == four_int(memory[p3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 25:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                if(acc < four_int(memory[p0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                if(acc < four_int(memory[p1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                if(acc < four_int(memory[p2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                if(acc < four_int(memory[p3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 26:
            if(strcmp(two_char_first(memory[program_line]), "P0") == 0){
                if(acc > four_int(memory[p0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P1") == 0){
                if(acc > four_int(memory[p1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P2") == 0){
                if(acc > four_int(memory[p2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "P3") == 0){
                if(acc > four_int(memory[p3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 27:
            if(acc > four_int(memory[program_line])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 28:
            if(acc == four_int(memory[program_line])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 29:
            if(acc < four_int(memory[program_line])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 30:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                if(acc == four_int(memory[r0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                if(acc == four_int(memory[r1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                if(acc == four_int(memory[r2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                if(acc == four_int(memory[r3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 31:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                if(acc < four_int(memory[r0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                if(acc < four_int(memory[r1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                if(acc < four_int(memory[r2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                if(acc < four_int(memory[r3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 32:
            if(strcmp(two_char_first(memory[program_line]), "R0") == 0){
                if(acc > four_int(memory[r0])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R1") == 0){
                if(acc > four_int(memory[r1])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R2") == 0){
                if(acc > four_int(memory[r2])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line]), "R3") == 0){
                if(acc > four_int(memory[r3])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 33:
            if(psw[0] == 'T'){
                program_line = two_int_first(memory[program_line]);
            }else{
                program_line++;
            }
            break;
        case 34:
            if(psw[0] == 'F'){
                program_line = two_int_first(memory[program_line]);
            }else{
                program_line++;
            }
            break;
        case 35:
            program_line = two_int_first(memory[program_line]);
            break;
        case 99:
            printf("Opcode: %d\n", opcode(memory[program_line]));
            break;
        default:
            printf("Unknown Opcode");
            break;
    }
}

