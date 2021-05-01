//
// Created by antronyx on 07/12/18.
//

#include "social.h"
#include <vector>
#include <algorithm>
#include <regex>





/***************************** Start Class gUser **********************************/
/**************** Constructors *********************/
gUser::gUser() {

}


gUser::gUser(string _file_name) {
    this->__file_ref = _file_name;
}


gUser::gUser(string _user_name, string _file_ref) {
    this->__username = _user_name;
    this->__file_ref = _file_ref;
}

/**************************************************/

string gUser::getUsername() const {
    return this->__username;
}


string gUser::getName() const {
    return this->__name;
}

void gUser::setName() {
    this->__name = getInfo(this->__file_ref, this->__username, "nome");
}

void gUser::setDate() {
    this->__date = getInfo(this->__file_ref, this->__username, "data");
    this->__dd = stoi(__date.substr(0, 2));
    this->__mm = stoi(__date.substr(3, 2));
    this->__yyyy = stoi(__date.substr(6, 4));
}

void gUser::setDate(string _date) {
    this->__date = _date;
    vector<string> date;
    date = split(_date, '/');
    this->__dd = stoi(date[0]);
    this->__mm = stoi(date[1]);
    this->__yyyy = stoi(date[2]);
}

void gUser::setUsername(string _user_name) {
    this->__username = _user_name;
};


string gUser::getDate() const {
    return __date;
}

void gUser::setCity() {
    this->__city = getInfo(this->__file_ref, this->__username, "citta");
}

string gUser::getCity() const {
    return __city;
}


int gUser::getDD() const {
    return __dd;
}

int gUser::getMM() const {
    return __mm;
}

int gUser::getYYYY() const {
    return __yyyy;
}


void gUser::setFileRef(string _file_ref) {
    this->__file_ref = _file_ref;
}

void gUser::setPostsFileRef(string _file_ref) {
    this->__posts_file_ref = _file_ref;
}

void gUser::setRelFileRef(string _file_ref) {
    this->__relation_file_ref = _file_ref;
}


int gUser::getDays() const {
    return __daysalive;
}


void gUser::setDays() {

    Date fdate{};
    Date today{};

    fdate.dd = this->getDD();
    fdate.mm = this->getMM();
    fdate.yyyy = this->getYYYY();

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    today.dd = ltm->tm_mday;
    today.mm = 1 + ltm->tm_mon;
    today.yyyy = ltm->tm_year + 1900;

    this->__daysalive = dateDiff(fdate, today);

}

gUser::~gUser() {

}

string gUser::getPostsFileRef() {
    return this->__posts_file_ref;
};

string gUser::getFileRef() {
    return this->__file_ref;
};

string gUser::getRelFileRef() {
    return this->__relation_file_ref;
};

void gUser::SetPost(vector<Post> _posts) {
    this->__post = _posts;
}

unsigned long gUser::GetNPosts() {
    return this->__post.size();
}


void gUser::loadPosts() {
    string line, id;
    unsigned long start = 0;
    unsigned long stop = 0;
    ifstream myfile(this->__posts_file_ref);
    while (getline(myfile, line)) {


        id = line.substr(0, line.find(',', 0));


        if (id == this->__username) {

            string mess;

            string likers, dislikers;

            start = line.find(",\"", 0) + 2; /*** +2 stand por the pos first char***/
            stop = line.find("\",", start);
            mess = line.substr(start, stop - start);
            Post post;
            vector<string> users;
            users = getUsers(this->__file_ref);

            likers = line.substr(line.find("like:{") + 6,
                                 line.find("},", line.find("like:{") + 6) - line.find("like:{") - 6);
            post.likes = split(likers, ',');
            post.nLikes = post.likes.size();


            dislikers = line.substr(line.find("dislike:{") + 9,
                                    line.find('}', line.find("dislike:{") + 9) - line.find("dislike:{") - 9);
            post.dislikes = split(dislikers, ',');
            post.nDislikes = post.dislikes.size();

            /**Now i control if a group or company gave a like/dislike to post (illegal) ***/
            for (int i = 0; i < post.likes.size(); i++) {
                if (getUserType(this->__file_ref, post.likes[i]) != 'S') {
                    cerr << "ERROR: There is a illegal like, exiting..." << endl;
                    exit(EXIT_FAILURE);
                }

            }
            for (int i = 0; i < post.dislikes.size(); i++) {
                if (getUserType(this->__file_ref, post.dislikes[i]) != 'S') {
                    cerr << "ERROR: There is a illegal like, exiting..." << endl;
                    exit(EXIT_FAILURE);
                }

            }


            /** Now i control if someone gave a like and dislike in the same post (not possible) ****/
            if (common(post.likes, post.dislikes) == 1) {
                cerr << "Someone liked and disliked the same post, Exiting" << endl;
                exit(EXIT_FAILURE);
            }

            post.message = mess;
            post.username = id;
            post.sdate = line.substr(line.find("\",") + 2, line.find(",like") - line.find("\",") - 2);
            post.date = strtoD(post.sdate);
            this->__post.emplace_back(post);
        }
    }
    myfile.close();

}


vector<Post> gUser::getPost() {

    return this->__post;
}

void gUser::setName(string _name) {
    this->__name = _name;

}

void gUser::setCity(string _city) {
    this->__city = _city;
}



char gUser::GetType() {
    return this->__type;
}

void gUser::addPost(Post _to_add) {
    this->__post.emplace_back(_to_add);

}

void gUser::loadPosts(vector<Post> _to_add) {
    this->__post = _to_add;
}






/************************** End Class gUser ******************************************************/



/************************************************* Class User ***************************************************/

User::User() {

};

User::User(string _username, string _file_ref, string _relation_file, string _post_file) {
    this->setFileRef(_file_ref);
    this->setUsername(_username);
    this->setRelFileRef(_relation_file);
    this->setPostsFileRef(_post_file);
    this->setDate();
    this->setDays();
    this->setName();
    this->setCity();
    this->setAge();
    this->setRelations();
    this->loadPosts();
    this->setSurname();
    this->setCity();
    this->setUniversity();
    this->setReligion();
    this->setSex();
    this->setParty();
}


User::~User() {

}

string User::GetFather() {
    return this->__father;
};

