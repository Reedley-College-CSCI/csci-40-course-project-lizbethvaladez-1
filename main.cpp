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
#include <fstream> // for file reading

using namespace std;

const int MAX_SIZE = 50; //max

//struct for library
struct musicLibrary {
    string song;
    string artist;
    double minutes;

};

//FUNCTIONS 
void addSong(musicLibrary*& library, int& size);
void printMusicLibrary(musicLibrary*& library, int size);
void readLibraryFile(musicLibrary*& library, int& songCount);


int main() {
    int songCount = 0; 

    musicLibrary* library = new musicLibrary[MAX_SIZE]; //dynamic array

    //printing welcome to program
    cout << "--------   Welcome to your Music Library  --------" << endl;
   
    //load playlist 
    readLibraryFile(library, songCount);
   

    //add songs test for the array
    int size;
    //cout << "\nHow many songs would you like to add?\n";
    //cin >> size;
    //addSong(library, size);

    printMusicLibrary(library, songCount); //test read

    //menu for actions (switch loop?)
    // - view library, edit library(remove or add song), search, end program 
    // and sort playlist a certain way (potentially create playlist) 
    /*
    int action;
    cout << "\nWhat would you like to do?(enter number)\n"
        << "1: View Libray 2: Edit Library 3: Search 4: Sorting Options 5: Quit\n";
    cin >> action;
    while (action != 5) {
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
        default:
            cout << "Invalid Option-Retry." << endl;
            break;
        }
        cout << "\nWhat would you like to do?(enter number)\n"
           << "1: View Libray 2: Edit Library 3: Search 4: Sorting Options 5: Quit\n";
        cin >> action;
    }
            //cout << "\nProgram ran." << endl;
*/
 


            return 0;

   
}
//reading library file into a dynamic array
void readLibraryFile(musicLibrary*& library, int& songCount) {
    ifstream libFile("music_library.txt");

    if (!libFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

    musicLibrary* newLibrary = new musicLibrary[MAX_SIZE];
    songCount = 0;

    while (songCount < MAX_SIZE && getline(libFile, newLibrary[songCount].song)) {
        cout << "--- Song " << songCount + 1 << " ---" << endl;

        cout << "\nSong Name: " << newLibrary[songCount].song << endl;

        cout << "Artist: ";
        getline(libFile, newLibrary[songCount].artist);
        cout << newLibrary[songCount].artist << endl;

        cout << "Length in Minutes (0.00): ";
        string minutesStr;
        getline(libFile, minutesStr);
        newLibrary[songCount].minutes = stod(minutesStr);
        cout << newLibrary[songCount].minutes << endl;

        cout << "Song Loaded" << endl;
        cout << endl;

        songCount++;
    }

    cout << endl;
    delete[] library;
    library = newLibrary;


    cout << "\nAdded Succesfully" << endl;
    libFile.close();
    cout << "Total Songs Loaded: " << songCount << endl;

}

//print library function
void printMusicLibrary(musicLibrary*& library, int songCount) {
    /* cout << "\n--- Songs Added ---" << endl;
     for (int i = 0; i < size; i++) {

         cout << i + 1 << ". " << library[i].song << " | by "
             << library[i].artist << " | " << library[i].minutes << " minutes" << endl;

 */
    cout << "\n--- Library ---" << endl;
    if (songCount == 0) {
        cout << "Library is empty" << endl;
        return;
    }
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << library[i].song << " | by "
            << library[i].artist << " | " << library[i].minutes << " minutes" << endl;
    }
}
//add songs function
void addSong(musicLibrary*& library, int& size) {    
    library = new musicLibrary[size];

    for (int i = 0; i < size; i++) {
        cout << "--- Song " << i + 1 << " ---";

        cin.ignore();

        cout << "Song Name: ";
        getline(cin, library[i].song);

        cout << "Artist: ";
        getline(cin, library[i].artist);

        cout << "Length in Minutes (0.00): ";
        cin >> library[i].minutes;
        cout << endl;
    }

    cout << "\nAdded Succesfully" << endl;
}

//remove songs function
//search function
//sorting function
// edit song

// Maybe:
// library statistcs(Total songs, total minutes, etc)
//create playlist function
//delete playlist function
