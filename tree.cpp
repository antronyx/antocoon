//
// Created by antronyx on 03/02/19.
//

#include "tree.h"
#include <math.h>
#include <zconf.h>
#include <fstream>


void nspace(int n) {
    int i = 0;
    while (i < n) {

        cout << " ";
        i++;
    }

}

void Person::printTree(Person *p, int indent) {
    if (p != NULL) {
        if (p->father) {
            printTree(p->father, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->father) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << p->name << "\n ";
        if (p->mother) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            printTree(p->mother, indent + 4);
        }
    }
}


Person::Person() {

}

void Person::printFather() {
    if (this->father != NULL)
        cout << this->father->getName();

}

void Person::printMother() {
    if (this->mother != NULL) {
        cout << this->mother->getName();
    }
}

void Person::printSimple() {
    cout << this->name << endl;
    if (father != NULL) this->father->printSimple();
    if (mother != NULL) this->mother->printSimple();
}