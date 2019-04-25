#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#include "cities_NodeStructs.h"
#include "cities_ListFuncs.h"



    
    

void printCity(city *C) {
    
	setlocale(LC_NUMERIC, "en_US");

	printf("City: %s\n", C->data->name);
    printf("Country: %s\n", C->data->country);
    /*printf("Latitude: %lf | ", C->data->lat);
    printf("Longitude: %lf\n", C->data->lon);
    */

	double latCoord = C->data->lat;
	double lonCoord = C->data->lon;

	char lat_direction;
	if (latCoord > 0) {
		lat_direction = 'N';
	} else {
		lat_direction = 'S';
		latCoord = fabs(latCoord);
	}

	char lon_direction;
	if (lonCoord > 0) {
		lon_direction = 'E';
	} else {
		lon_direction = 'W';
		lonCoord = fabs(lonCoord);
	}
	printf("Coordinates: %lf %c, %lf %c\n", latCoord, lat_direction, lonCoord, lon_direction);
	printf("Population: %'lu\n", C->data->pop);
    printf("Avg. Air Pollution (PM2.5): %d\n", C->data->air);
    printf("%s", "\n");
    
}

void printCityToFile(city *C, FILE *ofp) {
    
	setlocale(LC_NUMERIC, "en_US");

	fprintf(ofp, "%s, %s\n", C->data->name, C->data->country);

	double latCoord = C->data->lat;
	double lonCoord = C->data->lon;

	char lat_direction;
	if (latCoord > 0) {
		lat_direction = 'N';
	} else {
		lat_direction = 'S';
		latCoord = fabs(latCoord);
	}

	char lon_direction;
	if (lonCoord > 0) {
		lon_direction = 'E';
	} else {
		lon_direction = 'W';
		lonCoord = fabs(lonCoord);
	}
	fprintf(ofp, "Coordinates: %lf %c, %lf %c\n", latCoord, lat_direction, lonCoord, lon_direction);
	fprintf(ofp, "Population: %'lu\n", C->data->pop);
    fprintf(ofp, "Avg. Air Pollution (PM2.5): %d\n", C->data->air);
    fprintf(ofp, "%s", "\n");
    
}

void printCityList(city *C) {
    
    int count = 1;
    while (C != NULL) {
        
        printf("%3d. %s, %s", count, C->data->name, C->data->country);
        C = C->next;
        printf("%s", "\n");
        count++;
    }
    
}

void printCityList_3col(city *C) {
    
    int count = 1;
    while (C != NULL) {
        
        printf("%3d. %-20s", count, C->data->name);
        C = C->next;
        
        if (count % 3 == 0) {
            printf("%s", "\n");
        }
        count++;
    }
    
    if (--count % 3 != 0) { //add line break if not divisible by 3
        printf("%s", "\n");
    }
    printf("%s", "\n"); //add line break if list is over
}




void printListByPopulation(city *C, int numToPrint) {

	setlocale(LC_NUMERIC, "en_US");
    
    printf("%s\n", "                City Name | Population");
    printf("%s\n", "     ------------------------------------------");
    
    int i = 0;
    for (i = 0; i < numToPrint; ++i) {
        printf("%3d. %20s | ", i+1, C->data->name);
        printf("%'lu\n", C->data->pop);
        C = C->next;

    }
    
    printf("%s", "\n");
    
    
}

void printListByAirQuality(city *C, int numToPrint) {
    
    printf("%s\n", "                City Name | Air Pollution");
    printf("%s\n", "     --------------------------------------------");
    
    int i = 0;
    for (i = 0; i < numToPrint; ++i) {
        printf("%3d. %20s | ", i+1, C->data->name);
        printf("%d\n", C->data->air);
        C = C->next;

    }
    
    printf("%s", "\n");
    
}

void printItinerary(city *C) {
    printf("%s\n", "-------------------------------------------------------");
    printf("%s", "Your tentative itinerary\n");
    printf("%s\n", "-------------------------------------------------------");
    printCityList(C);
    printf("%s\n", "-------------------------------------------------------");
    printf("%s", "\n");
}



void printItineraryToFile(city *C, FILE *ofp) {
   
   	city *i = NULL;
	city *j = NULL;
   
   	fprintf(ofp, "-------------------------------------------------\n");
    fprintf(ofp, "Your Itinerary\n");
    fprintf(ofp, "-------------------------------------------------\n");
   

    int count = 1;
    i = C;

	while (i != NULL) {
        
        
        fprintf(ofp, "%3d. %s, %s\n", count, i->data->name, i->data->country);
        i = i->next;
        count++;
    }

	i = C;
    
	fprintf(ofp, "\n\n");
   	fprintf(ofp, "-------------------------------------------------\n");
    fprintf(ofp, "City Stats\n");
    fprintf(ofp, "-------------------------------------------------\n");
	
	while (i != NULL) {
		printCityToFile(i, ofp);
		i = i->next;
	}


}

