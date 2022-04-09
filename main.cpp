#include <iostream>
#include <thread>
#include "my_lib.h"

using namespace std;

int basic_room::stat_num = 0;
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

    //arr[3] = &r3;
    //}
    //
    //for (int i = 0; i < 4; i++) {
    //    arr[i]->print();
    //}



    int size;
    cin >> size;
    map test_map(size);
    cout << test_map << endl;
    //test_map.print();
    
    //test_map.test_func();

    // string *chest;
    // chest = new string[4];
    // chest[0] = "#######\n#  _  #\n# |_| #\n#     #\n#######";
    // chest[1] = "#######\n#   \\ #\n# |_| #\n#     #\n#######";
    // chest[2] = "#######\n#    _#\n# |_| #\n#     #\n#######";
    // chest[3] = "#######\n#     #\n# |_|\\#\n#     #\n#######";

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