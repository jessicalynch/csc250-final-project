#include <stdio.h>
#include <stdlib.h>
#include "cities_NodeStructs.h"
#include "cities_ListFuncs.h"
#include "cities_MenuFuncs.h"


//* Main Menu

int getMainMenuChoice() {
    
    int userChoice = 0; //initilaize userChoice to 0
    char mainStr[50]; //temporary character array to hold the user's input
    int validChoice = 0; //initialize validation variable
    
    //print a menu of choices for user
    
    printf("%s", "\nMain Menu\n");
    printf("%s", "************************\n");
    
    printf("%s", "1. View all cities\n");
    printf("%s", "2. Make/edit an itinerary\n");
    printf("%s", "3. Calculate distance between two cities\n");
    printf("%s", "4. Quit\n\n");
    
    while (!validChoice) {
        printf("%s", "What would you like to do?  ");
        fgets(mainStr, 50, stdin); //char array to hold user's input, num to read (includes null char), input stream
        sscanf(mainStr, "%d", &userChoice); //read an integer from user's input
        
        if (userChoice < 1 || userChoice > MAIN_MENU_LENGTH){ //display a message if user input is not in range
           printf("\n>>> ERROR: Choose an option between 1 and %d.\n\n", MAIN_MENU_LENGTH);
        } else {
            validChoice = 1; //declare user's choice valid and end the while loop
        }
        
    }
    return userChoice;
}


//* Itinerary Menu

int getItinMenuChoice() {
    
    int userChoice = 0; //initilaize userChoice to 0
    char tempStr[50]; //temporary character array to hold the user's input
    int validChoice = 0; //initialize validation variable
    
    //print a menu of choices for user
    
    printf("%s", " Itinerary Options\n");
    printf("%s", "*************************\n");
    printf("%s", "1. Return to main menu \n");
    printf("%s", "2. Display cities alphabetically (A to Z)\n");
    printf("%s", "3. Display cities alphabetically (Z to A)\n");
    printf("%s", "4. Display cities by population (High to Low)\n");
    printf("%s", "5. Display cities by population (Low to High)\n");
    printf("%s", "6. Display cities by air quality (Best to Worst)\n");
    printf("%s", "7. Display cities by air quality (Worst to Best)\n");
    printf("%s", "8. Add city to itinerary\n");
    printf("%s", "9. Delete city from itinerary\n");
    printf("%s", "10. Save current itinerary to file\n\n");
    
    printf("%s", "What would you like to do?  ");
    while (!validChoice) {
        fgets(tempStr, 50, stdin); //char array to hold user's input, num to read (includes null char), input stream
        sscanf(tempStr, "%d", &userChoice); //read an integer from user's input
        
        if (userChoice < 1 || userChoice > ITIN_MENU_LENGTH){ //display a message if user input is not in range
            printf("\n>>> ERROR: Choose an option between 1 and %d.\n", ITIN_MENU_LENGTH);
        } else {
            validChoice = 1; //declare user's choice valid and end the while loop
        }
        
    }
    return userChoice;
}




