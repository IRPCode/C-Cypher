#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//prevents conflicting types errors
char* cypher(char *fileContents, int key);
char* getFile(char *filePath);
char* writeFile(char *fileContents);

int main()
{
    bool trueFalse = false; //declare variables
    int stringLength;
    const char *fileName;
    char *filePath;
    char *fileContents;
    int key = 0;

    printf("Enter the name of the file you would like to encrypt.\n"); //get and print file name
    printf("NOTE: File must be formatted as a file path (such as C:\\Users\\USEREXAMPLE\\Downloads\\UserDatabase.txt).\n");

    fileName = "C:\\Users\\USEREXAMPLE\\Downloads\\example.txt"; //Change this when running code on your machine
    printf("%s\n", fileName);

    while(trueFalse == false){
        printf("Enter any number between 0 and 10\n");
        scanf("%d", &key);
            if (key > 0 && key < 10){
                trueFalse = true;
            }
            else{
                printf("ERROR: Number out of range.");
            }
    }

    stringLength = strlen(fileName);
    filePath = (char*)malloc((stringLength + 1) * sizeof(char));
    filePath[strlen(filePath)] = '\0';
    strcpy(filePath, fileName);

    fileContents = getFile(filePath);
    fileContents = cypher(fileContents, key);
    free(filePath);
}

char* cypher(char *fileContents, int key){ //cyphers and de-cyphers file
    printf("TESTING FILE CONTENTS: %s\n",fileContents);

    const char arrayASCII[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";

    int x = 0;
    int y = 0;

    while (fileContents[x] != NULL){
        y = 0;
            while (arrayASCII[y] != NULL){
                if (fileContents[x] == arrayASCII[y]){
                    fileContents[x] = arrayASCII[abs((y + key) % strlen(arrayASCII))];
                    break;
                }
                y++;
            }
        x++;
    }

    printf("Key: %d\n", key);
    printf("Cyphered file content: %s\n", fileContents);

    x = 0;

    writeFile(fileContents);

    //decypher contents in file to prove it worked.

    while (fileContents[x] != '\0'){
        y = 0;
            while (arrayASCII[y] != NULL){
                if (fileContents[x] == arrayASCII[y]){
                    fileContents[x] = arrayASCII[abs((y - key) % strlen(arrayASCII))];
                    break;
                }
                y++;
            }
        x++;
    }
        printf("Decyphered file content: %s\n", fileContents);
        return;
}

char* getFile(char *filePath){ //Section finds the path of the file
    char buffer[255];
    char *fileContents = NULL;
    size_t totalSize = 0;

    FILE *file = fopen(filePath, "r");

    if(file == NULL){
        printf("ERROR: File couldn't be written to. Check the directory you are writing to, and allow program through anti-virus protections.\n");
        fclose(file);
        free(fileContents);
        exit(1); //safely exit file
    }
    else{
        while(fgets(buffer, 255, file) != NULL){
            size_t bufferSize = strlen(buffer);
            fileContents = (char*)realloc(fileContents, totalSize + bufferSize + 1);
            strcpy(fileContents + totalSize, buffer);
            totalSize += bufferSize;
            if (strlen(fileContents) > 255){
                printf("ERROR: File is longer than 255 characters. This is to prevent allocation overflows.");
                fclose(file);
                free(fileContents);
                exit(1); //safely exit file
            }
        }
    }
    fclose(file);
    return fileContents;
}

char* writeFile(char *fileContents){ //takes file content and writes to another file

    FILE *file = fopen("C:\\Users\\USEREXAMPLE\\Downloads\\cyphered.txt", "w"); //change this location if you want it somewhere else

    if (file == NULL){
        printf("ERROR: File couldn't be written to. Check the directory you are writing to, and allow program through anti-virus protections.\n");
        fclose(file);
        free(fileContents);
        exit(1); //safely exit file
    }
    else{
        fputs(fileContents, file);
        fclose(file);
        printf("Check your downloads folder for the file.\n");
    }
    return fileContents;
}
