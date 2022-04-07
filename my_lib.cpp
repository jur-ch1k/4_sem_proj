#include "my_lib.h"

//classes and func-s

map::map(int size) {
    srand(time(NULL));
        arr = new room[size*size];
        this->size = size;
        for (int i = 0; i < size*size; i ++) {
            if (i >= 0 && i < size || i >= size*size - size && i < size
            || i%size == 0 || i%size == size-1)
                arr[i].mod[1] = true;
            
            if (1);
        }
}

map::~map() {
        delete [] arr;
}

void map::move(int side){

} //0 - up; 1 - right; 2 - down; 3 - left

void map::print() {
    for (int i = 0; i < size*size; i++) {
            arr[i].print();
        }
}

std::ostream& operator <<(std::ostream& out, map& ob) {
    string window1 = "##/ \\##";
    string window2 = "##\\ /##";
    string close = "###-###";
    string open = "##| |##";

    for (int i = 0; i < ob.size; i++){//общее кол-во комнат ЭТАЖЕЙ!!!!

        for (int j = 0; j < ob.size; j++)//гориз. стены
            if (i == 0)
                out << window1;
            else if (ob.arr[i*ob.size+j].door[0])
                out << open;
            else
                out << close;
        out << endl;

        for (int j = 0; j < 3; j++){//внутрянняя часть комант + верт стены
            for (int k = 0; k < ob.size; k++) {
                if (j == 1) {//лев. стена
                    if (ob.arr[i*ob.size+k].mod[1] && (i*ob.size+k)%ob.size == 0)
                        out << 'O';
                    else if (ob.arr[i*ob.size+k].door[3])
                        out << '_';
                    else 
                        out << ']';
                }
                else
                    out << '#';

                out << ob.arr[i*ob.size+k].inside[j]; //добавить лев и прав двери + окна

                if (j == 1) {//прав. стена
                    if (ob.arr[i*ob.size+k].mod[1] && (i*ob.size+k)%ob.size == ob.size - 1)
                        out << 'O';
                    else if (ob.arr[i*ob.size+k].door[2])
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
        inside[0] = "     ";
        inside[1] = "  ?  ";
        inside[2] = "     ";
}

void room::print() {
    cout << "Num: " << room_num << endl
        << "mods: " << mod[0] << ' ' << mod[1] << ' ' << mod[2] << ' ' << mod[4] << ' ' << endl
        << "doors: " << door[0] << ' ' << door[1] << ' ' << door[2] << ' ' << door[4] << ' ' << endl
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