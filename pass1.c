#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passOne() {
    int locctr, start, length;
    char label[20], opcode[20], operand[20];
    char mnemonic[10], code[10];
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;


    fp1 = fopen("input.txt", "r");         
    fp2 = fopen("optab.txt", "r");         
    fp3 = fopen("symtab.txt", "w");        
    fp4 = fopen("intermediate.txt", "w");  
    fp5 = fopen("length.txt", "w");       

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL) {
        printf("Error: Couldn't open one or more files.\n");
        return;
    }

    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }

        // Reset optab file to beginning
        fseek(fp2, 0, SEEK_SET);
        int found = 0;
        while (fscanf(fp2, "%s %s", mnemonic, code) == 2) {
            if (strcmp(opcode, mnemonic) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += strlen(operand) - 3; // C'EOF' -> 3 bytes
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2; // X'F1' -> 1 byte
                }
            } else if (strcmp(opcode, "END") != 0) {
                printf("Warning: Opcode not found - %s\n", opcode);
            }
        }


        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }


    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;
    fprintf(fp5, "%d", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    printf("\nThe length of the code: %d\n", length);
}

int main() {
    passOne();
    return 0;
}