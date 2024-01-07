//
// Created by ZEYNEP on 3.01.2024.
//

#ifndef UNTITLED1_PATIENT_H
#define UNTITLED1_PATIENT_H
#ifndef PATIENT_H
#define PATIENT_H

// Define the Patient struct
typedef struct {
    int id;
    char social_security_number[20];
    char name[100];
    char department[50];
    char diagnosis[100];
    char prescriptions[200];
    char appointments_with_doctor[20];
    char treatment[100];
    char inpatient[5];  // "Yes" or "No"
    int services_cost;
    char payment_method[50];
    char telephone_number[20];
    char address[200];
} Patient;

// Function prototype for reading patients from a file
Patient* read_patients(const char* filename, int* patient_count);
void addPatient(Patient **patients, int *patient_count);
void viewPatientHistory(Patient* patients, int patient_count, int patient_id);
void searchPatientPrescriptions(Patient* patients, int patient_count, int patient_id);
void viewBilling(const Patient* patients, int patient_count, int patient_id);
void updatePaymentDetails(Patient* patients, int patient_count, int patient_id);
void generateFinancialReport(const Patient* patients, int patient_count);
void save_patients_data(Patient *patients, int patient_count, const char *filename);
#endif // PATIENT_H

#endif //UNTITLED1_PATIENT_H