string User::getParty() {
    return this->__party;
};

char User::getSex() {
    return this->__sex;
};

string User::getReligion() {
    return this->__religion;
};

string User::getUniversity() {
    return this->__university;
};

string User::getSurname() {
    return this->__surname;
};


string User::GetMother() {
    return this->__mother;
};

void User::SetFather(string _father) {
    this->__father = _father;
}

void User::SetMother(string _mother) {
    this->__mother = _mother;
}

void User::SetFriends(vector<string> _friends) {
    this->__friends = _friends;
}

void User::SetKnowed(vector<string> _knowed) {
    this->__knowedpoeple = _knowed;
}

void User::SetSubsGroups(vector<string> _subscribed) {
    this->__subscribed_groups = _subscribed;
}




unsigned short User::getAge() {
    return this->__age;
}

vector<string> User::GetFriends() {
    return this->__friends;
}

vector<string> User::GetSubsGroups() {
    return this->__subscribed_groups;
}

vector<string> User::GetSons() {
    return this->__sons;
}

void User::SetSons(vector<string> _sons) {
    this->__sons = _sons;
}



unsigned long User::GetNFriends() {
    return this->__friends.size();
}


vector<string> User::GetKnowed() {
    return this->__knowedpoeple;
}

unsigned long User::GetNKnowed() {
    return this->__knowedpoeple.size();
}

void User::setSurname() {
    this->__surname = getInfo(this->__file_ref, this->__username, "cognome");

}

void User::setUniversity() {
    this->__university = getInfo(this->__file_ref, this->__username, "universita");

}

void User::setParty() {
    this->__party = getInfo(this->__file_ref, this->__username, "partito");

}


void User::setReligion() {
    this->__religion = getInfo(this->__file_ref, this->__username, "religione");

}


void User::setSex() {
    this->__sex = getInfo(this->__file_ref, this->__username, "sesso").at(0);

}


void User::setAge() {
    this->__age = static_cast<unsigned short>(this->__daysalive / 365);
}

void User::setRelations() {
    ifstream rel_file(this->getRelFileRef());
    if (rel_file.is_open()) {
        vector<string> info;
        string line;

        while (getline(rel_file, line)) {
            info = split(line, ',');

            if (info[1] == this->__username) {
                if (info[2] == "componente") {
                    this->__subscribed_groups.emplace_back(info[0]);
                }

                if (info[2] == "genitore") {
                    vector<string> users;
                    users = getUsers(this->getFileRef());

                    long parent_pos;
                    parent_pos = getVecPos(info[0], users);
                    vector<User> all_users(users.size());

                    vector<User>::iterator it;
                    int i = 0;
                    for (it = all_users.begin(); it != all_users.end(); it++) {
                        it->setFileRef(this->getFileRef());
                        it->setUsername(users[i]);
                        it->setSex();
                        i++;
                    }
                    /*I know that the parent is at the pos parent_pos*/
                    /*Now  check if is a father or a mother*/

                    if (all_users[parent_pos].getSex() == 'M') {
                        this->__father = info[0];
                    }
                    if (all_users[parent_pos].getSex() == 'F') {
                        this->__mother = info[0];
                    }
                }

                if (info[2] == "coniuge") {
                    this->__mate = info[0];
                }

                if (info[2] == "figlio") {
                    this->__sons.emplace_back(info[0]);
                }



                if (info[2] == "amico") {                             /*** 0,1,friend ---->   0 is 1's friend ***/
                    this->__friends.emplace_back(info[0]);
                    cout << "aggiungo a " << this->__username << "l' amico " << info[0]
                         << endl;/////*****cancella dopo ****/
                }
                if (info[2] == "conoscente") {                             /*** 0,1,friend ---->   0 is 1's friend ***/
                    this->__knowedpoeple.emplace_back(info[0]);

                }


            }
            info.clear();
        }


    }
    rel_file.close();

}

void User::setSurname(string _surname) {
    this->__surname = _surname;
}

void User::setUniversity(string _university) {
    this->__university = _university;
}

void User::setReligion(string _religion) {
    this->__religion = _religion;
}

void User::setParty(string _party) {
    this->__party = _party;
}

void User::setSex(char _sex) {
    this->__sex = _sex;
}

void User::setDays() { /**Overriding setDays for age for simple users**/
    gUser::setDays();
    this->__age = (unsigned short) this->__daysalive / 365;
}

void User::SetMate(string _mate) {
    this->__mate = _mate;

}

string User::GetMate() {
    return this->__mate;
}


string User::GetParent(char _sex) {
    if (_sex == 'M') {
        return this->__father;

    }
    if (_sex == 'F') {
        return this->__mother;
    }

    /*if reach here there is an error*/
    return "ERROR";
}


/********************************************** End Class User ******************************************************/


/******************************************* Class Group **************************************************************/

void Group::SetComponents(vector<string> &_to_set) {
    this->__components = _to_set;
    this->__ncomponents = this->__components.size();
}


void Group::SetComponents() {
    string line;

    ifstream myfile(this->__relation_file_ref);
    if (myfile.is_open()) {
        vector<string> info;
        while (getline(myfile, line)) {
            info = split(line, ',');

            if (getUserType(this->__file_ref, this->__username) == 'G' and info[0] == this->__username) {

                if (info[2] == "componente") {
                    this->__components.emplace_back(info[1]);
                    this->__ncomponents = this->__components.size();
                }
            }
        }
        myfile.close();
    }
}


unsigned long Group::GetNComponents() {
    return this->__ncomponents;
}


vector<string> Group::GetComponents() {
    return this->__components;
}

string Group::GetHeadquarter() {
    return this->__headquarter;
}

void Group::SetField() {
    this->__field = getInfo(this->__file_ref, this->__username, "tipologia");

}

void Group::SetHeadquarter() {
    this->__headquarter = getInfo(this->__file_ref, this->__username, "sedelegale");

}

string Group::GetField() {
    return this->__field;
}

void Group::AddComponent(string _component) {
    this->__components.emplace_back(_component);
    this->__ncomponents = this->__components.size();

}

void Group::RemoveComponent(string _component) {

    vector<string>::iterator it = find(this->__components.begin(), this->__components.end(), _component);
    this->__components.erase(this->__components.begin(), it);
    this->__ncomponents = this->__components.size();
}



