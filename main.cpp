//da fare: levare i controlli in tutte le funzioni, i controlli voglio farli direttamente a inizio programma




#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <utility>

#include "social.h"
#include "menu.h"
#include "tree.h"


ostream &operator<<(ostream &vout, const vector<string> &to_print) {
    if (!to_print.empty()) {
        for (int i = 0; i < to_print.size() - 1; ++i) {
            vout << to_print[i] << ",";

        }
        vout << to_print.at(to_print.size() - 1);
    }
    return vout;
}



const char *characters = "/qwertyuiopasdfghjklzxcvbnm-.,_:;><|\tQWERTYUIOPASDFGHJKLZXCVBNM1234567890";

/**Here i overload the operator<< for likes***/


using namespace std;


int main(int argc, char *argv[]) {

    cout<<"Testing UTF-8"<<endl;
    cout << LIKE << DISLIKE;
    Menu menu1;
    menu1.SetLogo("logo.txt");
    menu1.SetUserFile("users.dat");
    menu1.SetReletionFile("relations.dat");
    menu1.SetPostFile("posts.dat");


    string file_name = menu1.GetUserFile();

    vector<string> Utentii;
    vector<string> groups_usernames;
    vector<string> company_usernames;
    Utentii = getUsers("users.dat");
    groups_usernames = getGroups("users.dat");
    company_usernames = getCompanies("users.dat");


    vector<string> postatori;
    postatori = PostingPeople("posts.dat");

    vector<User> Userss(Utentii.size());
    vector<Company> CompanyObj(company_usernames.size());
    vector<Group> Groups(groups_usernames.size());

/***************************************************************************/


    for (int i = 0; i < Userss.size(); i++) {

        Userss[i].setFileRef("users.dat");
        Userss[i].setUsername(Utentii[i]);
        Userss[i].setRelFileRef(menu1.GetRelationFile());
        Userss[i].setPostsFileRef(menu1.GetPostFile());
        Userss[i].setDate();
        Userss[i].setDays();
        Userss[i].setName();
        Userss[i].setCity();
        Userss[i].setAge();
        Userss[i].setRelations();
        Userss[i].loadPosts();
        Userss[i].setSurname();
        Userss[i].setCity();
        Userss[i].setUniversity();
        Userss[i].setReligion();
        Userss[i].setSex();
        Userss[i].setParty();

    }


    for (int i = 0; i < Groups.size(); i++) {
        Groups[i].setFileRef(menu1.GetUserFile());
        Groups[i].setPostsFileRef(menu1.GetPostFile());
        Groups[i].setRelFileRef("relations.dat");

        Groups[i].setUsername(groups_usernames[i]);
        Groups[i].setName();
        Groups[i].SetComponents();
        Groups[i].loadPosts();
        Groups[i].SetHeadquarter();
        Groups[i].SetField();
        Groups[i].setDate();

    }

    for (int i = 0; i < CompanyObj.size(); i++) {

        CompanyObj[i].setFileRef(menu1.GetUserFile());
        CompanyObj[i].setPostsFileRef(menu1.GetPostFile());
        CompanyObj[i].setRelFileRef("relations.dat");

        CompanyObj[i].setUsername(company_usernames[i]);
        CompanyObj[i].setName();
        CompanyObj[i].SetEmployees();
        CompanyObj[i].SetSubsidiary();
        CompanyObj[i].loadPosts();
        CompanyObj[i].setDate();
        CompanyObj[i].SetCode();
        CompanyObj[i].SetHeadquarter();
        CompanyObj[i].SetTaxOffice();
        CompanyObj[i].SetField();

        //cout<<CompanyObj[i].GetEmployees();
    }


    vector<User>::iterator it;
    vector<string>::iterator s;
    Person *treecomp[Userss.size()];

    int indxe;
    indxe = 0;
    for (it = Userss.begin(); it != Userss.end(); it++) {

        Person *_to_add = new Person(it->getUsername());
        _to_add->setFather(NULL);
        _to_add->setMother(NULL);
        treecomp[indxe] = _to_add;

        indxe++;
    }

    cout << "stampo le persone" << endl;

    for (int indxe = 0; indxe < Userss.size(); indxe++) {

        cout << treecomp[indxe]->getName() << endl;
    }
    cout << "ho finito di stampare le persone" << endl;

    indxe = 0;
    for (it = Userss.begin(); it != Userss.end(); it++) {


        if (!it->GetMother().empty()) {
            int pos = getVecPos(it->GetMother(), Utentii);
            treecomp[indxe]->setMother(treecomp[pos]);

        }

        if (!it->GetFather().empty()) {
            int pos = getVecPos(it->GetFather(), Utentii);

            treecomp[indxe]->setFather(treecomp[pos]);
        }

        indxe++;
    }

    indxe = 0;

    while (indxe < Utentii.size()) {
        cout << "Utente " << treecomp[indxe]->getName() << " ha padre ->";
        treecomp[indxe]->printFather();
        cout << "Utente " << treecomp[indxe]->getName() << " ha madre ->";
        treecomp[indxe]->printMother();
        //cout<<endl<<treecomp[indxe]->getFather();

        indxe++;
    }

    cout << endl;
    treecomp[1]->printTree(treecomp[1], 5);
    //cout<<treecomp[1]->getFather()->getName();
    cout << endl;


    cout << "********************************************" << endl;


    cout << CompanyObj[0].getName() << "------>" << CompanyObj[0].GetEmployees();
    cout << CompanyObj[1].getName() << "------>" << CompanyObj[1].GetEmployees();
    cout << CompanyObj[0].getName() << "------>" << CompanyObj[2].GetEmployees();


    // initObj(gruppi);
    cout << "amici di " << Userss[0].getName() << endl;
    cout << Userss[0].getSurname();
    menu1.welcomeScreen();


    /*** If menu1.GetPos<0 ----> exit while loop ***/
    while (menu1.GetPos() > 0) {

        int n_space = 0;
        string command;
        string argument;
        string ins = menu1.getQuery();
        string insert;

        for (char in : ins) {   /**     removing the lasts spaces using a range based loop    **/

            if (in == ' ') {
                n_space++;
            } else { n_space = 0; }


        }
        insert = ins.substr(0, ins.length() - n_space);
        if (isalnum(insert.at(0))) {
            command = insert.substr(0, insert.find(' ', 0));
            if (insert.find_first_not_of(' ', command.length()) != string::npos) {
                unsigned long start, end;
                start = insert.find_first_not_of(' ', command.length());
                end = insert.find_first_not_of(characters, command.length() + 1);

                argument = insert.substr(start, end - start);
            } else { argument = ""; }

        }



        /*** Now i have a command and a argument ***/

        switch (menu1.GetPos()) {
            case START_MENU:


                if (command == "statistiche") {
                    menu1.SetPos(STATS_MENU);
                    helpScreen(menu1.GetPos());
                } else if (command == "gestioneutenti") {
                    menu1.SetPos(MANAGER_MENU);
                    helpScreen(menu1.GetPos());

                } else if (command == "alberi") {
                    helpScreen(menu1.GetPos());
                    Menu *mtree = new Menu;
                    mtree->SetPos(FAMILY_TREE);
                    string ans;

                    while (mtree->GetPos() > 0) {


                        cout << "Immetti il nome dell' utente di cui vuoi l' albero, digita exit per uscire " << endl
                             << endl;
                        ans = mtree->getQuery();

                        if (ans == "exit") {
                            mtree->SetPos(EXIT_MENU);

                        } else {
                            if (common(ans, Utentii)) {
                                cout << "Stampo l'albero di" << ans << endl;
                                int pos = getVecPos(ans, Utentii);
                                cout << endl << endl;
                                treecomp[pos]->printTree(treecomp[pos], 2);
                                cout << endl << endl;

                            } else { cout << "Errore di immissione" << endl; }

                        }


                    }
                    delete mtree;
                } else if (command == "simpatia") {
                    menu1.SetPos(BEST_COMPANY);
                    helpScreen(menu1.GetPos());

                } else if (command == "gestionerelazioni") {
                    menu1.SetPos(RELATION_MENU);
                    helpScreen(menu1.GetPos());
                } else if (command == "gestionenotizie") {
                    menu1.SetPos(POST_MENU);
                    helpScreen(menu1.GetPos());
                } else if (command == "start") {
                    menu1.SetPos(START_MENU);
                } else if (command == "help") {
                } else if (command == "solitari") {
                    cout << "Sei entrato nel menu di ricerca lupi solitari" << endl;
                    cout
                            << "Devi prima definire dei parametri di lupo solitario, in base al numero di relazioni con altri utenti,"
                            << " l’appartenenza a gruppi, l’essere o meno dipendenti di una azienda ed al numero di apprezzamenti sulle news"
                            << endl << endl;
                    cout << endl
                         << "Una volta terminato l' inserimento, digita exit per uscire e visualizzare il risultato"
                         << endl << endl;
                    Menu *ms = new Menu;
                    ms->SetSubMenu('Y');
                    ms->SetPos(QUIET_USERS_MENU);
                    /*Minimal relation and iteration number to not be considered "lone wolf"*/
                    int rel_num = 0;
                    int interation_num = 0;
                    /*Need to know if is relevant to be in a group or company to not be considered "lone wolf"*/

                    bool in_group = false;
                    bool in_company = false;
                    /*By default no one is a lonely user*/

                    vector<string> _insertion;
                    helpScreen(ms->GetPos());
                    while (ms->GetPos() > 0) {
                        cout << endl;
                        cout << "Numero relazioni minime: " << rel_num << endl;
                        cout << "Numero apprezzamenti  minimi: " << interation_num << endl;
                        cout << "Appartenenza a gruppi impostato: " << in_group << endl;
                        cout << "Appartenenza ad aziende impostato: " << in_company << endl;
                        _insertion = ms->subQuery();
                        if (_insertion.size() == 2) {
                            if (_insertion[0] == "gruppi") {
                                if (_insertion[1] == "SI") { in_group = true; }
                                else if (_insertion[1] == "NO") { in_group = false; }
                                else { cout << "Errore di immissione" << endl; }

                            } else if (_insertion[0] == "aziende") {
                                if (_insertion[1] == "SI") { in_company = true; }
                                else if (_insertion[1] == "NO") { in_company = false; }
                                else { cout << "Errore di immissione" << endl; }

                            } else if (_insertion[0] == "relazioni") {
                                if (isnumerical(_insertion[1])) {
                                    rel_num = stoi(_insertion[1]);
                                } else { cout << "Errore di immissione" << endl; }

                            } else if (_insertion[0] == "apprezzamenti") {
                                if (isnumerical(_insertion[1])) {
                                    interation_num = stoi(_insertion[1]);
                                } else { cout << "Errore di immissione" << endl; }

                            }


                        } else { cout << "Errore di immissione" << endl; }


                    }/*Now that you exited the program have to print the quiet users*/
                    delete ms;/*deleting menu*/
                    cout << "Adesso stampo i forever alone" << endl;
                    vector<User> QuietUsers = Userss;/*first i copy all Users, after the program delete the not quiets*/
                    vector<string> quiet_usernames = Utentii;
                    vector<string> people_to_erase;
                    if (in_group) {
                        /*If be part of a group is required to not be a quiet user, the program will delete anyone who is not in a group*/
                        for (int i = 0; i < Groups.size(); i++) {
                            vector<string> _components;
                            _components = Groups[i].GetComponents();

                            people_to_erase.insert(people_to_erase.end(), _components.begin(), _components.end());
                        }


                    }
                    /************************ Make order **************************/
                    sort(people_to_erase.begin(), people_to_erase.end());
                    people_to_erase.erase(unique(people_to_erase.begin(), people_to_erase.end()),
                                          people_to_erase.end());
                    /*************************************************************/
                    if (in_company) {
                        /*If be part of a company is required to not be a quiet user, the program will delete anyone who is not in a company*/
                        for (int i = 0; i < CompanyObj.size(); i++) {
                            vector<string> _employees;
                            _employees = Groups[i].GetComponents();

                            people_to_erase.insert(people_to_erase.end(), _employees.begin(), _employees.end());
                        }


                    }
                    /******************* Make Order **************************/
                    sort(people_to_erase.begin(), people_to_erase.end());
                    people_to_erase.erase(unique(people_to_erase.begin(), people_to_erase.end()),
                                          people_to_erase.end());
                    /********************************************************/

                    /*Now likes and dislikes*/

                    /*first load all posts*/

                    if (interation_num >= 0) {
                        vector<Post> AllPosts;
                        for (int i = 0; i < Userss.size(); i++) {
                            vector<Post> user_posts = Userss[i].getPost();
                            AllPosts.insert(AllPosts.end(), user_posts.begin(), user_posts.end());
                        }
                        for (int i = 0; i < CompanyObj.size(); i++) {
                            vector<Post> user_posts = CompanyObj[i].getPost();
                            AllPosts.insert(AllPosts.end(), user_posts.begin(), user_posts.end());
                        }
                        for (int i = 0; i < Groups.size(); i++) {
                            vector<Post> user_posts = Groups[i].getPost();
                            AllPosts.insert(AllPosts.end(), user_posts.begin(), user_posts.end());
                        }
                        /*now store all likes and dislikes in a single vector, couting after the total number of appreciations*/
                        vector<string> AllAppreciations;
                        for (int i = 0; i < AllPosts.size(); i++) {
                            AllAppreciations.insert(AllAppreciations.end(), AllPosts[i].likes.begin(),
                                                    AllPosts[i].likes.end());
                            AllAppreciations.insert(AllAppreciations.end(), AllPosts[i].dislikes.begin(),
                                                    AllPosts[i].dislikes.end());



                        }
                        sort(AllAppreciations.begin(), AllAppreciations.end());
                        /*Now the program check the number of likes+dislikes for each user who liked or disliked a post*/
                        /* In program it is equal to store in a vector of pairs likes+disliked plus the relative username*/

                        vector<pair<int, string>> ApprAndUser;
                        ApprAndUser = occurr(AllAppreciations);

                        /*Now the program check interations>treshold*/
                        /*Remember that all users is supposed to be quiet users, but if they have sum> treshold they are "safe"*/

                        for (int i = 0; i < ApprAndUser.size(); i++) {
                            if (ApprAndUser[i].first > interation_num) {

                                people_to_erase.emplace_back(ApprAndUser[i].second);

                            }
                        }

                    }

                    /*Now check the relations*/
                    if (rel_num >= 0) {
                        /*This vector stores all users[i]'s relations whit relative relations finded (friends, knowed_people, parents,mate and sons)*/
                        auto *AllUserWithRelations = new vector<pair<string, vector<string>>>;
                        vector<User>::iterator it;
                        for (it = Userss.begin(); it != Userss.end(); it++) {
                            vector<string> all_relations;

                            vector<string> knowed;
                            knowed = it->GetKnowed();
                            all_relations.insert(all_relations.end(), knowed.begin(), knowed.end());
                            vector<string> friends;
                            friends = it->GetFriends();
                            all_relations.insert(all_relations.end(), friends.begin(), friends.end());
                            vector<string> sons;
                            sons = it->GetSons();
                            all_relations.insert(all_relations.end(), sons.begin(), sons.end());

                            all_relations.emplace_back(it->GetFather());
                            all_relations.emplace_back(it->GetMother());
                            all_relations.emplace_back(it->GetMate());

                            /*Now remove possible void string*/
                            all_relations.erase(remove_if(all_relations.begin(), all_relations.end(), isVoid),
                                                all_relations.end());


                            AllUserWithRelations->emplace_back(make_pair(it->getUsername(), all_relations));
                        }

                        /*Now the program "shrink" AllUserWithRelations' vector<string> into a number and make a pair with relative user_name*/
                        /******************************************************************************************************/
                        vector<pair<int, string>> AllRelationsNum;/*first is relations' number, second is the pos in Userss*/
                        /******************************************************************************************************/

                        vector<pair<string, vector<string>>>::iterator iter;
                        for (iter = AllUserWithRelations->begin(); iter != AllUserWithRelations->end(); iter++) {
                            AllRelationsNum.emplace_back(make_pair(iter->second.size(), iter->first));
                        }
                        delete AllUserWithRelations;


                        /*Now the program have a vector of pair with the number of relations and the relative usernames*/
                        /*The user[i] with a nuberofrelation>threshold will be eliminated from the list of quiet users*/
                        /* Everything from relation is now stored in AllRelationsNum*/

                        vector<pair<int, string>>::iterator iterator1;
                        for (iterator1 = AllRelationsNum.begin(); iterator1 != AllRelationsNum.end(); iterator1++) {
                            if (iterator1->first > rel_num) {

                                people_to_erase.emplace_back(iterator1->second);

                            }
                        }

                    }
                    /*Now all user that respect the thresholds are in a list that exclude them from the quiet users list*/
                    /*removing duplicates from people_to_erase*/

                    sort(people_to_erase.begin(), people_to_erase.end());
                    people_to_erase.erase(unique(people_to_erase.begin(), people_to_erase.end()),
                                          people_to_erase.end());

                    /*now get positions and erase the not quiet users */

                    for (int i = 0; i < people_to_erase.size(); i++) {
                        auto pos = getVecPos(people_to_erase[i], quiet_usernames);
                        QuietUsers.erase(QuietUsers.begin() + pos);
                        quiet_usernames.erase(quiet_usernames.begin() + pos);
                    }

                    /* End operations, now print */
                    cout << "Ecco gli utenti solitari secondo i parametri immessi" << endl << endl;
                    showSUser(QuietUsers);



                } else if (command == "mostrautenti") {

                    showSUser(Userss);
                    showCUser(CompanyObj);
                    showGUser(Groups);

                } else {
                    cerr << "Comando Sconosciuto" << endl;
                }
                break;

            case STATS_MENU:
                if (!isStatsCmd(command)) {
                    cerr << "Comando Sconosciuto" << endl;
                }
                if (command == "start") {
                    menu1.SetPos(START_MENU);
                }

                if (command == "tot") {
                    if (argument.empty()) {

                        cout << "Il numero totale di utenti è "
                             << numS(menu1.GetUserFile()) + numC(menu1.GetUserFile()) + numG(menu1.GetUserFile())
                             << endl;

                        cout << "Utenti Semplici: " << numS(menu1.GetUserFile()) << endl;
                        cout << "Utenti Azienda: " << numC(menu1.GetUserFile()) << endl;
                        cout << "Utenti Gruppo: " << numG(menu1.GetUserFile()) << endl;
                    } else if (argument == "S" || argument == "s") {
                        cout << "Utenti Semplici: " << numS(menu1.GetUserFile()) << endl;

                    } else if (argument == "A" || argument == "a") {
                        cout << "Utenti Azienda: " << numC(menu1.GetUserFile()) << endl;

                    } else if (argument == "G" || argument == "g") {
                        cout << "Utenti Gruppo: " << numG(menu1.GetUserFile()) << endl;

                    } else {
                        cout << "Errore di immissione parametro: parametro sconosciuto [" << argument << "]" << endl;
                    }


                }


                if (command == "nsince") {
                    if (!argument.empty()) {
                        int days = daysByDate(argument);
                        if (isDateCorrect(argument)) {

                            if (days >= 0) {

                                int count = 0;
                                for (int i = 0; i < Userss.size(); i++) {
                                    if (Userss[i].getDays() < days) {
                                        count++;

                                    }
                                }
                                cout << "Dopo il " << argument << " sono nati " << count << " utenti" << endl;


                            } else { cout << "Hai inserito una data del futuro" << endl; }


                        } else {
                            cout << "Errore di immissione parametro: Hai inserito una data in un formato scorretto"
                                 << endl;
                        }

                    } else {
                        cerr << "Errore di immissione parametro: Devi inserire una data nel formato GG/MM/YYYY" << endl;
                    }

                }


                if (command + argument == "ndipendenti" + argument) {


                    if (common(argument, company_usernames)) {
                        unsigned long pos = 0;
                        pos = getVecPos(argument, company_usernames);


                        cout << endl << "L' azienda @" << CompanyObj[pos].getUsername() << " con nome: "
                             << CompanyObj[pos].getName() << " ha " << CompanyObj[pos].GetNEmployees() << " dipendenti"
                             << endl;

                    } else if (argument.empty()) {
                        cout << "Non hai inserito un username, stampo tutte le info trovate" << endl << endl;
                        unsigned long pos = 0;
                        for (pos = 0; pos < CompanyObj.size(); pos++) {

                            cout << "L' azienda @" << CompanyObj[pos].getUsername() << " con nome: "
                                 << CompanyObj[pos].getName() << " ha " << CompanyObj[pos].GetNEmployees()
                                 << " dipendenti"
                                 << endl;
                        }
                    } else {

                        cerr << "Errore di immissione parametro: Azienda inesistente" << endl;
                    }


                }


                if (command + argument == "nconsociate" + argument) {


                    if (common(argument, company_usernames)) {
                        unsigned long pos = 0;
                        pos = getVecPos(argument, company_usernames);


                        cout << endl << "L' azienda @" << CompanyObj[pos].getUsername() << " con nome: "
                             << CompanyObj[pos].getName() << " ha " << CompanyObj[pos].GetNSubsidiary() << " consociate"
                             << endl;

                    } else if (argument.empty()) {
                        cout << "Non hai inserito un username, stampo tutte le info trovate" << endl << endl;
                        unsigned long pos = 0;
                        for (pos = 0; pos < CompanyObj.size(); pos++) {

                            cout << "L' azienda @" << CompanyObj[pos].getUsername() << " con nome: "
                                 << CompanyObj[pos].getName() << " ha " << CompanyObj[pos].GetNSubsidiary()
                                 << " consociate"
                                 << endl;
                        }
                    } else {

                        cerr << "Errore di immissione parametro: Azienda inesistente" << endl;
                    }


                }

                if (command + argument == "ncomponenti" + argument) {
                    if (argument.empty()) {
                        cout << "Gruppi e componenti:" << endl;

                        for (unsigned int i = 0; i < Groups.size(); i++) {

                            cout << "Gruppo con nome: " << Groups[i].getName() << ", username: @"
                                 << Groups[i].getUsername() << " ha " << Groups[i].GetNComponents() << " componenti"
                                 << endl;
                        }

                    } else if (common(argument, groups_usernames)) {
                        cout << "Gruppi e componenti:" << endl;

                        for (unsigned int i = 0; i < Groups.size(); i++) {
                            if (Groups[i].getUsername() == argument and !argument.empty()) {
                                cout << "Gruppo con nome: " << Groups[i].getName() << ", username: @"
                                     << Groups[i].getUsername() << " ha " << Groups[i].GetNComponents() << " componenti"
                                     << endl;
                            }
                        }

                    } else { cerr << "Errore di immissione parametro: Gruppo inesistente" << endl; }


                }
                if (command + argument == "maxdipendenti" + argument) {


                    if (argument == "S") {
                        unsigned long max = 0;

                        for (int i = 0; i < CompanyObj.size(); i++) {
                            if (CompanyObj[i].GetNEmployees() > max) {
                                max = CompanyObj[i].GetNEmployees();
                            }
                        }
                        cout << endl << endl;
                        if (max != 0) {
                            for (auto &i : CompanyObj) {

                                if (i.GetNEmployees() == max) {
                                    cout << "Azienda con nome " << i.getName()
                                         << " ha il numero più grande di dipendenti: "
                                         << i.GetNEmployees() << " dipendenti" << endl;
                                }
                            }

                        }


                    } else if (argument == "C") {
                        unsigned long max = 0;
                        vector<int> max_poss; /**Where are the max cumulative employees*/
                        vector<string> cumulative;
                        for (int i = 0; i < CompanyObj.size(); i++) {
                            cumulative = CompanyObj[i].GetEmployees();

                            if (CompanyObj[i].GetNSubsidiary() > 0) {
                                vector<string> subsidiaries;
                                subsidiaries = CompanyObj[i].GetSubsidiary();
                                vector<int> com_pos; /*Store the positions of the subsidiary*/

                                for (int j = 0; j < subsidiaries.size(); j++) {
                                    com_pos.emplace_back(getVecPos(subsidiaries[j], company_usernames));

                                }

                                for (int k = 0; k < com_pos.size(); k++) {
                                    vector<string> employees_to_add = CompanyObj[com_pos[k]].GetEmployees();
                                    cumulative.insert(cumulative.end(), employees_to_add.begin(),
                                                      employees_to_add.end());

                                }

                            }

                            sort(cumulative.begin(),
                                 cumulative.end()); /*** Now i remove possible double employees (cause a person can work both for two affiliated companies) ***/
                            auto last = unique(cumulative.begin(), cumulative.end());
                            cumulative.erase(last, cumulative.end());


                            if (cumulative.size() > max) {
                                max_poss.clear();
                                max = cumulative.size();
                                max_poss.emplace_back(i);

                            } else if (cumulative.size() == max) {
                                max_poss.emplace_back(i);
                            }

                        }

                        cout << "Aziende con il più alto numero di dipendenti cumulativi:" << endl;
                        for (int h = 0; h < max_poss.size(); h++) {
                            cout << "@" << CompanyObj[max_poss[h]].getUsername() << ", Azienda con nome:"
                                 << CompanyObj[max_poss[h]].getName() << ", ha " << max << " dipendenti" << endl;

                        }
                        cout << endl;


                    } else { cerr << "Errore di immissione parametro" << endl; }

                }


                if (command == "mostLiked") {


                    /************ Creating a list of posting people,groups,companies ***************************************/

                    vector<string> posting_usernames;

                    for (int i = 0; i < Userss.size(); i++) {
                        if (Userss[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(Userss[i].getUsername());
                        }

                    }

                    for (int i = 0; i < CompanyObj.size(); i++) {
                        if (CompanyObj[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(CompanyObj[i].getUsername());
                        }

                    }

                    for (int i = 0; i < Groups.size(); i++) {
                        if (Groups[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(Groups[i].getUsername());
                        }

                    }

                    vector<gUser> postingObjs(posting_usernames.size());

                    for (int i = 0; i < postingObjs.size(); i++) {

                        postingObjs[i].setUsername(posting_usernames[i]);

                    }

                    vector<vector<Post> > tutti_i_post;
                    int user_no = 0;
                    for (user_no = 0; user_no < postingObjs.size(); user_no++) {

                        if (common(postingObjs[user_no].getUsername(), Utentii)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), Utentii);

                            postingObjs[user_no].loadPosts(Userss[obj_pos].getPost());

                        }
                        if (common(postingObjs[user_no].getUsername(), company_usernames)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), company_usernames);

                            postingObjs[user_no].loadPosts(CompanyObj[obj_pos].getPost());

                        }
                        if (common(postingObjs[user_no].getUsername(), groups_usernames)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), groups_usernames);

                            postingObjs[user_no].loadPosts(Groups[obj_pos].getPost());

                        }
                        /*** Posts loaded in the generic list of posting objs****/

                    }

                    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
                        tutti_i_post.emplace_back(postingObjs[user_no].getPost());

                    }

                    unsigned long nLmax = 0;
                    vector<string> message;
                    vector<string> username;

                    vector<int> post_n;
                    vector<int> user_n;
                    if (argument.empty()) {
                        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
                            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {


                                if (tutti_i_post[user_no][post_no].likes.size() > nLmax) {
                                    message.clear();
                                    post_n.clear();
                                    user_n.clear();
                                    username.clear();

                                    nLmax = tutti_i_post[user_no][post_no].likes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                } else if (tutti_i_post[user_no][post_no].likes.size() == nLmax) {
                                    nLmax = tutti_i_post[user_no][post_no].likes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);

                                }


                            }

                        }
                        cout << "I post con più likes sono i seguenti" << endl;

                    } else if (!argument.empty() and common(command, posting_usernames)) {

                        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
                            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {
                                if (tutti_i_post[user_no][post_no].username == command and
                                    tutti_i_post[user_no][post_no].likes.size() == nLmax) {
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                } else if (tutti_i_post[user_no][post_no].username == command and
                                           tutti_i_post[user_no][post_no].likes.size() > nLmax) {
                                    message.clear();
                                    post_n.clear();
                                    user_n.clear();
                                    username.clear();
                                    nLmax = tutti_i_post[user_no][post_no].likes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                }

                            }
                        }
                        cout << "I post con più likes scritti da " << command << " sono i seguenti" << endl;

                    }

                    /** Now print **/
                    for (int i = 0; i < username.size(); i++) {
                        cout << message[i] << " scritto da  @" << username[i] << " con un totale di " << nLmax
                             << " Likes" << endl;
                    }



