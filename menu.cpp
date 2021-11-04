//
// Created by antronyx on 15/12/18.
//
#include "menu.h"
#include "social.h"





Menu::Menu() {

};

Menu::Menu(string _users_file) {
    this->__users_file = _users_file;
};

Menu::Menu(string _users_file, string _relations_file) {
    this->__users_file = _users_file;
    this->__relations_file = _relations_file;

};

Menu::Menu(string _users_file, string _relations_file, string _posts_file) {
    this->__users_file = _users_file;
    this->__relations_file = _relations_file;
    this->__posts_file = _posts_file;
};


string Menu::GetUserFile() const {
    return __users_file;
}

string Menu::GetRelationFile() const {
    return __relations_file;
}

string Menu::GetPostFile() const {
    return __posts_file;
}

void Menu::SetUserFile(string _users_file) {
    this->__users_file = _users_file;
}

void Menu::SetReletionFile(string _relations_file) {
    this->__relations_file = _relations_file;
}

void Menu::SetPostFile(string _post_file) {
    this->__posts_file = _post_file;
}

void Menu::SetPos(int _menu_pos) {
    this->__menu_pos = _menu_pos;
}

int Menu::GetPos() {
    return this->__menu_pos;
}

void Menu::SetLogo(string _logo_path) {
    this->__logo = _logo_path;
}


string Menu::GetLogo() {
    return this->__logo;
}

void Menu::welcomeScreen() {
    for (int i = 0; i < 29; i++) {
        cout << endl;
    }
    ifstream file_logo(this->__logo);
    string line;
    if (file_logo.is_open()) {
        while (getline(file_logo, line)) {
            cout << line << endl;
        }
        file_logo.close();
    }
    cout << "       A simple c++ social analyzer" << endl << endl << endl;
    cout << endl;
    cout << "Scrivi il comando \"exit\" per chiudere l' applicativo," << endl;
    cout << "\"start\" per tornare al menu iniziale, \"help\" per richiedere aiuto";
    helpScreen(
            this->__menu_pos);  /*** With start command i just first set menu_pos to 0, after display a start screen and helpScreen([menu_pos=0]) ***/


}


string Menu::posString() {
    int previous = this->__menu_pos;
    switch (this->__menu_pos) {              /****** It accept an int and set a label ********/
        case START_MENU:
            return "antocoon> ";
        case BEST_COMPANY:
            return "simpatia> ";
        case STATS_MENU:
            return "statistiche> ";
        case RELATION_MENU:
            return "gestionerelazioni> ";
        case MANAGER_MENU:
            return "gestioneutenti> ";
        case POST_MENU:
            return "gestionenotizie> ";
        case MODIFY_MENU:
            return "modifica>";
        case CREATION_MENU:
            return "nuovoutente>";
        case ID_POST_MENU:
            return "gestionenotizie/@" + this->__user_ref + "> ";
        case EXIT_MENU:
            return "";
        case LIKE_MENU:
            return "gestionenotizie/apprezzamenti/@" + this->__user_ref + "> ";
        case GROUP_MENU:
            return "gestionerelazioni/gruppo/@" + this->__user_ref + "> ";
        case COMPANY_MENU:
            return "gestionerelazioni/azienda/@" + this->__user_ref + "> ";
        case USER_REL_MENU:
            return "gestionerelazioni/semplice/@" + this->__user_ref + "> ";
        case QUIET_USERS_MENU:
            return "solitari/parametri> ";
        case FAMILY_TREE:
            return "alberi> ";
        default:
            return "ricordati di aggiungere il nuovo caso o da errore";
    }

}

string Menu::getQuery() {
    string insert;

    do {
        /*************************************************************************************************/
        cout << this->posString();/*********This way i take pretty well the command (the right way) *****/
        /***********************************************************************************************/

        getline(cin.ignore(EOF), insert);
        if (cin.eof()) {                        /**** If Ctrl-D is received program is interrupted as expected****/
            raise(SIGINT);
        }

    } while (insert.empty());

    if (this->_sub == 'Y') {

        if (insert == "exit") {
            this->__menu_pos = EXIT_MENU;
        }

        if (insert == "help" and helper(this->__menu_pos)) {

            helpScreen(this->__menu_pos);
        }

        //return insert;


    } else {


        if (insert == "exit") {
            this->__menu_pos = EXIT_MENU;
        }

        if (insert == "start") {

            this->__menu_pos = START_MENU;

        }
        if (insert == "help" and helper(this->__menu_pos)) {

            helpScreen(this->__menu_pos);
        }
    }

    return insert;
}

