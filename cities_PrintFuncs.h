#ifndef CITIES_PRINTFUNCS_H
#define CITIES_PRINTFUNCS_H




void printCity(city *C);
void printCityToFile(city *C, FILE *ofp);
void printCityList(city *C);
void printCityList_3col(city *C);
void printListByPopulation(city *C, int numToPrint);
void printListByAirQuality(city *C, int numToPrint);
void printItinerary(city *C);
void printItineraryToFile(city *C, FILE *ofp);



#endif
