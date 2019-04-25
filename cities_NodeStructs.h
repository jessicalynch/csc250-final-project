#ifndef CITIES_NODESTRUCTS_H
#define CITIES_NODESTRUCTS_H

#define MAX_NAME_LENGTH 100


typedef struct city_stats_struct {
    
    char *name; //city name
    double lat; //latitude
    double lon; //longitude
    char *country; //country name
    unsigned long pop; //population
    int air; //air pollution
    
} city_stats;


typedef struct city_struct {
    
    struct city_stats_struct *data;
    struct city_struct *next; //next pointer
    
} city;



#endif
