#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("inventory.txt", "r+");
    if(fp == NULL)
        fp = fopen("inventory.txt", "w+"); // create if not exists

    int fd = fileno(fp);

    printf("Writer: Trying for exclusive lock...\n");
    flock(fd, LOCK_EX);
    printf("Writer: Lock acquired\n");

    int choice;
    char name[50], item[50];
    int qty;

    printf("\n1. Add Product\n2. Update Quantity\n3. Delete Product\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter product name and quantity: ");
        scanf("%s %d", name, &qty);

        fseek(fp, 0, SEEK_END);
        fprintf(fp, "%s %d\n", name, qty);

        printf("Product added.\n");
    }
 
    else if(choice == 2) // we cant update a new file so what we do is make a new file copy the contents of old file in new file and add the new content needed
    {
        FILE *temp = fopen("temp.txt", "w");

        char item[50]; // item name to be added
        int old_qty;
        int new_qty;

        printf("Enter product name to update: ");
        scanf("%s", name);

        printf("Enter new quantity: ");
        scanf("%d", &new_qty);

        rewind(fp);   // goes to the start of the file (inventory)

        while(fscanf(fp, "%s %d", item, &old_qty) != EOF) // function used : fscanf
        {
            if(strcmp(item, name) == 0)
            {
                // UPDATE happens here
                fprintf(temp, "%s %d\n", item, new_qty);
            }
            else
            {
                fprintf(temp, "%s %d\n", item, old_qty);
            }
        }

    fclose(fp);
    fclose(temp);

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt"); // rename used to rename the new file to the name of old file

    printf("Product updated.\n");
}
    else if(choice == 3)
    {
        FILE *temp = fopen("temp.txt", "w");

        printf("Enter product name to delete: ");
        scanf("%s", name);

        rewind(fp);

        while(fscanf(fp, "%s %d", item, &qty) != EOF)
        {
            if(strcmp(item, name) != 0)
            {
                fprintf(temp, "%s %d\n", item, qty);
            }
        }

        fclose(fp);
        fclose(temp);

        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");

        printf("Product deleted.\n");
    }

    sleep(10); // for demo

    flock(fd, LOCK_UN);
    printf("Writer: Lock released\n");

    fclose(fp);
    return 0;
}