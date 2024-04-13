#include <stdio.h>
#include <stdlib.h>

#include "bloomfilter.h"

int main(){

    // check filter
    // if position set go to local storage
        // bloomFilterCheckString -- True
        // write into text file

    // else set positions
        // bloomFilterSetString

    bloomFilter *filter = bloomFilterNewDefault(1024);
    int choice;
    char query[100];
    FILE *filePointer;

    do{

        printf("1.Search\n2.Exit\n---> ");
        scanf("%d", &choice);
        // printf("Check String:%d", bloomFilterCheckString(filter, "Sakshi")); // This is giving 0
        getchar();

        switch(choice){
            case 1:
                printf("Enter query---> ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = '\0'; // remove newline character

                // printf("Check String:%d", bloomFilterCheckString(filter, query));
                // printf("%s\n", query);

                if(bloomFilterCheckString(filter, query)){

                    filePointer = fopen("data.txt", "a");

                    if (filePointer == NULL) {
                        printf("Unable to open file.\n");
                        return 1;
                    }
                    fprintf(filePointer, "%s\n", query);
                    fclose(filePointer);
                }
                else{
                    bloomFilterSetString(filter, query);
                    // printf("%d\n", bloomFilterCheckString(filter, query));
                }
                break;

            case 2:
                printf("Exiting...");

        }

    }while(choice != 2);
    return 0;

}