#include <iostream>
#include "my_lib.h"

using namespace std;

int entity::numer;

int main() {

    cout << "Hello!!\nWhat's your name hero?\nType it here and press ENTER: ";
    string name;
    cin >> name;
    hero_class player(name.c_str());

    cout << "\nHow cool are you from 5 to 15?\nType it here and press ENTER: ";
    int size;
    cin >> size;
    /*while (size < 5 || size > 15) {
        cout << "FROM 5 TO 15!!!\nType it here and press ENTER: ";
        cin >> size;
    }*/
    cout << "\nHi, " << name << "!!!\nWhait a bit please.\n";

    map main_map(size);
    int side;
    char wasd;
    system("clear");

    while (!main_map.win()) {
        try {
            cout << main_map << player << "\nuse \033[0;90mWASD\033[0m to move and \033[0;90mH\033[0m to heal\n";
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
            case 'h':
                if (!player.heal()) {
                    cout << "Not enough items!\n\033[0;90mpress any key to continue\033[0m\n";
                    cin >> wasd;
                }
                else {
                    cout << "You are healed!\n\033[0;90mpress any key to continue\033[0m\n";
                    cin >> wasd;
                }
                system("clear");
                continue;
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

    if (main_map.win())
        cout << main_map << player;
    player.print();
    return 0;
}