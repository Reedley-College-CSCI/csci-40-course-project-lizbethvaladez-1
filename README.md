[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7mdzU3H2)
# CS1 Final Project - Music_Library



## 1. Overview
- What problem does your project solve?  
- Briefly describe the purpose and key features of your program.  
This program solves the problem or organizing and managing a peronsal
music collection. Users can store, organize, search, and modify their music
library with persitent storage between sessions. There is a menu option to view 
the library, edit the library(add, remove, and/or edit songs), view library
statistics, and sort the library(by song name, artist, or duration). There 
are also validation functions that handle erros as well as an automatic backup
system that occurs before changes.


---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why?  
- Why did you choose to structure your data using structs?  
- How did you implement searching and sorting? What algorithms did you use and why?  
- How do you ensure data persistence between program runs?  
- Did you consider alternative approaches? If so, why did you not use them?  
---
1. I chose to use structs and dynamic arrays (musicLibrary) for easier handling of
    data and dynamic memory to store the library. I also used differenet functions
    to perform parts of the program as well as Files to save to. I chose them because
    it kept the data logicly grouped and sorted.
2. I chose structs because it was easier to group parts of a song into an array and was
    easier for passing data in the array and to a file. It was also easier to manahe the memory
3. I implemented searching and sorting through using case sensitive linear search that could math
    partial strings. I converted both search terms and library terms to lower. Using a linear
    search was simplier to implement and made searching user firendly. I used a bubble sort with nested
    loops to offer a straightforwaed implementation as it was only used for ascending and descending options.
4.I ensured data persitence betweem program runs through the use of file storage that was read from
     as well as saved to. I also added a backup for extra security with the file. I also made sure
    I also made sure to format it all the same so it could easily read.
5.I considered using classes to have the struct and funtions in, but I decided against due to
    limited time for implentation.
---

## 3. Testing Summary
- **Structured Testing Log:** Include a table with test cases, expected output, actual output, and pass/fail status.  
- What testing methods did you use?  
- Provide examples of test inputs (valid and invalid) and describe how your program responds.  
---        
1. My first testing method was manual tests I did with different inputs, checking to see how the program reacted
   and how the files would save.  I also tested the boundaries of my programs, like when there was an empty library
   or max capacity. I also used error handling tests and used that to fix it. Lastly I made sure to test the files 
   of my program, including music_library.txt and backup_library.txt
2. An example: When the menu starts and prompts for an int option, I put in a character. Normally 
    it cause the program to glitch and begin to loop, but after implementing error handling it now
    outputs invalid option.

| Test Case                | Input/Scenario                                   | Expected Output                                      | Actual Output                                         | Pass/Fail |
|--------------------------|--------------------------------------------------|------------------------------------------------------|-------------------------------------------------------|-----------|
| File Reading             | Empty music_library.txt                          | "Library is empty"                                   | "Library is empty" displayed                          | Pass      |
| File Writing - Add       | Add song with special characters in name         | Song saved correctly in file                         | File contains exact input with special chars          | Pass      |
| File Writing - Remove    | Remove song, check file updated                  | File has one less entry, format preserved            | File correctly rewritten with remaining songs         | Pass      |
| Backup System            | Edit library with backup_library.txt existing    | Old library saved, new changes applied               | backup_library.txt contains pre-edit state            | Pass      |
| Backup System            | Restore from empty backup file                   | "Backup file is empty" message                       | Correct error message displayed                       | Pass      |
| File Format              | Add song with 3 decimal places in minutes        | Rounded to 2 decimals in file                        | File shows 2 decimal precision                        | Pass      |
| Large Dataset            | Add 100 songs (MAX_SIZE)                         | "Max songs library can load" message                 | Program handles limit correctly                       | Pass      |
| Data Persistence         | Close program, reopen, check library             | All songs preserved from previous session            | Library loads identical to saved state                | Pass      |
| Sort & File Write        | Sort library, check file order                   | File reflects sorted order                           | music_library.txt matches sorted array                | Pass      |
| Edit & Save              | Edit song, verify file update                    | File contains edited information                     | Changes written to file correctly                     | Pass      |
---

## 4. Technical Walkthrough
- Explain the main functionality of your program.  
- **Include a link to your required video demonstration** showcasing how the project works (**3-7 minutes**). 
    Make sure it shareable without approval needed.
    # YouTube Link: 
---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?  
- What key lessons did you learn about programming and problem-solving?  
1. A trouble in the beginning was making sure everything saved to the file correctly as well as when it was read.
    Even with the backup file, I had to make sure it worked how it was supposed to when it was. Another personal challenege
    was trying to implement functions of searching and the input validations. Looking at past labs helped.
2. A key lesson I learned was to always try and give yourself enough time to implement then test something. It is easier
    to fix a function the same time it was created. I also learned that testing code as I went along rather
1. than trying to code the program in one day and test it at once was easier and a safer bet. It is like
    the approach in the lab that cycled through the protocols of building a program.
---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?  
If I had more time, I would try to move my functions to a seperate file and just link them as a header. I would also
want to make the functions into a class to manage it easier. In the future I would also like to increase the support size
and add the ability to create and delete playlists from the main library. In the future too, I could think about adding the
genre of the song or an album field. With more time, I would also like to add a way to detect
if there are duplicate songs in the function. In the end I am mostly happy with how my project
turned out, but there are for sure a lot I could add to it to improve and add more features.