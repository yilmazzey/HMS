//
// Created by ZEYNEP on 3.01.2024.
//

#ifndef UNTITLED1_LOGIN_H
#define UNTITLED1_LOGIN_H
#ifndef USER_FILTER_H
#define USER_FILTER_H

// Define the User struct
typedef struct {
    int id;
    char role[50];
    char name[100];
    char department[50];
    char password[50];
} User;

// Function prototype for filtering doctors by department
User* read_users(const char* filename, int* user_count);
User* authenticateUser(User* users, int user_count, int id, const char* password);
void addUser(User** users, int* user_count);
void removeUser(User** users, int* user_count, int user_id);
void viewUsers(const User* users, int user_count);
void save_user_data(User *users, int user_count, const char *filename);
User** filter_doctors_by_department(User* users, int total_users, const char* department_name, int* filtered_count);

#endif // USER_FILTER_H
#endif //UNTITLED1_LOGIN_H
