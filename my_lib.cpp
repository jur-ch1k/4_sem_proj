#include "my_lib.h"
#include <thread>
//#include <cmath>

//classes and func-s

map::map(int size) {
    int monster_room_num, chest_room_num; 
    this->size = size;
    room_arr = new room[size*size];
    srand(time(NULL));//random room generation

    //size* size / 4 : num empty room
    bool check[size*size];//rnd generation
    int rnd_order[size*size];
    for (int i = 0; i < size*size; i++)
        check[i] = true;
    for (int i = 0; i < size*size; i++) {//mod-s generation
        int cur_num = rand() % (size*size);
        while (!check[cur_num])
            cur_num = rand() % (size*size);
        check[cur_num] = false;
        rnd_order[i] = cur_num;
        //cout << i << ": " << cur_num << endl;
    }

    int monster_num, chest_num, empty_num;
    empty_num = size*size/2;
    chest_num = (size*size - empty_num) / 2;
    monster_num = size*size - empty_num - chest_num;
    //cout << "M: " << monster_num << " C: " << chest_num << " E: " << empty_num << endl;
    for (int i = 0; i < size*size; i++) {
        if (i >= 0 && i < size || i >= size*size - size && i < size*size //set windows
        || i%size == 0 || i%size == size-1)
            room_arr[i].mod[1] = true;

        if (monster_num) {
            room_arr[rnd_order[i]].mod[3] = true;
            room_arr[rnd_order[i]].mod[0] = false;
            //room_arr[rnd_order[i]].inside[0] = "  Ш  ";
            //room_arr[rnd_order[i]].inside[1] = " \\|/ ";
            //room_arr[rnd_order[i]].inside[2] = " / \\ ";
            room_arr[rnd_order[i]].inside[0] = "\033[1;31m  Ш  \033[0m";
            room_arr[rnd_order[i]].inside[1] = "\033[1;31m \\|/ \033[0m";
            room_arr[rnd_order[i]].inside[2] = "\033[1;31m / \\ \033[0m";
            monster_num--;
        }
        else if (chest_num) {
            room_arr[rnd_order[i]].mod[2] = true;
            room_arr[rnd_order[i]].mod[0] = false;
            //room_arr[rnd_order[i]].inside[0] = "  _  ";
            //room_arr[rnd_order[i]].inside[1] = " |_| ";
            //room_arr[rnd_order[i]].inside[2] = "     ";
            room_arr[rnd_order[i]].inside[0] = "\033[1;33m  _  \033[0m";
            room_arr[rnd_order[i]].inside[1] = "\033[1;33m |_| \033[0m";
            room_arr[rnd_order[i]].inside[2] = "\033[1;33m     \033[0m";
            chest_num--;
        }
    }

    /*room_arr[0].inside[0] = "  0  ";
    room_arr[0].inside[1] = " T|T ";
    room_arr[0].inside[2] = " / \\ ";*/ // "\033[1;32m{TEXT}\032[0m"
    room_arr[0].inside[0] = "\033[1;32m  0  \033[0m";
    room_arr[0].inside[1] = "\033[1;32m T|T \033[0m";
    room_arr[0].inside[2] = "\033[1;32m / \\ \033[0m";
    room_arr[0].mod[0] = true;
    room_arr[0].mod[4] = false;
}

void map::test_func() {
    for (int i = 0; i < size * size; i++) {
        room_arr[i].mod[4] = false;
    }
}

map::~map() {
    delete [] room_arr;
}

int map::move(hero_class &hero, int side) {
    if (hero.pos >= 0 && hero.pos < size && side == 0 ||
        hero.pos >= size*size - size && hero.pos < size*size && side == 2 ||
        hero.pos % size == 0 && side == 3 ||
        hero.pos % size == size - 1 && side == 1) {
        
        room_arr[hero.pos].inside[0] = "     ";
        room_arr[hero.pos].inside[1] = "     ";
        room_arr[hero.pos].inside[2] = "     ";
        hero.pos = -1;
        throw "w_loss";
    }
    
    room_arr[hero.pos].door[side] = true;
    int new_pos;
    switch (side)
    {
    case 0:
        new_pos = hero.pos - size;
        break;
    case 1:
        new_pos = hero.pos + 1;
        break;
    case 2:
        new_pos = hero.pos + size;
        break;
    case 3:
        new_pos = hero.pos - 1;
        break;
    }
    room_arr[new_pos].door[(side+2)%4] = true;
    room_arr[new_pos].mod[4] = false;

    if (room_arr[new_pos].mod[0]) {
        room_arr[hero.pos] >> room_arr[new_pos];
        hero.pos = new_pos;
        return 0;
    }
    else {
        cout << "WOW! What's there?" << endl;
        return new_pos;
    }
} //0 - up; 1 - right; 2 - down; 3 - left

