#include <iostream>
#include "my_lib.h"

using namespace std;

int entity::numer;

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
    //basic_room** arr;
    //arr = new basic_room * [4];
    //empty_room r0;
    //closed_room r1;
    //chest_room r2;
    //monster_room r3;
    //arr[0] = &r0;
    //arr[1] = &r1;
    //arr[2] = &r2;
    //{
    //
    //arr[3] = &r3;
    //}
    //
    //for (int i = 0; i < 4; i++) {
    //    arr[i]->print();
    //}

    //cout << "Hello!!\nWhat's your name hero?\nType it here and press ENTER: ";
    string name;
    cin >> name;
    hero_class player(name.c_str());

    //cout << "\nHow cool are you from 5 to 15?\nType it here and press ENTER: ";
    int size;
    cin >> size;
    //while (size < 5 || size > 15) {
    //    cout << "FROM 5 TO 15!!!\nType it here and press ENTER: ";
    //    cin >> size;
    //}
    //cout << "\nHi, " << name << "!!!\nWhait a bit please.\n";

    map main_map(size);
    //main_map.test_func();
    int side;
    char wasd;
    //main_map.test_func();//ЭТО ТЕСТОВО
    system("clear");
    while (1) {
        try {
            cout << main_map << player;
            cin >> wasd;
            switch (wasd) {
            case 'w':
                side = 0;
                break;
            case 'a':
                side = 3;
                break;
            case 's':
                side = 2;
                break;
            case 'd':
                side = 1;
                break;
            default:
                throw "input_error";
            }
            int new_room = main_map.move(player, side);
            if (new_room) {
                main_map.event_handler(player, new_room);
            }
        }
        catch (const char * str) {
            string msg(str);
            if (msg == "w_loss") {
                system("clear");
                cout << main_map << player << "Oh, no!You've just fallen out of the window(\nYou died(((\n";
            }
            if (msg == "input_error") {
                cout << "TERMINATED DUE TO WRONG INPUT\n";
            }
            if (msg == "hp_loss") {
                system("clear");
                cout << main_map << player << "Oh, no!You've just ran out of HP(\nYou died(((\n";
            }
            break;
        }
        system("clear");
    }

    ////попробовать зациклить через трай блок и потом в кэтчах обрабатывать события
    //int size;
    //map test_map(5);
    //hero_class player("test");
    ///*player.print();
    //for (int i = 0; i < 4; i++) {
    //    if (test_map.move(player, i)) {
    //        cout << i << " :ok ";
    //    }
    //    else {
    //        cout << i << " :Nok ";
    //    }
    //}
    //cout << '\n';*/
    //
    //    int side;
    //do {
    //    char wasd;
    //    cout << test_map;
    //    player.print();
    //    cin >> wasd;
    //    switch (wasd) {
    //    case 'w':
    //        side = 0;
    //        break;
    //    case 'a':
    //        side = 3;
    //        break;
    //    case 's':
    //        side = 2;
    //        break;
    //    case 'd':
    //        side = 1;
    //        break;
    //    }
    //    //test_map.test_func();
    //} while (test_map.move(player, side));

    ////test_map.test_func();

    //test_map.print();
    //
    //test_map.test_func();
    //
    // string *chest;
    // chest = new string[4];
    // chest[0] = "#######\n#  _  #\n# |_| #\n#     #\n#######";
    // chest[1] = "#######\n#   \\ #\n# |_| #\n#     #\n#######";
    // chest[2] = "#######\n#    _#\n# |_| #\n#     #\n#######";
    // chest[3] = "#######\n#     #\n# |_|\\#\n#     #\n#######";
    //
    // while (1)
    // {
    //     for (int i = 0; i < 4; i++){
    //         this_thread::sleep_for(std::chrono::milliseconds(500));
    //         system("clear");
    //         cout << chest[i] << endl;
    //     }
    // }
    // delete[] chest;
    
    return 0;
}