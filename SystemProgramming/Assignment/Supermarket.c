#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>
#include<unistd.h>

struct items
{
    char barcode[15];
    char name[15];
    double price;
    int quantity;
    int line;
};

double getValues(int isBill);
struct items *insertItem(char file[], struct items *temp);
struct items *selectItem(int star, void *arg, int isBill);
struct items *whereItem(char barcode[], int isBill);
double insertItems();
double whereBill(int id);
void *deleteItem(void *arg);

void *server_side()
{
    system("chmod u+rwx *.sh");
    system("gcc -pthread Server.c -o Server");
    system("gcc Client.c -o Client");
    system("./Server");
}

int main()
{
    int c;
   pthread_t server;
   pthread_create(&server, NULL, &server_side, NULL);
   sleep(1);

    do
    {
        checkIfNull("item.csv");
        //Menu
        printf("Menu:\n");
        printf("1. Add Item\n");
        printf("2. Show Item\n");
        printf("3. Buy\n");
        printf("4. Show Bills\n");
        printf("5. permissions\n");
        printf("0. Exit (At any time)\n");

        printf("Action: ");
        scanf("%d", &c);

        printf("\n***************************************************\n");

        switch(c)
        {
            //Add Item-->
            case 1:
            {
                printf("Add Item\n");
                getValues(0);
            break;
            }

            //option to select items
            case 2:
                printf("Show Item menu:\n");
                selectIOption();
            break;

            //buy
            case 3:
                printf("Buy\n");
                insertBill();
            break;

            //option to select bills
            case 4:
                printf("Show Bill Menu:\n");
                selectBOption();
            break;

            case 5:
                printf("permissions menu:\n");
                permissionsOption();
            break;
        }

        printf("***************************************************\n\n");

    } while(c != 0);

    system("fuser -k 8080/tcp");
    printf("Exiting...");
    return 0;
}

double getValues(int isBill)
{
    char barcode[15];
    printf("enter Barcode !(0, 1): "); scanf("%s", barcode);
    if(equalBarcode(barcode, "0"))
    return -2;
    else if(equalBarcode(barcode, "1"))
    return -1;
    
    if(isBill)
    {
        struct items *temp = selectItem(0, whereItem(barcode, 0), 0);
        if(temp)
        {
            if(whereItem(barcode, 1))
            {
                printf("item is already added...\n");
                return 0;
            } else
            {
                double total;
                int quantity;
                do{
                    printf("enter quantity (<=storage): ");
                    scanf("%d", &quantity);
                } while(quantity > temp->quantity || quantity < 0);

                if(quantity == 0)
                {
                    return 0;
                }
                temp->quantity = quantity;
                temp->price = temp->price * quantity;
                insertItem("billItem.csv", temp);
                return temp->price;
            }
        } else
        {
            return 0;
        }
    } else if(!whereItem(barcode, 0))
    {
        struct items *temp = (struct items*) malloc(sizeof(struct items));

        strcpy(temp->barcode, barcode);
        printf("enter Name: "); scanf("%s", temp->name);
        do
        {
            printf("enter Price: "); scanf("%lf", &temp->price);
        } while(temp->price <= 0);
        do
        {
            printf("enter Quantity: "); scanf("%d", &temp->quantity);
        } while(temp->quantity <= 0);

        insertItem("items.csv", temp);
        printf("item has been added successfuly...\n");
    } else
    {
        printf("item is already added...\n");
        return 0;
    }
}

struct items *insertItem(char file[], struct items *temp)
{
    char cmd[100];
    sprintf(cmd, "./InsertItem.sh %s %s %.2lf %d %s", temp->barcode, temp->name, temp->price, temp->quantity, file);
    system(cmd);
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
        scanf("%d", &c);

        printf("\n***************************************************\n");
        switch(c)
        {
            //All Items-->
            case 1:
                selectItem(1, fopen("items.csv", "r"), 0);
            break;

            //Select Item Where
            case 2:
            {
		system("./Client");
                //selectItem(0, whereItem(barcode, 0), 0);
            break;
            }

            case 0:
            return;
        }
        printf("***************************************************\n\n");
    } while(c != 0);
}

struct items *selectItem(int star, void *arg, int isBill)
{
struct items *temp;
    if(arg)
    {
        if(star)
        {
            FILE *fb = arg;
            temp = (struct items*) malloc(sizeof(struct items));
            while(fscanf(fb, "%s %s %lf %d", temp->barcode, temp->name, &temp->price, &temp->quantity) == 4)
            {
                if(isBill)
                printf("barcode: %s    name: %s    quantity: %d    total: %.2lf\n", temp->barcode, temp->name, temp->quantity, temp->price);
                else
                printf("barcode: %s    name: %s    price: %.2lf    storage: %d\n", temp->barcode, temp->name, temp->price, temp->quantity);
            }
            fclose(fb);
        } else
        {
            temp = arg;
            printf("name: %s    price: %.2lf    storage: %d\n", temp->name, temp->price, temp->quantity);
        }
    } else if(!star)
    {
        printf("item doesn't exist...\n");
        return NULL;
    }
    else if(star && !isBill)
    printf("no item has found...\n");
return temp;
}

