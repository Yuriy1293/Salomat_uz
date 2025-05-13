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
        cout << "-----------------------------------\nWelcome to our medical application!" << endl;
        cout << "Logging in..." << endl;


        UserFactory* factory = nullptr;


        while (true) {
            cout << "~\nEnter your PINFL (12 digits)" ;
            cin >> PINFL;

            if (!Validator::PINFL_checker(PINFL)) {
                cout << "Incorrect PINFL format, please try again..." << endl;
                continue;
            }

            if (!Validator::user_exists(PINFL)) {
                cout << "User with this PINFL doesn't exist." << endl;
                continue;
            }

            cout << "Correct PINFL!" << endl;
            break;
        }

        
        while (true) {
            cout << "~\nEnter your password:";
            cin >> password;
            if (!Validator::password_checher(password)) {
                cout << "\nIncorrect password, please try again..." << endl;
                continue; }
            break;
        }

        string name, surname;
        int role;
        
        try {
            if (!Validator::pinfl_password_connected(PINFL, password, name, surname, role)) {
                cout << "\nIncorrect PINFL or password, please try again..." << endl;
                return nullptr;
            }
        }
        catch (const exception& e) {
            cout << "An error occurred during login: " << e.what() << endl;
            return nullptr;
        }

        cout << "~\n\n\t      Hello, " << name << " " << surname << endl;




        
        int roles[2]; // массив для хранения до 2-х ролей

        int found = Validator::get_roles_by_pinfl_password(PINFL, password, name, surname, roles);

        if (found == 0) {
            cout << "Incorrect PINFL or password, please try again..." << endl;
            return nullptr;
        }

        

        if (found == 1) {
            role = roles[0]; // одна подходящая роль
        }
        else {
            // Предложить пользователю выбрать между двумя ролями
            cout << "======================================\nMultiple roles found for your account:" << endl;
            cout << "1) " << (roles[0] == 1 ? "Patient" : "Doctor") << endl;
            cout << "2) " << (roles[1] == 1 ? "Patient" : "Doctor") << endl;

            int choice;
            while (true) {
                cout << "Choose the role you want to login as: ";
                cin >> choice;
                cout << "\n--------------------------------------\n";
                if (choice == 1 || choice == 2) {
                    role = roles[choice - 1];
                    break;
                }
                else {
                    cout << "Invalid choice, please try again..." << endl;
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
        cout << "\n~\nWelcome to our medical application!" << endl;






        UserFactory* factory = nullptr;

        
        
        while (true) {
			cout << "=========================================\nChoose your role:\n1) Patient\n2) Doctor\n----------------------------------------" << endl;
            cin >> choise;
            
            // добавить проверку на буквы




            
            switch (choise) {

            case 1:
                cout << "\n~\nPatient option was chosen..." << endl;
                factory = new PatientFactory();
                break;

            case 2:
                cout << "\n~\nDoctor option was chosen..." << endl;
                factory = new DoctorFactory();
                break;

            default:
                cout << "\nThere is no such option... \nPlease,choose again~" << endl << endl;
                continue;

            }
            break;
        }


      

        

        while (true) {
            cout << "Enter your PINFL (12 digits):";
            cin >> PINFL;

            if (!Validator::PINFL_checker(PINFL)) {
                cout << "Invalid PINFL format, please try again..." << endl;
                continue;
            }

            if (!Validator::user_exists_in_govermental_database(PINFL, name, surname , number)) {
                cout << "PINFL was not found in database... \nplease try again~\n";
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
                    cout << "User with this PINFL already exists, try logging in, please." << endl;
                    return nullptr;
                }
            }



            
            string confirmation_code = "3462";
            string confirmation_code_entered;

            int attemps = 0;
            while (true) {

                if (attemps > 3) {
                    cout << "Number of atemps is limeted \n please try again later~" << endl;
                    return nullptr;
                }
                cout << "Confirmation code was send to your number " << "("<<number<<")" << endl;
                cout << "Enter confirmation code: "<<"(" << confirmation_code<<")" << endl;
                cin >> confirmation_code_entered;
                if (confirmation_code_entered != confirmation_code) {
                    cout << "~\nIncorrect confirmation code\n Code was sent again..." << endl;
                    attemps++;
                    continue;
                }
                break;
            }




            cout << "~ \nNow you need to set up your password..." << endl;

            while (true) {
                cout << "Enter new password:";
                cin >> password;
                if (Validator::password_checher(password)) {
                    cout << "Correct password!\n~" << endl;

                    ofstream file("accounts.txt", ios::app);

                    if (file.is_open()) {
                        file << PINFL << " " << password << " " << name << " " << surname << " " << choise << endl;
                    }

                    break;
                }
                else {
                    cout << "~\nInvalid password, please try again..." << endl;
                }
            }

            break;
        }


        User* user = factory->create_user(name, surname, password);
        user->registration();






        return user;

    }




};