// CSCI-40 Final Project
// Author: Lizbeth Valadez
/*
 * Description:
 * A music library program where users can add or remove songs that are read and stored on a file.
 * A menu will give options to add, remove, search, and sort the library. The search will be through song names
 * and artists. There will be options to sort by name and artist. There is also a backup function--whenever the user 
 * edits the library, the previous iteration is saved before any changes go through.
*/
#include <string> // be able to use string
#include <iostream>
#include <fstream> // for file reading
#include <iomanip>


using namespace std;

const int MAX_SIZE = 100; //max

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
//Editing -----------
void editLibrary(musicLibrary*& library, int& songCount);
void removeSong(musicLibrary*& library, int& songCount);
void libraryStats(musicLibrary*& library, int songCount);
void editSong(musicLibrary*& library, int songCount);
//sorting -------------
void sortLibrary(musicLibrary*& library, int songCount);
void sortBySong(musicLibrary*& library, int songCount, bool ascending);
void sortByArtist(musicLibrary*& library, int songCount, bool ascending);
void sortByMinutes(musicLibrary*& library, int songCount, bool ascending);
//searching ---------
void searchLibrary(musicLibrary*& library, int songCount);
void searchSong(musicLibrary*& library, int songCount);
void searchArtist(musicLibrary*& library, int songCount);
void searchBoth(musicLibrary*& library, int songCount);
//backup---------------
void backupBeforeChange(musicLibrary*& library, int songCount);
void restoreLibrary(musicLibrary*& library, int& songCount);

//VALIDATION FUNCTIONS
int getValidInt(string prompt, int minVal, int maxVal);


int main() {
    int songCount = 0;

    musicLibrary* library = new musicLibrary[MAX_SIZE]; //dynamic array

    //printing welcome to program
    cout << "--------   Welcome to your Music Library  --------" << endl;

    //menu for actions (switch loop?)
    // - view library, edit library(remove or add song), search, end program 
    // and sort playlist a certain way (potentially create playlist) 

    int action;
    cout << "What would you like to do? (enter number)\n"
        << "1: View Library\n"
        << "2: Edit Library\n"
        << "3: Search\n"
        << "4: Sorting Options\n"
        << "5: Quit\n";
    action = getValidInt("Enter choice: ", 1, 5);


    while (action != 5) {
        switch (action) {
        case 1:
            cout << "\n--- View Library ---" << endl;
            readLibraryFile(library, songCount); //rereads the array so when a new song is added it can read it
            libraryStats(library, songCount); // prints library stats when library viewed
            printMusicLibrary(library, songCount); //test read
            break;

        case 2: //edit library --------------------------------------------------------------------------- CASE 2
            cout << "\n--- Edit Library ---" << endl;
            editLibrary(library, songCount);
            break;

        case 3:
            cout << "\n--- Search ---" << endl;
            readLibraryFile(library, songCount); //rereads the array again
            searchLibrary(library, songCount);
            break;
        case 4:
            cout << "\n--- Sorting ---" << endl;
            readLibraryFile(library, songCount); //rereads the array again
            sortLibrary(library, songCount); // sorting
            break;
        default:
            cout << "Invalid Option - Retry." << endl;
            break;
        }
        cout << "\nWhat would you like to do? (enter number)\n"
            << "1: View Library\n"
            << "2: Edit Library\n"
            << "3: Search\n"
            << "4: Sorting Options\n"
            << "5: Quit\n";
    action = getValidInt("Enter choice: ", 1, 5);
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

    cout << "\n--- Music Library ---" << endl;
    if (songCount == 0) {
        cout << "Library is empty" << endl;
        return;
    }
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << library[i].song << " | by "
            << library[i].artist << " | " << library[i].minutes << " minutes" << endl;
    }
    cout << "--- End of Library ---" << endl;
}

