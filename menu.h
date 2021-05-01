//
// Created by antronyx on 15/12/18.
//

#ifndef ANTOCOON_V1_0_MENU_H
#define ANTOCOON_V1_0_MENU_H

#endif //ANTOCOON_V1_0_MENU_H


#include <vector>
#include <iostream>
#include <string>
#include <cstring>
//#include "social.h"


#define START_MENU 42
#define STATS_MENU 1
#define MANAGER_MENU 2
#define RELATION_MENU 3
#define POST_MENU 4
#define MODIFY_MENU 5
#define CREATION_MENU 6
#define ID_POST_MENU 7
#define LIKE_MENU 8
#define GROUP_MENU 9
#define COMPANY_MENU 10
#define USER_REL_MENU 11
#define BEST_COMPANY 12
#define QUIET_USERS_MENU 13

#define FAMILY_TREE 14

#define EXIT_MENU -12




/****** I create a class menu, so i can better manage all ******/
using namespace std;

class Menu {
private:
    int __menu_pos = START_MENU;
    string __users_file, __relations_file, __posts_file, __logo, __user_ref;
    char _sub = 'N';

public:

    void SetUserRef(string _user);

    string GetUserRef();

    void SetSubMenu(char);

    void SetUserFile(string _users_file);

    void SetReletionFile(string _relations_file);

    void SetPostFile(string _post_file);

    void SetLogo(string _logo_path);

    string GetLogo();



    string GetUserFile() const;

    string GetRelationFile() const;

    string GetPostFile() const;

    int GetPos(); /*** Getting the position in the menu ***/
    void SetPos(int _menu_pos);

    void welcomeScreen();

    string posString();

    string getQuery();

    // User modifySUser(User _to_modify,string _command,string _argument);

    void maxLiked(const string _username_argument);

    void maxDisliked(const string _username_argument);


    Menu();

    ~Menu();

    vector<string> subQuery();

    Menu(string _users_file);

    Menu(string _users_file, string _relations_file);

    Menu(string _users_file, string _relations_file, string _post_file);


};








static int menu_pos;  /*** This variable is used to know the positions in the menus, to know in which pos of the program i am, to put the right help_code ****/
using namespace std;



void helpScreen(int help_code); /************** I make only a function for all help possibility **********/
/******* It accept an help_code and swith among the helping message ******/




bool isStatsCmd(string _command);

bool isMngrCmd(string _command);

bool isRelCmd(string _command);
bool isMenuCmd(string _command);

void menu();


bool helper(int _menu_pos);