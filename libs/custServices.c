#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "custServices.h"

member memberList[100];

void initMembership() {
    char* buff = calloc(255, sizeof(char));
    FILE* mbr = fopen(memberFile, "r+");
    int ctr = -1;

    while (fgets(buff, 255, mbr)) {
        addMember(buff);
    }
}

void manageMembership() {
    char* name = calloc(255, sizeof(char));
    int opt = -1;
    printf("Enter Your Name: ");
    fflush(stdin);
    gets(name);

    while (opt != 4) {
        int hashVal = isMember(name);
        printf("Membership Counter=--\n");
        printf("[1] Check Status\n");
        printf("[2] Top Up\n");
        printf("[3] Register as Member\n");
        printf("[4] Revoke Membership\n");
        printf("[5] Back\n");
        printf("Enter your choices: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                if (hashVal == -1) printf("Please Sign Up As Our Member Now!\n");
                else {
                    memberStatus(name);
                }
                break;
            case 2:
                if (hashVal == -1) printf("Please Sign Up As Our Member Now!\n");
                else {
                    printf("Enter the amount: ");
                    scanf("%d", &opt);
                    addPoint(name, opt);
                }
                break;
            case 3:
                registerMember(name);
                break;
            case 4:
                revokeMember(name);
                break;
            case 5:
                return;
            default:
                printf("Please enter the correct option!\n");
                break;
        }
        getch();
        system("cls");
        updateMembership();
    }
}

int payment(char* name, int amount) {
    int opt = 0;
    printf("Payment:\n");
    printf("[1] Cash: SCH %d\n", amount);
    printf("[2] Point: %d Points\n", amount/100);
    printf("How do you want to pay? ");
    scanf("%d", &opt);
    if (opt == 1) {
        printf("Enter the amount of cash: ");
        scanf("%d", &opt);
        if (opt > amount) {
            printf("Your Charges: %d\n", opt - amount);
            return 0;
        } else if (opt == amount) return 0;
        else return -1;
    } else {
        opt = usePoint(name, amount/100);
        if (opt == -1) {
            printf("Pembayaran gagal!\n");
            return -1;
        }
    }

}

int usePoint(char* name, int used) {
    int hashVal = isMember(name);
    if (hashVal == -1)  {
        printf("Not a member (yet)!\n");
        return -1;
    }
    else {
        int temp = memberList[hashVal]->points;
        if (temp - used <= 0) {
            printf("Not Enough Point!\n");
            return -1;
        }
        else memberList[hashVal]->points -= used;
    }
}

void addPoint(char* name, int added) {
    int hashVal = isMember(name);
    if (hashVal == -1) printf("Not a member (yet)!\n");
    else memberList[hashVal]->points += added;
}

static void registerMember(char* name) {
    char* data = calloc(255, sizeof(char));
    snprintf(data, 255, "%s#0", name);
    addMember(data);
    updateMembership();
    memberStatus(name);
    free(data);
}

static void revokeMember(char* name) {
    int hashVal = isMember(name);
    if (hashVal == -1) printf("Not a member!\n");
    else {
        memberList[hashVal] = NULL;
        updateMembership();
    }
}

static int isMember(char* name) {
    int hashVal = generateHash(name);
    return (memberList[hashVal]) != NULL ? hashVal : -1;
}

static void addMember(char* data) {
    member newMem = malloc(sizeof(struct member_t));
    char* temp = data;
    int hashVal = 0;
    newMem->name = strdup(strtok(data,"#"));
    hashVal = generateHash(newMem->name);
    newMem->points = atoi(strtok(NULL, "#"));
    if (!memberList[hashVal]) memberList[hashVal] = newMem;
}

static void memberStatus(char* name) {
    int hashVal = isMember(name);
    if (hashVal == -1) printf("Not a member (yet)!\n");
    printf("┬─ %s\n├ ID: %d\n└ Point: %d\n", 
            memberList[hashVal]->name,
            hashVal,
            memberList[hashVal]->points);
}

static void updateMembership() {
    FILE *mbr = fopen(memberFile, "w+");

    for (int i=0; i<100; i++) {
        if (!memberList[i]) continue;
        member temp = memberList[i];
        fprintf(mbr, "%s#%d\n", temp->name, temp->points);
    }
    fclose(mbr);
}

static int generateHash(char* name) {
    int val = 0;
    unsigned long ctr = 0;
    for (int i=0; i<strlen(name)-1; i++) {
        ctr += i+1 < 10 ? (int) name[i]*10 + 1+1 : (int)name[i]*100 + i+1;
    }
    ctr = (unsigned long)pow(ctr, 2);
    while(length(ctr) > 2) {
        val += ctr%10;
        ctr = ctr/10;
    }
    return val;
}

static unsigned length(const unsigned long num) {
    if (num < 10) return 1;
    return 1 + length(num/10);
}