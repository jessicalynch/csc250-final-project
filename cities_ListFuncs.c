#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cities_NodeStructs.h"
#include "cities_PrintFuncs.h"


city_stats *makeCityStats(char *name, double lat, double lon, char *country, unsigned long pop, int air) {
    
    city_stats *stats = NULL;
    stats = malloc(sizeof(city_stats));
    
    
    stats->name = name;
    stats->lat = lat;
    stats->lon = lon;
    stats->country = country;
    stats->pop = pop;
	stats->air = air;    
    
    return stats;
    
}



city *makeCityNode(city_stats *stats) {
    
    city *new = NULL;
    city_stats *data = NULL;
    
    new = malloc(sizeof(city));
    data = malloc(sizeof(city_stats));
    
    new->data = stats; //add city_stats struct
	new->next = NULL;
    
    return new;
    
}

city *insertFront(city *head, city *new) {
    
    new->next = head;
    return new;
    
}


city *makeListFromFile(FILE *ifp, city *list) { //build a linked list with data from file
    
    
    int numCities = 0;
    fscanf(ifp, "%d", &numCities);
    
    char buf[2];
    fscanf(ifp, "%c", buf); //read newline char on first line
    
    int i = 0;
    for (i = 0; i < numCities; ++i) {
        
        char tmpName[MAX_NAME_LENGTH+1];
        char *tmpNamePtr = NULL;
        
        char tmpCountry[MAX_NAME_LENGTH+1];
        char *tmpCountryPtr = NULL;
        
        double tmpLat;
        double tmpLon;
        unsigned long tmpPop;
        int tmpAir;
        
        
        //get city name
        fgets(tmpName, MAX_NAME_LENGTH, ifp);
        tmpName[strlen(tmpName)-1] = '\0'; //remove newline char
        tmpNamePtr = malloc(sizeof(char) * (strlen(tmpName) + 1) );
        strcpy(tmpNamePtr, tmpName);
        
        //get country name
        fgets(tmpCountry, MAX_NAME_LENGTH, ifp);
        tmpCountry[strlen(tmpCountry)-1] = '\0'; //remove newline char
        tmpCountryPtr = malloc(sizeof(char) * (strlen(tmpCountry) + 1));
        strcpy(tmpCountryPtr, tmpCountry);
        
        //get latitude and longitude
        fscanf(ifp, "%lf", &tmpLat);
        fscanf(ifp, "%lf", &tmpLon);
        
        //get population
        fscanf(ifp, "%lu", &tmpPop);
        
        //get population
        fscanf(ifp, "%d", &tmpAir);
        
        fgets(buf, 2, ifp);
        //fscanf(ifp, "%c", buf); //read newline char
        
       	city_stats *tmp_stats = NULL;
		tmp_stats = makeCityStats(tmpNamePtr, tmpLat, tmpLon, tmpCountryPtr, tmpPop, tmpAir);
        
		city *tmp = NULL;
        tmp = makeCityNode(tmp_stats);

        list = insertFront(list, tmp);
    }
    
    return list;
}



//returns city node from name
city *getCityByName(city *list, char *name) {
    city *tmp = NULL;
    tmp = list;
    
    while (tmp != NULL) {
        if (strcmp(tmp->data->name, name) == 0){
            break;
        }
        tmp = tmp->next;
    }
    
    return tmp;
}

//returns city node from position in list
city *getCityByNum(city *list, int num) {
    city *tmp = NULL;
    tmp = list;
    
    int count = 1;
    while (tmp != NULL) {
        if (count == num) {
            break;
        }
        tmp = tmp->next;
        count++;
    }
    
    return tmp;
}

double calcDistance(city *A, city *B) {
    
    const double pi = acos(-1);
    //printf("%lf", pi);
    const int radiusOfEarth = 3963; //miles
    double distance = 0;
    
    
    double A_lat = A->data->lat*(pi/180); //convert from degrees to radians
    double A_lon = A->data->lon*(pi/180);
    
    double B_lat = B->data->lat*(pi/180);
    double B_lon = B->data->lon*(pi/180);
    
    
    double latDif = fabs(B_lat - A_lat);
    double lonDif = fabs(B_lon - A_lon);
    
    double haversine = 0;
    haversine = pow(sin(latDif / 2), 2) +  cos(A_lat) * cos(B_lat) *  pow(sin(lonDif / 2), 2);
    haversine = 2 * asin(sqrt(haversine));
    distance = haversine * radiusOfEarth;
    
    return distance;
}


void sortListByPopulation(city *list, int ascOrDesc) {
    
    city *i, *j;
    city_stats *tmp_data = NULL;
    
    for (i = list; i->next != NULL; i = i->next) {
        
        for (j = i->next; j != NULL; j = j->next) {
            
            if (ascOrDesc > 0) {
                //sort highest to lowest
                if ( i->data->pop < j->data->pop ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                    
                }
   
   			} else {
                //sort lowest to highest
                if ( i->data->pop > j->data->pop ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                    
                }
            }
           

        }
    }
}


void sortListByName(city *list, int ascOrDesc) {
    
    city *i, *j;
    city_stats *tmp_data = NULL;
    
    for (i = list; i->next != NULL; i = i->next) {
        
        for (j = i->next; j != NULL; j = j->next) {
            
            if (ascOrDesc > 0) {
                //sort A to Z
                if ( strcmp(i->data->name, j->data->name) > 0 ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                }

            } else {
                //sort Z to A
                if ( strcmp(i->data->name, j->data->name) < 0 ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                    
                }
		    }
       
	   }
    }
}








