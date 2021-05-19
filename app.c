#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "libs\custServices.h"
#include "libs\inventory.h"

int main(int argc, char* argv[]) {
  int opt = -1;
  char* buff = calloc(255, sizeof(char));
  items userCart[50] = {0};
  initMembership();
  initStorage();

  while (opt != 6) {
    printf("Welcome to SchneeKatze's Cafe!\n");
    printf("[1] Order a Coffee\n");
    printf("[2] Cancel an Item\n");
    printf("[3] Check Shopping Cart\n");
    printf("[4] Membership management\n");
    printf("[5] Checkout\n");
    printf("[6] Exit\n");
    printf("Enter your choices: ");
    scanf("%d", &opt);

    switch (opt) {
      case 1:
        if (showList()) {
          printf("No DATA!\n");
          break;
        }
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
          printf("There's no pending item(s)!\n");
          break;
        }
        printf("Enter your name: ");
        fflush(stdin);
        gets(buff);
        if (payment(buff, cost) == -1) break;
        for (int i=0; i<50; i++) userCart[i] = 0;
        break;
      case 6:
        printf("Thanks for coming :3 \n");
        break;
      case 99:
        manageStorage();
        break;
      default:
        printf("Wrong Choices :<\n");
    }
    getch();
    system("cls");
  }

}