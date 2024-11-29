//Alex Picard

//Currently up to the point of having it switch between them and not writing directly to the structs
//Need to figure out how to save in the different locations and how to save into the pcb not directly from the instructions
//Untested but am using the sp to change where it is looking into memory wherever the program line isn't
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define Partition1 100
struct PCB{
    struct PCB *Next_PCB;
    struct PCB *Prev_PCB;
    int r0, r1, r2, r3;
    short int p0, p1, p2, p3;
    int PID;
    char psw[2];
    char ir[9];
    int BaseReg, LimitReg;
    int acc;
    int context_switch;
    int program_line;

};
struct PCB *Next_PCB;
int r0, r1, r2, r3;
short int p0, p1, p2, p3;
int PID;
char psw[2];
char ir[6];
int opcode(char input_line[6]);
void instructions(char instruction[6]);
char* two_char_first(char input_line[6]);
char* two_char_second(char input_line[6]);
int two_int_first(char input_line[6]);
int two_int_second(char input_line[6]);
int four_int(char input_line[6]);
void save_program(struct PCB *program);
char output[2];
char input_line[9];
int fp, ret;
short int pc = 0;
short int sp = 0; //change to where the memory would actually start
int acc;
char memory[1000][7];// Need to have 7 to compensate for the '\0'
int program_line = 0;
int temp;
int BaseReg, LimitReg;
int main(int argc, char* argv[]) {
    struct PCB *Program1 = (struct PCB*) malloc (sizeof(struct PCB));
    struct PCB *Program2 = (struct PCB*) malloc (sizeof(struct PCB));
    
    Program1 -> PID = 0;
    Program1 -> BaseReg = 0;
    Program1 -> LimitReg = 99;
    Program1 -> Next_PCB = Program2;
    Program1 -> Prev_PCB = NULL;
    Program1->program_line = 0;
    Program1 -> context_switch = 5;
    Program2 -> PID = 1;
    Program2 -> BaseReg = 100;
    Program2 -> LimitReg = 199;
    Program2 -> Next_PCB = NULL;
    Program2 -> Prev_PCB = Program1;
    Program2 -> context_switch = 5;
    Program2->program_line = 0;
    int i;
    struct PCB *tmp = Program1;
    for(i = 1; i < argc; i++){
        FILE *file = fopen(argv[i], "r");
        if(file == NULL){
            printf("Cannot find file");
            exit(0);
        }
        while(fgets(input_line, 9, file)!= NULL){
            int j;
            for(j = 0; j < 6; j++){
                memory[program_line][j] = input_line[j];
            }
            memory[program_line][6] = '\0';
            program_line++;
        }
        if(tmp -> Next_PCB == NULL){
            break;
        }
        tmp = tmp -> Next_PCB;
        program_line = tmp -> BaseReg;
    }
    
    tmp = Program1;
    program_line = 0;
    pc = 0;
    while(1){
        while(1){
            instructions(memory[program_line + sp]);
            printf("%s\n",memory[program_line + sp]);
            if(opcode(memory[program_line+sp]) == 99){
                if(sp == 0){
                    save_program(Program1);
                }else if(sp == 100){
                        save_program(Program2);
                }
                break;
            }
        }
        if(tmp->Next_PCB == NULL){
            break;
        }
        tmp = tmp->Next_PCB;
        program_line = 0;
        sp = tmp->BaseReg;
    }
    printf("%s\n", memory[73]);
    printf("%d\n", Program2->acc);
    return 0;
}
void save_program(struct PCB *program){ 
    
    program->r0 = r0;
    program->r1 = r1;
    program->r2 = r2;
    program->r3 = r3;

    program->p0 = p0;
    program->p1 = p1;
    program->p2 = p2;
    program->p3 = p3;

    strncpy(program->psw, psw, strlen(psw));
    program->acc = acc;

    program->program_line = program_line;
    
}
int opcode(char input_line[6]){
    return (input_line[0] - '0')*10 + (input_line[1] - '0');
}

char* two_char_first(char input_line[6]){
    output[0] = input_line[2];
    output[1] = input_line[3];
    return output;
}
char* two_char_second(char input_line[6]){
    output[0] = input_line[4];
    output[1] = input_line[5];
    return output;
}
int two_int_first(char input_line[6]){
    return (input_line[2] - '0')*10 + (input_line[3] - '0');
}
int two_int_second(char input_line[6]){
    return (input_line[4] - '0')*10 + (input_line[5] - '0');
}

