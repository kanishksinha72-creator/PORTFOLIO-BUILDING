#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100

char *lines[MAX_LINES];
int lineCount = 0;

void insertLine(int lineNumber, char *text)
{
    if (lineNumber < 1 || lineNumber > lineCount + 1)
    {
        printf("Invalid line number.\n");
        return;
    }

    if (lineCount >= MAX_LINES)
    {
        printf("Document is full.\n");
        return;
    }

    for (int i = lineCount; i >= lineNumber; i--)
    {
        lines[i] = lines[i - 1];
    }

    lines[lineNumber - 1] = malloc(strlen(text) + 1);
    strcpy(lines[lineNumber - 1], text);

    lineCount++;

    printf("Line inserted successfully.\n");
}

void displayDocument()
{
    if (lineCount == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}

void deleteLine(int lineNumber)
{
    if (lineCount == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Invalid line number.\n");
        return;
    }

    free(lines[lineNumber - 1]);

    for (int i = lineNumber - 1; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lineCount--;

    printf("Line deleted successfully.\n");
}

void showHelp()
{
    printf("\n===== LINE EDITOR COMMANDS =====\n");
    printf("insert <line> <text>  - Insert a new line\n");
    printf("delete <line>         - Delete a line\n");
    printf("display               - Display the document\n");
    printf("replace <old> <new>   - Find and replace text\n");
    printf("search <word/phrase>  - Search the document\n");
    printf("help                  - Show available commands\n");
    printf("save <filename>       - Save the document to a file\n");
    printf("load <filename>       - Load a document from a file\n");
    printf("exit                  - Exit the editor\n");
    printf("================================\n");
}

void saveFile(char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("Document saved successfully.\n");
}

void loadFile(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return;
    }

    // Free the current document
    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }

    lineCount = 0;

    char buffer[500];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (lineCount >= MAX_LINES)
        {
            printf("Maximum line limit reached.\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        lines[lineCount] = malloc(strlen(buffer) + 1);
        strcpy(lines[lineCount], buffer);

        lineCount++;
    }

    fclose(file);

    printf("Document loaded successfully.\n");
}

void searchDocument(char *query)
{
    int found = 0;

    for (int i = 0; i < lineCount; i++)
    {
        char lineCopy[500];

        strcpy(lineCopy, lines[i]);

        for (int j = 0; lineCopy[j] != '\0'; j++)
        {
            if (lineCopy[j] >= 'A' && lineCopy[j] <= 'Z')
            {
                lineCopy[j] = lineCopy[j] + 32;
            }
        }

        char queryCopy[500];

        strcpy(queryCopy, query);

        for (int j = 0; queryCopy[j] != '\0'; j++)
        {
            if (queryCopy[j] >= 'A' && queryCopy[j] <= 'Z')
            {
                queryCopy[j] = queryCopy[j] + 32;
            }
        }

        if (strstr(lineCopy, queryCopy) != NULL)
        {
            printf("Found \"%s\" on line %d.\n", query, i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\"%s\" not found in document.\n", query);
    }
}

void replaceText(char *oldText, char *newText)
{
    int found = 0;

    for (int i = 0; i < lineCount; i++)
    {
        char *position = strstr(lines[i], oldText);

        if (position != NULL)
        {
            int oldLength = strlen(oldText);
            int newLength = strlen(newText);
            int currentLength = strlen(lines[i]);

            if (newLength > oldLength)
            {
                char *newLine = malloc(currentLength + newLength - oldLength + 1);

                strcpy(newLine, lines[i]);

                position = strstr(newLine, oldText);

                memmove(
                    position + newLength,
                    position + oldLength,
                    strlen(position + oldLength) + 1
                );

                memcpy(position, newText, newLength);

                free(lines[i]);
                lines[i] = newLine;
            }
            else
            {
                memmove(
                    position + newLength,
                    position + oldLength,
                    strlen(position + oldLength) + 1
                );

                memcpy(position, newText, newLength);
            }

            printf("Replaced on line %d.\n", i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\"%s\" not found in document.\n", oldText);
    }
}

void freeDocument()
{
    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }

    lineCount = 0;
}

int main()
{
    char text[500];
    char input[500];
    char filename[100];
    int lineNumber;

    printf("=== SIMPLE LINE EDITOR ===\n");
    printf("Type 'help' for commands.\n");

    while (1)
    {
        printf("\neditor> ");

        fgets(input, sizeof(input), stdin);

        if (strncmp(input, "insert", 6) == 0)
{
    if (sscanf(input, "insert %d %[^\n]", &lineNumber, text) == 2)
    {
        insertLine(lineNumber, text);
    }
    else
    {
        printf("Usage: insert <line> <text>\n");
    }
}
        else if (strncmp(input, "delete", 6) == 0)
        {
            if (sscanf(input, "delete %d", &lineNumber) == 1)
            {
                deleteLine(lineNumber);
            }
            else
            {
                printf("Usage: delete <line>\n");
            }
        }
        else if (strncmp(input, "display", 7) == 0)
        {
            displayDocument();
        }

        else if (strncmp(input, "search", 6) == 0)
{
    if (sscanf(input, "search %[^\n]", text) == 1)
    {
        searchDocument(text);
    }
    else
    {
        printf("Usage: search <word or phrase>\n");
    }
}
else if (strncmp(input, "replace", 7) == 0)
{
    char oldText[100];
    char newText[100];

    if (sscanf(input, "replace %99s %99s", oldText, newText) == 2)
    {
        replaceText(oldText, newText);
    }
    else
    {
        printf("Usage: replace <old> <new>\n");
    }
}

        else if (strncmp(input, "help", 4) == 0)
        {
        showHelp();
        }

        else if (strncmp(input, "save", 4) == 0)
{
    if (sscanf(input, "save %99s", filename) == 1)
    {
        saveFile(filename);
    }
    else
    {
        printf("Usage: save <filename>\n");
    }
}
else if (strncmp(input, "load", 4) == 0)
{
    if (sscanf(input, "load %99s", filename) == 1)
    {
        loadFile(filename);
    }
    else
    {
        printf("Usage: load <filename>\n");
    }
}
        else if (strncmp(input, "exit", 4) == 0)
        {
            printf("Exiting editor...\n");
            break;
        }
        else
        {
            printf("Unknown command. Type 'help'.\n");
        }
    }

    freeDocument();

    return 0;
}