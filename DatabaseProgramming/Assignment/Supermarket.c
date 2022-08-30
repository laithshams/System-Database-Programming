#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>

struct items
{
    char barcode[15];
    char name[15];
    double price;
    int quantity;
    struct items *next;
} *items;

struct bills
{
    int id;
    struct item *items;
    double total_price;
    struct bill *next;
} *bills;

struct arg
{
    int star;
    struct bills *bills;
};

//insert items
struct items* insertItem(struct items *item, struct items *tempelement);
//select items
void selectIOption();
struct items* selectItem(int star, struct items *item, int isBill);
struct items* whereItem(char barcode[], struct items *item);
//insert bills
void insertBill();
int insertItems(struct bills *bill);
void *deleteQ(void *item);
//select bills
void selectBOption();
void selectBill(int star, struct bills *bill);
struct bills* whereBill(int id);

int main()
{
    int c;
    
    do
    {
        //Menu
        printf("Menu:\n");
        printf("1. Add Item\n");
        printf("2. Show Item\n");
        printf("3. Buy\n");
        printf("4. Show Bills\n");
        printf("0. Exit (At any time)\n");

        printf("Action: ");
        scanf("%i", &c);

        printf("\n***************************************************\n");

        switch(c)
        {
            //Add Item-->
            case 1:
            {
                struct items *tempelement = (struct items*) malloc(sizeof(struct items));
                printf("enter Barcode !(1): "); scanf("%s", tempelement->barcode);
                if(equalBarcode(tempelement->barcode, "0") 
                || equalBarcode(tempelement->barcode, "1"))
                break;

                if(whereItem(tempelement->barcode, items))
                {
                    printf("item is already added...\n");
                    break;
                }

                printf("enter Name: "); scanf("%s", tempelement->name);
                do
                {
                    printf("enter Price: "); scanf("%lf", &tempelement->price);
                } while(tempelement->price <= 0);
                do
                {
                    printf("enter Quantity: "); scanf("%i", &tempelement->quantity);
                } while(tempelement->quantity <= 0);
                items = insertItem(items, tempelement);

                if(items)
                printf("item has been added successfuly...\n");
            break;
            }

            //option to select items
            case 2:
                selectIOption();
            break;

            //buy
            case 3:
                insertBill();
            break;

            //option to select bills
            case 4:
                selectBOption();
            break;
        }

        printf("***************************************************\n\n");

    } while(c != 0);

    printf("Exiting...");
    return 0;
}

//Functions

//Insert Into Items Function-->
struct items* insertItem(struct items *item, struct items *tempelement)
{
    struct items *currPos;

    if(!item)
    {
        item = tempelement;
        return item;
    }

    currPos = item;
    while(1)
    {
        if(currPos->next)
        currPos = currPos->next;
        else
        {
            currPos->next = tempelement;
            return item;
        }
    }

    printf("error has occurred...\n");
    return item;
}

//Select Items Menu-->
void selectIOption(){
    int c;
    do{
        //Menu
        printf("Select Items:\n");
        printf("1. All\n");
        printf("2. By Barcode\n");
        printf("0. Back\n");

        printf("Action: ");
        scanf("%i", &c);

        printf("\n***************************************************\n");
        switch(c)
        {
            //All Items-->
            case 1:
                selectItem(1, items, 0);
            break;

            //Select Item Where
            case 2:
            {
                char barcode[15];
                printf("enter barcode: ");
                scanf("%s", barcode);
                if(equalBarcode(barcode, "0"))
                break;
                selectItem(0, whereItem(barcode, items), 0);
            break;
            }

            case 0:
            return;
        }
        printf("***************************************************\n\n");
    } while(c != 0);
}
//Select Items From-->
struct items* selectItem(int star, struct items *item, int isBill)
{
    do
    {
        if(item)
        {
            if(star)
            {
                printf("barcode: %s", item->barcode);
                for(int i = 0; i<(15-strlen(item->barcode)); i++)
                printf(" ");
            }

            printf("name: %s", item->name);
            for(int i = 0; i<(15-strlen(item->name)); i++)
            printf(" ");

            printf("price: %.2lf", item->price);
            for(int i = 0; i<5; i++)
            printf(" ");
            
            if(isBill)
            printf("quantity: ");
            else
            printf("storage: ");
            printf("%i\n", item->quantity);
            
            if(star)
            item = item->next;

        } else if(!star)
        printf("item doesn't exist...\n");
        else if(star && !isBill)
        printf("no item has found...\n");
        
    } while(star && item);
    return item;
}
//Where Barcode-->
struct items* whereItem(char barcode[], struct items *item)
{
    struct items *currPos = item;

    while(currPos)
    {
        if(equalBarcode(barcode, currPos->barcode) == 1)
        return currPos;
        else
        currPos = currPos->next;
    }
    return currPos;
}
//helping method to match barcodes-->
int equalBarcode(char barcode[], char item[])
{

    int bool = 1;
    if(strlen(barcode) != strlen(item))
    {
        bool = 0;
        return bool;
    }
    for (int i = 0; i < strlen(barcode); i++)
    {
        if(barcode[i] == item[i])
        continue;
        else
        {
            bool = 0;
            break;
        }
    }

    return bool;
}

