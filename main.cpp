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
    // - view library, edit library(remove or add song), search, end program 
    // and sort playlist a certain way (potentially create playlist)
    int action;
    cout << "\nWhat would you like to do?(enter number)\n"
        << "1: View Libray 2: Edit Library 3: Search 4: Sorting Options 5: Quit\n";
   cin >> action;
    switch (action) {
        case 1:
            cout << "Option 1: View Libray" << endl;
            break;
        case 2:
            cout << "Option 2: Edit Library" << endl;
            break;
        case 3:
            cout << "Option 3: Search" << endl;
            break;
        case 4:
            cout << "Option 4: Sorting Options" << endl;
            break;
        case 5:
            cout << "Option 5: Quit" << endl;
            return 0;
            break;
        default:
            cout << "Invalid Option-Retry." << endl;
            break;


    }

    cout << "\nProgram ran." << endl;

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