/*******************************************************************************************/


                    }

                if (command == "mostDisliked") {

                    vector<string> posting_usernames;

                    for (int i = 0; i < Userss.size(); i++) {
                        if (Userss[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(Userss[i].getUsername());
                        }

                    }

                    for (int i = 0; i < CompanyObj.size(); i++) {
                        if (CompanyObj[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(CompanyObj[i].getUsername());
                        }

                    }

                    for (int i = 0; i < Groups.size(); i++) {
                        if (Groups[i].GetNPosts() > 0) {
                            posting_usernames.emplace_back(Groups[i].getUsername());
                        }

                    }

                    vector<gUser> postingObjs(posting_usernames.size());

                    for (int i = 0; i < postingObjs.size(); i++) {

                        postingObjs[i].setUsername(posting_usernames[i]);

                    }

                    vector<vector<Post> > tutti_i_post;
                    int user_no = 0;
                    for (user_no = 0; user_no < postingObjs.size(); user_no++) {

                        if (common(postingObjs[user_no].getUsername(), Utentii)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), Utentii);

                            postingObjs[user_no].loadPosts(Userss[obj_pos].getPost());

                        }
                        if (common(postingObjs[user_no].getUsername(), company_usernames)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), company_usernames);

                            postingObjs[user_no].loadPosts(CompanyObj[obj_pos].getPost());

                        }
                        if (common(postingObjs[user_no].getUsername(), groups_usernames)) {

                            /**I need to copy vector<post> in the new list**/
                            long obj_pos = getVecPos(postingObjs[user_no].getUsername(), groups_usernames);

                            postingObjs[user_no].loadPosts(Groups[obj_pos].getPost());

                        }
                        /*** Posts loaded in the generic list of posting objs****/

                    }

                    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
                        tutti_i_post.emplace_back(postingObjs[user_no].getPost());

                    }

                    unsigned long nDmax = 0;
                    vector<string> message;
                    vector<string> username;

                    vector<int> post_n;
                    vector<int> user_n;
                    if (argument.empty()) {
                        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
                            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {


                                if (tutti_i_post[user_no][post_no].dislikes.size() > nDmax) {
                                    message.clear();
                                    post_n.clear();
                                    user_n.clear();
                                    username.clear();

                                    nDmax = tutti_i_post[user_no][post_no].dislikes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                } else if (tutti_i_post[user_no][post_no].dislikes.size() == nDmax) {
                                    nDmax = tutti_i_post[user_no][post_no].dislikes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);

                                }


                            }

                        }
                        cout << "I post con più dislikes sono i seguenti" << endl;

                    } else if (!argument.empty() and common(command, posting_usernames)) {

                        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
                            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {
                                if (tutti_i_post[user_no][post_no].username == command and
                                    tutti_i_post[user_no][post_no].dislikes.size() == nDmax) {
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                } else if (tutti_i_post[user_no][post_no].username == command and
                                           tutti_i_post[user_no][post_no].dislikes.size() > nDmax) {
                                    message.clear();
                                    post_n.clear();
                                    user_n.clear();
                                    username.clear();
                                    nDmax = tutti_i_post[user_no][post_no].dislikes.size();
                                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                                    user_n.push_back(user_no);
                                    post_n.push_back(post_no);
                                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                                }

                            }
                        }
                        cout << "I post con più dislikes scritti da " << command << " sono i seguenti" << endl;

                    }

                    /** Now print **/
                    for (int i = 0; i < username.size(); i++) {
                        cout << message[i] << " scritto da  @" << username[i] << " con un totale di " << nDmax
                             << " Dislikes" << endl;
                    }

                }
                if (command == "etaMedia") {
                    unsigned long count = 0;
                    for (int i = 0; i < Userss.size(); i++) {
                        count += Userss[i].getAge();

                    }
                    cout << "L' età media sul social network è di " << (int) (count / Userss.size())
                         << " anni" << endl;
                }


                if (command == "maxfriends") {
                    unsigned long max = 0;

                    for (int i = 0; i < Userss.size(); i++) {


                        if (Userss[i].GetNFriends() > max) {
                            max = Userss[i].GetNFriends();
                        }
                    }
                    cout << endl << endl;
                    if (max != 0) {
                        for (auto &i : Userss) {

                            if (i.GetNFriends() == max) {
                                cout << "Utente con nome " << i.getName()
                                     << " ha il numero più grande di amici: "
                                     << i.GetNFriends() << " persone" << endl;
                            }
                        }

                    }
                }
                if (command == "maxconoscenti") {
                    unsigned long max = 0;

                    for (int i = 0; i < Userss.size(); i++) {


                        if (Userss[i].GetNKnowed() > max) {
                            max = Userss[i].GetNKnowed();
                        }
                    }
                    cout << endl << endl;
                    if (max != 0) {
                        for (auto &i : Userss) {

                            if (i.GetNKnowed() == max) {
                                cout << "Utente con nome " << i.getName()
                                     << " ha il numero più grande di conoscenti: "
                                     << i.GetNKnowed() << " persone" << endl;
                            }
                        }

                    }
                }

                break;
            case MANAGER_MENU:

                if (!isMngrCmd(command)) {
                    cerr << "Comando Sconosciuto" << endl;
                }
                if (command == "start") {
                    menu1.SetPos(START_MENU);
                }
                if (command == "help") {
                    helpScreen(menu1.GetPos());
                }

                if (command == "salva") {
                    save(Userss, CompanyObj, Groups, menu1.GetUserFile(), menu1.GetPostFile(), menu1.GetRelationFile());
                    cout << "Files salvati" << endl;
                }

                if (command == "mostra") {
                    if (argument == "S") {
                        cout << "Questi sono gli utenti semplici presenti sul social:" << endl << endl;

                        showSUser(Userss);

                    } else if (argument == "A") {
                        cout << "Questi sono le aziende presenti sul social:" << endl << endl;
                        showCUser(CompanyObj);

                    } else if (argument == "G") {
                        cout << "Questi sono i gruppi presenti sul social:" << endl << endl;
                        showGUser(Groups);
                    } else { cout << "Errore di immissione parametro" << endl; }


                }

                if (command == "rimuovi") {
                    if (common(argument, Utentii) or common(argument, groups_usernames) or
                        common(argument, company_usernames)) {
                        string response;
                        cout << "Sei sicuro di voler rimuovere " << argument << " ? (Rispondi SI o NO)" << endl;
                        do {
                            cout << "rimuovere " << argument << "?>";

                            getline(cin.ignore(EOF), response);
                            if (cin.eof()) {
                                raise(SIGINT);
                            }

                        } while (!(response == "SI" or response == "NO"));
                        if (response == "SI") {
                            long pos;


                            switch (getType(argument, Utentii, company_usernames, groups_usernames)) {
                                case 'S':
                                    pos = getVecPos(argument, Utentii);

                                    Utentii.erase(Utentii.begin() + pos);
                                    Userss.erase(Userss.begin() + pos);

                                    cout << "Utenti aggiornati" << endl;

                                    /**Now i eliminate traces from others g_users**/

                                    /*with people*/

                                    for (int i = 0; i < Userss.size(); i++) {
                                        if (common(argument, Userss[i].GetFriends())) {
                                            vector<string> friends_update = Userss[i].GetFriends();
                                            long f_pos = getVecPos(argument, friends_update);
                                            friends_update.erase(friends_update.begin() + f_pos);
                                            Userss[i].SetFriends(friends_update);
                                        }
                                        if (common(argument, Userss[i].GetKnowed())) {
                                            vector<string> know_update = Userss[i].GetKnowed();
                                            long k_pos = getVecPos(argument, know_update);
                                            know_update.erase(know_update.begin() + k_pos);
                                            Userss[i].SetKnowed(know_update);
                                        }
                                        if (common(argument, Userss[i].GetSons())) {
                                            vector<string> sons_update = Userss[i].GetSons();
                                            long s_pos = getVecPos(argument, sons_update);
                                            sons_update.erase(sons_update.begin() + s_pos);
                                            Userss[i].SetSons(sons_update);
                                        }

                                        if (argument == Userss[i].GetFather()) {
                                            Userss[i].SetFather("");
                                        }
                                        if (argument == Userss[i].GetMother()) {
                                            Userss[i].SetMother("");
                                        }
                                        /* With posts */
                                        if (Userss[i].GetNPosts() > 0) {
                                            vector<Post> posts = Userss[i].getPost();
                                            for (unsigned long post_pos = 0; post_pos < posts.size(); post_pos++) {
                                                if (common(argument, posts[post_pos].likes)) {
                                                    long l_pos = getVecPos(argument, posts[post_pos].likes);
                                                    posts[post_pos].likes.erase(posts[post_pos].likes.begin() + l_pos);

                                                }
                                                if (common(argument, posts[post_pos].dislikes)) {
                                                    long dl_pos = getVecPos(argument,
                                                                            posts[post_pos].dislikes);
                                                    posts[post_pos].dislikes.erase(
                                                            posts[post_pos].dislikes.begin() + dl_pos);
                                                }

                                            }
                                            Userss[i].SetPost(posts);
                                        }

                                    }

                                    /*with companyes*/
                                    for (int i = 0; i < CompanyObj.size(); i++) {
                                        if (common(argument, CompanyObj[i].GetEmployees())) {
                                            vector<string> empl_update = CompanyObj[i].GetEmployees();
                                            long e_pos = getVecPos(argument, empl_update);
                                            empl_update.erase(empl_update.begin() + e_pos);
                                            CompanyObj[i].SetEmployees(empl_update);
                                        }

                                    }
                                    /*With Groups*/
                                    for (int i = 0; i < Groups.size(); i++) {
                                        if (common(argument, Groups[i].GetComponents())) {
                                            vector<string> comp_update = Groups[i].GetComponents();
                                            long c_pos = getVecPos(argument, comp_update);
                                            comp_update.erase(comp_update.begin() + c_pos);
                                            Groups[i].SetComponents(comp_update);
                                        }

                                    }
                                    break;


                                case 'G':
                                    /*** Removing from usernames list and objects list ***/
                                    pos = getVecPos(argument, groups_usernames);
                                    Groups.erase(Groups.begin() + pos);
                                    groups_usernames.erase(groups_usernames.begin() + pos);


                                    for (int i = 0; i < Userss.size(); i++) {
                                        if (common(argument, Userss[i].GetSubsGroups())) {
                                            vector<string> subs_update = Userss[i].GetSubsGroups();
                                            long s_pos = getVecPos(argument, subs_update);
                                            subs_update.erase(subs_update.begin() + s_pos);
                                            Userss[i].SetSubsGroups(subs_update);
                                        }

                                    }
                                    break;

                                case 'C':
                                    pos = getVecPos(argument, company_usernames);
                                    company_usernames.erase(company_usernames.begin() + pos);
                                    CompanyObj.erase(CompanyObj.begin() + pos);

                                    for (int i = 0; i < CompanyObj.size(); i++) {
                                        if (CompanyObj[i].GetNSubsidiary() > 0) {
                                            if (common(argument, CompanyObj[i].GetSubsidiary())) {
                                                vector<string> c_update = CompanyObj[i].GetSubsidiary();
                                                long c_pos = getVecPos(argument, c_update);
                                                c_update.erase(c_update.begin() + c_pos);
                                                CompanyObj[i].SetSubsidiary(c_update);
                                            }
                                        }
                                    }


                                    break;
                                default:
                                    cerr << "ERROR OCCURRED, exiting" << endl;
                                    exit(EXIT_FAILURE);
                                    break;

                            }/*end switch*/
                        }
                    } else { cout << "Errore di immissione: Utente inesistente" << endl; }
                }
                if (command == "accesso") {
                    if (common(argument, Utentii) or common(argument, groups_usernames) or
                        common(argument, company_usernames)) {

                        if (common(argument, Utentii)) {
                                auto pos = getVecPos(argument, Utentii);
                                cout << "Informazioni relative a @" << Userss[pos].getUsername() << endl << endl;
                                showSUser(Userss[pos]);
                                Menu menu2;
                                menu2.SetPos(MODIFY_MENU);
                                cout
                                        << "Scrivi l'informazione che vuoi modificare seguita dalla nuova informazione (es. citta torino), digita exit per uscire"
                                        << endl;
                            vector<string> subq;

                                while (menu2.GetPos() > 0) {
                                    subq = menu2.subQuery();

                                    if (subq.size() == 2) {

                                        Userss[pos] = modifySUser(Userss[pos], subq[0], subq[1]);
                                    }

                                }
                            cout << "Dati aggiornati" << endl;
                            showSUser(Userss[pos]);


                        }

                        if (common(argument, company_usernames)) {
                            cout << endl << endl;
                            auto pos = getVecPos(argument, company_usernames);
                            showCUser(CompanyObj[pos]);
                            cout << endl;
                            Menu menu2;
                            menu2.SetPos(MODIFY_MENU);
                            cout
                                    << "Scrivi l'informazione che vuoi modificare seguita dalla nuova informazione (es. sedefiscale Zurigo), digita exit per uscire"
                                    << endl;
                            vector<string> subq;

                            while (menu2.GetPos() > 0) {
                                subq = menu2.subQuery();

                                if (subq.size() == 2) {

                                    CompanyObj[pos] = modifyCUser(CompanyObj[pos], subq[0], subq[1]);
                                }

                            }
                            cout << "Dati aggiornati" << endl;
                            showCUser(CompanyObj[pos]);

                        }
                        if (common(argument, groups_usernames)) {
                            cout << endl << endl;
                            auto pos = getVecPos(argument, groups_usernames);
                            showGUser(Groups[pos]);
                            cout << endl;
                            Menu menu2;
                            menu2.SetPos(MODIFY_MENU);
                            cout
                                    << "Scrivi l'informazione che vuoi modificare seguita dalla nuova informazione (es. tipologia Associazione Culturale), digita exit per uscire"
                                    << endl;
                            vector<string> subq;

                            while (menu2.GetPos() > 0) {
                                subq = menu2.subQuery();

                                if (subq.size() == 2) {

                                    Groups[pos] = modifyGUser(Groups[pos], subq[0], subq[1]);
                                }


                            }
                            cout << "Dati aggiornati" << endl;
                            showGUser(Groups[pos]);
                        }

                    } else { cout << "Errore di immissione: Utente inesistente" << endl; }

                }

                if (command == "crea") {
                    if (argument == "S") {
                        Menu menu2;
                        int flag = 0;
                        menu2.SetPos(CREATION_MENU);
                        cout
                                << "Hai scelto di creare un nuovo utente semplice"
                                << endl;
                        User _to_add;
                        string str;
                        cout << "Inserisci un ID" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setUsername(str);

                        cout << "Inserisci il nome" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setName(str);
                        cout << "Inserisci la data di nascita" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setDate(str);

                        for (int i = 0; i < _to_add.getUsername().length(); i++) {
                            string _u = _to_add.getUsername();
                            if (!isalnum(_u.at(i))) {

                                cout << "Hai inserito un ID non valido,";
                                menu2.SetPos(EXIT_MENU);
                                flag++;
                            }
                        }

                        if (common(_to_add.getUsername(), Utentii) or common(_to_add.getUsername(), groups_usernames) or
                            common(_to_add.getUsername(), company_usernames)) {
                            cout << "L' ID che ha inserito è già presente,";
                            flag++;
                            menu2.SetPos(EXIT_MENU);

                        }

                        if (!isDateCorrect(_to_add.getDate())) {
                            cout << "Hai inserito una data scorretta,";
                            flag++;
                            menu2.SetPos(EXIT_MENU);
                        }
                        if (flag == 0) {
                            _to_add.setDays();
                            _to_add.setAge();
                            Userss.emplace_back(_to_add);
                            Utentii.emplace_back(_to_add.getUsername());
                            cout << "Ho aggiunto il nuovo utente, per aggiungere altre informazioni accedi" << endl;
                        } else { cout << " non sarà aggiunto alcun utente" << endl; }

                    } else if (argument == "G") {

                        Menu menu2;
                        int flag = 0;
                        menu2.SetPos(CREATION_MENU);
                        cout
                                << "Hai scelto di creare un nuovo utente gruppo"
                                << endl;
                        Group _to_add;
                        string str;
                        cout << "Inserisci un ID" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setUsername(str);

                        cout << "Inserisci il nome" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setName(str);
                        cout << "Inserisci la data di creazione" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setDate(str);
                        for (int i = 0; i < _to_add.getUsername().length(); i++) {
                            string _u = _to_add.getUsername();
                            if (!isalnum(_u.at(i))) {
                                cout << "Hai inserito un ID non valido,";
                                menu2.SetPos(EXIT_MENU);
                                flag++;
                            }
                        }
                        if (common(_to_add.getUsername(), Utentii) or common(_to_add.getUsername(), groups_usernames) or
                            common(_to_add.getUsername(), company_usernames)) {
                            cout << "L' ID che ha inserito è già presente,";
                            menu2.SetPos(EXIT_MENU);
                            flag++;
                        }

                        if (!isDateCorrect(_to_add.getDate())) {
                            cout << "Hai inserito una data scorretta,";
                            menu2.SetPos(EXIT_MENU);
                            flag++;
                        }

                        if (flag == 0) {
                            Groups.emplace_back(_to_add);
                            groups_usernames.emplace_back(_to_add.getUsername());
                            cout << "Ho aggiunto il nuovo utente gruppo, per aggiungere altre informazioni accedi"
                                 << endl;
                        } else { cout << " non sarà aggiunto alcun utente" << endl; }


                    } else if (argument == "A") {
                        Menu menu2;
                        int flag = 0;
                        menu2.SetPos(CREATION_MENU);
                        cout
                                << "Hai scelto di creare un nuovo utente azienda"
                                << endl;
                        Company _to_add;
                        string str;
                        cout << "Inserisci un ID" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setUsername(str);

                        cout << "Inserisci il nome" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setName(str);
                        cout << "Inserisci la data di creazione" << endl;
                        str = menu2.getQuery();
                        str = trim(str);
                        _to_add.setDate(str);
                        for (int i = 0; i < _to_add.getUsername().length(); i++) {
                            string _u = _to_add.getUsername();
                            if (!isalnum(_u.at(i))) {

                                cout << "Hai inserito un ID non valido,";
                                menu2.SetPos(EXIT_MENU);
                                flag++;
                            }
                        }
                        if (common(_to_add.getUsername(), Utentii) or common(_to_add.getUsername(), groups_usernames) or
                            common(_to_add.getUsername(), company_usernames)) {
                            cout << "L' ID che ha inserito è già presente,";
                            menu2.SetPos(EXIT_MENU);
                            flag++;
                        }

                        if (!isDateCorrect(_to_add.getDate())) {
                            cout << "Hai inserito una data scorretta,";
                            menu2.SetPos(EXIT_MENU);
                            flag++;
                        }

                        if (flag == 0) {

                            CompanyObj.emplace_back(_to_add);
                            company_usernames.emplace_back(_to_add.getUsername());
                            cout << "Ho aggiunto il nuovo utente azienda, per aggiungere altre informazioni accedi"
                                 << endl;
                        } else { cout << " non sarà aggiunto alcun utente" << endl; }


                    } else { cout << "Errore di immissione parametro" << endl; }

                }
                break;
            case POST_MENU:


                if (!isMngrCmd(command)) {
                    cerr << "Comando Sconosciuto" << endl;
                }
                if (command == "start") {
                    menu1.SetPos(START_MENU);
                }

                if (command == "mostra") {
                    if (argument == "S") {
                        cout << "Questi sono gli utenti semplici presenti sul social:" << endl << endl;

                        showSUser(Userss);

                    } else if (argument == "A") {
                        cout << "Questi sono le aziende presenti sul social:" << endl << endl;
                        showCUser(CompanyObj);

                    } else if (argument == "G") {
                        cout << "Questi sono i gruppi presenti sul social:" << endl << endl;
                        showGUser(Groups);
                    } else { cout << "Errore di immissione parametro" << endl; }
                }
                if (command == "salva") {
                    save(Userss, CompanyObj, Groups, menu1.GetUserFile(), menu1.GetPostFile(), menu1.GetRelationFile());
                    cout << "Ho salvato i file" << endl;

                }
                if (command == "accesso") {

                    if (common(argument, Utentii) or common(argument, groups_usernames) or
                        common(argument, company_usernames)) {
                        Menu menu2;
                        menu2.SetPos(ID_POST_MENU);
                        menu2.SetUserRef(argument);
                        menu2.SetSubMenu('Y');
                        helpScreen(menu2.GetPos());
                        long pos; /**When the generic user access to this, is useful to know the typr and position the position in its container */
                        char liker_enabled = 'N';
                        char type;
                        if (common(argument, Utentii)) {
                            pos = getVecPos(argument, Utentii);
                            liker_enabled = 'Y';
                            type = 'S';
                        }

                        if (common(argument, company_usernames)) {
                            pos = getVecPos(argument, company_usernames);
                            type = 'C';
                        }

                        if (common(argument, groups_usernames)) {
                            pos = getVecPos(argument, groups_usernames);
                            type = 'G';
                        }


                        while (menu2.GetPos() > 0) {

                            string _command;

                            _command = menu2.getQuery();

                            if (_command == "aggiungi") {

                                int flag = 0;

                                cout
                                        << "Hai scelto di creare una nuova notizia"
                                        << endl;
                                Post _to_add;
                                string str;

                                _to_add.username = argument;
                                cout << "Inserisci il messaggio" << endl;
                                str = menu2.getQuery();
                                str = trim(str);
                                _to_add.message = str;
                                cout << "Inserisci la data di creazione" << endl;
                                str = menu2.getQuery();
                                str = trim(str);
                                _to_add.sdate = str;


                                if (!isDateCorrect(_to_add.sdate)) {
                                    cout << "Hai inserito una data scorretta,";
                                    flag++;
                                }

                                /*Now because date control if the post's date is before the gUser date of birth (Not Permitted) */

                                if (flag == 0) {
                                    if (common(argument, Utentii)) {

                                        if (daysByDate(_to_add.sdate) < daysByDate(Userss[pos].getDate())) {
                                            Userss[pos].addPost(_to_add);
                                        } else {
                                            cout
                                                    << "Hai inserito una data scorretta, non puoi avere un post con una data antecedente alla data di nascita"
                                                    << endl;
                                        }

                                    }
                                    if (common(argument, company_usernames)) {
                                        if (daysByDate(_to_add.sdate) < daysByDate(CompanyObj[pos].getDate())) {

                                            CompanyObj[pos].addPost(_to_add);
                                        } else {
                                            cout
                                                    << "Hai inserito una data scorretta, non puoi avere un post con una data antecedente alla data di creazione"
                                                    << endl;
                                        }


                                    }
                                    if (common(argument, groups_usernames)) {

                                        if (daysByDate(_to_add.sdate) < daysByDate(Groups[pos].getDate())) {
                                            Groups[pos].addPost(_to_add);
                                        } else {
                                            cout
                                                    << "Hai inserito una data scorretta, non puoi avere un post con una data antecedente alla data di nascita"
                                                    << endl;
                                        }


                                    }

                                    cout
                                            << "Ho aggiunto il nuovo post, per aggiungere like/dislikes serviti delle altre sezioni"
                                            << endl;
                                } else { cout << " non sarà aggiunto alcun post" << endl; }


                            }

                            if (_command == "mostra") {
                                showPosts(Userss, CompanyObj, Groups, menu2.GetUserRef());


                                cout << endl << "Post di utenti azienda" << endl;
                                for (int _pos = 0; _pos < CompanyObj.size(); _pos++) {
                                    vector<Post> _to_show = CompanyObj[_pos].getPost();

                                    for (auto i = 0; i < _to_show.size(); i++) {
                                        cout << _to_show[i];

                                        if (common(menu2.GetUserRef(), _to_show[i].likes)) {
                                            cout << LIKE;
                                        }
                                        if (common(menu2.GetUserRef(), _to_show[i].dislikes)) {
                                            cout << DISLIKE;
                                        }
                                        cout << endl;
                                    }

                                }

                            }
                            if (_command == "rimuovi") {
                                switch (type) {
                                    case 'S':
                                        if (Userss[pos].getPost().empty()) {
                                            cout << "Non sono presenti presenti post nel tuo account" << endl;
                                        } else {
                                            int answer = -1;
                                            int post_number = 0;
                                            vector<Post> _to_show = Userss[pos].getPost();
                                            cout << "Segli la posizione del post che vuoi eliminare" << endl;
                                            for (post_number = 0; post_number < _to_show.size(); post_number++) {
                                                cout << "Pos [" << post_number << "] " << _to_show[post_number];
                                            }
                                            cin >> answer;
                                            if (answer >= 0 and answer < post_number) {
                                                _to_show.erase(_to_show.begin() + answer);
                                                Userss[pos].loadPosts(_to_show);
                                                cout << "Post rimosso" << endl;
                                            } else { cout << "Hai inserito una posizione scorretta" << endl; }


                                        }
                                        break;

                                    case 'C':
                                        if (CompanyObj[pos].getPost().empty()) {
                                            cout << "Non sono presenti presenti post nel tuo account" << endl;
                                        } else {
                                            int answer = -1;
                                            int post_number = 0;
                                            vector<Post> _to_show = CompanyObj[pos].getPost();
                                            cout << "Segli la posizione del post che vuoi eliminare" << endl;
                                            for (post_number = 0; post_number < _to_show.size(); post_number++) {
                                                cout << "Pos [" << post_number << "] " << _to_show[post_number];
                                            }
                                            cin >> answer;
                                            if (answer >= 0 and answer < post_number) {
                                                _to_show.erase(_to_show.begin() + answer);
                                                Userss[pos].loadPosts(_to_show);
                                                cout << "Post rimosso" << endl;
                                            } else { cout << "Hai inserito una posizione scorretta" << endl; }


                                        }
                                        break;
                                    case 'G':

                                        if (Groups[pos].getPost().empty()) {
                                            cout << "Non sono presenti presenti post nel tuo account" << endl;
                                        } else {
                                            int answer = -1;
                                            int post_number = 0;
                                            vector<Post> _to_show = Groups[pos].getPost();
                                            cout << "Segli la posizione del post che vuoi eliminare" << endl;
                                            for (post_number = 0; post_number < _to_show.size(); post_number++) {
                                                cout << "Pos [" << post_number << "] " << _to_show[post_number];
                                            }
                                            cin >> answer;
                                            if (answer >= 0 and answer < post_number) {
                                                _to_show.erase(_to_show.begin() + answer);
                                                Groups[pos].loadPosts(_to_show);
                                                cout << "Post rimosso" << endl;
                                            } else { cout << "Hai inserito una posizione scorretta" << endl; }


                                        }

                                        break;

                                    default:
                                        cerr << "ERROR"; /*Almost Impossible*/
                                }
                            }
                            if (_command == "apprezzamenti") {
                                long _to_evalutate = totPosts(Userss, CompanyObj, Groups);
                                long _pos = 0;
                                if (type == 'S') {

                                    showPosts(Userss, CompanyObj, Groups, menu2.GetUserRef());
                                    cout << endl;

                                    Menu *m3 = new Menu;
                                    m3->SetPos(LIKE_MENU);
                                    m3->SetSubMenu('Y');
                                    // string _user_logged=menu2.GetUserRef();
                                    m3->SetUserRef(menu2.GetUserRef());

                                    while (m3->GetPos() > 0) {

                                        vector<string> opinion_query;
                                        opinion_query = m3->subQuery();

                                        if (!opinion_query.empty()) {
                                            if ((opinion_query[0] == "like" or opinion_query[0] == "dislike") and
                                                isnumerical(opinion_query[1])) {

                                                auto pos_post_to_appreciate = stod(opinion_query[1]);
                                                if (pos_post_to_appreciate >= 0 and
                                                    pos_post_to_appreciate < _to_evalutate) {
                                                    /***LIKE/DISLIKE CASE CODE GOES HERE ***/
                                                    _pos = 0; /* Pos of the ID */
                                                    long _ppost = 0; /*Pos of Post*/
                                                    _to_evalutate = 0; /* It will be the sum of _pos and _ppost */

                                                    if (opinion_query[0] == "like") {

                                                        while (_pos < Userss.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < Userss[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */

                                                                    if (common(m3->GetUserRef(),
                                                                               Userss[_pos].getPost()[_ppost].likes)) {
                                                                        /**Removing like**/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      Userss[_pos].getPost()[_ppost].dislikes)) {
                                                                        /*If there is a dislike, it will be converted to like*/
                                                                        /*Removing dislike and add like*/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding Like **/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);
                                                                    }

                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }
                                                        _pos = 0;
                                                        while (_pos < CompanyObj.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < CompanyObj[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */

                                                                    if (common(m3->GetUserRef(),
                                                                               CompanyObj[_pos].getPost()[_ppost].likes)) {
                                                                        /**Removing like**/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      CompanyObj[_pos].getPost()[_ppost].dislikes)) {
                                                                        /*If there is a dislike, it will be converted to like*/
                                                                        /*Removing dislike and add like*/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding Like **/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);
                                                                    }


                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }
                                                        _pos = 0;
                                                        while (_pos < Groups.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < Groups[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */
                                                                    if (common(m3->GetUserRef(),
                                                                               Groups[_pos].getPost()[_ppost].likes)) {
                                                                        /**Removing like**/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      Groups[_pos].getPost()[_ppost].dislikes)) {
                                                                        /*If there is a dislike, it will be converted to like*/
                                                                        /*Removing dislike and add like*/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding Like **/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].addLike(m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);
                                                                    }
                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }
                                                        /*show code*/


                                                        /*end show code */
                                                    }
                                                    if (opinion_query[0] == "dislike") {


                                                        while (_pos < Userss.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < Userss[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */

                                                                    if (common(m3->GetUserRef(),
                                                                               Userss[_pos].getPost()[_ppost].dislikes)) {
                                                                        /**Removing dislike**/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      Userss[_pos].getPost()[_ppost].likes)) {
                                                                        /*If there is a like, it will be converted to dislike*/
                                                                        /*Removing like and add dislike*/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding DisLike **/
                                                                        vector<Post> _to_modify = Userss[_pos].getPost();
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        Userss[_pos].loadPosts(_to_modify);
                                                                    }


                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }
                                                        _pos = 0;
                                                        while (_pos < CompanyObj.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < CompanyObj[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */

                                                                    if (common(m3->GetUserRef(),
                                                                               CompanyObj[_pos].getPost()[_ppost].dislikes)) {
                                                                        /**Removing dislike**/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      CompanyObj[_pos].getPost()[_ppost].likes)) {
                                                                        /*If there is a like, it will be converted to dislike*/
                                                                        /*Removing like and add dislike*/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding DisLike **/
                                                                        vector<Post> _to_modify = CompanyObj[_pos].getPost();
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        CompanyObj[_pos].loadPosts(_to_modify);
                                                                    }


                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }
                                                        _pos = 0;
                                                        while (_pos < Groups.size()) {
                                                            _ppost = 0;

                                                            while (_ppost < Groups[_pos].getPost().size()) {

                                                                if (_to_evalutate == pos_post_to_appreciate) {
                                                                    /* Reaching the N position */

                                                                    if (common(m3->GetUserRef(),
                                                                               Groups[_pos].getPost()[_ppost].dislikes)) {
                                                                        /**Removing dislike**/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].removeDislike(
                                                                                m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);

                                                                    } else if (common(m3->GetUserRef(),
                                                                                      Groups[_pos].getPost()[_ppost].likes)) {
                                                                        /*If there is a like, it will be converted to dislike*/
                                                                        /*Removing like and add dislike*/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].removeLike(m3->GetUserRef());
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);

                                                                    } else {/** Adding DisLike **/
                                                                        vector<Post> _to_modify = Groups[_pos].getPost();
                                                                        _to_modify[_ppost].addDislike(m3->GetUserRef());
                                                                        Groups[_pos].loadPosts(_to_modify);
                                                                    }


                                                                }
                                                                _to_evalutate++;


                                                                _ppost++;
                                                            }
                                                            _pos++;
                                                        }


                                                        /**End dislike part**/
                                                    }

                                                    /***END LIKE/DISLIKE CASE CODE  ***/
                                                } else {
                                                    cout << "Errore, devi inserire una delle posizioni indicate"
                                                         << endl;
                                                }


                                            } else { cout << "Errore di inserimento" << endl; }
                                        }//else{cout<<"Errore di inserimento: Devi inserire like/dislike e una posizione corretta"<<endl;}


                                        cout << endl << "Ecco gli apprezzamenti:" << endl << endl;
                                        showPosts(Userss, CompanyObj, Groups, m3->GetUserRef());
                                        cout << endl;
                                    }

                                    delete m3;

                                } else {
                                    cout
                                            << "Sezione inaccessibile: Solo gli utenti semplici possono esprimere apprezzamenti"
                                            << endl;
                                }

                            }

                            if (_command == "modifica") {
                                vector<Post> _posts_to_modify;
                                switch (type) {
                                    case 'S':
                                        string selection;
                                        int sel;
                                        _posts_to_modify = Userss[pos].getPost();
                                        if (!_posts_to_modify.empty()) {
                                            cout << "Ecco tutti i post di @" << menu2.GetUserRef()
                                                 << ", selezione quello che voui modificare" << endl;
                                            vector<Post>::iterator i_post;
                                            /*First print all users's post with N pos to select*/
                                            int n = 0;
                                            for (i_post = _posts_to_modify.begin();
                                                 i_post != _posts_to_modify.end(); i_post++) {
                                                cout << "Pos [" << n << "] " << *i_post << endl;
                                                n++;
                                            }
                                            do {
                                                cout << ">";
                                                getline(cin, selection);
                                            }
                                            while (selection.empty());
                                            if (isnumerical(selection) and !selection.empty()) {


                                                sel = stoi(selection);

                                                Post _post_to_modify;
                                                _post_to_modify = _posts_to_modify[sel];
                                                Menu *m3 = new Menu;
                                                m3->SetPos(MODIFY_MENU);
                                                m3->SetSubMenu('Y');
                                                cout
                                                        << "Scrivi l'informazione che vuoi modificare seguita dalla nuova informazione (es. messaggio ciao),digita exit per uscire"
                                                        << endl;
                                                vector<string> subquery;

                                                while (m3->GetPos() > 0) {
                                                    subquery = m3->subQuery();

                                                    if (subquery.size() == 2) {

                                                        _post_to_modify = modifyPost(_post_to_modify, subquery[0],
                                                                                     subquery[1]);
                                                        _posts_to_modify[sel] = _post_to_modify;
                                                        Userss[pos].loadPosts(_posts_to_modify);
                                                    } else { cout << "Errore di immissione" << endl; }

                                                }
                                                cout << "Post aggiornato" << endl;
                                                Userss[pos].getPost();

                                                delete m3;

                                            } else { cout << "Devi inserire un numero intero positivo" << endl; }


                                        } else {
                                            cout << "L' utente @" << menu2.GetUserRef()
                                                 << " non ha pubblicato nulla, vai su aggiungi per creare un nuovo post"
                                                 << endl;
                                        }


                                }


                            }/**end modify menu **/
                            if (_command == "salva") {
                                save(Userss, CompanyObj, Groups, "users.antocoon", "posts.antocoon", "relations.antocoon");
                                cout << "Ho salvato i file" << endl;
                            }

                            /**I am in the access menu**/




                        }
                    } else { cout << "Hai inserito un utente inesistente" << endl; }


                }

                break;/*Already in menu1 */

            case RELATION_MENU:
                if (command == "salva") {
                    save(Userss, CompanyObj, Groups, menu1.GetUserFile(), menu1.GetPostFile(), menu1.GetRelationFile());
                    cout << "Ho salvato i file" << endl;
                }
                if (command == "mostra") {
                    if (argument == "S") {
                        cout << "Questi sono gli utenti semplici presenti sul social:" << endl << endl;

                        showSUser(Userss);

                    } else if (argument == "A") {
                        cout << "Questi sono le aziende presenti sul social:" << endl << endl;
                        showCUser(CompanyObj);

                    } else if (argument == "G") {
                        cout << "Questi sono i gruppi presenti sul social:" << endl << endl;
                        showGUser(Groups);
                    } else { cout << "Errore di immissione parametro" << endl; }
                }

                if (command == "accesso") {
                    if (common(argument, groups_usernames)) {


                        cout << "Sei entrato nell' utente gruppo @" << argument << endl;
                        Menu *m3 = new Menu;
                        m3->SetSubMenu('Y');
                        m3->SetPos(GROUP_MENU);
                        m3->SetUserRef(argument);
                        helpScreen(m3->GetPos());
                        cout << endl;
                        long pos = getVecPos(m3->GetUserRef(), groups_usernames);

                        cout << "Questi sono i componenti" << endl;
                        cout << Groups[pos].GetComponents() << endl;

                        vector<string> _insertion;
                        vector<string> _components;//=Groups[pos].GetComponents();



                        while (m3->GetPos() > 0) {
                            _insertion = m3->subQuery();

                            if (_insertion.size() == 2) {
                                _components = Groups[pos].GetComponents();


                                if ((_insertion[0] == "aggiungi" or _insertion[0] == "rimuovi") and
                                    !_insertion[1].empty() and common(_insertion[1], Utentii)) {
                                    if (_insertion[0] == "aggiungi") {

                                        if (common(_insertion[1], _components)) {
                                            cout << "L' utente @" << m3->GetUserRef() << " include gia @"
                                                 << _insertion[1] << ", modifiche non effettuate" << endl;
                                        } else {
                                            Groups[pos].AddComponent(_insertion[1]);
                                            cout << "Ho aggiunto @" << _insertion[1] << " al gruppo @"
                                                 << m3->GetUserRef() << endl;
                                        }


                                    }


                                    if (_insertion[0] == "rimuovi") {
                                        if (common(_insertion[1], _components)) {


                                            Groups[pos].RemoveComponent(_insertion[1]);

                                            cout << "Ho rimosso @" << _insertion[1] << " dal gruppo @"
                                                 << m3->GetUserRef() << endl;
                                            long to_erase_pos = getVecPos(_insertion[1], _components);
                                            _components.erase(_components.begin() + to_erase_pos);
                                            Groups[pos].SetComponents(_components);
                                            cout << Groups[pos].GetComponents();
                                        } else {
                                            cout << "L' utente @" << _insertion[1] << " non fa parte del gruppo @"
                                                 << m3->GetUserRef() << ", non saranno apportate modifiche" << endl;

                                        }

                                    }


                                } else { cout << "Errore di immissione" << endl; }

                            }
                        }

                        delete m3;

                    } else if (common(argument, company_usernames)) { /*I am yet in the access menu */

                        cout << "Sei entrato nell' utente azienda @" << argument << endl;
                        Menu *m3 = new Menu;
                        m3->SetSubMenu('Y');
                        m3->SetPos(COMPANY_MENU);
                        m3->SetUserRef(argument);
                        helpScreen(m3->GetPos());
                        cout << endl;
                        long pos = getVecPos(m3->GetUserRef(), company_usernames);

                        cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary() << endl;
                        cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees() << endl;
                        cout << endl << endl;

                        vector<string> _insertion;
                        vector<string> _components; /*** this vector stores the employees or the subsidiary, it depends of insertions ***/

                        while (m3->GetPos() > 0) {
                            _insertion = m3->subQuery();

                            if (_insertion.size() == 2) {

                                /* Case employees */
                                if ((_insertion[0] == "aggiungi" or _insertion[0] == "rimuovi") and
                                    !_insertion[1].empty() and common(_insertion[1], Utentii)) {

                                    _components = CompanyObj[pos].GetEmployees();

                                    if (_insertion[0] == "aggiungi") {

                                        if (common(_insertion[1], _components)) {
                                            cout << "L' azienda @" << m3->GetUserRef() << " ha gia il dipendente @"
                                                 << _insertion[1] << ", modifiche non effettuate" << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        } else {

                                            vector<string> _emp = CompanyObj[pos].GetEmployees();
                                            _emp.emplace_back(_insertion[1]);
                                            CompanyObj[pos].SetEmployees(_emp);
                                            cout << "Ho aggiunto @" << _insertion[1] << " all' azienda @"
                                                 << m3->GetUserRef() << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;

                                        }


                                    }


                                    if (_insertion[0] == "rimuovi") {
                                        if (common(_insertion[1], _components)) {

                                            long to_erase_pos = getVecPos(_insertion[1], _components);
                                            _components.erase(_components.begin() + to_erase_pos);
                                            CompanyObj[pos].SetEmployees(_components);

                                            cout << "Ho rimosso @" << _insertion[1] << " dal gruppo @"
                                                 << m3->GetUserRef() << endl;
                                            cout << Groups[pos].GetComponents();
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        } else {
                                            cout << "L' utente @" << _insertion[1] << " non fa parte dell' azienda @"
                                                 << m3->GetUserRef() << ", non saranno apportate modifiche" << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        }

                                    }

                                    /*case subsidiries*/
                                } else if ((_insertion[0] == "aggiungi" or _insertion[0] == "rimuovi") and
                                           !_insertion[1].empty() and common(_insertion[1], company_usernames)) {
                                    _components = CompanyObj[pos].GetSubsidiary();

                                    if (_insertion[0] == "aggiungi") {

                                        if (_insertion[1] != m3->GetUserRef()) {
                                        if (common(_insertion[1], _components)) {
                                            cout << "L' azienda @" << m3->GetUserRef() << " ha gia la consociata @"
                                                 << _insertion[1] << ", modifiche non effettuate" << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        } else {

                                            vector<string> _subs = CompanyObj[pos].GetSubsidiary();
                                            _subs.emplace_back(_insertion[1]);
                                            CompanyObj[pos].SetSubsidiary(_subs);
                                            cout << "Ho aggiunto la consociata @" << _insertion[1] << " all' azienda @"
                                                 << m3->GetUserRef() << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;

                                        }
                                        } else {
                                            cout << "Errore: Hai inserito la stessa azienda a cui sei loggato, @"
                                                 << m3->GetUserRef() << endl;
                                        }

                                    }


                                    if (_insertion[0] == "rimuovi") {
                                        if (common(_insertion[1], _components)) {

                                            long to_erase_pos = getVecPos(_insertion[1], _components);
                                            _components.erase(_components.begin() + to_erase_pos);
                                            CompanyObj[pos].SetSubsidiary(_components);

                                            cout << "Ho rimosso @" << _insertion[1] << " dalle consociate di @"
                                                 << m3->GetUserRef() << endl;
                                            cout << Groups[pos].GetComponents();
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        } else {
                                            cout << "L' azienda @" << _insertion[1]
                                                 << " non fa parte delle consociate dell' azienda @"
                                                 << m3->GetUserRef() << ", non saranno apportate modifiche" << endl;
                                            cout << "Stampo le consociate:" << endl << CompanyObj[pos].GetSubsidiary()
                                                 << endl;
                                            cout << "Stampo i dipendenti:" << endl << CompanyObj[pos].GetEmployees()
                                                 << endl;
                                            cout << endl << endl;
                                        }

                                    }


                                } else { cout << "Errore di immissione" << endl; }

                            }
                        }

                        delete m3;


                    } else if (common(argument, Utentii)) {
                        /*** Entering now in the people relation modify menu ***/
                        Menu *m3 = new Menu;
                        m3->SetSubMenu('Y');
                        m3->SetUserRef(argument);
                        m3->SetPos(USER_REL_MENU);
                        helpScreen(m3->GetPos());
                        cout << "Sei entrato nell' utente semplice @" << m3->GetUserRef() << endl;
                        long pos = getVecPos(m3->GetUserRef(), Utentii);

                        helpScreen(m3->GetPos());

                        cout << endl << endl;
                        vector<string> _insertion;

                        while (m3->GetPos() > 0) {
                            cout << endl;
                            cout << "Stampo le relazioni di @" << m3->GetUserRef() << endl;
                            cout << "Stampo gli amici:" << endl << Userss[pos].GetFriends() << endl;
                            cout << "Stampo i conoscenti:" << endl << Userss[pos].GetKnowed() << endl;
                            cout << "Stampo il padre:  " << Userss[pos].GetFather() << endl;
                            cout << "Stampo la madre:  " << Userss[pos].GetMother() << endl;
                            cout << "Stampo il coniuge:  " << Userss[pos].GetMate() << endl;
                            cout << "Stampo i figli:" << endl << Userss[pos].GetSons() << endl;

                            cout << endl;
                            _insertion = m3->subQuery();
                            vector<string> _container; /*It stores friends, knowed_people....*/
                            if (_insertion[0] == "amico") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {
                                    _container = Userss[pos].GetFriends();

                                    if (common(_insertion[1], _container)) {
                                        //remove friend

                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " tra gli amici, verrà rimosso" << endl;

                                        long to_erase_pos = getVecPos(_insertion[1], _container);
                                        _container.erase(_container.begin() + to_erase_pos);
                                        Userss[pos].SetFriends(_container);
                                        cout << "Utente rimosso dagli amici" << endl;

                                    } else {
                                        //add friend
                                        _container.emplace_back(_insertion[1]);
                                        Userss[pos].SetFriends(_container);
                                        cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " l' amico @"
                                             << _insertion[1] << endl;

                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "conoscente") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {
                                    _container = Userss[pos].GetKnowed();

                                    if (common(_insertion[1], _container)) {
                                        //remove knowed

                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " tra i conoscenti, verrà rimosso" << endl;

                                        long to_erase_pos = getVecPos(_insertion[1], _container);
                                        _container.erase(_container.begin() + to_erase_pos);
                                        Userss[pos].SetKnowed(_container);
                                        cout << "Utente rimosso dai conoscenti" << endl;

                                    } else {
                                        //add knowed
                                        _container.emplace_back(_insertion[1]);
                                        Userss[pos].SetKnowed(_container);
                                        cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " il conoscente @"
                                             << _insertion[1] << endl;
                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "amico") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {
                                    _container = Userss[pos].GetFriends();

                                    if (common(_insertion[1], _container)) {
                                        //remove friend

                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " tra gli amici, verrà rimosso" << endl;

                                        long to_erase_pos = getVecPos(_insertion[1], _container);
                                        _container.erase(_container.begin() + to_erase_pos);
                                        Userss[pos].SetFriends(_container);
                                        cout << "Utente rimosso dagli amici" << endl;

                                    } else {
                                        //add friend
                                        _container.emplace_back(_insertion[1]);
                                        Userss[pos].SetFriends(_container);
                                        cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " l' amico @"
                                             << _insertion[1] << endl;

                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "help") {/*do nothing*/}
/********************************************************************************************************************************/
                            else if (_insertion[0] == "padre") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {


                                    if (_insertion[1] == Userss[pos].GetFather()) {


                                        /* Remove father from this user*/
                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " come padre, verrà rimosso" << endl;
                                        Userss[pos].SetFather("");
                                        /*remove this son from father*/
                                        long _fpos = getVecPos(_insertion[1], Utentii);
                                        vector<string> sons = Userss[_fpos].GetSons();
                                        long son_to_erase = getVecPos(m3->GetUserRef(), sons);
                                        sons.erase(sons.begin() + son_to_erase);
                                        Userss[_fpos].SetSons(sons);
                                        cout << "Utente rimosso " << endl;


                                    } else {
                                        //add father, but only if it is male and older than son

                                        if (Userss[getVecPos(_insertion[1], Utentii)].getSex() == 'M' and
                                            Userss[getVecPos(_insertion[1], Utentii)].getAge() >
                                            Userss[pos].getAge() + 13) {
                                            Userss[pos].SetFather(_insertion[1]);
                                            cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " il padre @"
                                                 << _insertion[1] << endl;

                                            /*Now add this son to the father*/
                                            long _fpos = getVecPos(_insertion[1], Utentii);
                                            vector<string> sons = Userss[_fpos].GetSons();
                                            sons.emplace_back(m3->GetUserRef());
                                            Userss[_fpos].SetSons(sons);


                                        } else {
                                            cout
                                                    << "Errore: Il padre deve essere un uomo e almeno più grande di qualche anno del figlio, modifica le info nel menu di gestione utenti"
                                                    << endl;
                                        }

                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "madre") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {


                                    if (_insertion[1] == Userss[pos].GetMother()) {
                                        /* Remove mother*/
                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " come madre, verrà rimossa" << endl;

                                        Userss[pos].SetMother("");
                                        /*remove this son from mother*/
                                        long _mpos = getVecPos(_insertion[1], Utentii);
                                        vector<string> sons = Userss[_mpos].GetSons();
                                        sons.erase(sons.begin() + getVecPos(m3->GetUserRef(), sons));
                                        Userss[_mpos].SetSons(sons);
                                        cout << "Utente rimosso " << endl;

                                    } else {
                                        //add mother, but only if it is female and older a tot years than son

                                        if (Userss[getVecPos(_insertion[1], Utentii)].getSex() == 'F' and
                                            Userss[getVecPos(_insertion[1], Utentii)].getAge() >
                                            Userss[pos].getAge() + 13) {
                                            Userss[pos].SetMother(_insertion[1]);
                                            cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " la madre @"
                                                 << _insertion[1] << endl;

                                            /*Now add this son to the mother*/
                                            long _mpos = getVecPos(_insertion[1], Utentii);
                                            vector<string> sons = Userss[_mpos].GetSons();
                                            sons.emplace_back(m3->GetUserRef());
                                            Userss[_mpos].SetSons(sons);

                                        } else {
                                            cout
                                                    << "Errore: La madre deve essere una donna e almeno più grande di qualche anno del figlio, modifica le info nel menu di gestione utenti"
                                                    << endl;
                                        }

                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "coniuge") {
                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {


                                    if (_insertion[1] == Userss[pos].GetMate()) {
                                        /* Remove mate*/
                                        cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                             << " come coniuge, verrà cancellato" << endl;

                                        Userss[pos].SetMate("");
                                        /*Now remove this from _inseryion[1]'s mate*/
                                        int _mpos = getVecPos(_insertion[1], Utentii);

                                        Userss[_mpos].SetMate("");

                                        cout << "Utente rimosso " << endl;

                                    } else {


                                        Userss[pos].SetMate(_insertion[1]);
                                        cout << "Ho aggiunto all' utente @" << m3->GetUserRef() << " il coniuge @"
                                             << _insertion[1] << endl;
                                        /*Now add this user to _insertion[1]'s mate*/
                                        int _mpos = getVecPos(_insertion[1], Utentii);

                                        Userss[_mpos].SetMate(m3->GetUserRef());

                                    }


                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "figlio") {


                                if (common(_insertion[1], Utentii) and _insertion[1] != m3->GetUserRef()) {

                                    /*This relation is modifiable only if the son have no parents, to avoid conflicts*/



                                    if (Userss[getVecPos(_insertion[1], Utentii)].GetParent(
                                            Userss[getVecPos(m3->GetUserRef(), Utentii)].getSex()).empty()) {

                                        if (common(_insertion[1], Userss[pos].GetSons())) {
                                            /* Remove son*/
                                            cout << "L' utente @" << m3->GetUserRef() << " ha già @" << _insertion[1]
                                                 << "tra i figli, verrà rimosso" << endl;

                                            vector<string> sons;
                                            sons = Userss[pos].GetSons();
                                            sons.erase(sons.begin() + getVecPos(_insertion[1], sons));
                                            Userss[pos].SetSons(sons);
                                            cout << "Utente rimosso " << endl;
                                            /*now remove son from this(parent)*/

                                            long _spos = getVecPos(_insertion[1], Utentii); /*son's pos in vector*/
                                            if (Userss[pos].getSex() == 'M') {
                                                Userss[_spos].SetFather("");
                                            }
                                            if (Userss[pos].getSex() == 'F') {
                                                Userss[_spos].SetMother("");
                                            }


                                        } else {
                                            //add son, but only of diffage(parent,son)>13

                                            if (Userss[getVecPos(_insertion[1], Utentii)].getAge() + 13 <
                                                Userss[pos].getAge()) {
                                                /*Adding son to this user*/
                                                vector<string> sons;
                                                sons = Userss[pos].GetSons();
                                                sons.emplace_back(_insertion[1]);
                                                Userss[pos].SetSons(sons);
                                                /*Adding this user as parent of _insertion[1]*/
                                                long _spos = getVecPos(_insertion[1], Utentii); /*son's pos in vector*/
                                                if (Userss[pos].getSex() == 'M') {
                                                    Userss[_spos].SetFather(m3->GetUserRef());
                                                }
                                                if (Userss[pos].getSex() == 'F') {
                                                    Userss[_spos].SetMother(m3->GetUserRef());
                                                }


                                                cout << "Ho aggiunto all' utente @" << m3->GetUserRef()
                                                     << " il figlio @"
                                                     << _insertion[1] << endl;
                                            } else {
                                                cout
                                                        << "Errore: Il genitore deve essere almeno più grande di qualche anno del figlio, modifica le info nel menu di gestione utenti"
                                                        << endl;
                                            }

                                        }
                                    } else {
                                        cout << "Non puoi modificare questo campo perchè non è vuoto" << endl
                                             << "Se vuoi modificarlo, accedi nella gestione relazioni con l' utente @"
                                             << _insertion[1] << " e svuota il campo tramite il comando padre/madre"
                                             << endl;
                                    }

                                } else { cout << "Errore di immissione" << endl << endl; }


                            } else if (_insertion[0] == "exit") { cout << "Sto uscendo..." << endl; }


                            else { cout << "Errore di immissione" << endl; }
                            /*** End now (after else) ***/


                        }
                        delete m3; /**End while, destroy m3 --> end modify relation menu **/





                    } else { cout << "Errore: Utente non trovato" << endl; }


                }

                break;


                // default:
                //   break;

            case BEST_COMPANY:
                string _command;
                cout << endl << "Digita start per tornare al menu principale" << endl << endl;
                //_command=menu1.getQuery();
                if (command == "singole_l") {


                    cout
                            << "Hai scelto di mostrare le aziende singolarmente che hanno il maggiore rapporto likes/dislikes"
                            << endl;
                    vector<tuple<float, int, float>> ratio; /*creating a vector containig the ratio of all companies, the position and the percentage*/
                    vector<Post> _to_elaborate;
                    float totl;
                    float totd;

                    for (int pos = 0; pos < company_usernames.size(); pos++) {
                        /** These variables stores the number of likes and dislikes*/
                        totl = 0;
                        totd = 0;
                        _to_elaborate = CompanyObj[pos].getPost();

                        for (int ppos = 0;
                             ppos < _to_elaborate.size(); ppos++) { /** ppos is the positin of the post in user(n) **/

                            totl += _to_elaborate[ppos].likes.size();
                            totd += _to_elaborate[ppos].dislikes.size();

                        }
                        tuple<float, int, float> _to_add;

                        if (totd == 0) {
                            if (totl == 0) {
                                _to_add = make_tuple(0, pos, 0);
                                ratio.emplace_back(_to_add);
                            } else {

                                _to_add = make_tuple(totl, pos, 100);
                                ratio.emplace_back(_to_add);

                            }


                        } else {
                            _to_add = make_tuple((totl / totd), pos, (totl / (totd + totl)) * 100);
                            ratio.emplace_back(_to_add);
                        }
                    }

                    sort(ratio.rbegin(), ratio.rend());

                    for (auto i = 0; i < ratio.size(); i++) {

                        cout << "Rapporto like/dislike " << setprecision(2) << fixed << get<0>(ratio[i]);
                        cout << setw(30);
                        cout.left;

                        cout << "\tNome azienda @" << CompanyObj[get<1>(ratio[i])].getUsername();
                        cout << setw(30);
                        cout.left;

                        cout << "\tPercentuale " << setprecision(2) << fixed << get<2>(ratio[i]) << endl;
                        //cout<<resetiosflags()

                    }


                } else if (command == "singole_d") {


                    cout
                            << "Hai scelto di mostrare le aziende singolarmente che hanno il maggiore rapporto dislikes/likes"
                            << endl;
                    vector<tuple<float, int, float>> ratio; /*creating a vector containig the ratio of all companies, the position and the percentage*/
                    vector<Post> _to_elaborate;
                    float totl;
                    float totd;

                    for (int pos = 0; pos < company_usernames.size(); pos++) {
                        /** These variables stores the number of likes and dislikes*/
                        totl = 0;
                        totd = 0;
                        _to_elaborate = CompanyObj[pos].getPost();

                        for (int ppos = 0;
                             ppos < _to_elaborate.size(); ppos++) { /** ppos is the positin of the post in user(n) **/

                            totl += _to_elaborate[ppos].likes.size();
                            totd += _to_elaborate[ppos].dislikes.size();

                        }
                        tuple<float, int, float> _to_add;

                        if (totl == 0) {
                            if (totd == 0) {
                                _to_add = make_tuple(0, pos, 0);
                                ratio.emplace_back(_to_add);
                            } else {

                                _to_add = make_tuple(totd, pos, 100);
                                ratio.emplace_back(_to_add);

                            }


                        } else {
                            _to_add = make_tuple((totd / totl), pos, (totd / (totd + totl)) * 100);
                            ratio.emplace_back(_to_add);
                        }
                    }

                    sort(ratio.rbegin(), ratio.rend());

                    for (auto i = 0; i < ratio.size(); i++) {

                        cout << "Rapporto dislikes/likes " << setprecision(2) << fixed << get<0>(ratio[i]);
                        cout << setw(30);
                        //cout.left;

                        cout << "\tNome azienda @" << CompanyObj[get<1>(ratio[i])].getUsername();
                        cout << setw(30);
                        //cout.left;

                        cout << "\tPercentuale " << setprecision(2) << fixed << get<2>(ratio[i]) << endl;
                        //cout<<resetiosflags()

                    }


                } else if (command == "consociate_l") {


                    cout
                            << "Hai scelto di mostrare le aziende che hanno in modo cumulativo il maggiore rapporto likes/dislikes"
                            << endl;
                    vector<tuple<float, int, float>> ratio; /*creating a vector containig the ratio of all companies, the position and the percentage*/
                    vector<Post> _to_elaborate;
                    float totl;
                    float totd;

                    for (int pos = 0; pos < company_usernames.size(); pos++) {
                        /** These variables stores the number of likes and dislikes*/
                        totl = 0;
                        totd = 0;
                        _to_elaborate = CompanyObj[pos].getPost();

                        for (int ppos = 0;
                             ppos < _to_elaborate.size(); ppos++) { /** ppos is the positin of the post in user(n) **/

                            totl += _to_elaborate[ppos].likes.size();
                            totd += _to_elaborate[ppos].dislikes.size();

                        }
                        /*Now add likes and dislikes from the subsidiaries*/

                        if (!CompanyObj[pos].GetSubsidiary().empty()) {
                            /*First get the positions of subs.*/
                            vector<string> _subs;
                            _subs = CompanyObj[pos].GetSubsidiary();
                            vector<int> subpos(_subs.size());

                            for (int i = 0; i < _subs.size(); i++) {
                                subpos.emplace_back(getVecPos(_subs[i], company_usernames));
                            }

                            /*Now add likes and dislikes*/
                            for (int i = 0; i < subpos.size(); i++) {
                                vector<Post> _to_count;
                                _to_count = CompanyObj[subpos[i]].getPost();
                                for (int j = 0; j < _to_count.size(); j++) {
                                    totl += _to_count[j].likes.size();
                                    totd += _to_count[j].dislikes.size();

                                }


                            }

                        }


                        tuple<float, int, float> _to_add;

                        if (totd == 0) {
                            if (totl == 0) {
                                _to_add = make_tuple(0, pos, 0);
                                ratio.emplace_back(_to_add);
                            } else {

                                _to_add = make_tuple(totl, pos, 100);
                                ratio.emplace_back(_to_add);

                            }


                        } else {
                            _to_add = make_tuple((totl / totd), pos, (totl / (totd + totl)) * 100);
                            ratio.emplace_back(_to_add);
                        }
                    }

                    sort(ratio.rbegin(), ratio.rend());

                    for (auto i = 0; i < ratio.size(); i++) {

                        cout << "Rapporto likes/dislikes " << setprecision(2) << fixed << get<0>(ratio[i]);
                        cout << setw(30);
                        //cout.left;

                        cout << "\tNome azienda @" << CompanyObj[get<1>(ratio[i])].getUsername();
                        cout << setw(30);
                        //cout.left;

                        cout << "\tPercentuale " << setprecision(2) << fixed << get<2>(ratio[i]) << endl;
                        //cout<<resetiosflags()

                    }


                } else if (command == "consociate_d") {


                    cout
                            << "Hai scelto di mostrare le aziende che hanno in modo cumulativo il maggiore rapporto dislikes/likes"
                            << endl;
                    vector<tuple<float, int, float>> ratio; /*creating a vector containig the ratio of all companies, the position and the percentage*/
                    vector<Post> _to_elaborate;
                    float totl;
                    float totd;

                    for (int pos = 0; pos < company_usernames.size(); pos++) {
                        /** These variables stores the number of likes and dislikes*/
                        totl = 0;
                        totd = 0;
                        _to_elaborate = CompanyObj[pos].getPost();

                        for (int ppos = 0;
                             ppos < _to_elaborate.size(); ppos++) { /** ppos is the positin of the post in user(n) **/

                            totl += _to_elaborate[ppos].likes.size();
                            totd += _to_elaborate[ppos].dislikes.size();

                        }
                        /*Now add likes and dislikes from the subsidiaries*/

                        if (!CompanyObj[pos].GetSubsidiary().empty()) {
                            /*First get the positions of subs.*/
                            vector<string> _subs;
                            _subs = CompanyObj[pos].GetSubsidiary();
                            vector<int> subpos(_subs.size());

                            for (int i = 0; i < _subs.size(); i++) {
                                subpos.emplace_back(getVecPos(_subs[i], company_usernames));
                            }

                            /*Now add likes and dislikes*/
                            for (int i = 0; i < subpos.size(); i++) {
                                vector<Post> _to_count;
                                _to_count = CompanyObj[subpos[i]].getPost();
                                for (int j = 0; j < _to_count.size(); j++) {
                                    totl += _to_count[j].likes.size();
                                    totd += _to_count[j].dislikes.size();

                                }


                            }

                        }


                        tuple<float, int, float> _to_add;

                        if (totl == 0) {
                            if (totd == 0) {
                                _to_add = make_tuple(0, pos, 0);
                                ratio.emplace_back(_to_add);
                            } else {

                                _to_add = make_tuple(totd, pos, 100);
                                ratio.emplace_back(_to_add);

                            }


                        } else {
                            _to_add = make_tuple((totd / totl), pos, (totd / (totd + totl)) * 100);
                            ratio.emplace_back(_to_add);
                        }
                    }

                    sort(ratio.rbegin(), ratio.rend());

                    for (auto i = 0; i < ratio.size(); i++) {

                        cout << "Rapporto dislikes/likes " << setprecision(2) << fixed << get<0>(ratio[i]);
                        cout << setw(30);
                        cout << "\tNome azienda @" << CompanyObj[get<1>(ratio[i])].getUsername();
                        cout << setw(30);
                        cout << "\tPercentuale " << setprecision(2) << fixed << get<2>(ratio[i]) << endl;

                    }


                } else if (command == "help") {
                    /*do nothing*/

                } else { cout << "Errore di immissione" << endl; }

                break;

        }


    }

    /***********************************************************************************/
    return 0;
}
