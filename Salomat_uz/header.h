#pragma once
#include <iostream>
#include"Menu.h"

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
        menu = new PatientMenu(n,s);

    }

    void registration() override {
        cout << "\tSuccessful patient registration!" << endl;


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
        menu = new DoctorMenu(n,s);
    }


    void registration() override {
        cout << "\tSuccessful doctor registration!" << endl;


    }



    void show_menu() override {


        if (menu) {
            menu->show();
        }

    }
};



