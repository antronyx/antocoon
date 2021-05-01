
//
// Created by antronyx on 07/12/18.
//

#ifndef ANTOCOON_SOCIAL_H
#define ANTOCOON_SOCIAL_H

#endif //ANTOCOON_SOCIAL_H


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>
#include <csignal>
#include <iomanip>
#include <iterator>
#include <sstream>


using namespace std;


const std::string LIKE = " \xF0\x9F\x91\x8D  LIKE";
const std::string DISLIKE = " \xF0\x9F\x91\x8E  DISLIKE";
/*ricorda che se la funzione si chiama isQUALCOSA ritorna 1 in caso positivo sempre*/
/*poiche se qualcosa va strorto indipendentemente, conviene per verificate l assenza
 * imporre il !isPresent*/

struct Date {
    int dd, mm, yyyy;
};

class Post {
public:
    void print();

    unsigned long nLikes = 0;
    unsigned long nDislikes = 0;
    string username = "";
    string message = "";
    string sdate = "";
    Date date;
    vector<string> likes{};
    vector<string> dislikes{};

    void addLike(string _username);
    void addDislike(string _username);

    void removeLike(string _username);
    void removeDislike(string _username);

    long GetNLikes();

    long GetNDislikes();

    Post(const Post &_post) { /*copy constructor */
        message = _post.message;
        sdate = _post.sdate;
        date = _post.date;
        nLikes = _post.nLikes;
        nDislikes = _post.nDislikes;
        username = _post.username;
        likes = _post.likes;
        dislikes = _post.dislikes;

    }

    friend std::ostream &operator<<(std::ostream &out, const Post &post);


    Post();
    ~Post();
private:

};






class gUser {
protected:
    char __type;
    int __dd, __mm, __yyyy, __daysalive;
    string __username, __file_ref, __posts_file_ref, __relation_file_ref, __name, __date, __city;
    vector<Post> __post;
public:


    virtual string getUsername() const;

    char GetType();

    virtual string getName() const;


    virtual int getDays() const;   //ritorna il valore privato di giorni dalla nascita

    virtual string getCity() const;

    virtual string getDate() const;

    virtual int getDD() const;

    virtual int getMM() const;

    virtual int getYYYY() const;

    virtual string getPostsFileRef();

    virtual string getFileRef();

    virtual string getRelFileRef();

    virtual unsigned long GetNPosts();

    virtual void SetPost(vector<Post> _posts);


    virtual void setUsername(string _user_name);
    virtual void setDays();

    virtual void setName();

    virtual void setName(string _name);


    virtual void setCity();

    virtual void setCity(string _city);


    virtual void setDate();

    virtual void setDate(string _date);

    virtual void addPost(Post _to_add);

    virtual void setFileRef(string _file_ref);

    virtual void setPostsFileRef(string _file_ref);

    virtual void setRelFileRef(string _file_ref);

    //virtual void addLikes();
    virtual void loadPosts();


    //virtual void addDisLikes();
    virtual vector<Post> getPost();

    void loadPosts(vector<Post> _to_add);


    gUser(const gUser &obj) {  /** Declaring Copy-Constructor **/
        __dd = obj.__dd;
        __mm = obj.__mm;
        __yyyy = obj.__yyyy;
        __daysalive = obj.__daysalive;
        __username = obj.__username;
        __file_ref = obj.__file_ref;
        __posts_file_ref = obj.__posts_file_ref;
        __relation_file_ref = obj.__relation_file_ref;
        __name = obj.__name;
        __date = obj.__date;
        __city = obj.__city;
        __post = obj.__post;

    }

    gUser();

    explicit gUser(string _file_name);
    gUser(string _user_name, string _file_ref);

    ~gUser();


};



class User : public gUser {
private:
    vector<string> __friends, __sons, __knowedpoeple, __subscribed_groups;
    string __surname, __university, __religion, __party, __father, __mother, __mate;
    char __sex;
    char __type = 'S';

    unsigned short __age;
public:
    void setDays() override;

    string getSurname();

    string getUniversity();

    string getReligion();

    string getParty();

    char getSex();

    string GetFather();

    string GetMother();

    void SetMate(string _mate);

    string GetMate();

    string GetParent(char _sex); /*Generic getfather/getmother it dipend by the insertion*/

    void SetFather(string _father);

    void SetMother(string _father);

    void SetFriends(vector<string> _friends);

    void SetKnowed(vector<string> _knowed);

    void SetSubsGroups(vector<string> _subsribed);

    vector<string> GetFriends();

    vector<string> GetSubsGroups();

    vector<string> GetSons();

    void SetSons(vector<string> _sons);

    unsigned long GetNFriends();

    vector<string> GetKnowed();

    unsigned long GetNKnowed();

    unsigned short getAge();

    void setAge();

    void setRelations();

    void setSurname();

    void setSurname(string _surname);


    void setUniversity();

    void setUniversity(string _university);


    void setReligion();

    void setReligion(string _religion);


    void setParty();

    void setParty(string _party);


    void setSex(char _sex);
    void setSex();
    User();

    friend void gUser::setDays(); /**Overriding, to make possible to set age for people**/

    User(string _username, string _file_ref, string _relation_file, string _post_file);

    ~User();

};

class Group : public gUser {
private:
    string __field, __headquarter;
    vector<string> __components;
    unsigned long __ncomponents;
    char __type = 'G';

public:

    void AddComponent(string _component);

    void RemoveComponent(string _component);

    string GetField();
    string GetHeadquarter();
    void SetField();
    void SetField(string _field);
    void SetHeadquarter();
    void SetHeadquarter(string _headquarter);



