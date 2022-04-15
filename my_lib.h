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
    void chest_animation(int room_num, int loot_type, hero_class& hero);
public:
    map(int size = 1);
    //room operator []
    int move(hero_class& hero, int side); //0 - up; 1 - right; 2 - down; 3 - left
    ~map();
    void print();
    void test_func();
    void event_handler(hero_class& hero, int new_room);

    friend std::ostream& operator <<(std::ostream& out, map& ob);
};

class room {
    int room_num;
    bool mod[5]; //0 - empty; 1 - window; 2 - chest; 3 - monster; 4 - closed
    bool door[4]; //0 - up; 1 - right; 2 - down; 3 - left //1 - open 0 - close
    string inside[3];
public:
    void print();
    room();
    void operator >>(room& new_room);

    friend std::ostream& operator <<(std::ostream& out, map& ob);
    friend class map;
};

class entity {
protected:
    static int numer;
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
    int loot[4];//0 - sword; 1 - shield; 2 - armor; 3 - heal
public:
    hero_class(const char * str);
    void print();

    friend std::ostream& operator <<(std::ostream& out, hero_class& ob);
    friend class map;
};

class monster_class : public entity {
    static int num;
    int type;
    //int num;
public:
    monster_class();
    friend void map::event_handler(hero_class& hero, int room_num);
    void print();
};

#endif