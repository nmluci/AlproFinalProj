#ifndef __CX_INV__
    #define __CX_INV__
    #define invFile "inventory.data"

    struct items_t {
        char* name;
        unsigned price;
        unsigned stocks;
    };
    typedef struct items_t* items;

    extern void initStorage();
    extern void manageStorage();
    extern int showList();
    extern void showCart(items* cart);
    extern int checkout(items* cart);
    extern void removeItem(char* name);
    extern void buyItem(items* cart, char* name, unsigned sum);
    extern void returnItem(items* cart, char* name, unsigned sum); 
    static void addItem(char* data);
    static void appendItem(char* name, unsigned price, unsigned qty);
    static void getItemInfo(char* name);
    static void updateStorage();
    static int generateHash(char* name);
    static unsigned length(const unsigned long num);
#endif