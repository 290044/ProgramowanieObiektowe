#include <iostream>
#include <string>

using namespace std;

const int MAX_PERSON_COUNT = 10;
const int MAX_LISTS_COUNT = 5;

class Person {
private:
    int index;
    string firstname;
    string lastname;

public:
    Person() : index(-1), firstname(""), lastname("") {
    }

    Person(int newIndex, const string& newFirstName, const string& newLastName) : index(-1), firstname(""), lastname("") {
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

    void ClearData() {
        index = -1;
        firstname = "";
        lastname = "";
    }
};

class PresentsList{
    private:
        bool* presentsArray;
        Person* peopleList;

    public:
        PresentsList(): presentsArray(new bool[MAX_PERSON_COUNT]), peopleList(new Person[MAX_PERSON_COUNT]) {
            for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                presentsArray[i] = false;
            }
        }
        PresentsList(bool newPresentsArray[], Person* newPeopleList){
            setPeopleList(newPeopleList);
            setPresentsArray(newPresentsArray);
        }

        void setPeopleList(Person* newPeopleList){
            peopleList = newPeopleList;
        }

        void setPresentsArray(bool* newPresentsArray){
            presentsArray = newPresentsArray;
        }

        void addPerson(int index, const string& fistName, const string& lastName){
            if (index <= 0) {
                cout << "Indeks musi byc wiekszy od 0" << endl;
                return;
            }


            for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                if (index == peopleList[i].GetIndex()) {
                    cout << "Istnieje juz taki indeks" << endl;
                    return;
                }
            }

            for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                if (peopleList[i].GetIndex() <= 0) {
                    peopleList[i].SetIndex(index);
                    peopleList[i].SetFirstname(fistName);
                    peopleList[i].SetLastname(lastName);
                    presentsArray[i] = false;
                    return;
                }
            }

            cout << "Lista jest pelna, nie mozna dodac kolejnej osoby" << endl;
        }

        void updatePresence(int index, bool isPresent){
            if (MAX_PERSON_COUNT > 0) {
                for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                    if (index == peopleList[i].GetIndex()) {
                        presentsArray[i] = isPresent;
                        return;
                    }
                }
                cout << "Nie osoby z takim indeksem" << endl;
                return;
            }

            cout << "Nie ma jest zadnej osoby na liscie" << endl;


        }

        void printList() {
            cout << "|--Indeks--|--Imie--|--Nazwisko--|--Obecnosc--|" << endl;

            for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                if (peopleList[i].GetIndex() <= 0)
                    continue;

                string obStr = presentsArray[i] ? "TAK" : "NIE";
                cout << "|--" << peopleList[i].GetIndex() << "--|--" << peopleList[i].GetFirstName() << "--|--" << peopleList[i].GetLastName() << "--|--" << obStr << "--|" << endl;
            }
        }

        void deletePersonByIndex(int index) {
            for (int i = 0; i < MAX_PERSON_COUNT; i++) {
                if (index == peopleList[i].GetIndex()) {
                    for (int j = i; j < MAX_PERSON_COUNT - 1; j++) {
                        peopleList[j] = peopleList[j + 1];
                        presentsArray[j] = presentsArray[j + 1];
                    }

                    peopleList[MAX_PERSON_COUNT - 1].ClearData();
                    presentsArray[MAX_PERSON_COUNT - 1] = false;
                    return;
                }
            }

            cout << "Nie ma osoby o takim indeksie." << endl;
        }

        void editPersonByIndex(int index) {
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
};


class UserInterface{
    private:
        PresentsList *arrayOfLists;
        int listCount;
    
    public:
        UserInterface(): arrayOfLists(new PresentsList[MAX_LISTS_COUNT]), listCount(0) {}

        UserInterface(PresentsList *newArrayOfLists, int newListCount){
            arrayOfLists = newArrayOfLists;
            listCount = newListCount;
        }

