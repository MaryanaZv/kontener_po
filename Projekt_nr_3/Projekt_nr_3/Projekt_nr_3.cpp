#include <iostream>
#include "Kontener.h"

using namespace std;

void print_menu() {
    system("cls");
    cout << "Co trzeba zrobic?" << endl;
    cout << " " << endl;
    cout << "1. Dodac nowy obiekt do kontenera." << endl;
    cout << " " << endl;
    cout << "2. Usunac obiekt z kontenera." << endl;
    cout << " " << endl;
    cout << "3. Prodemonstrowac dzialanie operatora przypisania." << endl;
    cout << " " << endl;
    cout << "4. Prodemonstrowac dzialanie operatora porownania." << endl;
    cout << " " << endl;
    cout << "5. Prodemonstrowac dzialanie operatora indeksowania." << endl;
    cout << " " << endl;
    cout << "6. Prodemonstrowac dzialanie operatora dodawania." << endl;
    cout << " " << endl;
    cout << "7. Zakoncz." << endl;
    cout << " " << endl;
    cout << "Prosze napisac numer i nacisnac enter > ";
}

int main() {
    Kontener<int> kont;

    kont.dodajElem(10, 0);
    kont.dodajElem(20, 1);
    kont.dodajElem(30, 2);
    kont.dodajElem(40, 3);

    Kontener<int> kont2;

    kont2.dodajElem(10, 0);
    kont2.dodajElem(20, 1);
    kont2.dodajElem(30, 2);
    kont2.dodajElem(40, 3);
    //   kont2.dodajElem(50, 4);

    Kontener <int> kont3;

    int variant;

    do {
        print_menu();

        cin >> variant;
        cin.clear();
        cin.ignore(7777, '\n');

        switch (variant) {
        case 1:
            cout << "\nAktualna zawartosc kontenera: " << endl;

            for (int i = 0; i < kont.GetSize(); i++) {
                cout << kont[i] << endl;
            }

            try {
                kont.DodajElementMenu();
            }
            catch (invalid_argument i) {
                cout << "Wyjatek: " << i.what() << endl;
            }

            cout << "\nZawartosc kontenera: " << endl;

            for (int i = 0; i < kont.GetSize(); i++) {
                cout << kont[i] << endl;
            }
            break;

        case 2:
            cout << "\nAktualna zawartosc kontenera: " << endl;

            for (int i = 0; i < kont.GetSize(); i++) {
                cout << kont[i] << endl;
            }

            try {
                kont.WyrzucElementMenu();
            }
            catch (exception e) {
                cout << "Wyjatek: " << e.what() << endl;
            }

            cout << "\nZawartosc kontenera: " << endl;

            for (int i = 0; i < kont.GetSize(); i++) {
                cout << kont[i] << endl;
            }
            break;

        case 3:
            kont3 = kont;

            cout << "Zawartosc kontenera kont3 po przypisaniu: " << endl;

            for (int i = 0; i < kont3.GetSize(); i++) {
                cout << kont3[i] << endl;
            }
            break;

        case 4:
            kont.operator==(kont2);
            break;

        case 5:
            try {
                cout << kont[0] << endl;
                cout << kont[1] << endl;
                cout << kont[2] << endl;
                cout << kont[-4] << endl;
            }
            catch (string s) {
                cout << "Nieprawidlowy index: " << s << endl;
            }
            break;

        case 6:
            kont.operator+=(kont2);

            for (int i = 0; i < kont.GetSize(); i++) {
                cout << kont[i] << endl;
            }
            break;

        case 7:
            break;

        default:
            cout << "Wprowadzony numer jest zly, nie ma takiego polecenia." << endl;

        } if (variant != 7)
            system("pause");

    } while (variant != 7);

    return 0;
}