void sortListByAirQuality(city *list, int ascOrDesc) {
    
    city *i, *j;
    city_stats *tmp_data = NULL;
    
    for (i = list; i->next != NULL; i = i->next) {
        
        for (j = i->next; j != NULL; j = j->next) {
            
            if (ascOrDesc > 0) {
                //sort high to low
                if ( i->data->air > j->data->air) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                }

            } else {
                //sort low to high
                if ( i->data->air < j->data->air) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                    
                }
		    }
       
	   }
    }
}



city *findBestAirCity(city *head) {

	city *i;
	city *minNode = head;
	int minAirVal = minNode->data->air;

	for (i = head; i != NULL; i = i->next) {
		if (i->data->air < minAirVal) {
			minAirVal = i->data->air;
			minNode = i;
		}

	}

	return minNode;
}


city *findWorstAirCity(city *head) {

	city *i;
	city *maxNode = head;
	int maxAirVal = maxNode->data->air;

	for (i = head; i != NULL; i = i->next) {
		if (i->data->air > maxAirVal) {
			maxAirVal = i->data->air;
			maxNode = i;
		}

	}

	return maxNode;
}

void selSortAirQuality_BestToWorst(city *list) {
	city *min_node = NULL;
	city *temp = NULL;
	city_stats *stats_temp = NULL;
	
	for (temp = list; temp != NULL; temp = temp->next) {

		min_node = findBestAirCity(temp);
	
		stats_temp = temp->data;
		temp->data = min_node->data;
		min_node->data = stats_temp;

	}


}
void selSortAirQuality_WorstToBest(city *list) {
	city *max_node = NULL;
	city *temp = NULL;
	city_stats *stats_temp = NULL;

	for (temp = list; temp != NULL; temp = temp->next) {

		max_node = findWorstAirCity(temp);

		stats_temp = temp->data;
		temp->data = max_node->data;
		max_node->data = stats_temp;

	}


}


int getListLength(city *list){
    
    int count = 0;
    city *tmp = NULL;
    tmp = list;
    
    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    
    return count;
}


int inList(city *list, char *name) {
    
    city *tmp = list;
    int found = 0;
    
    while (tmp != NULL) {
        
        if (strcmp(tmp->data->name, name) == 0) {
            found = 1;
        }
        
        tmp = tmp->next;
    }
    
    return found;
    
}


city *deleteCityNode(city *list, char *name) {
    
    
    city *tmp = list;
    city *buf = NULL;
    
    if (tmp != NULL) {
        
        if ( strcmp(tmp->data->name, name) == 0) {
            list = tmp->next;
            free(tmp);
            tmp = NULL;
        } else {
            while (tmp->next != NULL) {
                if ( strcmp(tmp->next->data->name, name) == 0) {
                    buf = tmp->next->next;
                    free(tmp->next);
                    tmp->next = NULL;
                    tmp->next = buf;
                    break;
                }
                
                tmp = tmp->next;
            }
            
        }
        
        
    }
    
    return list;
}



city *makeUserCityList(city *list) {
    
    
    
    printf("\nWhich cities would you like to visit?\n");
    
    city *wishlist = NULL;
    
    int userCity = 1;
    int numCities = 0;
    numCities = getListLength(list);
    
    while (userCity !=0)  {
        
        if (userCity > numCities){
            printf(">>> ERROR: there are only %d cities in the list\n\n", numCities);
        } else if (userCity < 0) {
            printf(">>> ERROR: number must be positive\n\n");
        }
        printf("Enter a number  between between 1 and %d (0 to stop): ", numCities);
        
        userCity = -99999; //set to -1 to validate whether new number is received
        char str[100];
        fgets(str, 100, stdin);
        sscanf(str, "%d", &userCity);
        
        if (userCity >= 1 && userCity <= numCities) { //valid number was received
            city *tmp = NULL;
            city *tmp2 = NULL;
            tmp = getCityByNum(list, userCity);
            
            //check if it's already in wishlist
            int inListCheck = 0;
            inListCheck = inList(wishlist, tmp->data->name);
            
            if(!inListCheck){
                tmp2 = makeCityNode(tmp->data);
                wishlist = insertFront(wishlist, tmp2);
                printf("(+) %s, %s has been added to your itinerary\n\n", wishlist->data->name, wishlist->data->country);
            } else {
                char str2[4];
                char deleteFromItin;
                printf(">>> ERROR: %s, %s is already in your itinerary\n\n", tmp->data->name, tmp->data->country);
                printf("Would you like to remove it? (y/n): ");
                fgets(str2, 4, stdin);
                sscanf(str2, "%c", &deleteFromItin);
                
                deleteFromItin = tolower(deleteFromItin); //convert user character to lowercase
                
                if (deleteFromItin == 121) { //if user enters "y" (yes to deleting city)
                    wishlist = deleteCityNode(wishlist, tmp->data->name);
                    printf("(-) %s, %s has been removed from your itinerary\n\n", tmp->data->name, tmp->data->country);
                    
                } else {
                    printf("%s", "\n");
                }
                
            }
            
        } else if (userCity == -99999) { //number was not received
            printf(">>> ERROR: choice must be a number\n\n");
            userCity = 1;
        }
        
        
    }
    
    printf("%s", "\n"); //print new line after user stops input
    
    
    return wishlist;
    
}



