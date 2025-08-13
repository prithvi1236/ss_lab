#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passOne(void){
    int locctr, start, length;
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("length.txt", "w");
    
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL) {
        printf("Error: Could not open one or more files.\n");
        return;
    }
    
    fscanf(fp1, "%s %s %s", label, opcode, operand);
    
    if (strcmp(opcode, "START") == 0){
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0){
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        
        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }
        
        fseek(fp2, 0, SEEK_SET);
        fscanf(fp2, "%s %s", code, mnemonic);
        
        while (strcmp(code, "END") != 0){
            if (strcmp(opcode, code) == 0){
                locctr += 3;
                break;
            }
            fscanf(fp2, "%s %s", code, mnemonic);
        }

        // Handle directives
        if (strcmp(opcode, "WORD") == 0){
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0){
            locctr += (3 * (atoi(operand)));
        } else if (strcmp(opcode, "BYTE") == 0){
            locctr += (strlen(operand) - 3) / 2; 
        } else if (strcmp(opcode, "RESB") == 0){
            locctr += atoi(operand);
        }
        
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }
    
    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    length = locctr - start;
    fprintf(fp5, "%d", length);
    fclose(fp5);
    
    printf("\nThe length of the code: %d\n", length);
}

int main(){
    passOne();
    return 0;
}