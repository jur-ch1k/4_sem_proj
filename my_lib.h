#ifndef __my_lib__h__
#define __my_lib__h__

#include <iostream>
using namespace std;

class map;
class entity;
class hero_class;
class room;

class map {
    room* room_arr;
    int size; // map = size * size
    //int player_pos;
public:
    map(int size = 1);
    //room operator []
    bool move(hero_class& hero, int side); //0 - up; 1 - right; 2 - down; 3 - left
    ~map();
    void print();
    void test_func();

    friend std::ostream& operator <<(std::ostream& out, map& ob);
};

class room {
protected:
    static int stat_num;
    int room_num;
    bool mod[5]; //0 - empty; 1 - window; 2 - chest; 3 - monster; 4 - closed
    bool door[4]; //0 - up; 1 - right; 2 - down; 3 - left //1 - open 0 - close
    string inside[3];
public:
    void print();
    room();

    friend std::ostream& operator <<(std::ostream& out, map& ob);
    friend class map;
};

class entity {
protected:
    string name;
    int strength;
public:
    entity(const char * str);
    virtual void print() = 0;
};


class hero_class: public entity {// test
    int hp;
    int pos;
    int stamina;
    int harizma;
    bool loot[5];
public:
    hero_class(const char * str);
    void print();
    bool window_lose();
    friend class map;
};

#endif