//Insert Into Bills-->
void insertBill()
{
    struct bills *tempelement = (struct bills*) malloc(sizeof(struct bills));
    struct bills *currPos;
    int id = 1;

    if(!bills)
    {
        tempelement->id = id;
        if(insertItems(tempelement) == 1)
        {
            if(tempelement->items)
            {
                bills = tempelement;
                printf("Total Price: %.2lf\n", bills->total_price);
                printf("operation has ended successfuly\n");
            } else
            printf("can't add bill with no items\n");
        } else
        printf("operation has ended unsuccessfuly\n");
        return;
    }
    currPos = bills;
    while(1)
    {
        id++;
        if(currPos->next)
        currPos = currPos->next;
        else
        {
            if(insertItems(tempelement))
            {
                if(tempelement->items)
                {
                    tempelement->id = id;
                    currPos->next = tempelement;
                    printf("Total Price: %.2lf\n", currPos->total_price);
                    printf("operation has ended successfuly\n");
                } else
                printf("can't add bill with no items\n");
            }
            return;
        }
    }
    printf("error has occurred...\n");
    return;
}
//Insert Into Bill Items-->
int insertItems(struct bills *bill)
{
    char barcode[15];
    double total;
    strcpy(barcode, "2");
    printf("to finish the operation enter 1 ,to cancel enter 0\n");
    while(1){
        if(equalBarcode(barcode, "2") == 1)
        {
            printf("***************************************************\n");
            printf("Enter Barcode: ");
            scanf("%s", barcode);
        }

        if(equalBarcode(barcode, "1") == 1)
        {
            bill->total_price = total;
            pthread_t deleteItems;
            if(!pthread_create(&deleteItems, NULL, &deleteQ, bill->items))
            {
                printf("updating using threading...\n");
                return 1;
            } else
            {
                printf("error while threading...\n");
                return 0;
            }
        }

        if(equalBarcode(barcode, "0") == 1)
        {
            printf("canceling...\n");
            return 0;
        } else
        {
            struct items *tempelement = (struct items*) malloc(sizeof(struct items));
            struct items *item = selectItem(0, whereItem(barcode, items), 0);
            double price;
            int quantity;
            if(item){
                if(whereItem(barcode, bill->items))
                {
                    printf("item is already added...\n");
                    strcpy(barcode, "2");
                    continue;
                }

                do{
                    printf("enter quantity (<=storage): ");
                    scanf("%i", &quantity);
                } while(quantity > item->quantity || quantity < 0);

                if(quantity == 0)
                {
                    strcpy(barcode, "2");
                    continue;
                }

                price = (double) item->price * quantity;
                total += (double) price;
                strcpy(tempelement->barcode, item->barcode);
                strcpy(tempelement->name, item->name);
                tempelement->price = price;
                tempelement->quantity = quantity;

                printf("total: %.2lf\n", price);
                bill->items = insertItem(bill->items, tempelement);
            }
        }
        strcpy(barcode, "2");
    }
}

//Select Bills Menu-->
void selectBOption(){
    int c;
    do{
        //Menu
        printf("Select Bills:\n");
        printf("1. All\n");
        printf("2. By ID\n");
        printf("0. Back\n");

        printf("Action: "); scanf("%i", &c);

        printf("\n***************************************************\n");
        switch(c)
        {
            //All Items-->
            case 1:
            {
                selectBill(1, bills);
            break;
            }

            //Select Item Where
            case 2:
            {
                int id;
                printf("enter ID: ");
                scanf("%i", &id);
                if(id == 0)
                break;
                selectBill(0, whereBill(id));
            break;
            }

            case 0:
            return;
        }
        printf("***************************************************\n\n");
    } while(c != 0);
}
//Select Bills From-->
void selectBill(int star, struct bills *bill)
{
    int next;
    do
    {
        if(bill)
        {
            if(star)
            printf("ID: %i\n", bill->id);

            selectItem(1, bill->items, 1);
            printf("total price: %.2lf\n", bill->total_price);

            if(star)
            {
                printf("next(any positive): ");
                scanf("%i", &next);
                printf("***************************************************\n");
                bill = bill->next;
            }
        } else if(!star)
        printf("bill doesn't exist...\n");
        else
        {
            printf("no bill has found...\n");
            return;
        }
    } while(star && bill && next);
    if(star)
    printf("finish...\n");
    return;
}
//Where ID-->
struct bills* whereBill(int id)
{
    struct bills *currPos = bills;

    while(currPos)
    {
        if(id == currPos->id)
        return currPos;
        else
        currPos = currPos->next;
    }
    return currPos;
}

//Alter Quantity On Items-->
void *deleteQ(void *item){
    struct items *currPos = item;
    while(currPos){
        whereItem(currPos->barcode, items)->quantity -= currPos->quantity;
        currPos = currPos->next;
    }
    deleteI();
    return;
}
//Delete From Items-->
void deleteI(){
    struct items *parent;
    struct items *currPos = items;
    while(currPos)
    {  
        if(currPos == items && currPos->quantity == 0)
        {
            items = items->next;
            currPos = items;
        } else if(currPos->quantity == 0)
        {
            currPos = currPos->next;
            parent->next = currPos;
        } else
        {
            parent = currPos;
            currPos = currPos->next;
        }
    }
    return;
}