bool helper(int _menu_pos) {
    switch (_menu_pos) {
        case ID_POST_MENU:
            return true;
        case POST_MENU:
            return true;
        case MANAGER_MENU:
            return true;
        case START_MENU:
            return true;
        case STATS_MENU:
            return true;
        case GROUP_MENU:
            return true;
        case RELATION_MENU:
            return true;
        case USER_REL_MENU:
            return true;
        case COMPANY_MENU:
            return true;
        case BEST_COMPANY:
            return true;
        default:
            return false;
    }

}





void Menu::maxLiked(const string _username_argument) {

    vector<string> posting_usernames;
    posting_usernames = PostingPeople(this->__posts_file); /*cambiare postingpeople con posting guser */


    vector<gUser> postingObjs(posting_usernames.size());
    for (int i = 0; i < postingObjs.size(); i++) {
        postingObjs[i].setPostsFileRef(this->__posts_file);
        postingObjs[i].setFileRef(this->__users_file);

        postingObjs[i].setUsername(posting_usernames[i]);

    }

    vector<vector<Post> > tutti_i_post;
    int user_no = 0;
    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
        postingObjs[user_no].loadPosts();

    }

    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
        tutti_i_post.emplace_back(postingObjs[user_no].getPost());

    }

    unsigned long nLmax = 0;
    vector<string> message;
    vector<string> username;

    vector<int> post_n;
    vector<int> user_n;
    if (_username_argument.empty()) {
    for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
        for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {


            if (tutti_i_post[user_no][post_no].nLikes > nLmax) {
                message.clear();
                post_n.clear();
                user_n.clear();
                username.clear();

                nLmax = tutti_i_post[user_no][post_no].nLikes;
                message.emplace_back(tutti_i_post[user_no][post_no].message);
                user_n.push_back(user_no);
                post_n.push_back(post_no);
                username.emplace_back(tutti_i_post[user_no][post_no].username);
            } else if (tutti_i_post[user_no][post_no].nLikes == nLmax) {
                nLmax = tutti_i_post[user_no][post_no].nLikes;
                message.emplace_back(tutti_i_post[user_no][post_no].message);
                user_n.push_back(user_no);
                post_n.push_back(post_no);
                username.emplace_back(tutti_i_post[user_no][post_no].username);

            }


        }

    }
        cout << "I post con più likes sono i seguenti" << endl;

    } else if (!_username_argument.empty() and common(_username_argument, posting_usernames)) {

        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {
                if (tutti_i_post[user_no][post_no].username == _username_argument and
                    tutti_i_post[user_no][post_no].nLikes == nLmax) {
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                } else if (tutti_i_post[user_no][post_no].username == _username_argument and
                           tutti_i_post[user_no][post_no].nLikes > nLmax) {
                    message.clear();
                    post_n.clear();
                    user_n.clear();
                    username.clear();
                    nLmax = tutti_i_post[user_no][post_no].nLikes;
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                }

            }
        }
        cout << "I post con più likes scritti da " << _username_argument << " sono i seguenti" << endl;

    }

    /** Now print **/
    for (int i = 0; i < username.size(); i++) {
        cout << message[i] << " scritto da  @" << username[i] << " con un totale di " << nLmax << " Likes" << endl;
    }

}


