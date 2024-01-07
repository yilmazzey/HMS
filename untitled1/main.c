#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"


void showUserOptions(const char* role, Patient** patients, int* patient_count, User* users, int user_count, const char* userfile, const char* patientfile) {
    if (strcmp(role, "management") == 0) {
        printf("Select Operation:\n");
        printf("1. Add Personnel\n");
        printf("2. View Personnel Info\n");
        printf("3. View Doctors in Department\n");
        printf("4. Remove Personnel\n");
        printf("5. Exit\n");
        int choice;
        do {

            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    // Function to add personnel (to be implemented)
                    addUser(&users, &user_count);
                    save_user_data(users, user_count, userfile);
                    break;
                case 2:
                    // Function to view personnel info (to be implemented)
                    printf("List of Personnel of Hospital\n");
                    viewUsers(users, user_count);
                    break;
                case 3:

                    printf("Enter department name: ");
                    char department[50];
                    scanf("%49s", department);

                    int filtered_count = 0;
                    User **filtered_doctors = filter_doctors_by_department(users, user_count, department,
                                                                           &filtered_count);

                    if (filtered_doctors != NULL) {
                        for (int i = 0; i < filtered_count; i++) {
                            printf("Doctor ID: %d, Name: %s\n", filtered_doctors[i]->id, filtered_doctors[i]->name);
                        }
                        free(filtered_doctors); // Remember to free the allocated memory
                    } else {
                        printf("No doctors found in %s department.\n", department);
                    }
                    break;
                case 4:
                    printf("Enter the ID of the personnel to remove: ");
                    int user_id;
                    scanf("%d", &user_id);
                    removeUser(&users, &user_count, user_id);
                    save_user_data(users, user_count, userfile);
                    break;
                case 5:
                    printf("Exiting...\n");
                    exit(0);
                    break;
                default :
                    printf("Invalid choice.");
                    break;
            }
        }while(choice != 5);

    }else if (strcmp(role, "doctor") == 0) {
        int choice;
        int patient_id;
        printf("Select Operation:\n");
        printf("1. Add patient\n");
        printf("2. Look patient history\n");
        printf("3. Search patient prescriptions\n");
        printf("4. Exit\n");

        do{
            printf("Enter your choice: ");
            scanf("%d", &choice);
        switch (choice) {
            case 1:
                // Call function to add patient (to be implemented in patient.c)
                addPatient(patients, patient_count);
                save_patients_data(*patients, *patient_count, patientfile);
                break;
            case 2:
                // Call function to look up patient history (to be implemented in patient.c)
                printf("Enter Patient ID: ");
                scanf("%d", &patient_id);
                viewPatientHistory(*patients, *patient_count, patient_id);
                break;
            case 3:
                // Call function to search patient prescriptions (to be implemented in patient.c)
                printf("Enter Patient ID to search prescriptions: ");
                scanf("%d", &patient_id);
                searchPatientPrescriptions(*patients, *patient_count, patient_id);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.");
                break;

            }
        }while(choice != 4);
    } else if (strcmp(role, "accountant") == 0) {  // Assuming 'accountant' role for the third set of options
            printf("Select Operation:\n");
            printf("1. View Billing\n");
            printf("2. Update Payment Details\n");
            printf("3. Generate financial report\n");
            printf("4. Exit\n");
            int choice;

            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("Enter Patient ID for billing information: ");
                        int patient_id;
                        scanf("%d", &patient_id);
                        viewBilling(*patients, *patient_count, patient_id);
                        break;
                    case 2:
                        printf("Enter Patient ID to update payment details: ");
                        scanf("%d", &patient_id);
                        updatePaymentDetails(*patients, *patient_count, patient_id);
                        save_patients_data(*patients, *patient_count, patientfile);
                        break;
                    case 3:
                        generateFinancialReport(*patients, *patient_count);
                        break;
                    case 4:
                        printf("Exiting...\n");
                        break;
                    default:
                        printf("Invalid choice.");
                        break;
                }
            }while (choice != 4);
        }
    }


    int main(int argc, char *argv[]) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
            return 1;
        }

        int user_count = 0;
        User *users = read_users(argv[1], &user_count);

        if (!users) {
            fprintf(stderr, "Failed to read users from the file.\n");
            return 1;
        }
        int patient_count = 0;

        Patient *patients = read_patients(argv[2], &patient_count);
        if (!patients) {
            fprintf(stderr, "Failed to read patients from the file.\n");
            return 1;
        }
        printf("\n\n\n");
        printf("---------------------------------------------------------\n");
        printf("---------------------------------------------------------\n");
        printf("--------------HOSPITAL MANAGEMENT SYSTEM------------------\n");
        printf("----------------------------------------------------------\n");
        printf("----------------------------------------------------------\n\n");
        printf("\n");
        int id;
        char password[50];
        User *authenticated_user = NULL;

        while (authenticated_user == NULL) {
            printf("\n\n\n");
            printf("Enter User ID: ");
            scanf("%d", &id);
            printf("\n");
            printf("Enter Password: ");
            scanf("%s", password);

            authenticated_user = authenticateUser(users, user_count, id, password);

            if (authenticated_user) {
                printf("Access Granted. Hello %s!\n", authenticated_user->name);
                printf("\n\n\n");
                printf("\n\n\n");
                printf("\n\n\n");
                showUserOptions(authenticated_user->role, &patients, &patient_count, users, user_count, argv[1], argv[2]);
            } else {
                printf("Access Denied. Please try again.\n");
            }
        }
         // Save users to the file

        // Free memory and other cleanup
        free(users);
        free(patients);

        return 0;
    }
