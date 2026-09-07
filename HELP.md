# Line Editor Help

## Start the Editor

Compile:

gcc line_editor.c -o editor

Run:

.\editor.exe

---

## Commands

### 1. Insert

Adds a new line at the specified line number.

Syntax:

insert <line> <text>

Example:

insert 1 Hello World

---

### 2. Delete

Deletes the specified line.

Syntax:

delete <line>

Example:

delete 2

---

### 3. Display

Displays all lines with their line numbers.

Syntax:

display

Example:

display

---

### 4. Search

Searches the document for a word or phrase.

Syntax:

search <word or phrase>

Example:

search programming

The search is case-insensitive.

---

### 5. Replace

Replaces text in the document.

Syntax:

replace <old> <new>

Example:

replace programming coding

---

### 6. Save

Saves the current document to a text file.

Syntax:

save <filename>

Example:

save notes.txt

---

### 7. Load

Loads a document from a text file.

Syntax:

load <filename>

Example:

load notes.txt

---

### 8. Help

Displays all available commands.

Syntax:

help

---

### 9. Exit

Closes the editor.

Syntax:

exit