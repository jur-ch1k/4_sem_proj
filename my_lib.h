#ifndef __my_lib__h__
#define __my_lib__h__

#include <iostream>
using namespace std;

class map;
class entity;
class hero;
class basic_room;
class empty_room;
class closed_room;
class chest_room;
class monster_room;

//class map {
//    basic_room **room_arr;
//    empty_room def_rooms_arr[4];
//    int size; // map = size * size
//    //int player_pos;
//public:
//    map(int size = 1);
//    //room operator []
//    void move(int side); //0 - up; 1 - right; 2 - down; 3 - left
//    ~map();
//    void print();
//    void test_func();
//    friend std::ostream& operator <<(std::ostream& out, map& ob);
//};

class basic_room {
protected:
    static int stat_num;
    int room_num;
    bool mod[4]; //0 - empty; 1 - window; 2 - chest; 3 - enemy; 4 - ???
    bool door[4]; //0 - up; 1 - right; 2 - down; 3 - left
    string inside[3];
public:
    void print();
    basic_room();
    friend std::ostream& operator <<(std::ostream& out, map& ob);
    friend class map;
};

class empty_room: public basic_room {
public:
    empty_room();
};

class closed_room : public basic_room {
public:
    closed_room();
};

class chest_room: public basic_room {
public:
    chest_room();
};

class monster_room: public basic_room {
public:
    monster_room();
};

class entity {
protected:
    string name;
    int strength;
public:
    entity(const char * str);
    virtual void print() = 0;
};

class hero: public entity {// test
    int hp;
    int pos;
    int stamina;
    int harizma;
    bool loot[5];
public:
    hero(const char * str);
    void print();
    friend class map;
};

class map {
    basic_room** room_arr;//это всё просто тестово,
    empty_room r_arr_1[4];//переделай нах
    closed_room r_arr_2[4];
    chest_room r_arr_3[4];
    monster_room r_arr_4[4];
    int size; // map = size * size
    //int player_pos;
public:
    map(int size = 1);
    //room operator []
    void move(int side); //0 - up; 1 - right; 2 - down; 3 - left
    ~map();
    void print();
    void test_func();
    friend std::ostream& operator <<(std::ostream& out, map& ob);
};

#endif