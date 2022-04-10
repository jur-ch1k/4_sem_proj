#include "my_lib.h"
#include <cmath>

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
    chest_num = (size * size - empty_num) / 2;
    monster_num = size*size - empty_num - chest_num;
    cout << "M: " << monster_num << " C: " << chest_num << " E: " << empty_num << endl;
    for (int i = 0; i < size*size; i++) {
        if (i >= 0 && i < size || i >= size*size - size && i < size //set windows
        || i%size == 0 || i%size == size-1)
            room_arr[i].mod[1] = true;

        if (monster_num) {//ПЕРЕДЕЛАТЬ СОДЕРЖИМОЕ КОМНАТ!!!!!!!!!!!
            room_arr[rnd_order[i]].mod[3] = true;
            //cout << i << ": " << 'M' << endl;
            monster_num--;
        }
        else if (chest_num) {
            room_arr[rnd_order[i]].mod[2] = true;
            //cout << i << ": " << 'C' << endl;
            chest_num--;
        }
    }

}

void map::test_func() {
    for (int i = 0; i < size*size; i++)
        room_arr[i].print();
}

map::~map() {
    delete [] room_arr;
}

void map::move(int side){

} //0 - up; 1 - right; 2 - down; 3 - left

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
    string chest_room[3] = { "  _  ", " |_| ", "     " };
    string monster_room[3] = { "  Ш  ", " \\|/ ", " / \\ " };

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

                //if (ob.room_arr[i * ob.size + k].mod[4])//ПЕРЕДЕЛАТЬ СОДЕРЖИМОЕ КОМНАТ!!!!!!!!!!!
                //    out << closed_room[j];
                //else 
                if (ob.room_arr[i * ob.size + k].mod[2])
                    out << chest_room[j];
                else if (ob.room_arr[i * ob.size + k].mod[3])
                    out << monster_room[j];
                else
                    out << ob.room_arr[i*ob.size+k].inside[j]; //добавить лев и прав двери + окна

                if (j == 1) {//прав. стена
                    if (ob.room_arr[i*ob.size+k].mod[1] && (i*ob.size+k)%ob.size == ob.size - 1)
                        out << 'O';
                    else if (ob.room_arr[i*ob.size+k].door[2])
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
    room_num = stat_num++;
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

entity::entity(const char * str): name(str), strength(0){}

hero::hero(const char * str): entity(str) {
    hp = 0;
    pos = 0;
    stamina = 1;
    harizma = 0;
    for (int i = 0; i < 5; i++) {
        loot[i] = false;
    }
}

void hero::print() {
    cout << "hp: " << hp << "pos: " << pos;
}