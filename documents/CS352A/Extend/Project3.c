#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROGRAMSIZE        30

typedef struct Instruction {
    int OpCode;
    int DeviceOrAddress;
} Instruction;

static Instruction IM[MAXPROGRAMSIZE];
static Instruction MDR1, IR;
static int Accu = 0;
static int PC = 3;
static int MAR1, MAR2;
static int MDR2;
static int DM[1000];

/* function to read instructions from input file */
int get_instructions(char *file_name)
{
    char str[20];
    int i = 0, instruction_count = 0;
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("error open file\n");
        return -1;
    }

    while(instruction_count < MAXPROGRAMSIZE)
    {
        str[i] = fgetc(file);
        i++;
        if (str[i-1] == ' ')
        {
            IM[instruction_count].OpCode = atoi(str);
            memset(str, 0, i);
            i = 0;
        }
        else if (str[i-1] == '\n')
        {
            IM[instruction_count].DeviceOrAddress = atoi(str);
            instruction_count++;
            memset(str, 0, i);
            i = 0;
        }
        else if (str[i-1] == EOF)
        {
            IM[instruction_count].DeviceOrAddress = atoi(str);
            break;
        }
    }
    fclose(file);
    return 0;
}


int main(int argc, char **argv)
{
    int i, OpCode, isStop = 0;
    char str[20];

    if (argc < 2)
    {
        printf("error: need input file name argument\n");
        return 0;
    }
    printf("Assembling Program…\nProgram Assembled.\nRun.\n");
    get_instructions(argv[1]);
    // for (i = 0; i < 20; i++)
    //     printf("%d %d\n", IM[i].OpCode, IM[i].DeviceOrAddress);

    OpCode = 0; // FETCH firstly
    while (!isStop)
    {
        /* code implements instructions from IM array */
        switch(OpCode)
        {
            case 0: // FETCH/EXECUTE
                MAR1 = PC;
                PC++;
                MDR1 = IM[MAR1];
                IR = MDR1;
                break;

            case 1: // LOAD
                MAR2 = IR.DeviceOrAddress;
                MDR2 = DM[MAR2];
                Accu = MDR2;
                break;

            case 2: // ADD
                MAR2 = IR.DeviceOrAddress;
                MDR2 = DM[MAR2];
                Accu = Accu + MDR2;
                break;

            case 3: // STORE
                MAR2 = IR.DeviceOrAddress;
                MDR2 = Accu;
                DM[MAR2] = MDR2;
                break;

            case 4: // SUB
                MAR2 = IR.DeviceOrAddress;
                MDR2 = DM[MAR2];
                Accu = Accu - MDR2;
                break;

            case 5: // IN
                printf("Read input from keyboard: ");
                scanf("%d",&Accu);
                break;

            case 6: // OUT
                if (Accu)
                    printf("PC = %3d A = %3d  MEM = [", PC, Accu);
                else
                    printf("PC = %3d A = NULL MEM = [", PC);
                for(i = 0; i < 20; i++)
                    printf("%d, ", DM[i]);
                printf("%d]\n", DM[i]);
                break;

            case 7: // END
                printf("Program complete.\n");
                isStop = 1;
                break;

            case 8: // JMP
                PC = IR.DeviceOrAddress;
                break;

            case 9: // SKIPZ
                if (Accu == 0)
                    PC++;
                break;

            default: //error
                printf("Instruction error\n");
                break;
        }

        /* get next OpCode */
        if (OpCode == 0) //FETCH
        {
            OpCode = MDR1.OpCode;
        }
        else
        {
            OpCode = 0;
        }
    }

    return 0;
}