void map::event_handler(hero_class& hero, int room_num) {
    if (room_arr[room_num].mod[2]) {
        srand(time(NULL));
        system("clear");
        cout << *this << hero << "Do you want to open it? (y/n)\n";
        char ans;
        cin >> ans;
        if (ans == 'n')
            return;
        if (ans != 'y')
            throw "input_error";
        int loot_type = rand()%4;
        if (loot_type == 3 && hero.loot[3] == 3)
            loot_type = rand()%3;
        chest_animation(room_num, loot_type, hero);
        room_arr[room_num].mod[2] = false;
        room_arr[room_num].mod[0] = true;
        string item_name;
        switch (loot_type)
        {
        case 0:
            item_name = "a sword";
            break;
        case 1:
            item_name = "a shield";
            break;
        case 2:
            item_name = "an armor";
            break;
        case 3:
            item_name = "a healing";
            break;
        }
        cout << "You have just found "
             << item_name <<"!!!\nPress any key to take it\n";
        cin >> ans;

        room_arr[hero.pos] >> room_arr[room_num];

        hero.pos = room_num;
        hero.loot[loot_type]++;
    }
    else {
        if (/*проверка наличия монстра внутри через vector<monster_class>*/) {
            //enemy = arr[i];
        }
        else
            monster_class enemy;
        system("clear");
        cout << *this << hero << "Do you want to fight with " + enemy.name + "? (y/n)\n";
        char ans;
        cin >> ans;
        if (ans == 'n') {
            //save monster into vector<monster_class>
            return;
        }
        if (ans != 'y')
            throw "input_error";
        cout << "\"FIGHT\"\n";
        hero.hp-= 20;
        if (hero.hp <= 0) {
            room_arr[hero.pos].inside[0] = "     ";
            room_arr[hero.pos].inside[1] = "     ";
            room_arr[hero.pos].inside[2] = "     ";
            throw "hp_loss";
        }
        room_arr[room_num].mod[3] = false;
        room_arr[room_num].mod[0] = true;
        room_arr[hero.pos] >> room_arr[room_num];
        hero.pos = room_num;
        hero.harizma++;
    }
}

