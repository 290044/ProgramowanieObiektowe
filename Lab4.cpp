#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    int index;
    string firstname;
    string lastname;

public:
    Person() : index(-1), firstname(""), lastname("") {}

    Person(int newIndex, const string& newFirstName, const string& newLastName)
        : index(-1), firstname(""), lastname("") {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
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

    void ClearData() { 
        index = -1; firstname = ""; lastname = ""; 
    }

    virtual void PrintData() {
        cout << "Person: " << firstname << " " << lastname << endl;
    }
};

class IIntroduceable {
public:
    virtual string IntroduceYourself() = 0;
};

class Student : public Person, public IIntroduceable {
public:
    Student() {}

    Student(int newIndex, const string& newFirstName, const string& newLastName) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void PrintData() override {
        cout << "Student: " << firstname << " " << lastname << endl;
    }

    string IntroduceYourself() override {
        return "Hi, my name is: " + firstname + " " + lastname + " and I am a student";
    }
};

class Employee : public Person, public IIntroduceable {
public:
    Employee() {}

    Employee(int newIndex, const string& newFirstName, const string& newLastName) {
        SetIndex(newIndex);
        SetFirstname(newFirstName);
        SetLastname(newLastName);
    }

    void PrintData() override {
        cout << "Employee: " << firstname << " " << lastname << endl;
    }

    string IntroduceYourself() override {
        return "Hi, my name is: " + firstname + " " + lastname + " and I am an employee";
    }
};

class PartTimeStudent : public Student {
public:
    PartTimeStudent() {}

    PartTimeStudent(int newIndex, const string& newFirstName, const string& newLastName)
        : Student(newIndex, newFirstName, newLastName) {}

    void PrintData() override {
        cout << "PartTimeStudent: " << firstname << " " << lastname << endl;
    }

    string IntroduceYourself() override {
        return "Hi, my name is: " + firstname + " " + lastname + " and I am a part-time student";
    }
};



int main() {
    Person *tab[4];

    Person person1(1111, "Jan",  "Kowalski");
    Student student1(2222, "Filip", "Winkler");
    Employee employee1(3333, "Piotr", "Wisniewski");
    PartTimeStudent partTimeStudent1(4444, "Robert", "Lewandowski");

    tab[0] = &person1;
    tab[1] = &student1;
    tab[2] = &employee1;
    tab[3] = &partTimeStudent1;

    for (int i = 0; i < 4; i++) {
        tab[i]->PrintData();
    }

    return 0;
}