#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Person {
protected:
    int index;
    string firstname;
    string lastname;
    bool isPresent;

public:
    Person() : index(-1), firstname(""), lastname(""), isPresent(false) {}

    Person(int newIndex, const string& newFirstName, const string& newLastName)
        : index(-1), firstname(""), lastname(""), isPresent(false) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void SetPresence(bool newPresence) { 
        isPresent = newPresence; 
    }

    void SetIndex(int newIndex) { 
        if (newIndex > 0) 
            index = newIndex; 
    }
    void SetFirstname(const string& newFirstName) { 
        if (newFirstName.length() > 1) 
            firstname = newFirstName; 
    }
    void SetLastname(const string& newLastName) { 
        if (newLastName.length() > 1) 
            lastname = newLastName; 
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

    bool GetPresence() const {
        return isPresent;
    }

    void ClearData() { 
        index = -1; firstname = ""; lastname = ""; isPresent = false;
    }

    virtual void PrintData(bool showPresence = false) {
        cout << firstname << " " << lastname << " " << (showPresence ? (isPresent ? "Tak" : "Nie") : "") << endl;
    }
};


class ISerializable {
public:
    virtual string Serialize() = 0;
};

class PresentList : public ISerializable {

private:
    Person* people[100];
    int count;

public:
    PresentList() : count(0) {}

    void Add(Person* person) {
        if (person != nullptr && count < 100) {
            people[count++] = person;
        }
    }

    void SetList(Person* person[], int size) {
        for (int i = 0; i < size && count < 100; i++) {
            if (person[i] != nullptr) {
                people[count++] = person[i];
            }
        }
    }

    void Show() {
        cout << "|--Indeks--|--Imie--|--Nazwisko--|--Obecny--|\n";
        for (int i = 0; i < count; i++) {
            if (people[i] != nullptr) {
                people[i]->PrintData(true);
            }
        }
    }

    string Serialize() override {
        string result = "|--Indeks--|--Imie--|--Nazwisko--|--Obecny--|\n";

            for (int i = 0; i < count; i++) {
                if (people[i]->GetIndex() <= 0)
                    continue;

                result += "|--" + to_string(people[i]->GetIndex()) + "--|--" + people[i]->GetFirstName() + "--|--" + people[i]->GetLastName() + "--|" + (people[i]->GetPresence() ? "Tak" : "Nie") + "|\n";
            }
        return result;
    }
};

class Student : public Person, public ISerializable {
public:
    Student() {}

    Student(int newIndex, const string& newFirstName, const string& newLastName) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void PrintData(bool showPresence = false) override {
        cout << "Student: " << firstname << " " << lastname << " " << (showPresence ? (isPresent ? "Tak" : "Nie") : "") << endl;
    }

    string Serialize() override {
        return "Nazywam sie: " + firstname + " " + lastname + " i jestem studentem dziennym";
    }
};

class Employee : public Person, public ISerializable {
public:
    Employee() {}

    Employee(int newIndex, const string& newFirstName, const string& newLastName) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void PrintData(bool showPresence = false) override {
        cout << "Employee: " << firstname << " " << lastname << " " << (showPresence ? (isPresent ? "Tak" : "Nie") : "") << endl;
    }

    string Serialize() override {
        return "Nazywam sie: " + firstname + " " + lastname + " i jestem pracownikiem";
    }
};

class PartTimeStudent : public Student {
public:
    PartTimeStudent() {}

    PartTimeStudent(int newIndex, const string& newFirstName, const string& newLastName)
        : Student(newIndex, newFirstName, newLastName) {}

    void PrintData(bool showPresence = false) override {
        cout << "Student zaoczny: " << firstname << " " << lastname << " " << (showPresence ? (isPresent ? "Tak" : "Nie") : "") << endl;
    }

    string Serialize() override {
        return "Nazywam sie: " + firstname + " " + lastname + " i jestem studentem zaocznym";
    }
};

class UI{
    private:
        Person* tab[100];
        int tabSize;
        PresentList presentList;
        
    public:
        UI() : tabSize(0) {}
        
        void ShowMenu();
        void ShowObjects(Person* tab[], int size);
        void ShowAttendance(Person* tab[], int size);
        void saveToFile(ISerializable* object);
        void AddPerson();
        void SetPresence();
        void SaveAttendanceToFile();
    };

void UI::ShowObjects(Person* tab[], int size) {
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        tab[i]->PrintData();
    }
}

void UI::ShowAttendance(Person* tab[], int size) {
    PresentList attendance;
    for (int i = 0; i < size; i++) {
        attendance.Add(tab[i]);
    }
    attendance.Show();
}