        void listMenuLoop(int listIndex) {
            bool listMenuWorks = true;

            while (listMenuWorks) {
                cout << "\n|----- MENU LISTY " << listIndex << " -----|" << endl;
                cout << "1. Wyswietl liste" << endl;
                cout << "2. Dodaj osobe" << endl;
                cout << "3. Usun osobe po indeksie" << endl;
                cout << "4. Edytuj osobe po indeksie" << endl;
                cout << "5. Zmien obecnosc" << endl;
                cout << "0. Powrot" << endl;
                cout << "Wybor: ";

                int choiceNumber;
                cin >> choiceNumber;

                switch (choiceNumber) {
                    case 1:
                        arrayOfLists[listIndex].printList();
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
                        arrayOfLists[listIndex].addPerson(nowyIndeks, noweImie, noweNazwisko);
                        break;
                    }
                    case 3: {
                        int indeksDoUsuniecia;
                        cout << "Podaj indeks osoby do usuniecia: ";
                        cin >> indeksDoUsuniecia;
                        arrayOfLists[listIndex].deletePersonByIndex(indeksDoUsuniecia);
                        break;
                    }
                    case 4: {
                        int indeksDoEdycji;
                        cout << "Podaj indeks osoby do edycji: ";
                        cin >> indeksDoEdycji;
                        arrayOfLists[listIndex].editPersonByIndex(indeksDoEdycji);
                        break;
                    }
                    case 5: {
                        int indeksDoObecnosci;
                        int obc;

                        cout << "Podaj indeks osoby: ";
                        cin >> indeksDoObecnosci;

                        cout << "Obecny? (1: tak, 0: nie): ";
                        cin >> obc;

                        bool obecnosc = (obc != 0);
                        arrayOfLists[listIndex].updatePresence(indeksDoObecnosci, obecnosc);
                        break;
                    }
                    case 0:
                        listMenuWorks = false;
                        break;
                    default:
                        cout << "Niepoprawny wybor." << endl;
                }
            }
        }

        void loop(){
            bool programWorks = true;

            while (programWorks) {
                cout << "\n|----- MENU GLOWNE -----|" << endl;
                if(listCount > 1){
                    cout << "1. Wybierz liste po indeksie" << endl;
                } else{
                    cout << "1. Wybierz pierwsza liste" << endl;
                }
                cout << "2. Dodaj nowa liste" << endl;
                cout << "0. Wyjscie" << endl;
                cout << "Wybor: ";

                int choiceNumber;
                cin >> choiceNumber;

                switch (choiceNumber) {
                    case 1: {
                        int selectedListIndex = 0;
                        if (listCount > 1){
                            cout << "Podaj indeks listy (0-" << listCount - 1 << "): ";
                            cin >> selectedListIndex;

                            if (selectedListIndex < 0 || selectedListIndex >= listCount) {
                                cout << "Niepoprawny indeks listy." << endl;
                                continue;
                            }
                        }

                        listMenuLoop(selectedListIndex);
                        break;
                    }
                    case 2: {
                        int newListIndex = listCount;

                        if (newListIndex >= MAX_LISTS_COUNT) {
                            cout << "Brak wolnego miejsca na nowa liste." << endl;
                            break;
                        }

                        listCount++;
                        cout << "Dodano nowa liste o indeksie " << newListIndex << "." << endl;
                        listMenuLoop(newListIndex);
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
        }
};

int main() {
    Person personArray[MAX_PERSON_COUNT] = {
        Person(1111, "Tomasz", "Kowalski"),
        Person(2222, "Patrycja", "Nowacka"),
        Person(3333, "Marek", "Marciniak"),
        Person(4444, "Katarzyna", "Stefaniak"),
        Person(5555, "Piotr", "Maj")
    };
    bool presenceArray[MAX_PERSON_COUNT] = {false, false, false, false, false, false, false, false, false, false};

    PresentsList arrayOfLists[MAX_LISTS_COUNT];
    int listCount = 1;

    arrayOfLists[0].setPeopleList(personArray);
    arrayOfLists[0].setPresentsArray(presenceArray);

    UserInterface ui(arrayOfLists, listCount);
    ui.loop();

    return 0;
}