void map::chest_animation(int room_num, int loot_type, hero_class& hero) {
    string frame[5][3];
    frame[0][0] = "   \\ ";
    frame[0][1] = " |_| ";
    frame[0][2] = "     ";
    
    frame[1][0] = "    _";
    frame[1][1] = " |_| ";
    frame[1][2] = "     ";
    
    frame[2][0] = "     ";
    frame[2][1] = " |_|\\";
    frame[2][2] = "     ";

    frame[3][0] = frame[3][1] = frame[3][2] = "     ";
    switch (loot_type)
    {
    case 0:
        frame[4][0] = "\033[1;33m  |  \033[0m";//"\033[1;33m{TEXT}\033[0m"
        frame[4][1] = "\033[1;33m _|_ \033[0m";
        frame[4][2] = "\033[1;33m  T  \033[0m";
        break;
    case 1:
        frame[4][0] = "\033[1;33m ___ \033[0m";
        frame[4][1] = "\033[1;33m| X |\033[0m";
        frame[4][2] = "\033[1;33m \\_/ \033[0m";
        break;
    case 2:
        frame[4][0] = "\033[1;33m_ _ _\033[0m";
        frame[4][1] = "\033[1;33mI|_|I\033[0m";
        frame[4][2] = "\033[1;33m// \\\\\033[0m";
        break;
    case 3:
        frame[4][0] = "\033[1;33m ___ \033[0m";
        frame[4][1] = "\033[1;33mT + T\033[0m";
        frame[4][2] = "\033[1;33m|___|\033[0m";
        break;
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            room_arr[room_num].inside[j] = frame[i][j];
        }
        system("clear");
        cout << *this << hero;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void map::print() {
    for (int i = 0; i < size*size; i++) {
            room_arr[i].print();
        }
}

std::ostream& operator <<(std::ostream& out, map& ob) {
    string window1 = "##/ \\##";
    string window2 = "##\\ /##";
    string close = "###-###";
    string open = "##| |##";
    string closed_room[3] = { "     ", "  ?  ", "     " };
    

    for (int i = 0; i < ob.size; i++){//общее кол-во комнат ЭТАЖЕЙ!!!!

        for (int j = 0; j < ob.size; j++)//гориз. стены
            if (i == 0)
                out << window1;
            else if (ob.room_arr[i*ob.size+j].door[0])
                out << open;
            else
                out << close;
        out << endl;

        for (int j = 0; j < 3; j++){//внутрянняя часть комант + верт стены
            for (int k = 0; k < ob.size; k++) {
                if (j == 1) {//лев. стена
                    if (ob.room_arr[i*ob.size+k].mod[1] && (i*ob.size+k)%ob.size == 0)
                        out << 'O';
                    else if (ob.room_arr[i*ob.size+k].door[3])
                        out << '_';
                    else 
                        out << ']';
                }
                else
                    out << '#';

                if (ob.room_arr[i * ob.size + k].mod[4])//ПЕРЕДЕЛАТЬ СОДЕРЖИМОЕ КОМНАТ!!!!!!!!!!!
                    out << closed_room[j];
                else 
                    out << ob.room_arr[i*ob.size+k].inside[j]; //добавить лев и прав двери + окна

                if (j == 1) {//прав. стена
                    if (ob.room_arr[i*ob.size+k].mod[1] && (i*ob.size+k)%ob.size == ob.size - 1)
                        out << 'O';
                    else if (ob.room_arr[i*ob.size+k].door[1])
                        out << '_';
                    else
                        out << '[';
                }
                else
                    out << '#';
            }
            out << endl;
        }
        
    }

    for (int i = 0; i < ob.size; i++) {
        out << window2;
    }
    out << endl;

    return out;
}

room::room() {
    for (int i = 0; i < 4; i++) {
        door[i] = false; //closed
        mod[i] = false;
    }
    mod[0] = true;
    mod[4] = true;
    inside[0] = "     ";
    inside[1] = "     ";
    inside[2] = "     ";
}

void room::print() {
    cout << "Num: " << room_num << endl
        << "mods: " << mod[0] << ' ' << mod[1] << ' ' << mod[2] << ' ' << mod[3] << ' ' << endl
        << "doors: " << door[0] << ' ' << door[1] << ' ' << door[2] << ' ' << door[3] << ' ' << endl
        << "inside: " << endl << "#####" << endl
        << inside[0] << endl << inside[1] << endl << inside[2] << endl << "#####" << endl;
}

void room::operator >>(room& to_room) {
    to_room.inside[0] = this->inside[0];
    to_room.inside[1] = this->inside[1];
    to_room.inside[2] = this->inside[2];

    this->inside[0] = this->inside[1] = this->inside[2] = "     ";
}

entity::entity(const char* str = "") : name(str), strength(0) {}

hero_class::hero_class(const char * str): entity(str) {
    numer = 0;
    hp = 100;
    pos = 0;
    stamina = 10;
    harizma = 0;
    for (int i = 0; i < 4; i++) {
        loot[i] = 0;
    }
}

std::ostream& operator <<(std::ostream& out, hero_class& ob) {
    /*out << "NAME: " <<ob.name
        << "\nLOOT:\nx" << ob.loot[0] << "   |   x" << ob.loot[1] << "  ___  x" 
        << ob.loot[2] << " _ _ _  x" << ob.loot[3]
        << "  ___ \n    _|_     | X |    I|_|I     T + T\n     T       \\_/     // \\\\     |___|\nHP: "
        << ob.hp <<"\nSTAMINA: " << ob.stamina << endl;*/
    out << "NAME: " << ob.name
        << "\nLOOT:\nx" << ob.loot[0] << "\033[1;33m   |   \033[0mx" << ob.loot[1]
        << "\033[1;33m  ___  \033[0mx" << ob.loot[2] << "\033[1;33m _ _ _  \033[0mx" << ob.loot[3]
        << "\033[1;33m  ___ \n    _|_     | X |    I|_|I     T + T\n     T       \\_/     // \\\\     |___|\033[0m\n";
    if (ob.hp > 70)
        out << "\033[0;32mHP: ";
    else if (ob.hp > 50)
        out << "\033[0;35mHP: ";
    else
        out << "\033[0;31mHP: ";
    out << ob.hp <<"\033[0m\nSTAMINA: " << ob.stamina << "\nHARIZMA: " << ob.harizma << endl;
    return out; //"\033[1;33m{TEXT}\033[0m"
}

void hero_class::print() {
    cout << "hp: " << hp << " pos: " << pos << endl;
}

monster_class::monster_class() {
    srand(time(NULL));
    
    int moster_type = rand()%4;
    switch (moster_type)
    {
    case 0:
        name = "Vampire";
        break;
    case 1:
        name = "Goblin";
        break;
    case 2:
        name = "Werewolf";
        break;
    case 3:
        name = "Baba-Yaga";
        break;
    }
    type = moster_type;
    strength += (++numer)*2 + moster_type;
}
void monster_class::print() {}