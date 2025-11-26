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
#include <iomanip>

using namespace std;

const int MAX_SIZE = 50; //max

//struct for library
struct musicLibrary {
    string song;
    string artist;
    double minutes;

};

//FUNCTIONS 
void addSong();
void printMusicLibrary(musicLibrary*& library, int size);
void readLibraryFile(musicLibrary*& library, int& songCount);
void removeSong(musicLibrary*& library, int& songCount);
void libraryStats(musicLibrary*& library, int songCount);



int main() {
    int songCount = 0;

    musicLibrary* library = new musicLibrary[MAX_SIZE]; //dynamic array

    //printing welcome to program
    cout << "--------   Welcome to your Music Library  --------" << endl;

    //menu for actions (switch loop?)
    // - view library, edit library(remove or add song), search, end program 
    // and sort playlist a certain way (potentially create playlist) 

    int action;
    cout << "\nWhat would you like to do?(enter number)\n"
        << "1: View Libray 2: Edit Library 3: Search 4: Sorting Options 5: Quit\n";
    cin >> action;

    while (action != 5) {
        switch (action) {
        case 1:
            cout << "Option 1: View Libray";
            readLibraryFile(library, songCount); //rereads the array so when a new song is added it can read it
            libraryStats(library, songCount); // prints library stats when library viewed
            printMusicLibrary(library, songCount); //test read
            break;

        case 2: //edit library
            cout << "Option 2: Edit Library" << endl;
            char option;
            cout << "A. Add a song, B. Edit a Song, or C. Remove a Song? (A, B, or C)\n X to Cancel\n";
            cin >> option;
            while ((option != 'x') && (option != 'X')) {
                switch (option) {
                case 'A': //adds song/s
                case 'a':
                    addSong();
                    break;

                case 'B': //edits a song
                case 'b':
                    cout << "Editing song" << endl;
                    break;

                case 'C': //removing song
                case 'c':
                    readLibraryFile(library, songCount); //rereads the array so it can display the songs that could be removed
                    removeSong(library, songCount);
                        break;
                default:
                    cout << "Invalid Option - Retry" << endl;
                    break;
                }
                cout << "\nA. Add a song, B. Remove a Song, or C. Remove a Song? (A, B, or C)\n X to Cancel\n";
                cin >> option;
            }
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
        cout << "\nWhat would you like to do?\n"
            << "1: View Libray 2: Edit Library 3: Search 4: Sorting Options 5: Quit\n";
        cin >> action;
    }


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

        //song already read into the while function, 

    //Artist
        getline(libFile, newLibrary[songCount].artist);

        //minutes - needs to be converted from string to double
        string minutesStr;
        getline(libFile, minutesStr);
        newLibrary[songCount].minutes = stod(minutesStr);

        songCount++;

        if (songCount == MAX_SIZE) { //incase it goes over max songs
            cout << "Max songs library can load" << endl;
            break;
        }

    }

    cout << endl;
    delete[] library;
    library = newLibrary;

    libFile.close();
   // cout << "\nTotal Songs Loaded: " << songCount;

}

//print library function
void printMusicLibrary(musicLibrary*& library, int songCount) {
    /* cout << "\n--- Songs Added ---" << endl;
     for (int i = 0; i < size; i++) {

         cout << i + 1 << ". " << library[i].song << " | by "
             << library[i].artist << " | " << library[i].minutes << " minutes" << endl;

 */
    cout << "--- Library ---" << endl;
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
void addSong() {
    ofstream libFile("music_library.txt", ios::app);

    if (!libFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

    int size;
    cout << "\nHow many songs would you like to add?\n";
    cin >> size;

    string song, artist;
    double minutes;

    for (int i = 0; i < size; i++) {
        cout << "--- Song " << i + 1 << " ---" << endl;

        cin.ignore();

        cout << "Song Name: ";
        getline(cin, song);

        cout << "Artist: ";
        getline(cin, artist);

        cout << "Length in Minutes (0.00): ";
        cin >> minutes;
        cout << endl;

        libFile << song << "\n";
        libFile << artist << "\n";
        libFile << fixed << setprecision(2) << minutes << "\n";

        cout << "Added: " << song << " by " << artist << " (" << minutes << " minutes)" << endl;
    }
    libFile.close();
    cout << "\nAdded Succesfully" << endl;
}

//remove songs function 
void removeSong(musicLibrary*& library, int& songCount) {
    int choice;
    if (songCount == 0) {
        cout << "Library is empty - no songs to remove." << endl;
        return;
    }

    cout << "Current songs in library:" << endl; //displays songs to remove
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << library[i].song << " | by "
            << library[i].artist << " | " << library[i].minutes << " minutes" << endl;
    }

    cout << "Which song would would you like to remove?" << endl;
    cin >> choice;
     
    if (choice < 1 || choice > songCount) {
        cout << "Invalid choice." << endl;
        return;
    }

    int indexChoice = choice - 1; //makes choice aligns correctly with array index

    // shows song being remoced
    cout << "Removing: " << library[indexChoice].song << " by "
        << library[indexChoice].artist << endl;

    // shifts array elements left
    for (int i = indexChoice; i < songCount - 1; i++) {
        library[i] = library[i + 1];
    }
    songCount--; 

    ofstream libFile("music_library.txt");
    if (!libFile.is_open()) {
        cout << "Error: Could not open file for writing" << endl;
        return;
    }

    for (int i = 0; i < songCount; i++) {
        libFile << library[i].song << endl;
        libFile << library[i].artist << endl;
        libFile << fixed << setprecision(2) << library[i].minutes << endl;
    }

    libFile.close();
    cout << "Song removed successfully!" << endl;
}

// edit song
void editSong(musicLibrary*& library, int songCount) {

    if (songCount == 0) { //checks if songCount is 0
        cout << "Library is empty, unable to write it." << endl;
        return;
    }

    int choice;
    cout << "Which song would would you like to remove?" << endl;
    cin >> choice;
    if (choice < 1 || choice > songCount) { //validates choice
        cout << "Invalid choice." << endl;
        return;
    }

    int indexChoice = choice - 1; //makes choice aligns correctly with array index

    cout << "Editing: " << library[indexChoice].song << " by "
        << library[indexChoice].artist << endl;
}
//search function
//sorting function
// Maybe:
// library statistcs(prints total songs, total minutes, etc)
void libraryStats(musicLibrary*& library, int songCount) {
    double totalMinutes = 0.0;
    for (int i = 0; i < songCount; i++) {
        totalMinutes += library[i].minutes; //incramenting total minutes
    }
    //hour convert
    double hours = totalMinutes / 60;
    //check if at least an hour, if not print in minutes
    if (hours < 1) {
        cout << "\nTotal Songs: " << songCount << " | Length: " << totalMinutes << " minutes" << endl;
    } 
    else {
        cout << "\nTotal Songs: " << songCount << " | Length: " << hours << " hour(s)" << endl;
    }
}
//create playlist function
//delete playlist function