void Menu::maxDisliked(const string _username_argument) {

    vector<string> posting_usernames;
    posting_usernames = PostingPeople(this->__posts_file); /*cambiare postingpeople con posting guser */


    vector<gUser> postingObjs(posting_usernames.size());
    for (int i = 0; i < postingObjs.size(); i++) {
        postingObjs[i].setPostsFileRef(this->__posts_file);
        postingObjs[i].setFileRef(this->__users_file);

        postingObjs[i].setUsername(posting_usernames[i]);

    }

    vector<vector<Post> > tutti_i_post;
    int user_no = 0;
    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
        postingObjs[user_no].loadPosts();

    }

    for (user_no = 0; user_no < postingObjs.size(); user_no++) {
        tutti_i_post.emplace_back(postingObjs[user_no].getPost());

    }

    unsigned long nDmax = 0;
    vector<string> message;
    vector<string> username;

    vector<int> post_n;
    vector<int> user_n;
    if (_username_argument.empty()) {
        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {


                if (tutti_i_post[user_no][post_no].nDislikes > nDmax) {
                    message.clear();
                    post_n.clear();
                    user_n.clear();
                    username.clear();

                    nDmax = tutti_i_post[user_no][post_no].nDislikes;
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                } else if (tutti_i_post[user_no][post_no].nDislikes == nDmax) {
                    nDmax = tutti_i_post[user_no][post_no].nDislikes;
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);

                }


            }

        }
        cout << "I post con più Dislikes sono i seguenti:" << endl;

    } else if (!_username_argument.empty() and common(_username_argument, posting_usernames)) {

        for (user_no = 0; user_no < tutti_i_post.size(); user_no++) {
            for (int post_no = 0; post_no < (postingObjs[user_no].getPost()).size(); post_no++) {
                if (tutti_i_post[user_no][post_no].username == _username_argument and
                    tutti_i_post[user_no][post_no].nDislikes == nDmax) {
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                } else if (tutti_i_post[user_no][post_no].username == _username_argument and
                           tutti_i_post[user_no][post_no].nDislikes > nDmax) {
                    message.clear();
                    post_n.clear();
                    user_n.clear();
                    username.clear();
                    nDmax = tutti_i_post[user_no][post_no].nDislikes;
                    message.emplace_back(tutti_i_post[user_no][post_no].message);
                    user_n.push_back(user_no);
                    post_n.push_back(post_no);
                    username.emplace_back(tutti_i_post[user_no][post_no].username);
                }

            }
        }
        cout << "I post con più Dislikes scritti da " << _username_argument << " sono i seguenti:" << endl;

    }

    /** Now print **/
    for (int i = 0; i < username.size(); i++) {
        cout << message[i] << " scritto da  @" << username[i] << " con un totale di " << nDmax << " Dislikes" << endl;
    }

}

Menu::~Menu() {

}

vector<string> Menu::subQuery() {
    if (this->__menu_pos > 0) {
        string inserted;
        string __argument;
        string __command;
        inserted = this->getQuery();
        vector<string> _to_ret;


        if (!inserted.empty()) {

            if (inserted.find(' ', 0) != string::npos) {
                __command = inserted.substr(0, inserted.find(' '));
                _to_ret.emplace_back(__command);

                if (inserted.find(' ', __command.length()) != string::npos) {
                    __argument = inserted.substr(inserted.find(' ', __command.length()),
                                                 inserted.length() - inserted.find(' ', __command.length()));
                    __argument = trim(__argument);
                    _to_ret.emplace_back(__argument);

                }
                // __command=trim(__argument);
            } else { _to_ret.emplace_back(inserted); }


        } else {
            cerr
                    << "Errore di immissione"
                    << endl;
        }


        return _to_ret;

    }

}

void Menu::SetUserRef(string _user) {
    this->__user_ref = _user;
}

string Menu::GetUserRef() {
    return this->__user_ref;
}

void Menu::SetSubMenu(char) {
    this->_sub = 'Y';
}


