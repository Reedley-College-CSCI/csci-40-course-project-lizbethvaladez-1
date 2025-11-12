// CSCI-40 Final Project
// Author: Lizbeth Valadez
/* 
 * Description:
 * A music library program where users can add or remove songs that are read and stored on a file. 
 * A menu will give options to add, remove, search, and sort the library. The search will be through song names
 * and artists. There will be options to sort by name and artist. 
 * (WIP) There will be an option to create playlists from the main music library, potentially using pointers
 * to add the songs from the library
*/
#include <string> // be able to use string
#include <iostream>
using namespace std;

//struct for library
struct musicLibrary {
    string song;
    int minutes;
    string artist;

};



int main() {
    //printing welcome to program
    cout << "--------   Welcome to your Music Library  --------" << endl;

    //load playlist

    //menu for actions (switch loop?)
    // - view library, edit playlist(remove or add song), search, 
    // and sort playlist a certain way (potentially create playlist)


    return 0;
}

//reading library file function into a dynamic array
//print library function
//add songs function
//remove songs function
//search function
//sorting function
// Maybe:
//create playlist function
//delete playlist function
