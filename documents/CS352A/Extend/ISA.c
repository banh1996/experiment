#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROGRAMSIZE        50
#define MAXMEMORYSIZE         30
#define MAXBUFLENGTH          30 

typedef struct Instruction_t {
    int OpCode;
    int DeviceOrAddress;
} Instruction_t;

typedef enum state_t {
    NOTHING = 0,
    RUNNING,
    PAUSE,
    END
} state_t;

Instruction_t IM[MAXPROGRAMSIZE];
Instruction_t IR;
int Accumulator = 0;
int InstNum = 0;
int PC = 0;
int MAR, MAR2;
int MDR, MDR2;
int DM[MAXMEMORYSIZE];

// funnction to read instructions from file
void read_input(char *file_name)
{
    char str[MAXBUFLENGTH], c, i = 0, ex[2] = " ", *token;
    size_t nread;
    FILE *file;
    file = fopen(file_name, "r");
    if (file)
    {
        while((c = fgetc(file)) != EOF && InstNum < MAXPROGRAMSIZE)
        {
            if (c == '\n')
            {
                token = strtok(str, ex);
                IM[InstNum].OpCode = atoi(token);
                token = strtok(NULL, ex);
                IM[InstNum].DeviceOrAddress = atoi(token);
                InstNum++;
                memset(str, 0, sizeof(str));
                i = 0;
            }
            else
            {
                str[i] = c;
                i++;
            }
        }
        fclose(file);
    }
    else
    {
        printf("error open file\n");
    }

    token = strtok(str, ex);
    IM[InstNum].OpCode = atoi(token);
    token = strtok(NULL, ex);
    IM[InstNum].DeviceOrAddress = atoi(token);
    InstNum++;
}

// function will implement instruction in IM array
// OpCode 0 to implement fetch/execute in cycle.
state_t ImplementInstruction(int OpCode)
{
    int i = 0;
    //printf("OpCode: %d\n", OpCode);
    switch(OpCode)
    {
        case 0: //FETCH
            MAR = PC;
            PC++;
            MDR = IM[MAR].OpCode;
            IR = IM[MAR];
            break;

        case 1: //LOAD
            MAR2 = IR.DeviceOrAddress;
            MDR2 = DM[MAR2];
            Accumulator = MDR2;
            break;

        case 2: //ADD
            MAR2 = IR.DeviceOrAddress;
            MDR2 = DM[MAR2];
            Accumulator = Accumulator + MDR2;
            break;

        case 3: //STORE
            MAR2 = IR.DeviceOrAddress;
            MDR2 = Accumulator;
            DM[MAR2] = MDR2;
            break;

        case 4: //SUB
            MAR2 = IR.DeviceOrAddress;
            MDR2 = DM[MAR2];
            Accumulator = Accumulator - MDR2;
            break;

        case 5: //IN
            //Accumulator = getchar();
            printf("Read input from keyboard: ");
            scanf("%d",&Accumulator);
            //printf("ss %d\n", Accumulator);
            //Accumulator = IR.DeviceOrAddress;
            break;

        case 6: //OUT
            printf("PC = %4d A = %4d \t MEM = [", PC, Accumulator);
            for(i = 0; i < InstNum; i++)
                printf("%d, ", DM[i]);
            printf("%d]\n", DM[i]);
            break;

        case 7: //END
            printf("Program complete.\n");
            return END;
            break;

        case 8: //JMP
            PC = IR.DeviceOrAddress;
            break;

        case 9: //SKIPZ
            if (Accumulator == 0)
                PC++;
            break;

        default: //error
            printf("Instruction error\n");
            break;
    }

    return RUNNING;
}

int main(int argc, char **argv)
{
    read_input("input.txt");
    while (ImplementInstruction(0)) //Fetch/Execute each cycle
    {
        if (ImplementInstruction(MDR) == END) //parse next instruction
            break;
    }

    return 0;
}
