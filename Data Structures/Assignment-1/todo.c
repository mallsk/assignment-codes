#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char taskName[100];
    int isCompleted; // 0 = Pending, 1 = Completed
} Task;

void addTask(Task **tasks, int *count) {
    *tasks = realloc(*tasks, (*count + 1) * sizeof(Task));
    printf("Enter task name: ");
    scanf(" %[^\n]", (*tasks)[*count].taskName);
    (*tasks)[*count].isCompleted = 0;
    (*count)++;
    printf("Task added successfully.\n");
}

void markTaskCompleted(Task *tasks, int count) {
    char name[100];
    printf("Enter task name to mark as completed: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(tasks[i].taskName, name) == 0) {
            tasks[i].isCompleted = 1;
            printf("Task marked as completed.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void deleteTask(Task **tasks, int *count) {
    char name[100];
    printf("Enter task name to delete: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < *count; i++) {
        if (strcmp((*tasks)[i].taskName, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                (*tasks)[j] = (*tasks)[j + 1];
            }
            (*count)--;
            *tasks = realloc(*tasks, (*count) * sizeof(Task));
            printf("Task deleted successfully.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void displayTasks(Task *tasks, int count) {
    printf("\nCurrent Tasks:\n");
    for (int i = 0; i < count; i++) {
        printf("Task: %s, Status: %s\n", tasks[i].taskName, tasks[i].isCompleted ? "Completed" : "Pending");
    }
}

int main() {
    Task *tasks = NULL;
    int count = 0;

    int choice;
    do {
        printf("\n1. Add Task\n2. Mark Task Completed\n3. Delete Task\n4. Display Tasks\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&tasks, &count);
                break;
            case 2:
                markTaskCompleted(tasks, count);
                break;
            case 3:
                deleteTask(&tasks, &count);
                break;
            case 4:
                displayTasks(tasks, count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free(tasks);
    return 0;
}