//edit library options ----------------------------------------------
void editLibrary(musicLibrary*& library, int& songCount) { // keeps main code less cluttered
    //add menu for editing library here
    char option;
    cout << "\nEdit Options:\n"
        << "A. Add a song\n"
        << "B. Edit a Song\n"
        << "C. Remove a Song\n"
        << "R. Backup Options\n"
        << "X. Cancel\n"
        << "Enter choice: ";
    cin >> option; 
    while ((option != 'x') && (option != 'X')) {
        switch (option) {
        case 'A': //adds song/s
        case 'a':
            backupBeforeChange(library, songCount);
            addSong();
            break;

        case 'B': //edits a song
        case 'b':
            cout << "--- Editing Library --- " << endl;
            readLibraryFile(library, songCount); //rereads the array so it can display the songs that could be added
            backupBeforeChange(library, songCount);
            editSong(library, songCount);
            break;

        case 'C': //removing song
        case 'c':
            readLibraryFile(library, songCount); //rereads the array so it can display the songs that could be removed
            backupBeforeChange(library, songCount);
            removeSong(library, songCount);
            break;
        case 'R': //backup options
        case 'r':
            readLibraryFile(library, songCount);
            restoreLibrary(library, songCount);
            break;
        default:
            cout << "Invalid Option - Retry" << endl;
            break;
        }
        break;
    } //---------------------------------------------------------------------------------------------
}
//add songs function
void addSong() {
    ofstream libFile("music_library.txt", ios::app);

    if (!libFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

 
    string song, artist;
    double minutes;


    cout << "\n--- Add a New Song ---" << endl;
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

    cout << "\nCurrent songs in library:" << endl; //displays songs to remove
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << library[i].song << " | by "
            << library[i].artist << " | " << library[i].minutes << " minutes" << endl;
    }

    choice = getValidInt("\nEnter the number of the song you would like to remove: ", 1, songCount);


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
    cout << "\nCurrent songs in library:" << endl; //displays songs available to edit
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << library[i].song << " | by "
            << library[i].artist << " | " << library[i].minutes << " minutes" << endl;
    }
    choice = getValidInt("Enter song number: ", 1, songCount);
    if (choice < 1 || choice > songCount) { //validates choice
        cout << "Invalid choice." << endl;
        return;
    }

    int indexChoice = choice - 1; //makes choice aligns correctly with array index

    cout << "Editing: " << library[indexChoice].song << " by " //displays song
        << library[indexChoice].artist << endl;

    //add choice swtich statement
    char editOption;
    string newSongName, newArtistName;
    double newMinutes;

    cout << "\nWhat would you like to edit?\n"
        << "A. Song Name\n"
        << "B. Artist\n"
        << "C. Duration\n"
        << "D. All Fields\n"
        << "X. Cancel\n"
        << "Enter choice: ";
    cin >> editOption;
    cin.ignore();
    //switch ------------------------------------------------
    switch (editOption) {
    case 'A':
    case 'a':
        cout << "Current song name: " << library[indexChoice].song << endl;
        cout << "Enter new song name: ";
        getline(cin, newSongName);
        library[indexChoice].song = newSongName;
        cout << "Song name updated successfully" << endl;
        break;
    case 'B':
    case 'b':
        cout << "Current Artist name: " << library[indexChoice].artist << endl;
        cout << "Enter new Artist name: ";
        getline(cin, newArtistName);
        library[indexChoice].artist = newArtistName;
        cout << "Artist name updated successfully" << endl;
        break;
    case 'C':
    case 'c':
        cout << "Current Minutes: " << library[indexChoice].minutes << endl;
        cout << "Enter new time(0.00): ";
        cin >> newMinutes;
        library[indexChoice].minutes = newMinutes;
        cout << "Minutes updated successfully" << endl;
        break;
    case 'D':
    case 'd':
        //song
        cout << "Current song name: " << library[indexChoice].song << endl;
        cout << "Enter new song name: ";
        getline(cin, newSongName);
        library[indexChoice].song = newSongName;
        cout << "Song name updated successfully" << endl;
        //artist
        cout << "Current Artist name: " << library[indexChoice].artist << endl;
        cout << "Enter new Artist name: ";
        getline(cin, newArtistName);
        library[indexChoice].artist = newArtistName;
        cout << "Artist name updated successfully" << endl;
        //minutes
        cout << "Current Minutes: " << library[indexChoice].minutes << endl;
        cout << "Enter new time(0.00): ";
        cin >> newMinutes;
        library[indexChoice].minutes = newMinutes;
        cout << "Minutes updated successfully" << endl;
        break;
    case 'X':
    case 'x':
        cout << "Edit cancelled." << endl;
        return;
    default:
        cout << "Invalid option, retry." << endl;
        return;
    }
    //outputting new songs to file-----------------------------
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
//------------------------------------------------------------------