void helpScreen(int help_code) {
    int space_of_row = 109;
    switch (help_code) {
        case START_MENU:

            cout << endl << endl << "SEZIONI:" << endl;
            //cout.width(56); cout << internal << n << '\n';
            //cout.width(56); cout << left << n << '\n';
            cout << "mostrautenti";
            cout.width(97);
            cout << right << "Visualizza tutti gli utenti, aziende e gruppi" << endl;
            cout << "statistiche";
            cout.width(98);
            cout << right << "Visualizza le statistiche" << endl;
            cout << "gestioneutenti";
            cout.width(95);
            cout << right << "Inserimenti, cancellazione, modifiche degli utenti" << endl;
            cout << "gestionerelazioni";
            cout.width(92);
            cout << right << "Inserimenti, cancellazioni, modifiche relazioni" << endl;
            cout << "gestionenotizie";
            cout.width(94);
            cout << right << "Gestione dei messaggi e opinioni" << endl;
            cout << "simpatia";
            cout.width(101);
            cout << right << "Ordine di aziende per rapporto apprezzamenti" << endl;
            cout << "solitari";
            cout.width(101);
            cout << right << "Visualizza gli utenti semplici con un basso livello di interazione" << endl;
            cout << "alberi";
            cout.width(101);
            cout << right << "Crea alberi genealogici basati sui dati presenti sul socialnetwork" << endl;


            cout << endl << endl;
            break;
        case STATS_MENU:
            cout << endl << endl;
            cout
                    << "Questo è il menu delle statistiche" << endl
                    << "I parametri <PARAMETRO> sono obbligatori, i parametri del tipo [PARAMETRO], quando assenti danno tutte le info che possono"
                    << endl;
            cout << "STATISTICHE:" << endl;
            cout << "tot [S/A/G]";
            cout.width(space_of_row - strlen("tot [S/A/G]"));
            cout << right << "Mostra numero complessivo di utenti semplici,azienda,gruppo" << endl;
            cout << "nsince <GG/MM/AAAA>";
            cout.width(space_of_row - strlen("nsince <GG/MM/YYYY>"));
            cout << right << "Numero di utenti nati dopo una certa data" << endl;
            cout << "nconnessi [ID]";
            cout.width(space_of_row - strlen("nconnessi [ID]"));
            cout << right << "Numero di amici e parenti connessi a ID" << endl;
            cout << "ndipendenti [ID]";
            cout.width(space_of_row - strlen("ndipendenti [ID]"));
            cout << right << "Numero di dipendenti per azienda" << endl;
            cout << "nconsociate [ID]";
            cout.width(space_of_row - strlen("nconsociate [ID]"));
            cout << right << "Numero di consociate per azienda" << endl;
            cout << "ncomponenti [ID]";
            cout.width(space_of_row - strlen("ncomponenti [ID]"));
            cout << right << "Numero di componenti per gruppo" << endl;
            cout << "maxdipendenti [S/C]";
            cout.width(space_of_row - strlen("maxdipendenti [S/C]"));
            cout << right << "Azienda/e con il max numero di dipendenti (da sola/cumulativo)" << endl;
            cout << "mostLiked [ID]";
            cout.width(space_of_row - strlen("mostLiked [ID]"));
            cout << right << "Notizia/e con il maggior numero di Likes" << endl;
            cout << "mostDisliked [ID]";
            cout.width(space_of_row - strlen("mostdisliked [ID]"));
            cout << right << "Notizia/e con il massimo numero di disLikes" << endl;
            cout << "etaMedia";
            cout.width(space_of_row - strlen("etaMedia"));
            cout << right << "  Età media sul social" << endl;
            cout << "maxfriends";
            cout.width(space_of_row - strlen("maxfriends"));
            cout << right << "Persona/e con il max numero di amici" << endl;
            cout << "maxconoscenti";
            cout.width(space_of_row - strlen("maxconoscenti"));
            cout << right << "Persona/e con il max numero di conoscenti" << endl;


            cout << endl << endl;
            break;
        case MANAGER_MENU:
            cout << endl << endl;
            cout
                    << "Questo è il menu di modifica degli utenti, puoi aggiungere, eliminare o modificare utenti e informazioni personali,"
                    << endl <<
                    "che siano persone, aziende o gruppi; immetti <salva> quando vuoi aggiornare il database"
                    << endl << "I parametri [PARAMETRO] sono necessari"
                    << endl << endl;
            cout << "GESTIONE UTENTI:" << endl;
            cout << "mostra [S/A/G]";
            cout.width(space_of_row - strlen("mostra [S/A/G]"));
            cout << right << "Mostra l' username di utenti (S)emplici,(A)zienda,(G)ruppo" << endl;
            cout << "accesso [ID]";
            cout.width(space_of_row - strlen("accesso [ID]"));
            cout << right << "Entra nell' account di [ID] per modificare le relative informazioni" << endl;
            cout << "crea [S/A/G]";
            cout.width(space_of_row - strlen("crea [S/A/G]"));
            cout << right << "Aggiungi un nuovo utente di tipo (S)emplice,(A)zienda,(G)ruppo" << endl;
            cout << "rimuovi [ID]";
            cout.width(space_of_row - strlen("rimuovi [ID]"));
            cout << right << "Cancella l' utente [ID]" << endl;
            cout << "salva";
            cout.width(space_of_row - strlen("salva"));
            cout << right << "Salva sul file di database le modifiche apportate" << endl;

            cout << endl << endl;

            break;
        case POST_MENU:
            cout << endl << endl;
            cout
                    << "Questo è il menu di modifica dei post, puoi visualizzare, aggiungere, eliminare o modificare post e mettere like/dislike;"
                    << endl <<
                    "immetti <salva> quando vuoi aggiornare il database"
                    << endl << endl;
            cout << "GESTIONE POST:" << endl;
            cout << "mostra [S/A/G]";
            cout.width(space_of_row - strlen("mostra [S/A/G]"));
            cout << right << "Mostra l' username di utenti (S)emplici,(A)zienda,(G)ruppo" << endl;
            cout << "accesso [ID]";
            cout.width(space_of_row - strlen("accesso [ID]"));
            cout << right << "Entra nell' account di [ID] per le operazioni sui post, digita <exit> per uscire" << endl;
            cout << "salva";
            cout.width(space_of_row - strlen("salva"));
            cout << right << "Salva sul file di database le modifiche apportate" << endl;

            cout << endl << endl;

            break;
        case ID_POST_MENU:
            cout << endl << endl;
            cout
                    << "Ti trovi nel sottomenu delle notizie, puoi visualizzare, aggiungere, eliminare o modificare post e mettere like/dislike;"
                    << endl <<
                    "relativamente all' account in cui è stato effettuato l' accesso, per salvare il database esci prima dal submenu "
                    << endl << endl;
            cout << "GESTIONE POST-> ACCESSO:" << endl;
            cout << "aggiungi";
            cout.width(space_of_row - strlen("aggiungi"));
            cout << right << "Crea una nuova notizia" << endl;
            cout << "mostra";
            cout.width(space_of_row - strlen("mostra"));
            cout << right << "Mostra tutti i post" << endl;
            cout << "rimuovi";
            cout.width(space_of_row - strlen("rimuovi"));
            cout << right << "Rimuovi un tuo post" << endl;
            cout << "apprezzamenti";
            cout.width(space_of_row - strlen("apprezzamenti"));
            cout << right << "Ti permette di aggiungere un like/dislike a un post" << endl;
            cout << "modifica";
            cout.width(space_of_row - strlen("modifica"));
            cout << right << "Modifica le notizie, messaggio e data dei tuoi post" << endl;
            cout << "salva";
            cout.width(space_of_row - strlen("salva"));
            cout << right << "Salva i tre file di database" << endl;


            cout << endl << endl;
            break;

        case RELATION_MENU:
            cout << endl << endl;
            cout
                    << "Ti trovi nel menu delle relazioni, puoi visualizzare, aggiungere, eliminare o modificare le relazioni tra gli utenti;"
                    << endl << endl;

            cout << "mostra";
            cout.width(space_of_row - strlen("mostra"));
            cout << right << "Mostra tutti gli utenti" << endl;
            cout << "accesso [ID]";
            cout.width(space_of_row - strlen("accesso [id]"));
            cout << right << "Accedi a [ID] in modo da modificare le relazioni" << endl;
            cout << "salva";
            cout.width(space_of_row - strlen("salva"));
            cout << right << "Salva i tre file di database" << endl;
        case GROUP_MENU:
            cout << endl
                 << "Una volta effettuato l' accesso, digita <rimuovi> [ID] per rimuovere il componente ID, digita <aggiungi> [ID] per aggiungere un componente ID"
                 << endl;
            break;
        case COMPANY_MENU:
            cout << endl
                 << "Una volta effettuato l' accesso, digita <rimuovi> [ID] per rimuovere il componente ID, digita <aggiungi> [ID] per aggiungere un componente ID"
                 << endl;
            break;
        case USER_REL_MENU:
            cout << "Digita <comando> <ID> per modificare le relazioni" << endl << endl << "COMANDI:" << endl;
            cout << "amico [ID]";
            cout.width(109 - strlen("amico [ID]"));
            cout << right << "Aggiungi/rimuovi amico" << endl;
            cout << "conoscente [ID]";
            cout.width(109 - strlen("conoscente [ID]"));
            cout << right << "Aggiungi/rimuovi conoscente" << endl;
            cout << "madre [ID]";
            cout.width(109 - strlen("madre [ID]"));
            cout << right << "Aggiungi/rimuovi madre" << endl;
            cout << "padre [ID]";
            cout.width(109 - strlen("padre [ID]"));
            cout << right << "Aggiungi/rimuovi padre" << endl;
            cout << "figlio [ID]";
            cout.width(109 - strlen("amico [ID]"));
            cout << right << "Aggiungi/rimuovi figlio/figlia" << endl;
            break;
        case BEST_COMPANY:
            cout << endl << endl;
            cout
                    << "Sei entrato nel menu simpatia: Verranno ordinate le aziende in base al rapporto degli apprezzamenti alle notizie"
                    << endl;
            cout
                    << "Immetti <singole_l>, <singole_d>, <consociate_l> o <consociate_d> per indicare se vuoi considerare il totale o le aziende singole"
                    << endl
                    << "e impostare il rapporto like/dislike o dislike/like" << endl << endl;


            break;
        case QUIET_USERS_MENU:
            cout << "Digita <comando> <attributo> per modificare i parametri di lupo solitario" << endl << endl
                 << "PARAMETRI:" << endl;
            cout << "relazioni [NUM]";
            cout.width(109 - strlen("relazioni [num]"));
            cout << right << "Numero al di sotto del quale l'utente va considerato solitario" << endl;
            cout << "apprezzamenti [NUM]";
            cout.width(109 - strlen("apprezzamenti [num]"));
            cout << right << "Numero al di sotto del quale l' utente va considerato solitario" << endl;
            cout << "gruppi [SI/NO]";
            cout.width(109 - strlen("gruppi [SI/NO]"));
            cout << right << "Non appartenere a un gruppo è un fattore di lupo solitario?" << endl;
            cout << "aziende [SI/NO]";
            cout.width(109 - strlen("azienda [SI/NO]"));
            cout << right << "Non far parte di un' azienda è un fattore di lupo solitario?" << endl;
            cout << right << endl << endl;
            break;

        case FAMILY_TREE:
            cout
                    << "Sei entrato nella sezione alberi genealogici, digita <alberi> <username> per stampare l'albero genealogico di ID"
                    << endl << endl
                    << endl;
            break;

        default:
            //nothing//
            break;

    }

}