    vector<string> GetComponents();

    unsigned long GetNComponents();

    void SetComponents();

    void SetComponents(vector<string> &_to_set);

    Group();

};

class Company : public gUser {
private:
    char __type = 'C';
    string __field, __tax_office, __code, __headquarter;
    vector<string> __employees, __subsidiary;

public:

    void SetField();
    void SetField(string _field);
    void SetHeadquarter();
    void SetHeadquarter(string _headquarter);
    void SetTaxOffice();
    void SetTaxOffice(string _tax_office);
    void SetCode();
    void SetCode(string _code);


    string GetField();
    string GetHeadquarter();
    string GetTaxOffice();
    string GetCode();


    void SetEmployees(vector<string> _emp);

    void SetEmployees();

    void SetSubsidiary();

    void SetSubsidiary(vector<string> _subs);


    vector<string> GetEmployees();

    vector<string> GetSubsidiary();

    vector<string> SetCumulativeEmployees();

    unsigned long GetNEmployees();

    unsigned long GetNSubsidiary();

    unsigned long GetComulativeEmployees();

};



/**#########################################################################################################################################**/
/**###################Here i declare all the prototypes of the functions that can be used to read, write or modify the file ################**/
/**#########################################################################################################################################**/
/** void showFile(string _file_name) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ As declared **/
/** void showIDs(string _file_name) -------------------------------------------------------------------------------------------- As declared **/
/** bool isIdPresent(string _file_name, string _user_name) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ As declared **/
/** unsigned int typeUsersNum(string _file_name, char type) ---------- type accept S,C,G; It return the number of simple/company/group users **/
/** unsigned int getIdPos(string _file_name, string _user_name) ~~~~~~~~~~~~~~~~~~~Return position in file, else return error with the code 0 **/
/** char getUserType(string _file_name, string _user_name) ---------------------- return S/C/G=simple/company/group; else error w/ err_code E **/
/** bool isEntry(string _parameter) ~~~~~~~~~~~~~~~~~~~~~~~~~some parameters is not accepted in parser (e.g <shoe_size> or <number_of_hair>) **/
/** bool isParameterPresent(string _file_name, string _user_name, string _parameter) -----tell if a parameter (e.g. <name>) is already present **/
/** void modifyInfo(string _file_name, string _user_name, string _parameter, string _info) ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Modify Info by parameter **/
/** string getInfo(string _file_name, string _user_name, string _parameter) -------------------------------------------- Get Info by parameter **/
/** void addParameterAndInfo(string _file_name, string _user_name, string _parameter,string _info) ~~~~~~~~~~~~NOW WRITE ON LOG*******************/
/**#########################################################################################################################################**/


void showFile(string _file_name);

void showIDs(string _file_name);

bool isIdPresent(string _file_name, string _user_name);


unsigned int typeUsersNum(string _file_name, char type);

unsigned int getIdPos(string _file_name, string _user_name); //0 se non esiste, in altri casi ritorna posizione
char getUserType(string _file_name, string _user_name);

bool isEntry(string _parameter);

bool isUsEntry(string _parameter);
bool isParameterPresent(string _file_name, string _user_name, string _parameter);

void modifyInfo(string _file_name, string _user_name, string _parameter, string _info);


string getInfo(string _file_name, string _user_name, string _parameter);//get info by parameter


void addParameterAndInfo(string _file_name, string _user_name, string _parameter, string _info);


unsigned int numS(string _file_username);/***Functions to now analytics***/
unsigned int numC(string _file_name);
unsigned int numG(string _file_name);

int countLeapYears(Date d);
bool isDateCorrect(string _date);

int dateDiff(Date dmin, Date dsup);

Date strtoD(string _date); /**String to Date **/
int daysByDate(string _date); /*** ritorna giorni di vita, da data, In case of ERROR, return -1 ****/




/** return a vector with all users/company/groups **/
vector<string> getUsers(string _file_users);

vector<string> getCompanies(string _file_users);

vector<string> getGroups(string _file_users);
/**************************************************/

vector<string> PostingPeople(string _file_posts);

vector<string> split(const string &_string_in, char _delimiter);

bool common(vector<string> _bigger, vector<string> _little);

bool common(const string _str_to_compare,
            const vector<string> _list2);

long getVecPos(string _to_find, vector<string> _vec);

unsigned long getEmployees(Company __company);

void showSUser(User _to_show);
void showSUser(vector<User> _to_show);

void showCUser(Company _to_show);
void showCUser(vector<Company> _to_show);

void showGUser(Group _to_show);
void showGUser(vector<Group> _to_show);


User modifySUser(User _to_modify, string _command, string _argument);

Company modifyCUser(Company _to_modify, string _command, string _argument);
Group modifyGUser(Group _to_modify, string _command, string _argument);


string trim(const std::string &s);

std::string ltrim(const std::string &s);

std::string rtrim(const std::string &s);



long totPosts(vector<User> &_u, vector<Company> &_c, vector<Group> &_g);

void showPosts(vector<User> &_u, vector<Company> &_c, vector<Group> &_g, string _username_logged);

char getType(string _to_find, vector<string> _users, vector<string> _companyes, vector<string> _groups);


bool isnumerical(string);

Post modifyPost(Post &_to_modify, string _command, string _argument);


void
save(vector<User> &_u, vector<Company> &_c, vector<Group> &_g, string userfile, string postfile, string relationfile);

string
printLD(const vector<string> &to_print);/*function for printing likes and dislikes in file respecting right notation*/

vector<pair<int, string>> occurr(vector<string> &_to_analize);

bool isVoid(string _to_know);

