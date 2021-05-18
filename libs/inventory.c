#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "inventory.h"

items Inventory[255];

void initStorage() {
    char* buff = calloc(255, sizeof(char));
    FILE* inv = fopen(invFile, "r+");
    while (fgets(buff, 255, inv)) addItem(buff); 
    fclose(inv);
}

void manageStorage() {
    unsigned qty = 0;
    int opt;
    char* name = calloc(255, sizeof(char));

    system("cls");
    printf("SchneeKatze's Shop Admin Panel\n");
    showList();
    printf("[1] Add Stocks\n");
    printf("[2] Remove Item\n");
    printf("[3] Sync Storage\n");
    printf("[4] Back\n");
    printf("> ");
    scanf("%d", &opt);

    switch (opt) {
        case 1:
            printf("Item Name: ");
            fflush(stdin);
            gets(name);
            printf("Price: ");
            scanf("%d", &opt);
            printf("Qty: ");
            scanf("%ju", &qty);
            appendItem(name, opt, qty);
            break;
        case 2:
            printf("Item name: ");
            fflush(stdin);
            gets(name);
            removeItem(name);
            break;
        case 3:
            updateStorage();
            break;
        case 4:
        default:
        break;
    }
}

void showCart(items* cart) {
    for (int i=0; i<50; i++) {
        if (cart[i]) printf("<%d> %s x%d\n", i, cart[i]->name, cart[i]->stocks);
    }
}

int showList() {
    int ctr = 0;
    for (int i=0; i<255; i++) {
        if (Inventory[i]) {
            getItemInfo(Inventory[i]->name);
            ctr++;
        }
    }
    return ctr == 0;
}

int checkout(items* cart) {
    unsigned bought = 0;
    
    printf("--==Shopping Cart==--");
    for (int i=0; i<50; i++) {
        if (cart[i]) {
            printf("%s x%d\n", cart[i]->name, cart[i]->stocks);
            bought += cart[i]->price * cart[i]->stocks;
        }
    }
    printf("Total: %ju\n", bought);
    return bought;
}

void removeItem(char* name) {
    int hashVal = generateHash(name);
    if (Inventory[hashVal]) Inventory[hashVal] = NULL;
    updateStorage();
}

void buyItem(items* cart, char* name, int sum) {
    int hashVal = generateHash(name);
    if (!Inventory[hashVal]) printf("Items not yet available!\n");
    else {
        if (Inventory[hashVal]->stocks <= sum) {
            printf("Hanya tersedia %d!\n", Inventory[hashVal]->stocks);
            sum = Inventory[hashVal]->stocks;
        }
        for (int i=0; i<50; i++) {
            if (cart[i]) {
                if (!strcmp(cart[i]->name, name)) {
                    cart[i]->stocks+=sum;
                }
                else continue;
                break;
            } else {
                cart[i] = malloc(sizeof(struct items_t));
                cart[i]->name = strdup(Inventory[hashVal]->name);
                cart[i]->price = Inventory[hashVal]->price;
                cart[i]->stocks = sum;
                break;
            }
        }
        Inventory[hashVal]->stocks -= (int)sum;
    }
}

void appendItem(char* name, int price, unsigned qty) {
    char* temp = strdup(name);
    char* data = calloc(255, sizeof(char));
    snprintf(data, 255, "%s#%d#%u", temp, price, qty);
    addItem(data);
    updateStorage();
    getItemInfo(name);
    free(data);
}

void returnItem(items* cart, char* name, int sum) {
    int hashVal = generateHash(name);
    Inventory[hashVal]->stocks += sum;
    for (int i=0; i<50; i++) {
        if (cart[i] && !strcmp(cart[i]->name, name)) {
            if (cart[i]->stocks == sum) cart[i] = NULL;
            else cart[i] -= sum;
        }
    }
}

static void updateStorage() {
    FILE* inv = fopen(invFile, "w+");
    for (int i=0; i<255; i++) {
        if (!Inventory[i]) continue;
        items temp = Inventory[i];
        fprintf(inv, "%s#%d#%ju\n", temp->name, temp->price, temp->stocks);
    }
    fclose(inv);
}

static void getItemInfo(char* name) {
    items obj = Inventory[generateHash(name)];
    printf("┬─ %s\n├ Rp. %d,00\n└ Qty: %d\n",
            obj->name,
            obj->price,
            obj->stocks);
}

static void addItem(char* data) {
    items newItem = malloc(sizeof(struct items_t));
    char* temp = data;
    int hashVal = 0;
    newItem->name = strdup(strtok(temp, "#"));
    hashVal = generateHash(newItem->name);
    newItem->price = atoi(strtok(NULL, "#"));
    newItem->stocks = (unsigned)atoi(strtok(NULL, "#"));
    if (!Inventory[hashVal]) Inventory[hashVal] = newItem;
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