void Group::SetField(string _field) {
    this->__field = _field;
}

void Group::SetHeadquarter(string _headquarter) {
    this->__headquarter = _headquarter;
}

Group::Group() {

};

/*************************************End Class Group *****************************************************************/






/************************************ Start Class Company ****************************************************************/

void Company::SetEmployees() {
    string line;

    ifstream myfile(this->__relation_file_ref);
    if (myfile.is_open()) {
        vector<string> info;
        while (getline(myfile, line)) {
            info = split(line, ',');
            if (getUserType(this->__file_ref, this->__username) == 'C' and info[2] == "dipendente" and
                info[1] == this->__username) {
                this->__employees.emplace_back(info[0]);

            }
        }
        myfile.close();
    }

}

void Company::SetSubsidiary(vector<string> _subs) {
    this->__subsidiary = _subs;
}



void Company::SetSubsidiary() {
    string line;

    ifstream myfile(this->__relation_file_ref);
    if (myfile.is_open()) {
        vector<string> info;
        while (getline(myfile, line)) {
            info = split(line, ',');
            if (getUserType(this->__file_ref, this->__username) == 'C' and info[2] == "consociata" and
                info[1] == this->__username) {
                this->__subsidiary.emplace_back(info[0]);

            }
        }
        myfile.close();
    }

}

vector<string> Company::GetSubsidiary() {
    return this->__subsidiary;
}

unsigned long Company::GetNSubsidiary() {
    return this->__subsidiary.size();
}

vector<string> Company::GetEmployees() {
    return this->__employees;
}

unsigned long Company::GetNEmployees() {
    return this->__employees.size();
}




void Company::SetEmployees(vector<string> _emp) {
    this->__employees = _emp;
}

string Company::GetField() {
    return this->__field;
}

string Company::GetTaxOffice() {
    return this->__tax_office;
}

string Company::GetCode() {
    return this->__code;
}

string Company::GetHeadquarter() {
    return this->__headquarter;
}

void Company::SetField() {
    this->__field = getInfo(this->__file_ref, this->__username, "tipologia");

}

void Company::SetTaxOffice() {
    this->__tax_office = getInfo(this->__file_ref, this->__username, "sedefiscale");

}

void Company::SetHeadquarter() {
    this->__headquarter = getInfo(this->__file_ref, this->__username, "sedeoperativa");

}

void Company::SetCode() {
    this->__code = getInfo(this->__file_ref, this->__username, "codice");

}

void Company::SetCode(string _code) {
    this->__code = _code;
}

void Company::SetHeadquarter(string _headquarter) {
    this->__headquarter = _headquarter;
}

void Company::SetTaxOffice(string _tax_office) {
    this->__tax_office = _tax_office;
}

void Company::SetField(string _field) {
    this->__field = _field;
}


/************************************** End Class Company *****************************************************************/





void showFile(string _file_name) {
    string line;
    ifstream myfile(_file_name);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << '\n';
        }
        myfile.close();
    } else {
        cout << "\a";
        cerr << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
}


void showIDs(string _file_name) {
    string line, id;

    int i = 0;
    ifstream myfile(_file_name);
    if (myfile.is_open()) {
        cout << endl;
        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            cout << setw(15);
            cout << left << id;
            i++;
            if (i == 5) {
                setw(0);
                cout << "\n";
                i = 0;
            }

        }
        cout << setw(0);
        cout << endl;
        myfile.close();
    } else {
        cout << "\a" << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }

}

bool isIdPresent(string _file_name, string _user_name) {
    string line, id;
    ifstream myfile(_file_name);
    while (getline(myfile, line)) {
        id = line.substr(0, line.find(','));
        if (id == _user_name) {
            myfile.close();
            return true;
        }

    }
    myfile.close();
    return false;
}


unsigned int getIdPos(string _file_name, string _user_name) {
    if (!isIdPresent(_file_name, _user_name)) {
        return 0;
    }

    string line, id;
    unsigned int pos = 1;
    ifstream myfile(_file_name);

    while (!myfile.eof()) {
        getline(myfile, line);
        id = line.substr(0, line.find(','));
        if (id == _user_name) {
            myfile.close();
            return pos;
        }
        pos++;

    }
    myfile.close();
    return 0;
}


char getUserType(string _file_name, string _user_name) {      //con get id pos --> 0 se non ce
    unsigned int pos = 1;
    unsigned int pos_n = getIdPos(_file_name, _user_name);
    string line, type;
    ifstream myfile(_file_name);

    if (getIdPos(_file_name, _user_name) == 0) {
        return 'E';
    }
    if (myfile.is_open()) {
        do {
            getline(myfile, line);
            pos++;
        } while (pos <= pos_n);
    }
    myfile.close();
    type = line.substr(line.find(',') + 1, (line.find(',', (line.find(',') + 1))) - (line.find(',') + 1));

    if (type == "azienda") {
        return 'C';  /**** C stand for Company ****/
    }

    if (type == "semplice") {
        return 'S';
    }

    if (type == "gruppo") {
        return 'G';

    }

    return 'E'; /*** If you come here there must be an error ***/
}


string getInfo(string _file_name, string _user_name, string _parameter) {

    //se _info non e nel parser non fare nulla
    if (!isEntry(_parameter)) {
        return "";
    }

    unsigned int pos = 1;
    unsigned long i, a = 0;
    string line, info;

    ifstream myfile(_file_name);
    while (getline(myfile, line)) {
        if (getIdPos(_file_name, _user_name) == pos) {

            if (line.find(_parameter) != string::npos) {  /*** Execute this only if you havent a finding error ***/
                i = line.find(_parameter, line.find('{')) + _parameter.length() + 1;
                // cout<<line.find('}',i)-1<<endl;
                a = line.find(',', i);

                a = a - i;
                info = line.substr(i, a);

                if (info.at(info.length() - 1) == '}') {
                    info = info.substr(0, info.length() - 1);
                }
                myfile.close();
                return info;
            }
        }
        pos++;
    }

    myfile.close();
    return "";
}


