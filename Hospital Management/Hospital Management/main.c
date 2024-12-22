#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct patient {
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char date[12];
} p;

struct doctor {
    int id;
    char name[50];
    char address[50];
    char specialize[50];
    char date[12];
} d;

FILE *fp;

void admitPatient();
void patientList();
void dischargePatient();
void addDoctor();
void doctorList();

int main() {
    int ch;

    while (1) {
        system("cls");
        printf("<== Hospital Management System ==>\n");
        printf("1.Admit Patient\n");
        printf("2.Patient List\n");
        printf("3.Discharge Patient\n");
        printf("4.Add Doctor\n");
        printf("5.Doctors List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 0:
            exit(0);

        case 1:
            admitPatient();
            break;

        case 2:
            patientList();
            break;

        case 3:
            dischargePatient();
            break;

        case 4:
            addDoctor();
            break;

        case 5:
            doctorList();
            break;

        default:
            printf("Invalid Choice...\n\n");
        }

        printf("\n\nPress Enter To Continue...");
        getchar();
        getchar();
    }

    return 0;
}

void admitPatient() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("patient.txt", "ab");

    printf("Enter Patient id: ");
    scanf("%d", &p.id);

    printf("Enter Patient name: ");
    fflush(stdin);
    fgets(p.patientName, sizeof(p.patientName), stdin);
    p.patientName[strcspn(p.patientName, "\n")] = '\0';

    printf("Enter Patient Address: ");
    fflush(stdin);
    fgets(p.patientAddress, sizeof(p.patientAddress), stdin);
    p.patientAddress[strcspn(p.patientAddress, "\n")] = '\0';

    printf("Enter Patient Disease: ");
    fflush(stdin);
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = '\0';

    printf("\nPatient Added Successfully");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void patientList() {
    system("cls");
    printf("<== Patient List ==>\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "Id", "Patient Name", "Address", "Disease", "Date");
    printf("----------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-10d %-30s %-30s %-20s %s\n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }

    fclose(fp);
}

void dischargePatient() {
    int id, f = 0;
    system("cls");
    printf("<== Discharge Patient ==>\n\n");
    printf("Enter Patient id to discharge: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    if (fp == NULL) {
        printf("Error opening patient file.\n");
        return;
    }

    ft = fopen("temp.txt", "wb");
    if (ft == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            f = 1;
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nPatient Discharged Successfully.");
    } else {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");
}

void addDoctor() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    int f = 0;

    system("cls");
    printf("<== Add Doctor ==>\n\n");

    fp = fopen("doctor.txt", "ab");
    if (fp == NULL) {
        printf("Error opening doctor file.\n");
        return;
    }

    printf("Enter Doctor id: ");
    scanf("%d", &d.id);

    printf("Enter Doctor Name: ");
    fflush(stdin);
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0';

    printf("Enter Doctor Address: ");
    fflush(stdin);
    fgets(d.address, sizeof(d.address), stdin);
    d.address[strcspn(d.address, "\n")] = '\0';

    printf("Doctor Specialize in: ");
    fflush(stdin);
    fgets(d.specialize, sizeof(d.specialize), stdin);
    d.specialize[strcspn(d.specialize, "\n")] = '\0';

    printf("Doctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}

void doctorList() {
    system("cls");
    printf("<== Doctor List ==>\n\n");

    printf("%-10s %-30s %-30s %-30s %s\n", "id", "Name", "Address", "Specialize", "Date");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&d, sizeof(d), 1, fp) == 1) {
        printf("%-10d %-30s %-30s %-30s %s\n", d.id, d.name, d.address, d.specialize, d.date);
    }

    fclose(fp);
}
