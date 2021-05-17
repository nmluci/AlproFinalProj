#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "libs\custServices.h"
#include "libs\inventory.h"

// int main() {
//   initMembership();
//   items userCart[50] = {0}; // 50 stack items a.k.a 50 jenis items
//   initStorage();
//   showList();
//   removeItem("tamago");
//   appendItem("Weedo", 15000, 420);
//   buyItem(userCart, "Weedo");
//   unsigned paid = checkout(userCart);
//   printf("%ju\n", paid);
// }

int main(int argc, char* argv[]) {
  int opt = -1;
  char* buff = calloc(255, sizeof(char));
  items userCart[50] = {0};
  initMembership();
  initStorage();

  printf("Welcome to SchneeKatze's Shop!\n");
  while (opt != 9) {
    printf("[1] Buy an Item\n");
    printf("[2] Return an Item\n");
    printf("[3] Check Shopping Cart\n");
    printf("[4] Membership management\n");
    printf("[5] Checkout\n");
    printf("[6] Exit\n");
    printf("Enter your choices: ");
    scanf("%d", &opt);

    switch (opt) {
      case 1:
        showList();
        printf("Enter the name of product to buy: ");
        fflush(stdin);
        gets(buff);
        printf("Sum: ");
        scanf("%d", &opt);
        buyItem(userCart, buff, opt);
        break;
      case 2:
        showCart(userCart);
        printf("Enter the name of product to return: ");
        fflush(stdin);
        gets(buff);
        printf("Sum: ");
        scanf("%d", &opt);
        returnItem(userCart, buff, opt);
        break;
      case 3:
        showCart(userCart);
        break;
      case 4:
        manageMembership();
        break;
      case 5:
        int cost = checkout(userCart);
        if (!cost) {
          printf("There's no pending cart!");
          break;
        }
        printf("Enter your name: ");
        fflush(stdin);
        gets(buff);
        if (payment(buff, cost) == -1) break;
        for (int i=0; i<50; i++) userCart[i] = 0;
        break;
      case 6:
        exit(0);
      case 99:
        unsigned qty = 0;
        int price = 0;
        showList();
        printf("[1] Add Stocks\n");
        printf("[2] Remove Item\n");
        printf("[3] Back\n");
        printf("> ");
        scanf("%d", &opt);

        switch (opt) {
          case 1:
            printf("Item Name: ");
            fflush(stdin);
            gets(buff);
            printf("Price: ");
            scanf("%d", &price);
            printf("Qty: ");
            scanf("%ju", &qty);
            appendItem(buff, price, qty);
            break;
          case 2:
            printf("Item name: ");
            fflush(stdin);
            gets(buff);
            removeItem(buff);
            break;
          case 3:
            break;
          default:
            break;
        }
        break;
      default:
        printf("Not Implemented yet!");
    }
    // getch();
    // system("cls");
  }

}