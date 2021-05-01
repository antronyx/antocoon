//
// Created by antronyx on 03/02/19.
//

#ifndef ANTOCOON_TREE_H
#define ANTOCOON_TREE_H
#endif

#include <iostream>
#include <string>
#include <iomanip>
#include <zconf.h>

using namespace std;


class Person {

private:
    string name;
    Person *father = NULL;
    Person *mother = NULL;


public:
    Person(string _name) {
        this->name = _name;
    }

    Person();


    Person(const Person &obj) {  /** Declaring Copy-Constructor **/
        name = obj.name;
        this->father = obj.father;
        this->mother = obj.mother;


    }

    string getName() { return name; }

    Person *getFather() { return this->father; }

    void setFather(Person *_father) {

        if (this->father == NULL) { this->father = _father; }
    }

    Person *getMother() { return this->mother; }

    void setMother(Person *_mother) {
        if (this->mother == NULL) {
            this->mother = _mother;
        }
    }


    void printSimple();

    void printFather();

    void printMother();

    void setName(string _name) {
        this->name = _name;
    }


    void saveTree(int count);

    void printTree(Person *p, int indent);

    void setFile(string _file_name);


};