bool isParameterPresent(string _file_name, string _user_name, string _parameter) {

    if (!isEntry(_parameter)) {
        return 0;
    }

    unsigned int pos_i = 1;
    unsigned int pos_u = getIdPos(_file_name, _user_name);
    unsigned int i, a = 0;
    string line, info;

    ifstream myfile(_file_name);

    while (pos_i <= pos_u) {
        getline(myfile, line);
        if (pos_i == pos_u) {
            i = line.find(_parameter, line.find('{'));
            if (i == -1) //non riesce a trovare e ritorna -1//
            {
                return false;
            }

            a = line.find(':', i);


            info = line.substr(i, a - i);

            if (info == _parameter) {
                myfile.close();
                return true;
            } else {
                myfile.close();
                return false;
            }

        }
        pos_i++;

    }
    myfile.close();
    return false; //If you come here there is no parameter in id

}

void addParameterAndInfo(string _file_name, string _user_name, string _parameter, string _info) {
    if (!isParameterPresent(_file_name, _user_name, _parameter) && isEntry(_parameter) &&
        isIdPresent(_file_name, _user_name)) {

        unsigned int pos = 1;
        string line, line_to_write;
        ifstream infile(_file_name);
        ofstream outfile("log.dat");

        while (getline(infile, line)) {
            line_to_write.clear();
            if (pos == getIdPos(_file_name, _user_name)) {

                line_to_write = line.substr(0, line.length() - 1);
                line_to_write.append(",");
                line_to_write.append(_parameter);//, line.find('}'));
                line_to_write.append(":");
                line_to_write.append(_info);
                line_to_write.append("}");
                line.clear();

            }
            outfile << line_to_write;
            outfile << line;
            outfile << "\n";
            pos++;
        }
        //outfile<<line_to_write;
        infile.close();
        outfile.close();

    }

}

bool isUsEntry(string _parameter) {
    unsigned int j;
    vector<string> AVAILABLE_ENTRY;
    AVAILABLE_ENTRY.emplace_back("nome");
    AVAILABLE_ENTRY.emplace_back("cognome");
    AVAILABLE_ENTRY.emplace_back("data");
    AVAILABLE_ENTRY.emplace_back("religione");
    AVAILABLE_ENTRY.emplace_back("citta");
    AVAILABLE_ENTRY.emplace_back("universita");
    AVAILABLE_ENTRY.emplace_back("partito");
    AVAILABLE_ENTRY.emplace_back("sesso");


    for (j = 0; j < AVAILABLE_ENTRY.size(); j++) {
        if (AVAILABLE_ENTRY[j] == _parameter) {
            return true; //If you inserted a parameter parserizable continue, instead stop
        }

    }
    return false;
}


bool isEntry(string _parameter) {
    int j;
    vector<string> AVAILABLE_ENTRY;
    AVAILABLE_ENTRY.emplace_back("nome");
    AVAILABLE_ENTRY.emplace_back("cognome");
    AVAILABLE_ENTRY.emplace_back("data");
    AVAILABLE_ENTRY.emplace_back("religione");
    AVAILABLE_ENTRY.emplace_back("citta");
    AVAILABLE_ENTRY.emplace_back("tipologia");
    AVAILABLE_ENTRY.emplace_back("universita");
    AVAILABLE_ENTRY.emplace_back("partito");
    AVAILABLE_ENTRY.emplace_back("sesso");
    AVAILABLE_ENTRY.emplace_back("sedeoperativa");
    AVAILABLE_ENTRY.emplace_back("sedefiscale");
    AVAILABLE_ENTRY.emplace_back("sedelegale");

    AVAILABLE_ENTRY.emplace_back("codice");

    for (j = 0; j < AVAILABLE_ENTRY.size(); j++) {
        if (AVAILABLE_ENTRY[j] == _parameter) {
            return true; //If you inserted a parameter parserizable continue, instead stop
        }

    }
    return false;
}

void modifyInfo(string _file_name, string _user_name, string _parameter, string _info) {
    if (isEntry(_parameter) && isIdPresent(_file_name, _user_name) &&
        isParameterPresent(_file_name, _user_name, _parameter)) {
        unsigned int pos = 1;
        string line, line_to_write, line_l, line_r;
        ifstream infile(_file_name);
        ofstream outfile("log.dat");

        while (getline(infile, line)) {
            line_to_write.clear();
            if (pos == getIdPos(_file_name, _user_name)) {
                int i = line.find(_parameter, line.find('{')) + _parameter.length() + 1;
                line_l = line.substr(0, i);
                line_r = line.substr(getInfo(_file_name, _user_name, _parameter).length() + i, line.length());
                line_to_write = line_l.append(_info);
                line_to_write.append(line_r);
                line.clear();

            }
            outfile << line_to_write;
            outfile << line;
            outfile << "\n";
            pos++;
        }
        //outfile<<line_to_write;
        infile.close();
        outfile.close();
    }

}

unsigned int typeUsersNum(string _file_name, char _type) {

    unsigned int counter = 0;

    string line, id;
    ifstream myfile(_file_name);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            if (getUserType(_file_name, id) == _type) {
                counter++;
            }
        }

    }
    myfile.close();  /*****Aggiunto da poco se da troppi problemi ELIMINA ****/
    return counter;
}

unsigned int numS(string _file_name) {
    return typeUsersNum(_file_name, 'S');
}

unsigned int numC(string _file_name) {
    return typeUsersNum(_file_name, 'C');
}

unsigned int numG(string _file_name) {
    return typeUsersNum(_file_name, 'G');
}



int countLeapYears(Date d) {
    int years = d.yyyy;
    if (d.mm <= 2) {
        years--;
    }

    return years / 4 - years / 100 + years / 400;
}

int dateDiff(Date dmin, Date dsup) {
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    int n1 = dmin.yyyy * 365 + dmin.dd;

    for (int i = 0; i < dmin.mm - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dmin);

    int n2 = dsup.yyyy * 365 + dsup.dd;
    for (int i = 0; i < dsup.mm - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dsup);

    return (n2 - n1);
}


Date strtoD(string _date) {
    Date date_to_ret{};
    date_to_ret.dd = stoi(_date.substr(0, 2));
    date_to_ret.mm = stoi(_date.substr(3, 2));
    date_to_ret.yyyy = stoi(_date.substr(6, 4));
    return date_to_ret;
}


