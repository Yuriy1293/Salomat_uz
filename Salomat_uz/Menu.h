#pragma once
//this file consists of several classes which represents varios menu pages depending on user type

#include <iostream>
#include"MedcalHistory.h"
#include "Validator.h"
using namespace std;

class Menu {

public:
    virtual void show() = 0;

    virtual ~Menu() {};


};



class PatientMenu : public Menu {
private:
    string patient_name;
    string patient_surname;

public:
    // Конструктор с параметрами — передаём имя и фамилию пациента
    PatientMenu(const string& name, const string& surname)
        : patient_name(name), patient_surname(surname) {}

    void show() override {
        int choice;
        
        while (true) {

            cout << "Patient menu\n";
            cout << "\tChoose option:\n";
            cout << "1. View medical history\n";
            cout << "5. Log out\n";
            cin >> choice;

            switch (choice) {
            case 1: {
                // Загружаем и отображаем мед. анкету
                MedicalHistory history;
                if (history.file_checker(patient_name, patient_surname)) {
                    history.load_from_file(patient_name, patient_surname);
                }
                else {
                    cout << "No medical history found.\n";
                }
                break;
            }
            case 5:
                cout << "Logging out...\n";
                
                return;
            default:
                cout << "Invalid option.\n";
            }
        }
        
        
        
    }
};

     



class DoctorMenu : public Menu {
private:
    string doctor_name;
    string doctor_surname;

public:
    // Передаём имя и фамилию доктора
    DoctorMenu(const string& name, const string& surname)
        : doctor_name(name), doctor_surname(surname) {}



    

    void show() override {
        int choice;

        while (true) {




            cout << "Doctor menu\n";
            cout << "\tChoose option:\n";
            cout << "1. Create medical history\n";
            cout << "2. Show all patients\n";
            cout << "5. Log out\n";
            cin >> choice;

            switch (choice) {
            case 1: {
                
                int choise_2  =  - 1;
                cout << "Search patient by: \n1) Show patient's list \n 2) Search by pinfl" << endl;
                cin >> choise_2;


                if (choise_2 == 1) {
                    MedicalHistory::show_all_patients();
                    
                }
                else if (choise_2 == 2) {
                    string pinfl;
                    string complaints, diag, treat;
                    cout << "Enter patient's PINFL : " << endl;
                    
                    string p_name, p_surname;
                    while(true) {

                        cin >> pinfl;

                        
                        if (Validator::user_exists_in_govermental_database(pinfl, p_name, p_surname)) {
                            cout << "Name: " << p_name << ", Surname: " << p_surname << endl;
                            break;
                        }

                        else {
                            cout << "User not found" << endl;
                            continue;
                        }



                    }
                    

                    
                    
                    cout << "Enter complaints:\n";
                    cin.ignore(); // чтобы getline сработал корректно после cin
                    getline(cin, complaints);
                    cout << "Enter diagnosis:\n";
                    getline(cin, diag);
                    cout << "Enter treatment:\n";
                    getline(cin, treat);

                    // Создаём объект и сохраняем в файл
                    MedicalHistory history(doctor_name, doctor_surname, p_name, p_surname);
                    history.set_complains(complaints);
                    history.set_diagnosis(diag);
                    history.set_treatment(treat);
                    history.set_time();
                    history.save_to_file();

                    ofstream file("accounts.txt", ios::app);

                    if (file.is_open()) {
                        file << pinfl << " " << "_"  << " " << p_name << " " << p_surname << " " << 1 << endl;
                    }

                    break;
                   
                }
                



                
            }

            case 2:
                // all patients
                MedicalHistory::show_all_patients();
                break;







            case 5:
                cout << "Logging out...\n";
                
                return;
            default:
                cout << "Invalid option.\n";
            }
        }
    }
};
