#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the User struct
typedef struct {
    int id;
    char role[50];
    char name[100];
    char department[50];
    char password[50];
} User;

// Function to read and parse the file
User* read_users(const char* filename, int* user_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char line[256];
    User *users = NULL;
    int count = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // Reallocate array to accommodate new user
        User *temp = realloc(users, (count + 1) * sizeof(User));
        if (temp == NULL) {
            perror("Error reallocating memory");
            free(users);
            fclose(file);
            return NULL;
        }
        users = temp;

        // Parse the line and fill the struct
        sscanf(line, "%d,%49[^,],%99[^,],%49[^,],%49s",
               &users[count].id, users[count].role, users[count].name,
               users[count].department, users[count].password);

        count++;
    }

    fclose(file);
    *user_count = count;
    return users;
}
User* authenticateUser(User* users, int user_count, int id, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id && strcmp(users[i].password, password) == 0) {
            return &users[i];
        }
    }
    return NULL;
}
void addUser(User** users, int* user_count) {
    User *temp = realloc(*users, (*user_count + 1) * sizeof(User));
    if (temp == NULL) {
        perror("Error reallocating memory");
        return;
    }
    *users = temp;
// Input data for the new user
    printf("Enter details for the new user:\n");
    printf("ID: ");
    scanf("%d", &((*users)[*user_count].id));

    // Clear the input buffer before reading strings
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Role: ");
    fgets((*users)[*user_count].role, sizeof((*users)[*user_count].role), stdin);
    (*users)[*user_count].role[strcspn((*users)[*user_count].role, "\n")] = 0;

    printf("Name: ");
    fgets((*users)[*user_count].name, sizeof((*users)[*user_count].name), stdin);
    (*users)[*user_count].name[strcspn((*users)[*user_count].name, "\n")] = 0;

    printf("Department: ");
    fgets((*users)[*user_count].department, sizeof((*users)[*user_count].department), stdin);
    (*users)[*user_count].department[strcspn((*users)[*user_count].department, "\n")] = 0;

    printf("Password: ");
    fgets((*users)[*user_count].password, sizeof((*users)[*user_count].password), stdin);
    (*users)[*user_count].password[strcspn((*users)[*user_count].password, "\n")] = 0;

    (*user_count)++;
}

User** filter_doctors_by_department(User* users, int total_users, const char* department_name, int* filtered_count) {
    User** filtered_doctors = NULL;
    int count = 0;

    for (int i = 0; i < total_users; i++) {
        if (strcmp(users[i].role, "doctor") == 0 && strcmp(users[i].department, department_name) == 0) {
            User** temp = realloc(filtered_doctors, (count + 1) * sizeof(User*));
            if (temp == NULL) {
                perror("Error reallocating memory");
                free(filtered_doctors);
                return NULL;
            }
            filtered_doctors = temp;
            filtered_doctors[count] = &users[i];
            count++;
        }
    }

    *filtered_count = count;
    return filtered_doctors;
}

void removeUser(User** users, int* user_count, int user_id) {
    int found = 0;
    for (int i = 0; i < *user_count; i++) {
        if ((*users)[i].id == user_id) {
            found = 1;
            // Shift all elements after the found index
            for (int j = i; j < *user_count - 1; j++) {
                (*users)[j] = (*users)[j + 1];
            }
            (*user_count)--;
            break;
        }
    }

    if (found) {
        *users = realloc(*users, (*user_count) * sizeof(User));
        if (*users == NULL && *user_count > 0) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
        printf("User with ID %d removed.\n", user_id);
    } else {
        printf("User with ID %d not found.\n", user_id);
    }
}


void viewUsers(const User* users, int user_count) {
    printf("Listing all personnel:\n");
    for (int i = 0; i < user_count; i++) {
        printf("ID: %d, Role: %s, Name: %s, Department: %s\n",
               users[i].id, users[i].role, users[i].name, users[i].department);
    }
}
void save_user_data(User* users, int user_count, const char *filename) {
    FILE *file = fopen(filename, "w"); // Open in append mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n",
                users[i].id, users[i].role, users[i].name,
                users[i].department, users[i].password);
    }

    fclose(file);
}
