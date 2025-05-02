#pragma once
// this class is created for checkers

#include <iostream>
using namespace std;

class Validator {


public:

    
    
    // проверка на пароль и пинфл связаны с юзером пидором
    static bool pinfl_password_connected(const string &PINFL , const string &password ,  string& name , string& surname , int&role) {

        ifstream file("accounts.txt");

        if (!file.is_open()) {
            cout << "Error with opening file" << endl;
            return false;
        }

        string stored_pinfl, stored_password , stored_name , stored_surname;
        int stored_role;
        while (file >> stored_pinfl >> stored_password >> stored_name >> stored_surname >> stored_role) {
            if (stored_pinfl == PINFL && stored_password == password) {
                name = stored_name;
                surname = stored_surname;
                role = stored_role;

                return true;
            }

        }
        return false;
    }
   

    
    // проыерка на наличие юзера в приложении учитывая роль 
    static bool user_exists_with_role(const string &PINFL , int role) {

        ifstream file("accounts.txt");

        string stored_pinfl, stored_password , stored_name, stored_surname;
        int stored_role;
        if (file.is_open()) {

           
            while (file >> stored_pinfl >> stored_password >> stored_name >> stored_surname >> stored_role) {

                if (stored_pinfl == PINFL && stored_role == role ) {
                    return true ;
                }
                
                
            }

        }
        return false;

    }
    
    
    static bool user_exists(const string& PINFL) {

        ifstream file("accounts.txt");

        string stored_pinfl, stored_password, stored_name, stored_surname;
        int stored_role;
        if (file.is_open()) {


            while (file >> stored_pinfl >> stored_password >> stored_name >> stored_surname >> stored_role) {

                if (stored_pinfl == PINFL ) {
                    return true;
                }


            }

        }
        return false;

    }






    static bool has_unset_password(const string& PINFL, int role) {
        ifstream file("accounts.txt");
        string stored_pinfl, stored_password, stored_name, stored_surname;
        int stored_role;

        while (file >> stored_pinfl >> stored_password >> stored_name >> stored_surname >> stored_role) {
            if (stored_pinfl == PINFL && stored_role == role && stored_password == "_") {
                return true;
            }
        }
        return false;
    }





    static bool user_exists_in_govermental_database(const string& PINFL, string& name, string& surname) {
        ifstream file("gov_database.txt");

        string stored_pinfl, stored_name, stored_surname;
        

        if (file.is_open()) {
            while (file >> stored_pinfl >> stored_name >> stored_surname) {
                if (stored_pinfl == PINFL) {
                    name = stored_name;
                    surname = stored_surname;
                    return true;
                }
            }
        }

        return false;
    }








    
    
    static int get_roles_by_pinfl_password(const string& pinfl, const string& password, string& name, string& surname, int roles[2]) {
        ifstream file("accounts.txt");
        string file_pinfl, file_password, file_name, file_surname;
        int file_role;
        int found = 0;

        while (file >> file_pinfl >> file_password >> file_name >> file_surname >> file_role) {
            if (file_pinfl == pinfl && file_password == password) {
                // Сохраняем имя/фамилию только из первой подходящей строки
                if (found == 0) {
                    name = file_name;
                    surname = file_surname;
                    roles[found++] = file_role;
                }
                // Проверка, что новая роль ещё не записана
                else if (found == 1 && file_role != roles[0]) {
                    roles[found++] = file_role;
                }

                if (found == 2) break; // достаточно двух ролей
            }
        }

        return found; // 0, 1 или 2 — сколько разных ролей найдено
    }



    
    
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