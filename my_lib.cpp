#include "my_lib.h"

//classes and func-s

map::map(int size) {
    //empty_room r0;
    /*closed_room r1;
    chest_room r2;
    monster_room r3;*/
    //basic_room* def_rooms_arr[4] = { &r0, &r1, &r2, &r3 };
    //def_rooms_arr[0] = &empty_room();//empty
    //def_rooms_arr[1] = &closed_room();//closed
    //def_rooms_arr[2] = &chest_room();//chest
    //def_rooms_arr[3] = &monster_room();//monster
    srand(time(NULL));//random room generation
    
    this->size = size;
    
    //basic_room** room_arr;
    room_arr = new basic_room * [size * size];

    for (int i = 0; i < size * size; i++) {
        room_arr[i] = &def_rooms_arr[i];
    }
    
    /*room_arr[0]->print();
    room_arr[1]->print();
    room_arr[2]->print();
    room_arr[3]->print();*/
    
    /*for (int i = 0; i < size * size; i++) {
        room_arr[i]->print();
    }*/

    //room_arr[0] = &r0;

    for (int i = 0; i < size*size; i++) {//set windows
        if (i >= 0 && i < size || i >= size*size - size && i < size
        || i%size == 0 || i%size == size-1)
            room_arr[i]->mod[1] = true;
            
        if (1);
    }
}

void map::test_func() {
    for (int i = 0; i < size*size; i++) {
        room_arr[i]->print();
    }
}

map::~map() {
    delete [] room_arr;
}

void map::move(int side){

} //0 - up; 1 - right; 2 - down; 3 - left

void map::print() {
    for (int i = 0; i < size*size; i++) {
            room_arr[i]->print();
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
            else if (ob.room_arr[i*ob.size+j]->door[0])
                out << open;
            else
                out << close;
        out << endl;

        for (int j = 0; j < 3; j++){//внутрянняя часть комант + верт стены
            for (int k = 0; k < ob.size; k++) {
                if (j == 1) {//лев. стена
                    if (ob.room_arr[i*ob.size+k]->mod[1] && (i*ob.size+k)%ob.size == 0)
                        out << 'O';
                    else if (ob.room_arr[i*ob.size+k]->door[3])
                        out << '_';
                    else 
                        out << ']';
                }
                else
                    out << '#';

                out << ob.room_arr[i*ob.size+k]->inside[j]; //добавить лев и прав двери + окна

                if (j == 1) {//прав. стена
                    if (ob.room_arr[i*ob.size+k]->mod[1] && (i*ob.size+k)%ob.size == ob.size - 1)
                        out << 'O';
                    else if (ob.room_arr[i*ob.size+k]->door[2])
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

basic_room::basic_room() {
    room_num = stat_num++;
    for (int i = 0; i < 4; i++) {
        door[i] = false; //closed
        mod[i] = false;
    }
    mod[0] = true;
    inside[0] = "";
    inside[1] = "";
    inside[2] = "";
}

void basic_room::print() {
    cout << "Num: " << room_num << endl
        << "mods: " << mod[0] << ' ' << mod[1] << ' ' << mod[2] << ' ' << mod[3] << ' ' << endl
        << "doors: " << door[0] << ' ' << door[1] << ' ' << door[2] << ' ' << door[3] << ' ' << endl
        << "inside: " << endl << "#####" << endl
        << inside[0] << endl << inside[1] << endl << inside[2] << endl << "#####" << endl;
}

empty_room::empty_room():basic_room() {
    inside[0] = "     ";
    inside[1] = "     ";
    inside[2] = "     ";
}

closed_room::closed_room() :basic_room() {
    inside[0] = "     ";
    inside[1] = "  ?  ";
    inside[2] = "     ";
}

chest_room::chest_room() :basic_room() {
    inside[0] = "  _  ";
    inside[1] = " |_| ";
    inside[2] = "     ";
}

monster_room::monster_room() :basic_room() {
    inside[0] = "  Ш  ";
    inside[1] = " \\|/ ";
    inside[2] = " / \\ ";
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