//sorting functions ------------------------------------------------
void sortLibrary(musicLibrary*& library, int songCount) { //sort function choice
    if (songCount == 0) {
        cout << "Library is empty, nothing to sort." << endl;
        return;
    }
    //add menu for sorting library here
    char option;
    cout << "\nSort Options:\n"
        << "A. Sort by Song\n"
        << "B. Sort by Artist\n"
        << "C. Sort by Length\n"
        << "X. Cancel\n"
        << "Enter choice: ";
    cin >> option;
    while ((option != 'x') && (option != 'X')) {
        backupBeforeChange(library, songCount);//backup
        switch (option) {
        case 'A': //sorts songs
        case 'a':
            //add ascending case --------------
            cout << "\nSort Order:\n"
                << "1. Ascending (A-Z)\n"
                << "2. Descending (Z-A)\n"
                << "0. Cancel\n";
            int songOpt; //option of ascending for songs
            songOpt = getValidInt("Enter choice: ", 0, 2);
            switch (songOpt) {
            case 1:
                sortBySong(library, songCount, true);
                break;
            case 2:
                sortBySong(library, songCount, false);
                break;
            case 0:
                cout << "Sort Cancled" << endl;
                break;
            default:
                cout << "Invalid Inputs" << endl;
                break;
            }
            break;

        case 'B': //edits a song
        case 'b':
            //add ascending case --------------
            cout << "\nSort Order:\n"
                << "1. Ascending (A-Z)\n"
                << "2. Descending (Z-A)\n"
                << "0. Cancel";
            int artistOpt; //ascending options for artists
            artistOpt = getValidInt("Enter choice: ", 0, 2);

            switch (artistOpt) {
            case 1:
                sortByArtist(library, songCount, true);
                break;
            case 2:
                sortByArtist(library, songCount, false);
                break;
            case 0:
                cout << "Sort Cancled" << endl;
                break;
            default:
                cout << "Invalid Inputs" << endl;
                break;
            }
            break;

        case 'C': //edits by minutes
        case 'c':
            //add ascending case --------------
            cout << "\nSort Order:\n"
                << "1. Ascending (Shortest to Longest)\n"
                << "2. Descending (Longest to Shortest)\n"
                << "0. Cancel\n";
            int minuteOpt; //ascending option for mintues
            minuteOpt = getValidInt("Enter choice: ", 0, 2);
            switch (minuteOpt) {
            case 1:
                sortByMinutes(library, songCount, true);
                break;
            case 2:
                sortByMinutes(library, songCount, false);
                break;
            case 0:
                cout << "Sort Cancled" << endl;
                break;
            default:
                cout << "Invalid Inputs" << endl;
                break;
            }            
            break;
        default:
            cout << "Invalid Option - Retry" << endl;
            break;
        }
        break;
    }
    //output the new sort order to files
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

}
void sortBySong(musicLibrary*& library, int songCount, bool ascending) {
    for (int i = 0; i < songCount - 1; i++) {
        for (int j = 0; j < songCount - i - 1; j++) {
            bool shouldSwap;

            if (ascending) {
                // A-Z: swap if current > next
                shouldSwap = (library[j].song > library[j + 1].song);
            }
            else {
                // Z-A: swap if current < next
                shouldSwap = (library[j].song < library[j + 1].song);
            }

            if (shouldSwap) {
                // Swap the entire struct
                musicLibrary temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    if (ascending) {
        cout << "Sorted by Song Name (A-Z)" << endl;
    }
    else {
        cout << "Sorted by Song Name (Z-A)" << endl;
    }

}
void sortByArtist(musicLibrary*& library, int songCount, bool ascending) {
    for (int i = 0; i < songCount - 1; i++) {
        for (int j = 0; j < songCount - i - 1; j++) {
            bool shouldSwap;

            if (ascending) {
                // A-Z: swap if current > next
                shouldSwap = (library[j].artist > library[j + 1].artist);
            }
            else {
                // Z-A: swap if current < next
                shouldSwap = (library[j].artist < library[j + 1].artist);
            }

            if (shouldSwap) {
                // Swap the entire struct
                musicLibrary temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    if (ascending) {
        cout << "Sorted by Artists Name (A-Z)" << endl;
    }
    else {
        cout << "Sorted by Artists Name (Z-A)" << endl;
    }
}
void sortByMinutes(musicLibrary*& library, int songCount, bool ascending) {
    for (int i = 0; i < songCount - 1; i++) {
        for (int j = 0; j < songCount - i - 1; j++) {
            bool shouldSwap;

            if (ascending) {
                // A-Z: swap if current > next
                shouldSwap = (library[j].minutes > library[j + 1].minutes);
            }
            else {
                // Z-A: swap if current < next
                shouldSwap = (library[j].minutes < library[j + 1].minutes);
            }

            if (shouldSwap) {
                // Swap the entire struct
                musicLibrary temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    if (ascending) {
        cout << "Sorted by Minutes (Shortest to Longest)" << endl;
    }
    else {
        cout << "Sorted by Minutes (Longest to Shortest)" << endl;
    }
}
//---------------------------------------------------------------------

//search functions -----------------------------------------------------
void searchLibrary(musicLibrary*& library, int songCount) {
    if (songCount == 0) {
        cout << "Library is empty, nothing to search." << endl;
        return;
    }
    //add menu for saerching library here
    char option;
    cout << "\nSearch Options:\n"
        << "A. Search by Song Name\n"
        << "B. Search by Artist\n"
        << "C. Search Both\n"
        << "X. Cancel\n"
        << "Enter choice: ";
    cin >> option;
    while ((option != 'x') && (option != 'X')) {
        switch (option) {
        case 'A': //searches songs
        case 'a':
            searchSong(library, songCount);
            break;
        case 'B': //Searches Arist 
        case 'b':
            searchArtist(library, songCount);
            break;
        case 'C': //Searches Arist 
        case 'c':
            searchBoth(library, songCount);
            break;
        default:
            cout << "Invalid Option - Retry" << endl;
            break;
        }
        break;
    }
}
void searchSong(musicLibrary*& library, int songCount) {

    cin.ignore();
    string songSearch;
    cout << "Enter song name to search for: ";
    getline(cin, songSearch);


    string songSearchLower = songSearch; //converts search term to lowercase
    for (char& c : songSearchLower) {
        c = tolower(c);
    }

    bool found = false;
    cout << "\n--- Search Results for " << songSearch << " ---\n";

    for (int i = 0; i < songCount; i++) {
        string songNameLower = library[i].song; //convert song name in array to lowercase to compare
        for (char& c : songNameLower) {
            c = tolower(c);
        }

        if (songNameLower.find(songSearchLower) != string::npos) { //checks if term is in songname
            cout << i + 1 << ". " << library[i].song
                << " | by " << library[i].artist
                << " | " << library[i].minutes << " minutes\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No songs matching " << songSearch << " were found" << endl;
    }
    else {
        cout << "--- End of Results ---" << endl;
    }


}
void searchArtist(musicLibrary*& library, int songCount) {
    cin.ignore();
    string artistSearch;
    cout << "Enter artist name to search for: ";
    getline(cin, artistSearch);

    string artistSearchLower = artistSearch; //converts search term to lowercase
    for (char& c : artistSearchLower) {
        c = tolower(c);
    }

    bool found = false;
    cout << "\n--- Search Results for Artist " << artistSearch << " ---\n";

    for (int i = 0; i < songCount; i++) {
        string artistNameLower = library[i].artist;  //convert artist name in array to lowercase to compare
        for (char& c : artistNameLower) {
            c = tolower(c);
        }

        if (artistNameLower.find(artistSearchLower) != string::npos) { //checks if term is in artist name
            cout << i + 1 << ". " << library[i].song
                << " | by " << library[i].artist
                << " | " << library[i].minutes << " minutes\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No artists matching " << artistSearch << " were found" << endl;
    }
    else {
        cout << "--- End of Results ---" << endl;
    }
}
void searchBoth(musicLibrary*& library, int songCount) {
    cin.ignore();
    string searchTerm;
    cout << "Enter search term to look for in song names and artists: ";
    getline(cin, searchTerm);

    string searchTermLower = searchTerm; //converts search term to lowercase
    for (char& c : searchTermLower) {
        c = tolower(c);
    }

    bool found = false;
    cout << "\n--- Search Results for " << searchTerm << " in Songs and Artists ---\n";

    //convert song and artist to lowercase for comparison
    for (int i = 0; i < songCount; i++) {
        string songNameLower = library[i].song; //convert song name in array to lowercase to compare
        for (char& c : songNameLower) {
            c = tolower(c);
        }
        string artistNameLower = library[i].artist;  //convert artist name in array to lowercase to compare
        for (char& c : artistNameLower) {
            c = tolower(c);
        }

        if (songNameLower.find(searchTermLower) != string::npos || //checks if term is in song OR artist name
            artistNameLower.find(searchTermLower) != string::npos) {
            cout << i + 1 << ". " << library[i].song
                << " | by " << library[i].artist
                << " | " << library[i].minutes << " minutes\n";
            found = true;
        }
    }
}

//--------------------------------------------------------------------

// library statistcs(prints total songs, total minutes, etc)
void libraryStats(musicLibrary*& library, int songCount) {
    double totalMinutes = 0.0;
    cout << "--- Library Staistics ---" << endl;

    for (int i = 0; i < songCount; i++) {
        totalMinutes += library[i].minutes; //incramenting total minutes
    }
    //hour convert
    double hours = totalMinutes / 60;
    //check if at least an hour, if not print in minutes
    if (hours < 1) {
        cout << "Total Songs: " << songCount << " | Length: " << fixed << setprecision(2) << totalMinutes << " minutes" << endl;
    }
    else {
        cout << "Total Songs: " << songCount << " | Length: " << fixed << setprecision(2) <<  hours << " hour(s)" << endl;
    }
}

// Backup feature - Before making changes to music library, the library is stored in a 'backup' txt file, in case user desires to return to a previous library look
void backupBeforeChange(musicLibrary*& library, int songCount) {
    ofstream backup("backup_library.txt");

    if (!backup.is_open()) {
        cout << "Error: Could not create backup file." << endl;
        return;
    }
    for (int i = 0; i < songCount; i++) {
        backup << library[i].song << endl;
        backup << library[i].artist << endl;
        backup << fixed << setprecision(2) << library[i].minutes << endl;
    }

    backup.close();

}
// Restore library from backup_library.txt
// Restore library from backup_library.txt and backup current library
void restoreLibrary(musicLibrary*& library, int& songCount) {

    ifstream backupFile("backup_library.txt");

    if (!backupFile.is_open()) {
        cout << "Error: Could not open backup file." << endl;
        return;
    }

    musicLibrary* backupLibrary = new musicLibrary[MAX_SIZE];
    int backupCount = 0;

    while (backupCount < MAX_SIZE && getline(backupFile, backupLibrary[backupCount].song)) {
        getline(backupFile, backupLibrary[backupCount].artist);

        string minutesStr;
        getline(backupFile, minutesStr);
        backupLibrary[backupCount].minutes = stod(minutesStr);

        backupCount++;
    }

    backupFile.close();

    delete[] library;
    library = backupLibrary;
    songCount = backupCount;

    // Write restored backup into main library file
    ofstream libFile("music_library.txt");

    for (int i = 0; i < songCount; i++) {
        libFile << library[i].song << endl;
        libFile << library[i].artist << endl;
        libFile << fixed << setprecision(2) << library[i].minutes << endl;
    }

    libFile.close();

    cout << "\n[Library successfully restored from backup]\n";
}

//VALID INPUT HADNLING ---------------------------------------------------------
int getValidInt(string prompt, int minVal, int maxVal) { //makes sure inputs with an int choice are correct, including cases where characters or symbols are added
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < minVal || value > maxVal) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number between "
                << minVal << " and " << maxVal << endl;
        }
        else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}