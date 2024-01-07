//
// Created by ZEYNEP on 3.01.2024.
//
#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read and parse the file for patient data
Patient* read_patients(const char* filename, int* patient_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char line[1024];
    Patient *patients = NULL;
    int count = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Patient* temp = realloc(patients, (count + 1) * sizeof(Patient));
        if (temp == NULL) {
            perror("Error reallocating memory");
            free(patients);
            fclose(file);
            return NULL;
        }
        patients = temp;

        // Parse the line and fill the struct
        sscanf(line, "%d,%19[^,],%99[^,],%49[^,],%99[^,],%199[^,],%19[^,],%99[^,],%4[^,],%d,%49[^,],%19[^,],%199[^\n]",
               &patients[count].id, patients[count].social_security_number, patients[count].name,
               patients[count].department, patients[count].diagnosis, patients[count].prescriptions,
               patients[count].appointments_with_doctor, patients[count].treatment, patients[count].inpatient,
               &patients[count].services_cost, patients[count].payment_method, patients[count].telephone_number,
               patients[count].address);

        count++;
    }

    fclose(file);
    *patient_count = count;
    return patients;
}
void addPatient(Patient **patients, int *patient_count) {
    // Allocate space for the new patient
    Patient *temp = realloc(*patients, (*patient_count + 1) * sizeof(Patient));
    if (temp == NULL) {
        perror("Error reallocating memory");
        return;
    }
    *patients = temp;

    // Input data for the new patient
    printf("Enter details for the new patient:\n");
    printf("ID: ");
    scanf("%d", &((*patients)[*patient_count].id));

    // Clear the input buffer before reading strings
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Social Security Number: ");
    fgets((*patients)[*patient_count].social_security_number, sizeof((*patients)[*patient_count].social_security_number), stdin);
    // Remove the potential newline character
    (*patients)[*patient_count].social_security_number[strcspn((*patients)[*patient_count].social_security_number, "\n")] = 0;

    printf("Name: ");
    fgets((*patients)[*patient_count].name, sizeof((*patients)[*patient_count].name), stdin);
    (*patients)[*patient_count].name[strcspn((*patients)[*patient_count].name, "\n")] = 0;

    printf("Department: ");
    fgets((*patients)[*patient_count].department, sizeof((*patients)[*patient_count].department), stdin);
    (*patients)[*patient_count].department[strcspn((*patients)[*patient_count].department, "\n")] = 0;

    printf("Diagnosis: ");
    fgets((*patients)[*patient_count].diagnosis, sizeof((*patients)[*patient_count].diagnosis), stdin);
    (*patients)[*patient_count].diagnosis[strcspn((*patients)[*patient_count].diagnosis, "\n")] = 0;

    printf("Prescriptions: ");
    fgets((*patients)[*patient_count].prescriptions, sizeof((*patients)[*patient_count].prescriptions), stdin);
    (*patients)[*patient_count].prescriptions[strcspn((*patients)[*patient_count].prescriptions, "\n")] = 0;

    printf("Appointments with Doctor (YYYY-MM-DD): ");
    fgets((*patients)[*patient_count].appointments_with_doctor, sizeof((*patients)[*patient_count].appointments_with_doctor), stdin);
    (*patients)[*patient_count].appointments_with_doctor[strcspn((*patients)[*patient_count].appointments_with_doctor, "\n")] = 0;

    printf("Treatment: ");
    fgets((*patients)[*patient_count].treatment, sizeof((*patients)[*patient_count].treatment), stdin);
    (*patients)[*patient_count].treatment[strcspn((*patients)[*patient_count].treatment, "\n")] = 0;
    (*patient_count)++;
}
void viewPatientHistory(Patient* patients, int patient_count, int patient_id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == patient_id) {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Social Security Number: %s\n", patients[i].social_security_number);
            printf("Name: %s\n", patients[i].name);
            printf("Department: %s\n", patients[i].department);
            printf("Diagnosis: %s\n", patients[i].diagnosis);
            printf("Prescriptions: %s\n", patients[i].prescriptions);
            printf("Last Appointment: %s\n", patients[i].appointments_with_doctor);
            printf("Treatment: %s\n", patients[i].treatment);
            return;
        }
    }
    printf("Patient with ID %d not found.\n", patient_id);
}
void searchPatientPrescriptions(Patient* patients, int patient_count, int patient_id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == patient_id) {
            printf("Prescriptions for patient ID %d:\n", patient_id);
            printf("%s\n", patients[i].prescriptions);
            return;
        }
    }
    printf("No patient found with ID %d.\n", patient_id);
}
void viewBilling(const Patient* patients, int patient_count, int patient_id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == patient_id) {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Inpatient Status: %s\n", patients[i].inpatient);
            printf("Services Cost: %d\n", patients[i].services_cost);
            printf("Payment Method: %s\n", patients[i].payment_method);
            printf("Telephone Number %s\n", patients[i].telephone_number);
            printf("Address: %s\n", patients[i].address);

            return;
        }
    }
    printf("No patient found with ID %d.\n", patient_id);
}
void updatePaymentDetails(Patient* patients, int patient_count, int patient_id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == patient_id) {
            printf("Updating payment details for Patient ID: %d\n", patient_id);
            printf("Current Inpatient Status: %s\n", patients[i].inpatient);
            printf("Enter new Inpatient Status (Yes/No): ");
            scanf("%3s", patients[i].inpatient); // Assuming 'inpatient' is a string
            printf("Current Services Cost: %d\n", patients[i].services_cost);
            printf("Enter new Services Cost: ");
            scanf("%d", &patients[i].services_cost);
            printf("Current Payment Method: %s\n", patients[i].payment_method);
            printf("Enter new Payment Method: ");
            scanf("%49s", patients[i].payment_method);
            printf("Payment details updated successfully.\n");
            return;
        }
    }
    printf("No patient found with ID %d.\n", patient_id);
}
void generateFinancialReport(const Patient* patients, int patient_count) {
    int totalRevenue = 0;
    for (int i = 0; i < patient_count; i++) {
        totalRevenue += patients[i].services_cost;
    }
    printf("Total Hospital Revenue from Services: %d\n", totalRevenue);
}
void save_patients_data(Patient *patients, int patient_count, const char *filename) {
    FILE *file = fopen(filename, "w"); // Open file in write mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < patient_count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n",
                patients[i].id, patients[i].social_security_number, patients[i].name,
                patients[i].department, patients[i].diagnosis, patients[i].prescriptions,
                patients[i].appointments_with_doctor, patients[i].treatment, patients[i].inpatient,
                patients[i].services_cost, patients[i].payment_method, patients[i].telephone_number,
                patients[i].address);
    }

    fclose(file);
}