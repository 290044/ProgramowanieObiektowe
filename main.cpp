#include <iostream>
#include <string>

using namespace std;

int LICZBA_OSOB = 5;

void dodajOsobe(int* tabIndeks, string* tabImie, string *tabNazwisko, int indeks, string imie, string nazwisko);
void ustawObecnosc(int indeks, bool obecnosc, int *tabIndeks, bool *tabObecnosc);
void drukujListe(int* tabIndeks, string* tabImie, string* tabNazwisko, bool* tabObecnosc);
void usunOsobe(int indeks, int* tabIndeks, string* tabImie, string* tabNazwisko, bool* tabObecnosc);
void edytujOsobe(int indeks, int* tabIndeks, string* tabImie, string* tabNazwisko);



int main() {
    int indeksy[5] = {1111, 2222, 3333, 4444, 5555};
    int* tabIndeks = indeksy;
    string imiona[5] = {"Tomasz", "Patrycja", "Marek", "Katarzyna", "Piotr"};
    string* tabImie = imiona;
    string nazwiska[5] = {"Kowalski", "Nowacka", "Marciniak", "Stefaniak", "Maj"};
    string* tabNazwisko = nazwiska;
    bool obecnosci[5] = {};
    bool* tabObecnosci = obecnosci;
    bool dzialaProgram = true;

    while (dzialaProgram) {
        cout << "\n|----- MENU -----|" << endl;
        cout << "1. Wyswietl liste" << endl;
        cout << "2. Dodaj osobe" << endl;
        cout << "3. Usun osobe po indeksie" << endl;
        cout << "4. Edytuj osobe po indeksie" << endl;
        cout << "5. Zmien obecnosc" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybor: ";

        int wybor;
        cin >> wybor;

        switch (wybor) {
            case 1:
                drukujListe(tabIndeks, tabImie, tabNazwisko, tabObecnosci);
                break;
            case 2: {
                int nowyIndeks;
                string noweImie;
                string noweNazwisko;
                cout << "Podaj indeks: ";
                cin >> nowyIndeks;
                cout << "Podaj imie: ";
                cin >> noweImie;
                cout << "Podaj nazwisko: ";
                cin >> noweNazwisko;
                dodajOsobe(tabIndeks, tabImie, tabNazwisko, nowyIndeks, noweImie, noweNazwisko);
                break;
            }
            case 3: {
                int indeksDoUsuniecia;
                cout << "Podaj indeks osoby do usuniecia: ";
                cin >> indeksDoUsuniecia;
                usunOsobe(indeksDoUsuniecia, tabIndeks, tabImie, tabNazwisko, tabObecnosci);
                break;
            }
            case 4: {
                int indeksDoEdycji;
                cout << "Podaj indeks osoby do edycji: ";
                cin >> indeksDoEdycji;
                edytujOsobe(indeksDoEdycji, tabIndeks, tabImie, tabNazwisko);
                break;
            }
            case 5: {
                int indeksDoObecnosci;
                int obc;

                cout << "Podaj indeks osoby: ";
                cin >> indeksDoObecnosci;

                cout << "Obecny? (1: tak, 0: nie): ";

                cin >> obc;

                bool obecnosc = obc;

                ustawObecnosc(indeksDoObecnosci, obecnosc, tabIndeks, tabObecnosci);
                break;
            }
            case 0:
                dzialaProgram = false;
                cout << "Koniec programu." << endl;
                break;
            default:
                cout << "Niepoprawny wybor." << endl;
        }
    }

    return 0;
}

void dodajOsobe(int* tabIndeks, string* tabImie, string *tabNazwisko, int indeks, string imie, string nazwisko){
    if (indeks <= 0) {
        cout << "Indeks musi być wiekszy od 0" << endl;
        return;
    }


    for (int i = 0; i < LICZBA_OSOB; i++) {
        if (indeks == tabIndeks[i]) {
            cout << "Istnieje juz taki indeks" << endl;
            return;
        }
    }

    for (int i = 0; i < LICZBA_OSOB; i++) {
        if (tabIndeks[i] <= 0) {
            tabIndeks[i] = indeks;
            tabImie[i] = imie;
            tabNazwisko[i] = nazwisko;
            return;
        }
    }
}

void ustawObecnosc(int indeks, bool obecnosc, int *tabIndeks, bool *tabObecnosc){
    if (LICZBA_OSOB > 0) {
        for (int i = 0; i < LICZBA_OSOB; i++) {
            if (indeks == tabIndeks[i]) {
                tabObecnosc[i] = obecnosc;
                return;
            }
        }
        cout << "Nie osoby z takim indeksem" << endl;
        return;
    }

    cout << "Nie ma jest zadnej osoby na liscie" << endl;


}

void drukujListe(int* tabIndeks, string* tabImie, string* tabNazwisko, bool* tabObecnosc) {
    cout << "|--Indeks--|--Imie--|--Nazwisko--|--Obecnosc--|" << endl;

    for (int i = 0; i < LICZBA_OSOB; i++) {
        if (tabIndeks[i] <= 0)
            continue;

        string obStr = tabObecnosc[i] ? "TAK" : "NIE";
        cout << "|--" << tabIndeks[i] << "--|--" << tabImie[i] << "--|--" << tabNazwisko[i] << "--|--" << obStr << "--|" << endl;
    }
}

void usunOsobe(int indeks, int* tabIndeks, string* tabImie, string* tabNazwisko, bool* tabObecnosc) {
    for (int i = 0; i < LICZBA_OSOB; i++) {
        if (indeks == tabIndeks[i]) {
            for (int j = i; j < LICZBA_OSOB - 1; j++) {
                tabIndeks[j] = tabIndeks[j + 1];
                tabImie[j] = tabImie[j + 1];
                tabNazwisko[j] = tabNazwisko[j + 1];
                tabObecnosc[j] = tabObecnosc[j + 1];
            }

            tabIndeks[LICZBA_OSOB - 1] = -1;
            tabImie[LICZBA_OSOB - 1] = "";
            tabNazwisko[LICZBA_OSOB - 1] = "";
            tabObecnosc[LICZBA_OSOB - 1] = false;
            return;
        }
    }

    cout << "Nie ma osoby o takim indeksie." << endl;
}

void edytujOsobe(int indeks, int *tabIndeks, string *tabImie, string *tabNazwisko) {
    for (int i = 0; i < LICZBA_OSOB; i++) {
        if (indeks == tabIndeks[i]) {
            cout << "Co chcesz edytowac?" << endl;
            cout << "1: indeks" << endl;
            cout << "2: Imie" << endl;
            cout << "3: Nazwisko" << endl;
            int choice;
            cin >> choice;


            switch (choice) {
                case 1:
                    cout << "Podaj Indeks: ";
                    cin >> tabIndeks[i];
                    cout << endl;
                    break;
                case 2:
                    cout << "Podaj Imie: ";
                    cin >> tabImie[i];
                    cout << endl;
                    break;

                case 3:
                    cout << "Podaj Nazwisko: ";
                    cin >> tabNazwisko[i];
                    cout << endl;
                    break;
            }
        } else {
            cout << "Nie ma takiego indeksu" << endl;
        }
    }


}