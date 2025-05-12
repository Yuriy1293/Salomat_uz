#pragma once
#include <iostream>
#include <fstream> // Added for file operations
#include <string>  // Added for std::getline
#include "header.h"
#include <ctime>
#include <iomanip> 
using namespace std;

class MedicalHistory {
protected:
    string doctor_name, doctor_surname;
    string patient_name, patient_surname;
    string diagnosis;
    string complains;
    string treatment;
    int year, month, day;
    int hour, minute, sec;
    

public:
    // Default constructor added to allow creation of empty objects
    MedicalHistory() {
        doctor_name = "";
        doctor_surname = "";
        patient_name = "";
        patient_surname = "";
        diagnosis = "";
        complains = "";
        treatment = "";
        year = 0;
        month = 0;
        day = 0;
    }

    MedicalHistory(string doctor_n, string doctor_s, string patient_n, string patient_s) {
        doctor_name = doctor_n;
        doctor_surname = doctor_s;
        patient_name = patient_n;
        patient_surname = patient_s;
    }

    // Setters added to allow doctors to update medical history
    void set_diagnosis(const string& new_diagnosis) {
        diagnosis = new_diagnosis;
    }

    void set_complains(const string& new_complains) {
        complains = new_complains;
    }

    void set_treatment(const string& new_treatment) {
        treatment = new_treatment;
    }

    void set_time() {
        time_t now = time(0);       // �������� ������� ����� (� �������� � 1970 ����)
        tm time_info;               // ��������� ��� �������� ���������� �������

        // ������������� ��������� �������� �� time_t
        localtime_s(&time_info, &now);
        year = 1900 + time_info.tm_year; // tm_year � ���������� ��� � 1900
        month = 1 + time_info.tm_mon;    // tm_mon � ������ �� 0 �� 11
        day = time_info.tm_mday;


        hour = time_info.tm_hour;
        minute = time_info.tm_min;
        sec = time_info.tm_sec;


    }

    // Getters added to access private data
    string get_patient_name() const {
        return patient_name;
    }

    string get_patient_surname() const {
        return patient_surname;
    }

    


    static void show_all_patients() {

        string pinfls[100], names[100], surnames[100];

        string pinfl, password, name, surname;
        int role;
        int count = 0;


        ifstream file("accounts.txt");

        if (!file.is_open()) {
            cout << "Error with file opening" << endl;
            return;
        }

        while (file >> pinfl >> password >> name >> surname >> role) {
            if (role == 1) {
                // ��������: ��� ���� ����� PINFL?
                bool already_exists = false;
                for (int i = 0; i < count; i++) {
                    if (pinfls[i] == pinfl) {
                        already_exists = true;
                        break;
                    }
                }

                if (!already_exists) {
                    pinfls[count] = pinfl;
                    names[count] = name;
                    surnames[count] = surname;
                    count++;
                }
            }
        }


        if (count == 0) {
            cout << "There is no patients in database" << endl;
        }

        cout << "List of patients:" << endl;
         

        cout << "\nList of patients:\n";
        cout << left << setw(5) << "No."<< setw(15) << "PINFL"<< setw(15) << "Name"<< setw(15) << "Surname" << endl;

        cout << "---------------------------------------------" << endl;

        for (int i = 0; i < count; i++) {
            cout << left << setw(5) << (i + 1)
                << setw(15) << pinfls[i]
                << setw(15) << names[i]
                << setw(15) << surnames[i] << endl;
        }


        int choise; 
        
        while (true) {
            cout << "Write number in order to choose patient:\n Choice 0 to back on previous page" << endl;
            cin >> choise;

            if (choise == 0) {
                return;
                
            }



            if (choise < 0 || choise > count) {
                cout << "Invalid chose" << endl;
                continue;
            }

            string selected_name = names[choise - 1];
            string selected_surname = surnames[choise - 1];
            string selected_pinfl = pinfls[choise - 1];

            MedicalHistory history;

            history.load_from_file(selected_name , selected_surname);
            


        }


    }




    static void delete_user_by_pinfl(const string& target_pinfl) {
        ifstream file("accounts.txt");
        string lines[1000]; // ������ ����� (�� 1000 �������������)
        int count = 0;

        if (!file.is_open()) {
            cout << "Cannot open accounts.txt" << endl;
            return;
        }

        string pinfl, password, name, surname;
        int role;
        while (file >> pinfl >> password >> name >> surname >> role) {
            if (pinfl != target_pinfl) {
                lines[count] = pinfl + " " + password + " " + name + " " + surname + " " + to_string(role);
                count++;
            }
        }
        file.close();

        ofstream out("accounts.txt"); // �������������� ���� ����
        for (int i = 0; i < count; ++i) {
            out << lines[i] << endl;
        }
        out.close();

        cout << "User with PINFL " << target_pinfl << " deleted (if existed)." << endl;
    }






    // Added method to save medical history to file
    void save_to_file() {
        string filename = patient_name + "_" + patient_surname + ".txt";
        ofstream file(filename, ios::app); // ����� append � ���������� � ����� �����

        if (file.is_open()) {
            // === ������ X === � ����� �� ����������, ������ ��� �����������
            file << "=== Anketa ===" << endl;

            // ��������� ������� ����
            
            file << "Date: " << year << ":" << month << ":" << day << endl;
            file << "Time: " << hour << ":" << minute << ":" << sec << endl;
            file << "Doctor: " << doctor_name << " " << doctor_surname << endl;
            file << "Complaiins: " << complains << endl;
            file << "Diagnosis: " << diagnosis << endl;
            file << "Treatment: " << treatment << endl;
            file << endl; // ������ ������ ����� ��������
            file.close();

            
        }
        else {
            cout << "Error zapic." << endl;
        }
    }


    bool file_checker(const string& p_name, const string& p_surname) {
        string filename = p_name + "_" + p_surname + ".txt";
        ifstream file(filename);

        if (file.is_open()) {
            file.close();
            return true;
        }
        else {
            cout << "Error File ne nayden ili ne udalos otkrit." << endl;
            return false;
        }
    }




    // Added method to load medical history from file
    void load_from_file(const string& p_name, const string& p_surname) {
        string filename = p_name + "_" + p_surname + ".txt";
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            int form_number = 0;

            cout << "Medical History for  " << p_name << " " << p_surname << ":" << endl<<endl;
            cout << "==============================" << endl<<endl;

            while (getline(file, line)) {
                // ���� ����� ������ "=== ������", ����������� ������� � ������� ���������
                if (line.find("=== Anketa ===") != string::npos) {
                    form_number++;
                    cout << endl << "Medical Patient Data " << form_number << endl;
                }
                else {
                    cout << line << endl;
                }
            }

            file.close();
        }
        else {
            cout << "File ne nayden ili ne udalos otkrit." << endl;
        }
    }

};
