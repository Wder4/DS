#include <stdio.h>
#include <stdlib.h>
#include "sstring.h"
#include "Stack_Arr.h"
#include "CQue_Arr.h"

int get_val(int loc, char *str) {
    int base = 1;
    int sum = 0;
    int len = strlen(str);
    for (int i = len - 1; i >= loc; --i) {
        int num = str[i] - '0';
        if (num >= 0 && num <= 9) {   // for stack
            sum += (str[i] - '0') * base;
            base *= 10;
        }
        else  // for queue
            return str[i];
    }
    return sum;
}

int main(int argc, char **argv) {

    char str[200][200] = {};  // input instruction
    // create stack, queue
    stack *sptr, st;
    sptr = &st;     sLib.Init(sptr);
    queue *qptr, q, *plqptr, plq;
    qptr = &q;      qLib.Init(qptr);
    plqptr = &plq;  qLib.Init(plqptr);

    FILE *fp = NULL, *ofp = NULL;
    fp = fopen(argv[1], "r");
    if (argv[2])
        ofp = fopen(argv[2], "w");
    else
        ofp = fopen("output.txt", "w");
    
    int i = 0;
    while (!feof(fp)) {
        if (fgets(str[i], 200, fp) == NULL)
            break;
        if (strstr(str[i], "^Z"))
           break;
        if (str[i][strlen(str[i]) - 1] == '\n')
            str[i][strlen(str[i]) - 1] = '\0';
        // puts(str[i]);
        stupr(str[i], strlen(str[i]));
        int loc = stloc(str[i], " ") + 1;

        if (strstr(str[i], "PUSH"))
            sLib.push(sptr, get_val(loc, str[i]));

        else if (strstr(str[i], "POP"))
            qLib.enque(plqptr, sLib.pop(sptr));

        else if (strstr(str[i], "ENQ"))
            qLib.enque(qptr, get_val(loc, str[i]));

        else if (strstr(str[i], "DEQ")){
            int customer =  qLib.deque(qptr);
            int plate =  qLib.deque(plqptr);
            printf("customer: %c, plate: %d\n", customer, plate);
            char *tmp = malloc(sizeof(char)*3);
            sprintf(tmp, "%d", plate);
            int slen = strlen(tmp);
            printf("%d\n", slen);
            char *out = malloc(sizeof(char) * (slen + 1));
            strcpy(out, tmp);
            out[slen] = '\n';
            fwrite(out, sizeof(char), slen + 1, ofp);
            free(tmp);
            free(out);
        }         
        ++i;
    }
    fclose(fp);
    fclose(ofp);

    return 0;
}