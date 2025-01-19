#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float price;
    int quantity;
} Product;

void addProduct(Product **inventory, int *count) {
    *inventory = realloc(*inventory, (*count + 1) * sizeof(Product));
    printf("Enter product name: ");
    scanf(" %[^\n]", (*inventory)[*count].name);
    printf("Enter product price: ");
    scanf("%f", &(*inventory)[*count].price);
    printf("Enter product quantity: ");
    scanf("%d", &(*inventory)[*count].quantity);
    (*count)++;
    printf("Product added successfully.\n");
}

void updateQuantity(Product *inventory, int count) {
    char name[50];
    printf("Enter product name to update: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Quantity updated successfully.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void deleteProduct(Product **inventory, int *count) {
    char name[50];
    printf("Enter product name to delete: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < *count; i++) {
        if (strcmp((*inventory)[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                (*inventory)[j] = (*inventory)[j + 1];
            }
            (*count)--;
            *inventory = realloc(*inventory, (*count) * sizeof(Product));
            printf("Product deleted successfully.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void displayInventory(Product *inventory, int count) {
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Price: %.2f, Quantity: %d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}

void saveToFile(Product *inventory, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving to file.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(inventory, sizeof(Product), count, file);
    fclose(file);
    printf("Inventory saved successfully.\n");
}

void loadFromFile(Product **inventory, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No inventory data found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    *inventory = realloc(*inventory, (*count) * sizeof(Product));
    fread(*inventory, sizeof(Product), *count, file);
    fclose(file);
    printf("Inventory loaded successfully.\n");
}

int main() {
    Product *inventory = NULL;
    int count = 0;
    const char *filename = "inventory.dat";
    loadFromFile(&inventory, &count, filename);

    int choice;
    do {
        printf("\n1. Add Product\n2. Update Quantity\n3. Delete Product\n4. Display Inventory\n5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(&inventory, &count);
                break;
            case 2:
                updateQuantity(inventory, count);
                break;
            case 3:
                deleteProduct(&inventory, &count);
                break;
            case 4:
                displayInventory(inventory, count);
                break;
            case 5:
                saveToFile(inventory, count, filename);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free(inventory);
    return 0;
}
