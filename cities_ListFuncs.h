#ifndef CITIES_LISTFUNCS_H
#define CITIES_LISTFUNCS_H



city *makeCity(char *name, double lat, double lon, char *country, unsigned long pop, int air);
city_stats *makeCityStats(char *name, double lat, double lon, char *country, unsigned long pop);
city *makeCityNode(city_stats *stats);
city *insertFront(city *head, city *new);
city *insertTail(city *head, city *new);
city *makeListFromFile(FILE *ifp, city *list);
city *makeUserCityList(city *list);
void sortListByPopulation(city *list, int ascOrDesc);
void sortListByName(city *list, int ascOrDesc);
void sortListByAirQuality(city *list, int ascOrDesc);
double calcDistance(city *A, city *B);
city *getCityByName(city *list, char *name);
city *getCityByNum(city *list, int num);
int getListLength(city *list);
int inList(city *list, char *name);
city *deleteCityNode(city *list, char *name);
city *findBestAirCity(city *head);
city *findWorstAirCity(city *head);
void selSortAirQuality_BestToWorst(city *list);
void selSortAirQuality_WorstToBest(city *list);

#endif
