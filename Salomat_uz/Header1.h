#pragma once

#include <iostream>

using namespace std;

class Menu {

public:
    virtual void show() = 0;

    virtual ~Menu() {};


};



class PatientMenu : public Menu {

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
        cout << "Patient menu\n";
        cout << "\tChoose option:\n";
        cout << "1. View medical history\n";
        cout << "5. Log out\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Загружаем и отображаем мед. анкету
            MedicalHistory history;
            if (history.load_from_file(patient_name, patient_surname)) {
                history.show_medical_history();
            } else {
                cout << "No medical history found.\n";
            }
            break;
        }
        case 5:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    }
};



};

class DoctorMenu :public Menu {

public:
    void show() override {


        int choise;

        cout << "Doctor menu" << endl;

        cout << "\tChoise option:" << endl << endl;
        cout << "1.Show patients\n2.Upload analysises\n3.Check patients appoitments\n4.Change profile info\n5.Log out" << endl;





    }




};


#include <fstream> // Added for file operations
#include <string>  // Added for std::getline

class MedicalHistory {
protected:
    string doctor_name, doctor_surname;
    string patient_name, patient_surname;
    string diagnosis;
    string complains;
    string treatment;

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

    // Getters added to access private data
    string get_patient_name() const {
        return patient_name;
    }

    string get_patient_surname() const {
        return patient_surname;
    }

    // Modified to display treatment as well
    void show_medical_history() {
        cout << "Patient Medical History:" << endl;
        cout << "Doctor: " << doctor_name << " " << doctor_surname << endl;
        cout << "Patient: " << patient_name << " " << patient_surname << endl;
        cout << "Complaints: " << complains << endl;
        cout << "Diagnosis: " << diagnosis << endl;
        cout << "Treatment: " << treatment << endl;
        cout << "====================" << endl;
    }

    // Added method to save medical history to file
    void save_to_file() {
        string filename = patient_name + "_" + patient_surname + ".txt";
        ofstream file(filename);

        if (file.is_open()) {
            file << doctor_name << endl;
            file << doctor_surname << endl;
            file << patient_name << endl;
            file << patient_surname << endl;
            file << diagnosis << endl;
            file << complains << endl;
            file << treatment << endl;
            file.close();
            cout << "Medical history saved to file: " << filename << endl;
        }
        else {
            cout << "Error: Could not open file for writing." << endl;
        }
    }

    // Added method to load medical history from file
    bool load_from_file(const string& p_name, const string& p_surname) {
        string filename = p_name + "_" + p_surname + ".txt";
        ifstream file(filename);

        if (file.is_open()) {
            getline(file, doctor_name);
            getline(file, doctor_surname);
            getline(file, patient_name);
            getline(file, patient_surname);
            getline(file, diagnosis);
            getline(file, complains);
            getline(file, treatment);
            file.close();
            return true;
        }
        else {
            cout << "Error: Could not open file for reading or file doesn't exist." << endl;
            return false;
        }
    }
};



class Registration {

protected:
    string name, surname, password, PINFL;



public:


    User* start() {

        int choise;
        cout << "Welcome to our medical application!" << endl;






        UserFactory* factory = nullptr;



        while (true) {
            cout << "Who you are? \n1)Patient\n2)Doctor" << endl;
            cin >> choise;

            // добавить проверку на буквы





            switch (choise) {

            case 1:
                cout << "Patient option was chosen" << endl;
                factory = new PatientFactory();
                break;

            case 2:
                cout << "Doctor option was chosen" << endl;
                factory = new DoctorFactory();
                break;

            default:
                cout << "There is no such option. Please,choise again" << endl << endl;
                continue;

            }
            break;
        }


        cout << "Enter your name:" << endl;
        cin >> name;
        cout << "Enter your surname" << endl;
        cin >> surname;


        while (true) {
            cout << "Enter your PINFL (12 digits)" << endl;
            cin >> PINFL;
            if (Validator::PINFL_checker(PINFL)) {
                cout << "Correct PINFL" << endl;
                break;
            }
            else {
                cout << "Incorrect PINFL, please , try again" << endl;
            }

        }






        cout << "Now you need to set up your passwort" << endl;
        while (true) {
            cout << "Enter new password" << endl;
            cin >> password;
            if (Validator::password_checher(password)) {
                cout << "Correct password" << endl;
                break;
            }
            else {
                cout << "Incorrect password, please , try again" << endl;
            }

        }

        User* user = factory->create_user(name, surname, password);
        user->registration();






        return user;

    }




};

class UserFactory {
public:
    virtual User* create_user(const string& name, const string& surname, const string& password) = 0;

};

class PatientFactory : public UserFactory {
public:

    User* create_user(const string& name, const string& surname, const string& password) override {

        cout << "Patient Factory" << endl;
        return new Patient(name, surname, password);

    };

};

class DoctorFactory : public UserFactory {
public:

    User* create_user(const string& name, const string& surname, const string& password) override {

        cout << "Doctor Factory" << endl;
        return new Doctor(name, surname, password);

    };

};


using namespace std;



class User {

protected:
    string name;
    string surname;
    string password;



public:





    Menu* menu;

    virtual void registration() = 0; // чисто виртуальная функция для регистрации 
    virtual void show_menu() = 0; // чисто виртуальная функция для регистрации 





    virtual ~User() {
        delete menu;
    }

    User(const string& n, const string& s, const string& p) : name(n), surname(s), password(p) {}



};


class Patient : public User {
public:

    Patient(const string& n, const string& s, const string& p) : User(n, s, p) {

        //создание обьекта меню для пациента при инициализации пациента. Реализовано в конструкторе, а не например в регистр чтобы не нарушать лог подход и метод ответсвтенности 
        menu = new PatientMenu();

    }

    void registration() override {
        cout << "Patient registration" << endl;


    }


    void show_menu() override {

        if (menu) {
            menu->show();
        }



    }


};







class Doctor : public User {
public:

    Doctor(const string& n, const string& s, const string& p) : User(n, s, p) {

        //создание меню для доктора
        menu = new PatientMenu();
    }


    void registration() override {
        cout << "Doctor registration" << endl;


    }



    void show_menu() override {


        if (menu) {
            menu->show();
        }

    }
};



class Validator {


public:

    // checking for password lenght
    static bool lenght_checker(string password) {
        if (password.length() >= 8) {

            return 1;
        }
        return 0;

    }



    //checking for digits in password
    static bool digit_checker(string password) {
        for (char ch : password) {
            if (ch >= '0' && ch <= '9') {
                return 1;
            }
        }
        return 0;
    }


    // general password checker
    static bool password_checher(string password) {

        if (lenght_checker(password) && digit_checker(password)) {
            return 1;

        }
        return 0;




    }

    // PINFL lenght checker
    static bool PINFL_lenght_checker(string PINFL) {
        if (PINFL.length() == 12) {

            return 1;
        }
        return 0;

    }


    static bool PINFL_digit_checker(string PINFL) {
        for (char ch : PINFL) {
            if (ch < '0' || ch > '9') {
                return 0;
            }
        }
        return 1;
    }

    static bool PINFL_checker(string PINFL) {
        if (PINFL_lenght_checker(PINFL) && PINFL_digit_checker(PINFL)) {

            return 1;


        }
        return 0;
    }








};


int main() {

    Registration reg;

    //указатель на обьект юзера (User* user это как int a , только принимает указатель на обьект )
    User* user = reg.start();

    if (user) {
        user->show_menu();
    }


    delete user;

    return 0;
}