bool isDateCorrect(string _date) {

    if (_date.length() > 10) {
        return false;
    }

    if (!(isnumerical(_date.substr(0, 2)) and isnumerical(_date.substr(3, 2)) and isnumerical(_date.substr(6, 4)))) {
        return false;
    }




    int dd, mm, yyyy;
    if (_date.length() == 10) {

        Date d_in{};
        //unsigned int date[3];
        vector<string> date;
        date = split(_date, '/');

        d_in.dd = stoi(date[0]);
        d_in.mm = stoi(date[1]);
        d_in.yyyy = stoi(date[2]);


        const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


        if (d_in.mm == 2 && d_in.yyyy % 4 == 0 && d_in.dd == 29) {         /*** Check if 29/02 is good for the year ***/
            return true;                                                   /*******************************************/
        }                                                                 /********************************************/
        if ((d_in.mm == 2 and d_in.dd == 29) and d_in.yyyy % 4 != 0) {    /********************************************/
            return false;
        }

        if (d_in.dd > 31 or d_in.dd < 1 or d_in.yyyy > 9998 or d_in.yyyy < 1 or d_in.mm > 12 or d_in.mm < 1) {
            return false;
        }

        if (d_in.dd <= monthDays[d_in.mm - 1]) {
            return true;

        } else { return false; }

    } else { return false; }

}


int daysByDate(string _date) {

    int dd, mm, yyyy;
    if (_date.length() == 10) {

        Date d_now{};
        Date d_in{};

        d_in.dd = stoi(_date.substr(0, 2));
        d_in.mm = stoi(_date.substr(3, 2));
        d_in.yyyy = stoi(_date.substr(6, 4));

        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        d_now.dd = ltm->tm_mday;
        d_now.mm = 1 + ltm->tm_mon;
        d_now.yyyy = ltm->tm_year + 1900;


        return dateDiff(d_in, d_now);
    } else { return -1; }


}

vector<string> getUsers(string _file_users) {
    vector<string> users;
    string line, id;


    ifstream myfile(_file_users);
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            if (getUserType(_file_users, id) == 'S') {
                users.emplace_back(id);
            }

        }

        myfile.close();
    } else {
        cerr << "\a" << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    return users;

}

vector<string> getCompanies(string _file_users) {
    vector<string> companies;
    string line, id;


    ifstream myfile(_file_users);
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            if (getUserType(_file_users, id) == 'C') {
                companies.emplace_back(id);
            }

        }

        myfile.close();
    } else {
        cerr << "\a" << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    return companies;

}

vector<string> getGroups(string _file_users) {
    vector<string> groups;
    string line, id;


    ifstream myfile(_file_users);
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            if (getUserType(_file_users, id) == 'G') {
                groups.emplace_back(id);
            }

        }

        myfile.close();
    } else {
        cerr << "\a" << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    return groups;

}


vector<string> PostingPeople(string _file_posts) {

    vector<string> postatori;
    string line, id;


    ifstream myfile(_file_posts);
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            id = line.substr(0, line.find(','));
            if (std::find(postatori.begin(), postatori.end(), id) == postatori.end()) {
                postatori.emplace_back(id);
            }

        }

        myfile.close();
    } else {
        cerr << "\a" << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    return postatori;


}

vector<string> split(const string &_string_in, char _delimiter) {
    vector<string> list_to_ret;
    std::string extracted_str;
    std::istringstream tokenStream(_string_in);
    while (std::getline(tokenStream, extracted_str, _delimiter)) {
        list_to_ret.push_back(extracted_str);
    }
    return list_to_ret;
}

bool common(const vector<string> _list1,
            const vector<string> _list2) {         /***return true if a vectror contain one or more elements with another one ***/
    string to_compare;
    //if(_list1.size()!=0 || _list2.size()!=0)
    for (const auto &i : _list1) {
        to_compare = i;

        if (!to_compare.empty()) {
            if (find(_list2.begin(), _list2.end(), to_compare) != _list2.end()) {
                return true;
            }
        }

    }
    return false;
}

bool common(const string _str_to_compare,
            const vector<string> _list2) {         /***return true if a vectror contain one or more elements with another one ***/


    return find(_list2.begin(), _list2.end(), _str_to_compare) != _list2.end();

}


long getVecPos(string _to_find, vector<string> _vec) {
    unsigned long i;

    for (i = 0; i < _vec.size(); i++) {
        if (_vec[i] == _to_find) {
            return i;
        }
    }

    /**If you come here no elements is in vec*/
    return NULL;

}

unsigned long getEmployees(Company __company) {

    return __company.GetNEmployees();
}

void showSUser(User _to_show) {


    cout << endl;
    char to_fill = cout.fill('-');
    cout << "ID";
    cout.width(109 - strlen("ID"));

    cout << _to_show.getUsername() << endl;

    cout << "NOME";
    cout.width(109 - strlen("NOME"));
    cout << _to_show.getName() << endl;

    cout << "COGNOME";
    cout.width(109 - strlen("COGNOME"));
    cout << _to_show.getSurname() << endl;


    cout << "DATA DI NASCITA";
    cout.width(109 - strlen("DATA DI NASCITA"));
    cout << _to_show.getDate() << endl;

    cout << "CITTÀ";
    cout.width(109 - strlen("CITTA"));
    cout << _to_show.getCity() << endl;

    cout << "UNIVERSITÀ";
    cout.width(109 - strlen("UNIVERSITA"));
    cout << _to_show.getUniversity() << endl;

    cout << "RELIGIONE";
    cout.width(109 - strlen("RELIGIONE"));
    cout << _to_show.getReligion() << endl;

    cout << "PARTITO";
    cout.width(109 - strlen("PARTITO"));
    cout << _to_show.getParty() << endl;

    cout << "SESSO";
    cout.width(109 - strlen("SESSO"));
    cout << _to_show.getSex() << endl << endl;
    cout.fill(' ');
}

