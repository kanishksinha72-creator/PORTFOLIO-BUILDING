# Simple Line Editor in C

## Team Members

- Name 1
- Name 2
- Name 3

## Project Description

Simple Line Editor is a command-line text editor written in C.

It allows the user to create, view, modify, search, and save a small
text document directly from the terminal.

## Data Structure

The editor uses an array of character pointers:

    char *lines[MAX_LINES];

Each element stores one line of text.

The variable `lineCount` keeps track of the number of lines currently
stored in the document.

### Why an Array?

An array was chosen because:

- It provides simple access to individual lines.
- It is easy to display the document.
- It makes the implementation straightforward.
- It is suitable for a small text editor.

The main disadvantage is that inserting and deleting lines requires
shifting existing elements.

## Features Implemented

### Core Features

- Insert a line
- Delete a line
- Display the document
- Save the document to a `.txt` file
- Load the document from a `.txt` file

### Bonus Features

- Search
- Find and Replace
- Help command
- Line and word count

### Robustness

The editor handles:

- Empty documents
- Invalid line numbers
- Invalid commands
- Invalid command syntax
- File errors
- Memory cleanup

## Commands

    insert <line> <text>
    delete <line>
    display
    search <word or phrase>
    replace <old> <new>
    save <filename>
    load <filename>
    help
    exit

## Example

    editor> insert 1 Hello World
    Line inserted successfully.

    editor> insert 2 C Programming
    Line inserted successfully.

    editor> display

    ----- DOCUMENT -----
    1. Hello World
    2. C Programming
    --------------------

    editor> search programming
    Found "programming" on line 2.

    editor> save notes.txt
    Document saved successfully.

    editor> exit

## Compilation

Compile using GCC:

    gcc line_editor.c -o editor

## Running

On Windows:

    .\editor.exe

## Files

- `line_editor.c` - Main C source code
- `HELP.md` - Command documentation
- `README.md` - Project documentation
- `notes.txt` - Optional sample saved document

## Project Goal

The project was developed as a command-line line editor for the
3rd Semester Coding Competition.