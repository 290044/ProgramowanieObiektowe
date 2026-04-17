#include <iostream>
#include <string>

using namespace std;

const int MAX_PERSON_COUNT = 10;

class Person {
private:
    int index;
    string firstname;
    string lastname;
    bool isPresent;

public:
    Person() : index(-1), firstname(""), lastname(""), isPresent(false) {
    }

    Person(int newIndex, const string& newFirstName, const string& newLastName) : index(-1), firstname(""), lastname(""), isPresent(false) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void SetIndex(int newIndex) {
        if (newIndex > 0) {
            index = newIndex;
        }
    }

    void SetFirstname(const string& newFirstName) {
        if (newFirstName.length() > 1) {
            firstname = newFirstName;
        }
    }

    void SetLastname(const string& newLastName) {
        if (newLastName.length() > 1) {
            lastname = newLastName;
        }
    }

    int GetIndex() const {
        return index;
    }

    string GetFirstName() const {
        return firstname;
    }

    string GetLastName() const {
        return lastname;
    }

    void SetPresence(bool newPresence) {
        isPresent = newPresence;
    }

    bool GetPresence() const {
        return isPresent;
    }

    void ClearData() {
        index = -1;
        firstname = "";
        lastname = "";
        isPresent = false;
    }
};

void addPerson(Person* tabOsob, int indeks, const string& imie, const string& nazwisko);
void updatePresence(int index, bool obecnosc, Person* tabOsob);
void printList(Person* tabOsob);
void deletePersonByIndex(int indeks, Person* tabOsob);
void editPersonByIndex(int indeks, Person* tabOsob);



int main() {
    Person personArray[MAX_PERSON_COUNT] = {
        Person(1111, "Tomasz", "Kowalski"),
        Person(2222, "Patrycja", "Nowacka"),
        Person(3333, "Marek", "Marciniak"),
        Person(4444, "Katarzyna", "Stefaniak"),
        Person(5555, "Piotr", "Maj")
    };
    Person* personList = personArray;
    bool programWorks = true;

    while (programWorks) {
        cout << "\n|----- MENU -----|" << endl;
        cout << "1. Wyswietl liste" << endl;
        cout << "2. Dodaj osobe" << endl;
        cout << "3. Usun osobe po indeksie" << endl;
        cout << "4. Edytuj osobe po indeksie" << endl;
        cout << "5. Zmien obecnosc" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybor: ";

        int choiceNumber;
        cin >> choiceNumber;

        switch (choiceNumber) {
            case 1:
                printList(personList);
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
                addPerson(personList, nowyIndeks, noweImie, noweNazwisko);
                break;
            }
            case 3: {
                int indeksDoUsuniecia;
                cout << "Podaj indeks osoby do usuniecia: ";
                cin >> indeksDoUsuniecia;
                deletePersonByIndex(indeksDoUsuniecia, personList);
                break;
            }
            case 4: {
                int indeksDoEdycji;
                cout << "Podaj indeks osoby do edycji: ";
                cin >> indeksDoEdycji;
                editPersonByIndex(indeksDoEdycji, personList);
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

                updatePresence(indeksDoObecnosci, obecnosc, personList);
                break;
            }
            case 0:
                programWorks = false;
                cout << "Koniec programu." << endl;
                break;
            default:
                cout << "Niepoprawny wybor." << endl;
        }
    }

    return 0;
}


void addPerson(Person* tabOsob, int indeks, const string& imie, const string& nazwisko){
    if (indeks <= 0) {
        cout << "Indeks musi byc wiekszy od 0" << endl;
        return;
    }


    for (int i = 0; i < MAX_PERSON_COUNT; i++) {
        if (indeks == tabOsob[i].GetIndex()) {
            cout << "Istnieje juz taki indeks" << endl;
            return;
        }
    }

    for (int i = 0; i < MAX_PERSON_COUNT; i++) {
        if (tabOsob[i].GetIndex() <= 0) {
            tabOsob[i].SetIndex(indeks);
            tabOsob[i].SetFirstname(imie);
            tabOsob[i].SetLastname(nazwisko);
            return;
        }
    }

    cout << "Lista jest pelna, nie mozna dodac kolejnej osoby" << endl;
}

void updatePresence(int index, bool isPresent, Person* peopleList){
    if (MAX_PERSON_COUNT > 0) {
        for (int i = 0; i < MAX_PERSON_COUNT; i++) {
            if (index == peopleList[i].GetIndex()) {
                peopleList[i].SetPresence(isPresent);
                return;
            }
        }
        cout << "Nie osoby z takim indeksem" << endl;
        return;
    }

    cout << "Nie ma jest zadnej osoby na liscie" << endl;


}

void printList(Person* tabOsob) {
    cout << "|--Indeks--|--Imie--|--Nazwisko--|--Obecnosc--|" << endl;

    for (int i = 0; i < MAX_PERSON_COUNT; i++) {
        if (tabOsob[i].GetIndex() <= 0)
            continue;

        string obStr = tabOsob[i].GetPresence() ? "TAK" : "NIE";
        cout << "|--" << tabOsob[i].GetIndex() << "--|--" << tabOsob[i].GetFirstName() << "--|--" << tabOsob[i].GetLastName() << "--|--" << obStr << "--|" << endl;
    }
}

void deletePersonByIndex(int indeks, Person* tabOsob) {
    for (int i = 0; i < MAX_PERSON_COUNT; i++) {
        if (indeks == tabOsob[i].GetIndex()) {
            for (int j = i; j < MAX_PERSON_COUNT - 1; j++) {
                tabOsob[j] = tabOsob[j + 1];
            }

            tabOsob[MAX_PERSON_COUNT - 1].ClearData();
            return;
        }
    }

    cout << "Nie ma osoby o takim indeksie." << endl;
}

void editPersonByIndex(int index, Person* peopleList) {
    for (int i = 0; i < MAX_PERSON_COUNT; i++) {
        if (index == peopleList[i].GetIndex()) {
            cout << "Co chcesz edytowac?" << endl;
            cout << "1: indeks" << endl;
            cout << "2: Imie" << endl;
            cout << "3: Nazwisko" << endl;
            int choice;
            cin >> choice;


            switch (choice) {
                case 1:
                    cout << "Podaj Indeks: ";
                    {
                        int nowyIndeks;
                        cin >> nowyIndeks;
                        peopleList[i].SetIndex(nowyIndeks);
                    }
                    cout << endl;
                    break;
                case 2:
                    cout << "Podaj Imie: ";
                    {
                        string noweImie;
                        cin >> noweImie;
                        peopleList[i].SetFirstname(noweImie);
                    }
                    cout << endl;
                    break;

                case 3:
                    cout << "Podaj Nazwisko: ";
                    {
                        string noweNazwisko;
                        cin >> noweNazwisko;
                        peopleList[i].SetLastname(noweNazwisko);
                    }
                    cout << endl;
                    break;
            }
            return;
        }
    }

    cout << "Nie ma takiego indeksu" << endl;

}