int four_int(char input_line[6]){
    int output = (input_line[2] - '0')*1000 + (input_line[3] - '0')*100+(input_line[4] - '0')*10 + (input_line[5] - '0');
    return output;
}


void instructions(char instruction[6]){
    switch(opcode(memory[program_line + sp])){
        case 0:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                p0 = two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                p1 = two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                p2 = two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                p3 = two_int_second(memory[program_line+sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 1:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                p0 += two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                p1 += two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                p2 += two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                p3 += two_int_second(memory[program_line+sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 2:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                p0 -= two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                p1 -= two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                p2 -= two_int_second(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                p3 -= two_int_second(memory[program_line+sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 3:
            acc = four_int(memory[program_line+sp]);
            program_line++;
            break;
        case 4:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                acc = four_int(memory[p0 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                acc = four_int(memory[p1 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                acc = four_int(memory[p2 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                acc = four_int(memory[p3 + sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 5:
            acc = memory[two_int_first(memory[program_line+sp])+sp][0]* 100000 + memory[two_int_first(memory[program_line+sp])+sp][1]* 10000 +memory[two_int_first(memory[program_line+sp])+sp][2] * 1000 + memory[two_int_first(memory[program_line+sp])+sp][3] * 100 +memory[two_int_first(memory[program_line+sp])+sp][4] * 10 + memory[two_int_first(memory[program_line+sp])+sp][5];
            program_line++;
            break;
        case 6:
            
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                memory[p0 + sp][0] = '9';
                memory[p0 + sp][1] = '9';
                memory[p0 + sp][2] = (acc / 1000) % 10 + '0';
                memory[p0 + sp][3] = (acc / 100) % 10 + '0';
                memory[p0 + sp][4] = (acc / 10) % 10 + '0';
                memory[p0 + sp][5] = acc % 10 + '0';
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                memory[p1 + sp][0] = '9';
                memory[p1 + sp][1] = '9';
                memory[p1 + sp][2] = (acc / 1000) % 10 + '0';
                memory[p1 + sp][3] = (acc / 100) % 10 + '0';
                memory[p1 + sp][4] = (acc / 10) % 10 + '0';
                memory[p1 + sp][5] = acc % 10 + '0';
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                memory[p2 + sp][0] = '9';
                memory[p2 + sp][1] = '9';
                memory[p2 + sp][2] = (acc / 1000) % 10 + '0';
                memory[p2 + sp][3] = (acc / 100) % 10 + '0';
                memory[p2 + sp][4] = (acc / 10) % 10 + '0';
                memory[p2 + sp][5] = acc % 10 + '0';
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                memory[p3 + sp][0] = '9';
                memory[p3 + sp][1] = '9';
                memory[p3 + sp][2] = (acc / 1000) % 10 + '0';
                memory[p3 + sp][3] = (acc / 100) % 10 + '0';
                memory[p3 + sp][4] = (acc / 10) % 10 + '0';
                memory[p3 + sp][5] = acc % 10 + '0';
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 7:
            memory[two_int_first(memory[program_line+sp])+sp][0] = '9';
            memory[two_int_first(memory[program_line+sp])+sp][1] = '9';
            memory[two_int_first(memory[program_line+sp])+sp][2] = acc/1000 +'0';
            memory[two_int_first(memory[program_line+sp])+sp][3] = acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line+sp])+sp][4] = acc/10 - acc/100 - acc/1000 +'0';
            memory[two_int_first(memory[program_line+sp])+sp][5] = acc%10 +'0';
            program_line++;
            break;
        case 8:
            if(strcmp(two_char_second(memory[program_line+sp]), "P0")== 0){
                if (strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    memory[p0 + sp][0] = '9';
                    memory[p0 + sp][1] = '9';
                    memory[p0 + sp][2] = (r0 / 1000) % 10 + '0';
                    memory[p0 + sp][3] = (r0 / 100) % 10 + '0';
                    memory[p0 + sp][4] = (r0 / 10) % 10 + '0';
                    memory[p0 + sp][5] = r0 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    memory[p0 + sp][0] = '9';
                    memory[p0 + sp][1] = '9';
                    memory[p0 + sp][2] = (r1 / 1000) % 10 + '0';
                    memory[p0 + sp][3] = (r1 / 100) % 10 + '0';
                    memory[p0 + sp][4] = (r1 / 10) % 10 + '0';
                    memory[p0 + sp][5] = r1 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    memory[p0 + sp][0] = '9';
                    memory[p0 + sp][1] = '9';
                    memory[p0 + sp][2] = (r2 / 1000) % 10 + '0';
                    memory[p0 + sp][3] = (r2 / 100) % 10 + '0';
                    memory[p0 + sp][4] = (r2 / 10) % 10 + '0';
                    memory[p0 + sp][5] = r2 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    memory[p0 + sp][0] = '9';
                    memory[p0 + sp][1] = '9';
                    memory[p0 + sp][2] = (r3 / 1000) % 10 + '0';
                    memory[p0 + sp][3] = (r3 / 100) % 10 + '0';
                    memory[p0 + sp][4] = (r3 / 10) % 10 + '0';
                    memory[p0 + sp][5] = r3 % 10 + '0';
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P1") == 0){
                if (strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    memory[p1 + sp][0] = '9';
                    memory[p1 + sp][1] = '9';
                    memory[p1 + sp][2] = (r0 / 1000) % 10 + '0';
                    memory[p1 + sp][3] = (r0 / 100) % 10 + '0';
                    memory[p1 + sp][4] = (r0 / 10) % 10 + '0';
                    memory[p1 + sp][5] = r0 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    memory[p1 + sp][0] = '9';
                    memory[p1 + sp][1] = '9';
                    memory[p1 + sp][2] = (r1 / 1000) % 10 + '0';
                    memory[p1 + sp][3] = (r1 / 100) % 10 + '0';
                    memory[p1 + sp][4] = (r1 / 10) % 10 + '0';
                    memory[p1 + sp][5] = r1 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    memory[p1 + sp][0] = '9';
                    memory[p1 + sp][1] = '9';
                    memory[p1 + sp][2] = (r2 / 1000) % 10 + '0';
                    memory[p1 + sp][3] = (r2 / 100) % 10 + '0';
                    memory[p1 + sp][4] = (r2 / 10) % 10 + '0';
                    memory[p1 + sp][5] = r2 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    memory[p1 + sp][0] = '9';
                    memory[p1 + sp][1] = '9';
                    memory[p1 + sp][2] = (r3 / 1000) % 10 + '0';
                    memory[p1 + sp][3] = (r3 / 100) % 10 + '0';
                    memory[p1 + sp][4] = (r3 / 10) % 10 + '0';
                    memory[p1 + sp][5] = r3 % 10 + '0';
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P2") == 0){
                if (strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    memory[p2 + sp][0] = '9';
                    memory[p2 + sp][1] = '9';
                    memory[p2 + sp][2] = (r0 / 1000) % 10 + '0';
                    memory[p2 + sp][3] = (r0 / 100) % 10 + '0';
                    memory[p2 + sp][4] = (r0 / 10) % 10 + '0';
                    memory[p2 + sp][5] = r0 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    memory[p2 + sp][0] = '9';
                    memory[p2 + sp][1] = '9';
                    memory[p2 + sp][2] = (r1 / 1000) % 10 + '0';
                    memory[p2 + sp][3] = (r1 / 100) % 10 + '0';
                    memory[p2 + sp][4] = (r1 / 10) % 10 + '0';
                    memory[p2 + sp][5] = r1 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    memory[p2 + sp][0] = '9';
                    memory[p2 + sp][1] = '9';
                    memory[p2 + sp][2] = (r2 / 1000) % 10 + '0';
                    memory[p2 + sp][3] = (r2 / 100) % 10 + '0';
                    memory[p2 + sp][4] = (r2 / 10) % 10 + '0';
                    memory[p2 + sp][5] = r2 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    memory[p2 + sp][0] = '9';
                    memory[p2 + sp][1] = '9';
                    memory[p2 + sp][2] = (r3 / 1000) % 10 + '0';
                    memory[p2 + sp][3] = (r3 / 100) % 10 + '0';
                    memory[p2 + sp][4] = (r3 / 10) % 10 + '0';
                    memory[p2 + sp][5] = r3 % 10 + '0';
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P3") == 0){
                if (strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    memory[p3 + sp][0] = '9';
                    memory[p3 + sp][1] = '9';
                    memory[p3 + sp][2] = (r0 / 1000) % 10 + '0';
                    memory[p3 + sp][3] = (r0 / 100) % 10 + '0';
                    memory[p3 + sp][4] = (r0 / 10) % 10 + '0';
                    memory[p3 + sp][5] = r0 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    memory[p3 + sp][0] = '9';
                    memory[p3 + sp][1] = '9';
                    memory[p3 + sp][2] = (r1 / 1000) % 10 + '0';
                    memory[p3 + sp][3] = (r1 / 100) % 10 + '0';
                    memory[p3 + sp][4] = (r1 / 10) % 10 + '0';
                    memory[p3 + sp][5] = r1 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    memory[p3 + sp][0] = '9';
                    memory[p3 + sp][1] = '9';
                    memory[p3 + sp][2] = (r2 / 1000) % 10 + '0';
                    memory[p3 + sp][3] = (r2 / 100) % 10 + '0';
                    memory[p3 + sp][4] = (r2 / 10) % 10 + '0';
                    memory[p3 + sp][5] = r2 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    memory[p3 + sp][0] = '9';
                    memory[p3 + sp][1] = '9';
                    memory[p3 + sp][2] = (r3 / 1000) % 10 + '0';
                    memory[p3 + sp][3] = (r3 / 100) % 10 + '0';
                    memory[p3 + sp][4] = (r3 / 10) % 10 + '0';
                    memory[p3 + sp][5] = r3 % 10 + '0';
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    memory[two_int_second(memory[program_line+sp])+sp][0] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][1] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][2] = (r0 / 1000) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][3] = (r0 / 100) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][4] = (r0 / 10) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][5] = r0 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    memory[two_int_second(memory[program_line+sp])+sp][0] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][1] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][2] = (r1 / 1000) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][3] = (r1 / 100) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][4] = (r1 / 10) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][5] = r1 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    memory[two_int_second(memory[program_line+sp])+sp][0] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][1] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][2] = (r2 / 1000) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][3] = (r2 / 100) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][4] = (r2 / 10) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][5] = r2 % 10 + '0';
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    memory[two_int_second(memory[program_line+sp])+sp][0] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][1] = '9';
                    memory[two_int_second(memory[program_line+sp])+sp][2] = (r3 / 1000) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][3] = (r3 / 100) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][4] = (r3 / 10) % 10 + '0';
                    memory[two_int_second(memory[program_line+sp])+sp][5] = r3 % 10 + '0';
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            program_line++;
            break;
        case 10:
            if(strcmp(two_char_second(memory[program_line+sp]), "P0") == 0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = four_int(memory[p0 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = four_int(memory[p0 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = four_int(memory[p0 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = four_int(memory[p0 + sp]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P1") == 0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = four_int(memory[p1 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = four_int(memory[p1 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = four_int(memory[p1 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = four_int(memory[p1 + sp]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P2")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = four_int(memory[p2 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = four_int(memory[p2 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = four_int(memory[p2 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = four_int(memory[p2 + sp]);
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "P3")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = four_int(memory[p3 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = four_int(memory[p3 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = four_int(memory[p3 + sp]);
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = four_int(memory[p3 + sp]);
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                r0 = four_int(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                r1 = four_int(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                r2 = four_int(memory[program_line+sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                r3 = four_int(memory[program_line+sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 12:
            r0 = four_int(memory[program_line+sp]);
            program_line++;
            break;
        case 13:
            if(strcmp(two_char_second(memory[program_line+sp]), "R0")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = r0;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = r0;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = r0;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = r0;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "R1")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = r1;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = r1;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = r1;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = r1;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "R2")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = r2;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = r2;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = r2;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                    r3 = r2;
                }else{
                    printf("Invalid Storage Location");
                    exit(0);
                }
            }else if(strcmp(two_char_second(memory[program_line+sp]), "R3")==0){
                if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                    r0 = r3;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                    r1 = r3;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                    r2 = r3;
                }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                acc = r0;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                acc = r1;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                acc = r2;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                acc = r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 15:
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                r0 = acc;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                r1 = acc;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                r2 = acc;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                acc += r0;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                acc += r1;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                acc += r2;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                acc += r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 19:
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                acc -= r0;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                acc -= r1;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                acc -= r2;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                acc -= r3;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 20:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                acc += four_int(memory[p0 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                acc += four_int(memory[p1 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                acc += four_int(memory[p2 + sp]);
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                acc += four_int(memory[p3 + sp]);
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 21:
            temp = two_int_first(memory[program_line+sp]);
            acc += (memory[temp + sp][2]-'0') * 1000 + (memory[temp + sp][3]-'0') * 100 +(memory[temp + sp][4]-'0') * 10 + (memory[temp + sp][5]-'0');
            program_line++;
            break;
        case 22:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                acc -= (memory[p0 + sp][2]-'0') * 1000 + (memory[p0 + sp][3]-'0') * 100 +(memory[p0+sp][4]-'0') * 10 + (memory[p0 + sp][5]-'0');
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                acc -= (memory[p1 + sp][2]-'0') * 1000 + (memory[p1 + sp][3]-'0') * 100 +(memory[p1+sp][4]-'0') * 10 + (memory[p1 + sp][5]-'0');
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                acc -= (memory[p2 + sp][2]-'0') * 1000 + (memory[p2 + sp][3]-'0') * 100 +(memory[p2+sp][4]-'0') * 10 + (memory[p2 + sp][5]-'0');;
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                acc -= (memory[p3 + sp][2]-'0') * 1000 + (memory[p3 + sp][3]-'0') * 100 +(memory[p3+sp][4]-'0') * 10 + (memory[p3 + sp][5]-'0');;
            }else{
                printf("Invalid Storage Location");
                exit(0);
            }
            program_line++;
            break;
        case 23:
            temp = two_int_first(memory[program_line+sp]);
            acc -= (memory[temp + sp][2]-'0') * 1000 + (memory[temp + sp][3]-'0') * 100 +(memory[temp + sp][4]-'0') * 10 + (memory[temp + sp][5]-'0');
            program_line++;
            break;
        case 24:
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                if(acc == four_int(memory[p0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                if(acc == four_int(memory[p1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                if(acc == four_int(memory[p2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                if(acc == four_int(memory[p3 + sp])){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                if(acc < four_int(memory[p0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                if(acc < four_int(memory[p1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                if(acc < four_int(memory[p2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                if(acc < four_int(memory[p3 + sp])){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "P0") == 0){
                if(acc > four_int(memory[p0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P1") == 0){
                if(acc > four_int(memory[p1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P2") == 0){
                if(acc > four_int(memory[p2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "P3") == 0){
                if(acc > four_int(memory[p3 + sp])){
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
            if(acc > four_int(memory[program_line+sp])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 28:
            if(acc == four_int(memory[program_line+sp])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 29:
            if(acc < four_int(memory[program_line+sp])){
                psw[0] = 'T';
            }else{
                psw[0] = 'F';
            }
            program_line++;
            break;
        case 30:
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                if(acc == four_int(memory[r0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                if(acc == four_int(memory[r1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                if(acc == four_int(memory[r2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                if(acc == four_int(memory[r3 + sp])){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                if(acc < four_int(memory[r0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                if(acc < four_int(memory[r1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                if(acc < four_int(memory[r2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                if(acc < four_int(memory[r3 + sp])){
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
            if(strcmp(two_char_first(memory[program_line+sp]), "R0") == 0){
                if(acc > four_int(memory[r0 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R1") == 0){
                if(acc > four_int(memory[r1 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R2") == 0){
                if(acc > four_int(memory[r2 + sp])){
                    psw[0] = 'T';
                }else{
                    psw[0] = 'F';
                }
            }else if(strcmp(two_char_first(memory[program_line+sp]), "R3") == 0){
                if(acc > four_int(memory[r3 + sp])){
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
                program_line = two_int_first(memory[program_line+sp]);
            }else{
                program_line++;
            }
            break;
        case 34:
            if(psw[0] == 'F'){
                program_line = two_int_first(memory[program_line+sp]);
            }else{
                program_line++;
            }
            break;
        case 35:
            program_line = two_int_first(memory[program_line+sp]);
            break;
        case 99:
            printf("Opcode: %d\n", opcode(memory[program_line+sp]));
            break;
        default:
            printf("Unknown Opcode");
            break;
    }
}