void showCUser(Company _to_show) {


    cout << endl;
    char to_fill = cout.fill('-');
    cout << "ID";
    cout.width(109 - strlen("ID"));

    cout << _to_show.getUsername() << endl;

    cout << "NOME";
    cout.width(109 - strlen("NOME"));
    cout << _to_show.getName() << endl;

    cout << "DATA";
    cout.width(109 - strlen("DATA"));
    cout << _to_show.getDate() << endl;

    cout << "SEDE FISCALE";
    cout.width(109 - strlen("SEDE FISCALE"));
    cout << _to_show.GetTaxOffice() << endl;



    cout << "SEDE OPERATIVA";
    cout.width(109 - strlen("SEDE OPERATIVA"));
    cout << _to_show.GetHeadquarter() << endl;

    cout << "CODICE";
    cout.width(109 - strlen("CODICE"));
    cout << _to_show.GetCode() << endl;

    cout << "TIPOLOGIA";
    cout.width(109 - strlen("TIPOLOGIA"));
    cout << _to_show.GetField() << endl;
    cout.fill(' ');
}

void showGUser(Group _to_show) {


    cout << endl;
    char to_fill = cout.fill('-');
    cout << "ID";
    cout.width(109 - strlen("ID"));

    cout << _to_show.getUsername() << endl;

    cout << "NOME";
    cout.width(109 - strlen("NOME"));
    cout << _to_show.getName() << endl;

    cout << "DATA";
    cout.width(109 - strlen("DATA"));
    cout << _to_show.getDate() << endl;

    cout << "SEDE LEGALE";
    cout.width(109 - strlen("SEDE LEGALE"));
    cout << _to_show.GetHeadquarter() << endl;


    cout << "TIPOLOGIA";
    cout.width(109 - strlen("TIPOLOGIA"));
    cout << _to_show.GetField() << endl;
    cout.fill(' ');
}


User modifySUser(User _to_modify, string _command, string _argument) {
    if (_command == "nome") {
        _to_modify.setName(_argument);
    } else
    if (_command == "citta") {
        _to_modify.setCity(_argument);
    } else

    if (_command == "data") {
        if (isDateCorrect(_argument)) {
            _to_modify.setDate(_argument);
        } else { cout << "Errore di inserimento" << endl; }
    } else

    if (_command == "cognome") {
        _to_modify.setSurname(_argument);
    } else
    if (_command == "religione") {
        _to_modify.setReligion(_argument);
    } else
    if (_command == "universita") {
        _to_modify.setUniversity(_argument);
    } else
    if (_command == "partito") {
        _to_modify.setParty(_argument);
    } else if (_command == "exit") {
        cout << "Sto Uscendo..." << endl;
    } else


    if (_command == "sesso") {
        if (_argument.at(0) == 'M' or _argument.at(0) == 'F') {
            _to_modify.setSex(_argument.at(0));
        } else { cout << "Errore di inserimento" << endl; }
    } else { cout << "Errore di inserimento" << endl; }
    return _to_modify;


}

Company modifyCUser(Company _to_modify, string _command, string _argument) {
    if (_command == "nome") {
        _to_modify.setName(_argument);
    } else if (_command == "citta") {
        _to_modify.setCity(_argument);
    } else if (_command == "data") {
        if (isDateCorrect(_argument)) {
            _to_modify.setDate(_argument);
        } else { cout << "Errore di inserimento" << endl; }
    } else if (_command == "sedefiscale") {
        _to_modify.SetTaxOffice(_argument);
    } else if (_command == "sedeoperativa") {
        _to_modify.SetHeadquarter(_argument);
    } else if (_command == "tipologia") {
        _to_modify.SetField(_argument);
    } else if (_command == "codice") {
        _to_modify.SetCode(_argument);
    } else if (_command == "exit") {
        cout << "Sto Uscendo..." << endl;
    } else { cout << "Errore di inserimento" << endl; }
    return _to_modify;


}



Group modifyGUser(Group _to_modify, string _command, string _argument) {
    if (_command == "nome") {
        _to_modify.setName(_argument);
    } else if (_command == "citta") {
        _to_modify.setCity(_argument);
    } else if (_command == "data") {
        if (isDateCorrect(_argument)) {
            _to_modify.setDate(_argument);
        } else { cout << "Errore di inserimento" << endl; }
    } else if (_command == "sedelegale") {
        _to_modify.SetHeadquarter(_argument);
    } else if (_command == "tipologia") {
        _to_modify.SetField(_argument);
    } else if (_command == "exit") {
        cout << "Sto Uscendo..." << endl;
    } else { cout << "Errore di inserimento" << endl; }

    return _to_modify;


}

Post modifyPost(Post &_to_modify, string _command, string _argument) {
    if (_command == "errore") {
        cout << "Sto uscendo ..." << endl;
    } else if (_command == "messaggio") {
        _to_modify.message = _argument;
    } else if (_command == "data") {
        if (isDateCorrect(_argument)) {
            _to_modify.sdate = _argument;
        } else { cout << "Errore di inserimento" << endl; }
    } else { cout << "Errore di inserimento" << endl; }

    return _to_modify;


}

long Post::GetNLikes() {
    return this->likes.size();
}

long Post::GetNDislikes() {
    return this->dislikes.size();
}


string trim(const string &s) {
    return ltrim(rtrim(s));
}

string ltrim(const string &s) {
    return std::regex_replace(s, regex("^\\s+"), string(""));
}

string rtrim(const string &s) {
    return regex_replace(s, regex("\\s+$"), string(""));
}

void showSUser(vector<User> _to_show) {
    for (int i = 0; i < _to_show.size(); i++) {
        int j = 0;
        cout << setw(15);
        cout << left << _to_show[i].getUsername();
        j++;
        if (j == 5) {
            cout << setw(0);
            cout << "\n";
            j = 0;
        }
    }
    cout << resetiosflags(ios::left);
    cout << endl << endl;
}


void showCUser(vector<Company> _to_show) {
    for (int i = 0; i < _to_show.size(); i++) {
        int j = 0;
        cout << setw(15);
        cout << left << _to_show[i].getUsername();
        j++;
        if (j == 5) {
            cout << setw(0);
            cout << "\n";
            j = 0;
        }
    }
    cout << resetiosflags(ios::left);
    cout << endl << endl;
}

void showGUser(vector<Group> _to_show) {
    for (int i = 0; i < _to_show.size(); i++) {
        int j = 0;
        cout << setw(15);
        cout << left << _to_show[i].getUsername();
        j++;
        if (j == 5) {
            cout << setw(0);
            cout << "\n";
            j = 0;
        }
    }
    cout << resetiosflags(ios::left);
    cout << endl << endl;
}


