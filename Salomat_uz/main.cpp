
#include <iostream>
#include"header.h"
#include"registration.h"

using namespace std;


int main() {

    
    cout << "=============================================\n";
    cout << "|                                           |\n";
    cout << "|         Hello! Welcome to our             |\n";
    cout << "|         Medical Application!              |\n";
    cout << "|                                           |\n";
    cout << "=============================================\n" << endl;

        //указатель на обьект юзера (User* user это как int a , только принимает указатель на обьект )
    


        int choice; 
        while (true) {


            cout << "Choose an option:\n1) Registration\n2) Authorization\n3) Exit" << endl;
            cin >> choice;

            if (choice == 1) {
                Registration reg;
                User* user = reg.start();

                if (user) {
                    
                    user->show_menu();

                }
                delete user;
            }

            else if (choice == 2) {
                Autorisation aut;
                User* user = aut.start();
                if (user) {

                    user->show_menu();

                }
           
            }

            else if (choice == 3) {
                cout << "\nExit" << endl;
                break;
            }

            }

           

       
    
    

    

    return 0;
}