bool isStatsCmd(string _command) {
    string command;
    command = _command.substr(0, _command.find(' '));
    vector<string> MENU_CMD;
    MENU_CMD.emplace_back("tot");
    MENU_CMD.emplace_back("nsince");
    MENU_CMD.emplace_back("ndipendenti");
    MENU_CMD.emplace_back("nconsociate");
    MENU_CMD.emplace_back("ncomponenti");
    MENU_CMD.emplace_back("maxdipendenti");
    MENU_CMD.emplace_back("simpatia");
    MENU_CMD.emplace_back("mostLiked");
    MENU_CMD.emplace_back("mostDisliked");
    MENU_CMD.emplace_back("etaMedia");
    MENU_CMD.emplace_back("maxfriends");
    MENU_CMD.emplace_back("maxconoscenti");
    MENU_CMD.emplace_back("start");   /*** ALWAYS accepted command ****/
    MENU_CMD.emplace_back("help");
    MENU_CMD.emplace_back("exit");
    MENU_CMD.emplace_back("alberi");

    for (int i = 0; i < MENU_CMD.size(); i++) {
        if (MENU_CMD[i] == command) {
            return true;
        }
    }
    return false;
}

bool isMngrCmd(string _command) {
    string command;
    command = _command.substr(0, _command.find(' '));
    vector<string> MENU_CMD;
    MENU_CMD.emplace_back("mostra");
    MENU_CMD.emplace_back("accesso");
    MENU_CMD.emplace_back("crea");
    MENU_CMD.emplace_back("rimuovi");
    MENU_CMD.emplace_back("start");
    MENU_CMD.emplace_back("exit");
    MENU_CMD.emplace_back("help");
    MENU_CMD.emplace_back("salva");


    for (int i = 0; i < MENU_CMD.size(); i++) {
        if (MENU_CMD[i] == command) {
            return true;
        }
    }
    return false;
}