void UI::saveToFile(ISerializable* object) {
    ofstream file("output.txt", ios::binary);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }

    file << object->Serialize();
    file.close();

    cout << "Saving to file: " << object->Serialize() << endl;
    
}

void UI::AddPerson() {
    if (tabSize >= 100) {
        cout << "Nie mozna dodac wiecej osob!" << endl;
        return;
    }

    int index;
    string firstname, lastname;
    int type;

    cout << "\n--- DODAJ OSOBE ---\n";
    cout << "Wprowadz indeks: ";
    cin >> index;
    cin.ignore();

    cout << "Wprowadz imie: ";
    getline(cin, firstname);

    cout << "Wprowadz nazwisko: ";
    getline(cin, lastname);

    cout << "\nWybierz typ:\n";
    cout << "1. Osoba (nie zwiazana z uczelnia)\n";
    cout << "2. Student\n";
    cout << "3. Pracownik\n";
    cout << "4. Student zaoczny\n";
    cout << "Wybor: ";
    cin >> type;

    Person* newPerson = nullptr;
    switch (type) {
        case 1:
            newPerson = new Person(index, firstname, lastname);
            break;
        case 2:
            newPerson = new Student(index, firstname, lastname);
            break;
        case 3:
            newPerson = new Employee(index, firstname, lastname);
            break;
        case 4:
            newPerson = new PartTimeStudent(index, firstname, lastname);
            break;
        default:
            cout << "Nieprawidlowy typ." << endl;
            return;
    }

    tab[tabSize++] = newPerson;
    presentList.Add(newPerson);
    cout << "Osoba zostala dodana pomyslnie!" << endl;
}

void UI::SetPresence() {
    if (tabSize == 0) {
        cout << "Brak osob na liscie!" << endl;
        return;
    }

    cout << "\n--- USTAW STATUS OBECNOSCI ---\n";
    ShowObjects(tab, tabSize);

    cout << "\nWybierz osobe (numer): ";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= tabSize) {
        cout << "Obecna? (1-Tak, 0-Nie): ";
        int presence;
        cin >> presence;
        tab[choice - 1]->SetPresence(presence == 1);
        cout << "Status obecnosci zmieniony!" << endl;
    } else {
        cout << "Nieprawidlowy wybor." << endl;
    }
}


void UI::SaveAttendanceToFile() {
    ofstream file("output.txt", ios::binary);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }

    file << presentList.Serialize();
    file.close();

    cout << "Lista obecnosci zapisana do pliku!" << endl;
}

void UI::ShowMenu() {
    Person person1(1111, "Jan",  "Kowalski");
    Student student1(2222, "Filip", "Winkler");
    Employee employee1(3333, "Piotr", "Wisniewski");
    PartTimeStudent partTimeStudent1(4444, "Robert", "Lewandowski");

    tab[0] = &person1;
    tab[1] = &student1;
    tab[2] = &employee1;
    tab[3] = &partTimeStudent1;
    tabSize = 4;

    presentList.SetList(tab, 4);

    int choice = -1;
    while (choice != 0) {
        cout << "\n--- MENU ---\n";
        cout << "1. Wyswietl Ludzi\n";
        cout << "2. Wyswietl liste obecnosci\n";
        cout << "3. Ustaw status obecnosci\n";
        cout << "4. Dodaj osobe\n";
        cout << "5. Zapisz osobe do pliku\n";
        cout << "6. Zapisz liste obecnosci do pliku \n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        if (choice == 1) {
            ShowObjects(tab, tabSize);
        } else if (choice == 2) {
            ShowAttendance(tab, tabSize);
        } else if (choice == 3) {
            SetPresence();
        } else if (choice == 4) {
            AddPerson();
        } else if (choice == 5) {
            int objChoice;
            cout << "Wybierz osobe (1-" << tabSize << "): ";
            cin >> objChoice;

            if (objChoice >= 1 && objChoice <= tabSize) {
                ISerializable* serializableObj = dynamic_cast<ISerializable*>(tab[objChoice - 1]);
                if (serializableObj) {
                    saveToFile(serializableObj);
                } else {
                    cout << "Wybrany obiekt nie jest serializowalny." << endl;
                }
            } else {
                cout << "Nieprawidlowy wybor obiektu." << endl;
            }
        } else if (choice == 6) {
            SaveAttendanceToFile();
        } else if (choice != 0) {
            cout << "Nieprawidlowy wybor.\n";
        }
    }
}


int main() {
    UI ui;
    ui.ShowMenu();

    return 0;
}