void showPosts(vector<User> &_u, vector<Company> &_c, vector<Group> &_g, string _username_logged) {
    long pos = 0;
    cout << endl << "Post di utenti semplici" << endl;
    for (int _pos = 0; _pos < _u.size(); _pos++) {
        vector<Post> _to_show = _u[_pos].getPost();

        for (int i = 0; i < _to_show.size(); i++) {

            cout << "Pos [" << pos << "] " << _to_show[i];

            if (common(_username_logged, _to_show[i].likes)) {
                cout << LIKE;
            }
            if (common(_username_logged, _to_show[i].dislikes)) {
                cout << DISLIKE;
            }
            cout << endl;

            pos++;


        }
    }
    cout << endl << "Post di utenti Azienda" << endl;
    for (int _pos = 0; _pos < _c.size(); _pos++) {
        vector<Post> _to_show = _c[_pos].getPost();

        for (int i = 0; i < _to_show.size(); i++) {
            cout << "Pos [" << pos << "] " << _to_show[i];

            if (common(_username_logged, _to_show[i].likes)) {
                cout << LIKE;
            }
            if (common(_username_logged, _to_show[i].dislikes)) {
                cout << DISLIKE;
            }
            cout << endl;
            pos++;

        }


    }
    cout << endl << "Post di utenti gruppo" << endl;
    for (int _pos = 0; _pos < _g.size(); _pos++) {
        vector<Post> _to_show = _g[_pos].getPost();

        for (int i = 0; i < _to_show.size(); i++) {
            cout << "Pos [" << pos << "] " << _to_show[i];

            if (common(_username_logged, _to_show[i].likes)) {
                cout << LIKE;
            }
            if (common(_username_logged, _to_show[i].dislikes)) {
                cout << DISLIKE;
            }
            cout << endl;
            pos++;

        }

    }


}


void Post::print() {
    cout << "\"" << this->message << "\"" << " scritto da " << this->username << " in data " << this->sdate;
}

Post::~Post() {

}

Post::Post() {

}

std::ostream &operator<<(std::ostream &out, const Post &post) {
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    //out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")"; // actual output done here
    out << "\"" << post.message << "\"" << " scritto da @" << post.username << " in data " << post.sdate;

    return out; // return std::ostream so we can chain calls to operator<<
}

void Post::addLike(string _username) {
    this->likes.emplace_back(_username);
}

void Post::addDislike(string _username) {
    this->dislikes.emplace_back(_username);
}

void Post::removeDislike(string _username) {

    this->dislikes.erase(this->dislikes.begin() + getVecPos(_username, this->dislikes));

}
void Post::removeLike(string _username) {

    this->likes.erase(this->likes.begin() + getVecPos(_username, this->likes));

}


bool isnumerical(string _to_know) {

    bool flag = true;
    for (int i = 0; i < _to_know.length(); i++) {
        if (isalpha(_to_know.c_str()[i])) {
            flag = false;
        }

    }
    return flag;
}


char getType(string _to_find, vector<string> _users, vector<string> _companyes, vector<string> _groups) {
    /**Attention to order **/

    if (getVecPos(_to_find, _users) >= 0) {
        return 'S';
    }

    if (getVecPos(_to_find, _companyes) >= 0) {
        return 'C';
    }

    if (getVecPos(_to_find, _groups) >= 0) {
        return 'G';
    }


}

long totPosts(vector<User> &_u, vector<Company> &_c, vector<Group> &_g) {


    long num = 0;
    for (int _num = 0; _num < _u.size(); _num++) {
        vector<Post> _to_show = _u[_num].getPost();

        for (int i = 0; i < _to_show.size(); i++) {


            num++;


        }
    }
    for (int _num = 0; _num < _g.size(); _num++) {
        vector<Post> _to_show = _g[_num].getPost();

        for (int i = 0; i < _to_show.size(); i++) {

            num++;

        }


    }

    for (int _num = 0; _num < _c.size(); _num++) {
        vector<Post> _to_show = _c[_num].getPost();

        for (int i = 0; i < _to_show.size(); i++) {

            num++;

        }

    }

    return num;

};


string printLD(const vector<string> &to_print) {

    string vout;

    if (!to_print.empty()) {
        for (int i = 0; i < to_print.size() - 1; ++i) {
            vout.append(to_print[i]);
            vout.append(",");

        }
        vout.append(to_print.at(to_print.size() - 1));
    }


    return vout;
}