//Insert Into Bills-->
void insertBill()
{
    double total = insertItems();
    if(total > 0)
    {
        printf("bill amount: %.2lf\n", total);
        char cmd[100];
        sprintf(cmd, "./InsertBill.sh %.2lf", total);
        
        pthread_t deleteI;
        if(!pthread_create(&deleteI, NULL, &deleteItem, NULL))
        {
            printf("operation has ended successfuly\n");
            system(cmd);
        } else
        {
            printf("operation has ended unsuccessfuly\n");
            system("./InsertBill.sh");
        }

    return;
    } else if(total == 0)
    {
        printf("can't add bill with no items\n");
    }
    system("rm -rf billItem.csv");
    return;
}
//Insert Into Bill Items-->
double insertItems()
{
    double total = 0;
    printf("to finish the operation enter 1 ,to cancel enter 0\n");
    while(1)
    {
        double price = getValues(1);
        if(price > 0)
        {
            printf("total price: %.2lf\n", price);
            total = total + price;
        } else if(price == -1)
        {
            return total;
        } else if(price == -2)
        {
            printf("cancel\n");
            return -1;
        }
        
        printf("***************************************************\n");
    }
}

void *deleteItem(void *arg)
{
    printf("updating storage using threading...\n");
    system("./DeleteItem.sh");
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
                int id = 1;
                double total = whereBill(id);
                while(whereBill(id) > 0)
                {
                    total = whereBill(id);
                    int next;
                    printf("id: %d\n", id);
                    selectItem(1, fopen("item.csv", "r"), 1);
                    printf("bill amount: %.2lf\n", total);
                    printf("next enter 1, cancel enter 0: ");
                    scanf("%d", &next);
                    printf("***************************************************\n");
                    id++;
                    if(!next)
                    break;
                }
                if(id == 1)
                printf("there is no bill\n");
                else
                printf("finish...\n");
            break;
            }

            //Select Item Where
            case 2:
            {
                int id;
                printf("enter ID: ");
                scanf("%d", &id);
                if(id == 0)
                break;
                double total = whereBill(id);
                if(whereBill(id) > 0)
                {
                    printf("id: %d\n", id);
                    selectItem(1, fopen("item.csv", "r"), 1);
                    printf("bill amount: %.2lf\n", total);
                } else
                {
                    printf("bill doesn't exist\n");
                }
            break;
            }

            case 0:
            return;
        }
        system("./WhereBill.sh");
        printf("***************************************************\n\n");
    } while(c != 0);
}

//Where ID-->
double whereBill(int id)
{
    char cmd[100];
    sprintf(cmd, "%d", id);
    if(fork() == 0)
    execl("./WhereBill.sh", "./WhereBill.sh", cmd, NULL);

    sleep(1);
    double total = 0;
    if(!checkIfNull("bill.csv"))
    {
        FILE *fb = fopen("bill.csv", "r");
        fscanf(fb, "%lf", &total);
        fclose(fb);
    }
    return total;
}

void permissionsOption()
{
    int c;
    do{
        //Menu
        printf("1. Add to group\n");
        printf("2. remove from group\n");
        printf("3. Add to others\n");
        printf("4. remove from others\n");
        printf("5. Add to all\n");
        printf("6. remove from all\n");
        printf("7. show permissions\n");
        printf("0. Back\n");

        printf("Action: "); scanf("%i", &c);

        printf("\n***************************************************\n");
        switch(c)
        {
            case 1:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "g+", NULL);
                printf("Added successfully\n");
            break;
            }

            case 2:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "g-", NULL);
                printf("Removed successfully\n");
            break;
            }

            case 3:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "o+", NULL);
                printf("Added successfully\n");
            break;
            }

            case 4:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "o-", NULL);
                printf("Removed successfully\n");
            break;
            }

            case 5:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "go+", NULL);
                printf("Added successfully\n");
            break;
            }

            case 6:
            {
                if(fork() == 0)
                execl("./Permission.sh", "./Permission.sh", "go-", NULL);
                printf("Removed successfully\n");
            break;
            }

            case 7:
            {
                system("./Permission.sh");
            break;
            }

            case 0:
            return;
        }
        printf("***************************************************\n\n");
    } while(c =! 0);
}

//helping methods -->
struct items *whereItem(char barcode[], int isBill)
{
    struct items *temp;
    
    char cmd[100];
    if(isBill)
    {
        if(checkIfNull("billItem.csv") == 0)
        {
            sprintf(cmd, "./WhereItem.sh %s billItem.csv", barcode);
            system(cmd);
        } else
        {
            return NULL;
        }
        if(checkIfNull("item.csv") == 1)
        {
            return NULL;
        }
    }
    sprintf(cmd, "./WhereItem.sh %s items.csv", barcode);
    system(cmd);
    if(checkIfNull("item.csv") == 1)
    {
        return NULL;
    }

    temp = (struct items*) malloc(sizeof(struct items));
    FILE *fb = fopen("item.csv", "r");
    fscanf(fb, "%d %s %s %lf %d", &temp->line, temp->barcode, temp->name, &temp->price, &temp->quantity);
    fclose(fb);
    system("./WhereItem.sh");
    return temp;
}

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

int checkIfNull(char file[100])
{
    if(access(file, R_OK))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
