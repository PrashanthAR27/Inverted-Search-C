# Inverted Search in C

## Overview

Inverted Search is a C-based project that implements an **inverted index** to efficiently store and search words across multiple text files.

The project uses **hashing and linked lists** to organize the database and supports creating, displaying, searching, saving, restoring, and updating the inverted database.

## Features

* Validate input `.txt` files
* Detect duplicate, empty, invalid, and unavailable files
* Create an inverted search database
* Search for a word and display:

  * Number of files containing the word
  * File names
  * Word occurrence count in each file
* Display the complete database
* Save the database into a backup file
* Restore the database from a backup file
* Update the database with new files
* Prevent duplicate files during update
* Use a traditional `Makefile` for compilation

## Data Structures

### 1. Hash Table

A hash table of **27 buckets** is used.

```text
arr[27]

0 - 25  →  alphabetic words (a-z)
26      →  words beginning with non-alphabetic characters
```

The index is calculated using the first character of the word.

### 2. Main Node

Each main node stores:

* Word
* Number of files containing the word
* Link to the next word
* Link to the file information nodes

```text
mnode
 ├── word
 ├── fileCount
 ├── mlink
 └── slink
```

### 3. Sub Node

Each sub node stores:

* File name
* Number of occurrences of the word in that file
* Link to the next file

```text
snode
 ├── fileName
 ├── wordCount
 └── link
```

## Database Structure

The overall database is organized like:

```text
Hash Table
    |
    +-- Bucket 0
    |      |
    |      +-- Word → File information
    |
    +-- Bucket 1
    |
    +-- ...
    |
    +-- Bucket 26
           |
           +-- @hello
           |      |
           |      +-- file2.txt → count
           |
           +-- #example
```

## Working

### Create Database

The program reads each input text file and extracts words using file handling functions.

For every word:

1. Calculate the hash index using its first character.
2. Check whether the bucket is empty.
3. If the word does not exist, create a new main node.
4. If the word already exists, check whether the current file is already associated with it.
5. If the file is new, create a sub node and increment the file count.
6. If the file already contains the word, increment its word count.

### Search

When a user enters a word:

```text
Input word
    ↓
Calculate hash index
    ↓
Access corresponding bucket
    ↓
Traverse main-node linked list
    ↓
Compare word
    ↓
Traverse sub-node list
    ↓
Display files and occurrence counts
```

### Save

The database can be stored in a backup text file so that the indexed information can be restored later without recreating the database from the original files.

### Restore

The saved database can be read from the backup file and reconstructed in memory using the same main-node and sub-node structures.

### Update

After restoring a database, new files can be added and indexed without recreating the complete database.

Duplicate files are rejected during the update operation.

## Project Modules

| File              | Responsibility                               |
| ----------------- | -------------------------------------------- |
| `main.c`          | Menu and overall program control             |
| `createDB.c`      | Database creation and node generation        |
| `display.c`       | Display inverted database                    |
| `search.c`        | Search words in the database                 |
| `save.c`          | Save database to backup file                 |
| `restore.c`       | Restore database from backup file            |
| `update.c`        | Add and index new files                      |
| `slist.c`         | File list operations                         |
| `validateFiles.c` | Input file validation                        |
| `inverted.h`      | Structures, macros and function declarations |
| `Makefile`        | Compilation and linking                      |

## File Validation

The project performs validations such as:

* Input file extension validation
* File existence validation
* Empty file validation
* Duplicate file validation
* Backup file validation during restore
* Database state validation before operations
* Prevention of restoring into a non-empty database
* Prevention of creating the database repeatedly
* Controlled update after database restoration

## Build and Run

### Using Makefile

Compile the complete project:

```bash
make
```

Run the application:

```bash
./a.out file1.txt file2.txt
```

Example:

```bash
./a.out file1.txt file2.txt file3.txt
```

### Manual Compilation

The project can also be compiled using GCC:

```bash
gcc *.c
```

Then:

```bash
./a.out file1.txt file2.txt
```

## Menu

```text
1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database
6. Restore Database
7. Exit
```

## Technologies Used

* **Language:** C
* **Compiler:** GCC
* **Operating Environment:** Linux / WSL
* **Build System:** GNU Make
* **Data Structures:** Hash Table, Linked Lists
* **Concepts:** Pointers, Dynamic Memory Allocation, Structures, File Handling, String Handling

## Key Learning

This project provided practical experience with:

* Hashing and indexing
* Linked-list based data organization
* Dynamic memory allocation
* Pointer manipulation
* File handling
* Searching and traversal
* Data persistence using backup files
* Input validation
* Modular C programming
* Multi-file compilation
* Object files and linking
* Traditional Makefile usage
* Debugging segmentation faults and memory-related issues

## Author

**Prashanth AR**

Embedded Systems / C Programming Project
