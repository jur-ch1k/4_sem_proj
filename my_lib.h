#ifndef __my_lib__h__
#define __my_lib__h__

#include <iostream>
using namespace std;

class map;
class room;
class entity;
class hero;

class map {
    room *arr;
    int size; // map = size * size
    //int player_pos;
public:
    map(int size = 1);
    //room operator []
    void move(int side); //0 - up; 1 - right; 2 - down; 3 - left
    ~map();
    void print();
    friend std::ostream& operator <<(std::ostream& out, map& ob);
};

class room {
    static int stat_num;
    int room_num;
    bool mod[4]; //0 - empty; 1 - window; 2 - chest; 3 - enemy; 4 - ???
    bool door[4]; //0 - up; 1 - right; 2 - down; 3 - left
    string inside[3];
    void print();
public:
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

#endif