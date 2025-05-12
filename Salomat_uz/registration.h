#pragma once
#include <iostream>
#include"User_fabrics.h"
#include<string>
#include"Validator.h"
using namespace std;







class Autorisation {

protected:
    string PINFL, password;

public:
    User* start() {

        int choise;
        cout << "Autorisation" << endl;
        cout << "Welcome to our medical application!" << endl;


        UserFactory* factory = nullptr;


        while (true) {
            cout << "Enter your PINFL (12 digits)" << endl;
            cin >> PINFL;

            if (!Validator::PINFL_checker(PINFL)) {
                cout << "Incorrect PINFL format, please try again." << endl;
                continue;
            }

            if (!Validator::user_exists(PINFL)) {
                cout << "User with this PINFL doesn't exist." << endl;
                continue;
            }

            cout << "Correct PINFL." << endl;
            break;
        }

        
        while (true) {
            cout << "Enter your password" << endl;
            cin >> password;
            if (!Validator::password_checher(password)) {
                cout << "Incorrect password." << endl;
                continue; }
            break;
        }

        string name, surname;
        int role;
        if (!Validator::pinfl_password_connected(PINFL, password ,name , surname, role)) {
            cout << "There is no such user with this PINFL or password" << endl;
            return nullptr;
        }
        cout << "Hello, " << name << " " << surname << endl;




        
        int roles[2]; // массив для хранения до 2-х ролей

        int found = Validator::get_roles_by_pinfl_password(PINFL, password, name, surname, roles);

        if (found == 0) {
            cout << "There is no such user with this PINFL and password." << endl;
            return nullptr;
        }

        

        if (found == 1) {
            role = roles[0]; // одна подходящая роль
        }
        else {
            // Предложить пользователю выбрать между двумя ролями
            cout << "Multiple roles found for your account:" << endl;
            cout << "1) " << (roles[0] == 1 ? "Patient" : "Doctor") << endl;
            cout << "2) " << (roles[1] == 1 ? "Patient" : "Doctor") << endl;

            int choice;
            while (true) {
                cout << "Choose the role you want to login as: ";
                cin >> choice;
                if (choice == 1 || choice == 2) {
                    role = roles[choice - 1];
                    break;
                }
                else {
                    cout << "Invalid choice. Try again." << endl;
                }
            }
        }






        if (role == 1) {
            factory = new PatientFactory();
        }
        else if (role == 2) {
            factory = new DoctorFactory();
        }
        else {
            cout << "Unknown role. Contact administrator." << endl;
            return nullptr;
        }

        User* user = factory->create_user(name, surname,password);
        user->registration();
        delete factory;

        return user;


    }
    
};





class Registration {

protected:
    string name, surname, password, PINFL;
    string number;

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


      

        

        while (true) {
            cout << "Enter your PINFL (12 digits)" << endl;
            cin >> PINFL;

            if (!Validator::PINFL_checker(PINFL)) {
                cout << "Incorrect PINFL format" << endl;
                continue;
            }

            if (!Validator::user_exists_in_govermental_database(PINFL, name, surname , number)) {
                cout << "This PINFL does not exist in the governmental database\n";
                continue;
            }

            if (Validator::user_exists_with_role(PINFL, choise)) {

                if (Validator::has_unset_password(PINFL, choise)) {
                    cout << "Hello " << name << " " << surname << ". Please set your password: \n";
                    cin >> password;

                    // перезапись accounts.txt с новым паролем
                    ifstream infile("accounts.txt");
                    ofstream temp("temp.txt");
                    string stored_pinfl, stored_password, stored_name, stored_surname;
                    int stored_role;

                    while (infile >> stored_pinfl >> stored_password >> stored_name >> stored_surname >> stored_role) {
                        if (stored_pinfl == PINFL && stored_role == choise) {
                            temp << stored_pinfl << " " << password << " " << stored_name << " " << stored_surname << " " << stored_role << endl;
                        }
                        else {
                            temp << stored_pinfl << " " << stored_password << " " << stored_name << " " << stored_surname << " " << stored_role << endl;
                        }
                    }

                    infile.close();
                    temp.close();
                    remove("accounts.txt");
                    rename("temp.txt", "accounts.txt");

                    cout << "Registration completed.\n";
                    break;
                }
                else {
                    cout << "User with this PINFL has already exists. Please , go to autorisation" << endl;
                    return nullptr;
                }
            }

            cout << "Now you need to set up your passwort" << endl;

            while (true) {
                cout << "Enter new password" << endl;
                cin >> password;
                if (Validator::password_checher(password)) {
                    cout << "Correct password" << endl;

                    ofstream file("accounts.txt", ios::app);

                    if (file.is_open()) {
                        file << PINFL << " " << password << " " << name << " " << surname << " " << choise << endl;
                    }

                    break;
                }
                else {
                    cout << "Incorrect password, please , try again" << endl;
                }
            }

            break;
        }


        User* user = factory->create_user(name, surname, password);
        user->registration();






        return user;

    }




};