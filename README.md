# ESE224 Library Management System
C++ Library Management System - ESE224 Fall 2020 Course Project
<br><br>
**Many of the features of this system and the way they were implemented were requirements decided by our instructors. For example, the 'availability' attribute of 'Copy' 
 and the 'Count'/'Index' attribute of 'Book' were required as per stated in the document. Although this data is useless and merely takes up more RAM, it was NOT our decision to implement this.**
 <br><br>
 **However, the `Database` class was my full design**

## Members:
 - Albert Bregonia
 - Xiangfeng Lin
 - Anthony Felicetta
 
 # Architecture and Functionality
 This simple pseudo-library management system is built upon the foundation of the `Database` class.
 This class provides many functions to allow for a developer to easily search for data within the database using a specific token.
 Many of the functions work by searching for the desired item given a token and returning the index in the database upon being found. If the item is not found, -1 is returned.
 This database class also allows for better sync within the text files and users as data does not have to be replicated in the user's data. As much of the data stored in the user
 would merely reference object in the database, system updates occurs automatically for all users.
 
 Using this database class allows for a high grade of scalability as it elimates much of the need for excessive `for-loops` and searching. Thus, allowing code to become more concise and new features are easily implementable.
 
 ### *This repository should serve as a time capsule of my skill in C++ as of 12/2020
 
 # Storage Format
 Upon initialization, the system loads into RAM the data saved in the following text files:
 - `admin.txt` - Contains the different admins accounts Stored in the format:
   - Username
   - Password
 - `book.txt` - Contains the different types of books. Stored in the format:
   - ISBN
   - Title
   - Author
   - Category
   - Unique Index
   - Count
   - Rating (Favor)
- `copy.txt` - Contains information about each copy of a book. Stored in the format:
   - Unique ID
   - ISBN
   - Current Borrower - *'none' if empty*
   - List of Reservors - Stored as usernames; *'none' empty*
   - Availability - Simple Boolean
   - Borrow Date - *-1 if empty*
   - List of Reservation Dates - *'none' if empty*
   - Expiration Date
- `student.txt` - Contains the different student accounts. Stored in the format:
   - Username
   - Password
   - Max Term
   - Max Number of Books Able to Borrow
   - List of Borrowed Books - Stored by Copy ID; *-1 if empty*
   - Number of Penalties
   - List of Reserved Books - Stored by Copy ID; *-1 if empty*
- `teacher.txt` - Contains the different teacher acocunts. Stored in the same format as the students.

Upon utilizing the `Database::save()` function, all data present in the database vectors are written out to these text files in this format.