void
save(vector<User> &_u, vector<Company> &_c, vector<Group> &_g, string userfile, string postfile, string relationfile) {


    /*Code for posts.dat*/
    ofstream outpost(postfile);
    for (int idd = 0; idd < _u.size(); idd++) {

        if (_u[idd].GetNPosts() > 0) {
            vector<Post> posts = _u[idd].getPost();
            for (unsigned long post_pos = 0; post_pos < posts.size(); post_pos++) {

                outpost << _u[idd].getUsername() << ",\"" << posts[post_pos].message << "\","
                        << posts[post_pos].sdate << ",like:{" << printLD(posts[post_pos].likes) << "},dislike:{"
                        << printLD(posts[post_pos].dislikes) << "}" << endl;

            }
        }

    }

    for (int idd = 0; idd < _g.size(); idd++) {

        if (_g[idd].GetNPosts() > 0) {
            vector<Post> posts = _g[idd].getPost();
            for (unsigned long post_pos = 0; post_pos < posts.size(); post_pos++) {

                outpost << _g[idd].getUsername() << ",\"" << posts[post_pos].message << "\","
                        << posts[post_pos].sdate << ",like:{" << printLD(posts[post_pos].likes) << "},dislike:{"
                        << printLD(posts[post_pos].dislikes) << "}" << endl;

            }
        }

    }
    for (int idd = 0; idd < _c.size(); idd++) {

        if (_c[idd].GetNPosts() > 0) {
            vector<Post> posts = _c[idd].getPost();
            for (unsigned long post_pos = 0; post_pos < posts.size(); post_pos++) {

                outpost << _c[idd].getUsername() << ",\"" << posts[post_pos].message << "\","
                        << posts[post_pos].sdate << ",like:{" << printLD(posts[post_pos].likes) << "},dislike:{"
                        << printLD(posts[post_pos].dislikes) << "}" << endl;

            }
        }

    }

    outpost.close();
    /*End code for posts*/

    /*Code for users.dat*/
    ofstream outuser(userfile);

    for (int idd = 0; idd < _u.size(); idd++) {
        outuser << _u[idd].getUsername() << ",semplice,{nome:" << _u[idd].getName();

        if (!_u[idd].getSurname().empty()) {
            outuser << ",cognome:" << _u[idd].getSurname();
        }
        outuser << ",data:" << _u[idd].getDate();


        if (!_u[idd].getCity().empty()) {
            outuser << ",citta:" << _u[idd].getCity();
        }

        if (!_u[idd].getReligion().empty()) {
            outuser << ",religione:" << _u[idd].getReligion();
        }

        if (!_u[idd].getUniversity().empty()) {
            outuser << ",universita:" << _u[idd].getUniversity();
        }

        if (!_u[idd].getParty().empty()) {
            outuser << ",partito:" << _u[idd].getParty();
        }

        if (_u[idd].getSex() == 'M' or _u[idd].getSex() == 'F') {
            outuser << ",sesso:" << _u[idd].getSex();
        }
        outuser << "}" << endl;


    }

    for (int idd = 0; idd < _c.size(); idd++) {
        outuser << _c[idd].getUsername() << ",azienda,{nome:" << _c[idd].getName();

        outuser << ",data:" << _c[idd].getDate();


        if (!_c[idd].GetTaxOffice().empty()) {
            outuser << ",sedefiscale:" << _c[idd].GetTaxOffice();
        }

        if (!_c[idd].GetHeadquarter().empty()) {
            outuser << ",sedeoperativa:" << _c[idd].GetHeadquarter();
        }

        if (!_c[idd].GetCode().empty()) {
            outuser << ",codice:" << _c[idd].GetCode();
        }

        if (!_c[idd].GetField().empty()) {
            outuser << ",tipologia:" << _c[idd].GetField();
        }

        outuser << "}" << endl;

    }

    for (int idd = 0; idd < _g.size(); idd++) {
        outuser << _g[idd].getUsername() << ",gruppo,{nome:" << _g[idd].getName();

        outuser << ",data:" << _g[idd].getDate();


        if (!_g[idd].GetField().empty()) {
            outuser << ",tipologia:" << _g[idd].GetField();
        }

        if (!_g[idd].GetHeadquarter().empty()) {
            outuser << ",sedelegale:" << _g[idd].GetHeadquarter();
        }


        outuser << "}" << endl;

    }

    outuser.close();

    /*Code for relations*/

    /*Relations with groups*/
    ofstream outrel(relationfile);

    vector<Group>::iterator gr;
    for (gr = _g.begin(); gr != _g.end(); gr++) {
        vector<string> n_components = gr->GetComponents();
        vector<string>::iterator comp;
        for (comp = n_components.begin(); comp != n_components.end(); comp++) {
            outrel << gr->getUsername() << "," << *comp << ",componente" << endl;
        }
    }
    /*Relations with companies*/
    vector<Company>::iterator c_iter;
    for (c_iter = _c.begin(); c_iter != _c.end(); c_iter++) {
        vector<string>::iterator comp_iter;
        vector<string> component;
        component = c_iter->GetSubsidiary();
        for (comp_iter = component.begin(); comp_iter != component.end(); comp_iter++) {
            outrel << *comp_iter << "," << c_iter->getUsername() << ",consociata" << endl;
        }
        component = c_iter->GetEmployees();
        for (comp_iter = component.begin(); comp_iter != component.end(); comp_iter++) {
            outrel << *comp_iter << "," << c_iter->getUsername() << ",dipendente" << endl;
        }
    }
    /*Relations with people*/
    vector<User>::iterator s_iter;
    for (s_iter = _u.begin(); s_iter != _u.end(); s_iter++) {
        vector<string> to_print;/*It will be recycled*/
        vector<string>::iterator ucomp_iter;

        to_print = s_iter->GetFriends();
        for (ucomp_iter = to_print.begin(); ucomp_iter != to_print.end(); ucomp_iter++) {
            outrel << *ucomp_iter << "," << s_iter->getUsername() << ",amico" << endl;
        }
        to_print = s_iter->GetKnowed();
        for (ucomp_iter = to_print.begin(); ucomp_iter != to_print.end(); ucomp_iter++) {
            outrel << *ucomp_iter << "," << s_iter->getUsername() << ",conoscente" << endl;
        }
        to_print = s_iter->GetSons();
        for (ucomp_iter = to_print.begin(); ucomp_iter != to_print.end(); ucomp_iter++) {
            outrel << *ucomp_iter << "," << s_iter->getUsername() << ",figlio" << endl;
        }

        if (!s_iter->GetFather().empty()) {
            outrel << s_iter->GetFather() << "," << s_iter->getUsername() << ",genitore" << endl;

        }
        if (!s_iter->GetMother().empty()) {
            outrel << s_iter->GetMother() << "," << s_iter->getUsername() << ",genitore" << endl;
        }
        if (!s_iter->GetMate().empty()) {
            outrel << s_iter->GetMate() << "," << s_iter->getUsername() << ",coniuge" << endl;
        }


    }

    outrel.close();





}




vector<pair<int, string>> occurr(vector<string> &_to_analize) {
    sort(_to_analize.begin(), _to_analize.end());
    vector<string> keys = _to_analize;

    keys.erase(unique(keys.begin(), keys.end()), keys.end());


    vector<pair<int, string>> to_ret;

    if (!_to_analize.empty()) {

        /*scan now keys and find the number of occurrance*/
        for (int i = 0; i < keys.size(); i++) {
            int occurrence = 0;
            for (int j = 0; j < _to_analize.size(); j++) {
                if (keys[i] == _to_analize[j]) {
                    occurrence++;

                }

            }
            to_ret.emplace_back(make_pair(occurrence, keys[i]));


        }


    } else { cerr << "ERROR" << endl; }

    return to_ret;

}


bool isVoid(string _to_know) {
    return _to_know.empty();

}

