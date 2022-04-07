#include <iostream>
#include <thread>

using namespace std;

class map;
class player;

class room {
    static int stat_num;
    int room_num;
    bool mod[4]; //0 - empty; 1 - window; 2 - chest; 3 - enemy; 4 - ???
    bool door[4]; //0 - up; 1 - right; 2 - down; 3 - left
    string inside[3];
    void print() {
        cout << "Num: " << room_num << endl
        << "mods: " << mod[0] << ' ' << mod[1] << ' ' << mod[2] << ' ' << mod[4] << ' ' << endl
        << "doors: " << door[0] << ' ' << door[1] << ' ' << door[2] << ' ' << door[4] << ' ' << endl
        << "inside: " << endl << "#####" << endl
        << inside[0] << endl << inside[1] << endl << inside[2] << endl << "#####" << endl;
    }
public:
    room() {
        room_num = stat_num++;
        for (int i = 0; i < 4; i++) {
            door[i] = false; //closed
            mod[i] = false;
        }
        mod[0] = true;
        inside[0] = "     ";
        inside[1] = "  ?  ";
        inside[2] = "     ";
        //inside[0][4] = room_num+'0';
    }
    friend std::ostream& operator <<(std::ostream& out, map& ob);
    friend class map;
};

class map {
    room *arr;
    int size; // map = size * size
    //int player_pos;
public:
    map(int size = 1) {
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
    //room operator []
    void move(int side) {//0 - up; 1 - right; 2 - down; 3 - left
        
    }
    ~map() {
        delete [] arr;
    }
    void print() {
        for (int i = 0; i < size*size; i++) {
            arr[i].print();
        }
    }
    friend std::ostream& operator <<(std::ostream& out, map& ob);
};

class entity {
protected:
    string name;
    int strength;
public:
    entity(const char * str): name(str), strength(0){}
    virtual void print() = 0;
};

class hero: public entity {// test
    int hp;
    int pos;
    int stamina;
    int harizma;
    bool loot[5];
public:
    hero(const char * str): entity(str) {
        hp = 0;
        pos = 0;
        stamina = 1;
        harizma = 0;
        for (int i = 0; i < 5; i++) {
            loot[i] = false;
        }
    }
    void print() {
        cout << "hp: " << hp << "pos: " << pos;
    }
    friend class map;
};

int room::stat_num = 0;
int main() {
//drawing test   this_thread::sleep_for(std::chrono::milliseconds(50));
    //int size;
    // //cin >> size;
    // char *empty_room[] = {"     ", "     ", "     "};
    // char *loked_room[] = {"     ", "  ?  ", "     "};
    // char *chest_room1[] = {"  _  ", " |_| ", "     "};
    // char *chest_room2[] = {"   \\ ", " |_| ", "     "};
    // char *chest_room3[] = {"    _", " |_| ", "     "};
    // char *chest_room4[] = {"     ", " |_|\\", "     "};
    // string test[5];
    // test[0] = "1234";
    // //int map[size][size];
    // // char a = 0;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 5; j++)
    //         cout << chest_room1[i][j]; 
    //     cout << endl;
    // }
    //     cout << chest_room2[0] << endl << 
    //     chest_room2[1] << endl << chest_room2[2] << endl;
    //     cout << chest_room3[0] << endl << 
    //     chest_room3[1] << endl << chest_room3[2] << endl;
    //     cout << chest_room4[0] << endl << 
    //     chest_room4[1] << endl << chest_room4[2] << endl;
    //     cout << test[0];

    int size;
    //cin >> size;
    //map test_map(size);
    //cout << test_map << endl;
    //test_map.print();
    
    string *chest;
    chest = new string[4];
    chest[0] = "#######\n#  _  #\n# |_| #\n#     #\n#######";
    chest[1] = "#######\n#   \\ #\n# |_| #\n#     #\n#######";
    chest[2] = "#######\n#    _#\n# |_| #\n#     #\n#######";
    chest[3] = "#######\n#     #\n# |_|\\#\n#     #\n#######";

    while (1)
    {
        for (int i = 0; i < 4; i++){
            this_thread::sleep_for(std::chrono::milliseconds(500));
            system("clear");
            cout << chest[i] << endl;
        }
    }
    delete[] chest;
    return 0;
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