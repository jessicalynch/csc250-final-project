# CSC250 Final Proejct: Trip planner with city data

**cities.c**

## Description
The program does various operations with an included data set of cities around the world with an emphasis on the following items:

- [ ] Header Files (Multiple C Files)
- [ ] Command Line Arguments
- [ ] Structures
- [ ] Linked Lists (Pointers) 
- [ ] Sorting
- [ ] File I/O

## Compiling the program
Multiple **header files** are required when compiling the program:

- `cities_NodeStructs.h`
- `cities_MenuFuncs.h`
- `cities_ListFuncs.h`
- `cities_PrintFuncs.h`

In addition to the main `cities.c` file, the following `.c` files must be included in the compliation command:

- `cities_MenuFuncs.c`
- `cities_ListFuncs.c`
- `cities_PrintFuncs.c`

**Example compliation command:**
```
gcc cities.c cities_ListFuncs.c cities_PrintFuncs.c cities_MenuFuncs.c
```
***Note:*** *`-lm` must also be added when compiling on dsunix server.*

## How to Use
The program must always be passed a data set of city information **(File I/O)** with the following command:

```
<exec> <filename.txt> [city_name] [city_name]
```

The text file must have the following format:

```
1st line: Number of cities in the set
2nd line: City name
3rd line: Country name
4th line: Latitude coordinate
5th line: Longitude coordinate
6th line: Population
7th line: Average air pollution (PM2.5)

Lines 2-7 should repeat for as many items as specified in line 1
```

The program will create a **linked list** of **structure pointers** with the following function:

```c
city *makeListFromFile(FILE *ifp, city *list) { //build a linked list with data from file
```
 The `city *node` structure is used for the **linked lists**:

```c
typedef struct city_struct {
    
    struct city_stats_struct *data;
    struct city_struct *next; //next pointer
    
} city;
```

It contains a nested `data` structure, `city_stats *data`:
```c
typedef struct city_stats_struct {
    
    char *name; //city name
    double lat; //latitude
    double lon; //longitude
    char *country; //country name
    unsigned long pop; //population
    int air; //air pollution
    
} city_stats;

```

### **Quick Use Mode (Command Line Arguments)**
---
If **command line arguments** are provided, the program will complete one of the following two tasks:

1. Show stats on a single city (one city name is provided)
2. Calculate the distance between two cities (two citiy names provided)

If a `single city name` is provided, the program will show stats on the city.

**Example command:**
```
./a.out city_data_100.txt "New York"
```
**Output:**

```
City: New York
Country: United States
Coordinates: 40.712784 N, 74.005941 W
Population: 18,593,220
Avg. Air Pollution (PM2.5): 7
```

If the city name is not found in the included data set, an error message will be displayed:

```
./a.out city_data_100.txt Beijin

>>> ERROR: "Beijin" was not found in the included data set.
```


However, the city will be returned regardless of the case of the input string:

```
./a.out city_data_100.txt sEoUl

City: Seoul
Country: South Korea
Coordinates: 37.566535 N, 126.977969 E
Population: 9,773,746
Avg. Air Pollution (PM2.5): 26
```


If `two city names` are provided, the program display the distance between the two cities.

**Example command:**
```
./a.out city_data_100.txt Seoul Beijing
```
**Output:**

```
>>> Distance between Seoul and Beijing: 592.38 miles
```

### **Standard mode**
---

If `no city names` are provided, a menu of options will be displayed: 
```
./a.out city_data_100.txt

Main Menu
************************
1. View all cities
2. Make/edit an itinerary
3. Calculate distance between two cities
4. Quit

What would you like to do?
```

Error checking has been added to ensure a legitimate menu selection: 

```
What would you like to do?  6

>>> ERROR: Choose an option between 1 and 4.
```

Selecting `menu option 2` will display a 3-column list of all cities in the data set and allow you to build a custom **linked list** of cities you'd like to visit: 

```
Which cities would you like to visit?
Enter a number  between between 1 and 100 (0 to stop): 95
(+) Washington D.C., United States has been added to your itinerary

Enter a number  between between 1 and 100 (0 to stop): 72
(+) Paris, France has been added to your itinerary

Enter a number  between between 1 and 100 (0 to stop): 93
(+) Tokyo, Japan has been added to your itinerary
```
Input error checking has been added:

```
Enter a number  between between 1 and 100 (0 to stop): 200
>>> ERROR: there are only 100 cities in the list

Enter a number  between between 1 and 100 (0 to stop): sdg8
>>> ERROR: choice must be a number

Enter a number  between between 1 and 100 (0 to stop): -235
>>> ERROR: number must be positive

Enter a number  between between 1 and 100 (0 to stop): 72
>>> ERROR: Paris, France is already in your itinerary

Would you like to remove it? (y/n): y
(-) Paris, France has been removed from your itinerary
```

The function that builds the initial master linked list from the provided data set makes use of the `insertFront()` function.

The function that creates the custom user linked list makes use of the `insertTail()` function.

```c
//adds node to front of linked list
city *insertFront(city *head, city *new) {
    new->next = head;
    return new;
}

//adds node to end of linked list
city *insertTail(city *head, city *new) {
    
    city *tmp = NULL;
    tmp = head;
    
    if (head == NULL) { //if list is empty
        head = new;
    } else if (head != NULL && head->next == NULL) { //if list contains one node
        head->next = new;
    } else { //if list contains more than one node
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    return head;
   
}
```



When you stop entry by typing a `0`, your list is displayed with a menu of options:

```
Enter a number  between between 1 and 100 (0 to stop): 0

-------------------------------------------------------
Your tentative itinerary
-------------------------------------------------------
  1. Bangkok, Thailand
  2. Dallas, United States
  3. Singapore, Singapore
  4. Tokyo, Japan
  5. Mexico City, Mexico
  6. Toronto, Canada
  7. Montreal, Canada
  8. Ho Chi Minh City, Vietnam
  9. Hong Kong, Hong Kong
 10. Istanbul, Turkey
 11. Bogota, Colombia
-------------------------------------------------------

 Itinerary Options
*************************
1. Return to main menu
2. Display cities alphabetically (A to Z)
3. Display cities alphabetically (Z to A)
4. Display cities by population (High to Low)
5. Display cities by population (Low to High)
6. Display cities by air quality (Best to Worst)
7. Display cities by air quality (Worst to Best)
8. Add city to itinerary
9. Delete city from itinerary
10. Save current itinerary to file
11. Delete entire itinerary

What would you like to do?
```

Selecting `options 2 thru 8` will **sort** the list accordingly and print the updated list. 

The program uses a **bubble sort**, as well as a **selection sort**:

### Bubble Sort
```c
void sortListByPopulation(city *list, int ascOrDesc) {
    
    city *i, *j;
    city_stats *tmp_data = NULL;
    
    for (i = list; i->next != NULL; i = i->next) {
        
        for (j = i->next; j != NULL; j = j->next) {
            
            if (ascOrDesc > 0) { //sort highest to lowest

                if ( i->data->pop < j->data->pop ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                }
   
            } else { //sort lowest to highest

                if ( i->data->pop > j->data->pop ) {
                    tmp_data = i->data;
                    i->data = j->data;
                    j->data = tmp_data;
                }
            }
           

        }
    }
}

```
**Sample Output:**
```
               City Name | Population
     ------------------------------------------
  1.                Tokyo | 38,001,000
  2.          Mexico City | 20,998,543
  3.             Istanbul | 14,163,989
  4.               Bogota | 9,764,769
  5.              Bangkok | 9,269,823
  6.            Hong Kong | 7,313,557
  7.     Ho Chi Minh City | 7,297,780
  8.              Toronto | 5,992,739
  9.               Dallas | 5,702,641
 10.            Singapore | 5,618,866
 11.             Montreal | 3,980,708
```

### Selection Sort
The first function finds the minimum value:
```c
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
```
The second function performs the selection sort:
```c
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
```
**Sample output:**
```
                City Name | Air Pollution
     --------------------------------------------
  1.               Dallas | 8
  2.             Montreal | 8
  3.              Toronto | 9
  4.               Bogota | 13
  5.             Istanbul | 15
  6.                Tokyo | 17
  7.            Singapore | 18
  8.          Mexico City | 22
  9.            Hong Kong | 23
 10.              Bangkok | 28
 11.     Ho Chi Minh City | 42
```


```
 Itinerary Options
*************************
1. Return to main menu
2. Display cities alphabetically (A to Z)
3. Display cities alphabetically (Z to A)
4. Display cities by population (High to Low)
5. Display cities by population (Low to High)
6. Display cities by air quality (Best to Worst)
7. Display cities by air quality (Worst to Best)
8. Add city to itinerary
9. Delete city from itinerary
10. Save current itinerary to file
11. Delete entire itinerary

What would you like to do?
```
### Modifying linked list
Selecting `option 8 or 9` will allow you to **add** or **delete** nodes from your **linked list**.

When you **add** a node via `option 8`, the program will only show cities that are not already in your linked list *(all cities in the master data set that are not already in your custom linked list*).

If you've added all cities in the master list and select `option 8`, you will receive this error message:

```
>>> Sorry, there are no more cities to add.
```

If you **delete** *all* nodes from your list via `option 9`, or delete your entire list with `option 11`, the program will return you to the main menu:

```
>>> Your itinerary is empty.

Returning to main menu...
```
### File Output
Selecting `option 10` will output a `.txt` file to your disk. The program makes use of `time()` to create a unique filename and outputs data **(File I/O)** with the following functions:

```c
void printItineraryToFile(city *C, FILE *ofp);
void printCityStatsToFile(city *C, FILE *ofp);
```
The data printed by the function includes:

1. Your current linked list
2. Stats on all cities in your list

**Example output file:**
```
-------------------------------------------------
Your Itinerary
-------------------------------------------------
  1. Washington D.C., United States
  2. Atlanta, United States
  3. Ankara, Turkey
  4. Alexandria, Egypt
  5. Abidjan, Cote d'Ivoire


-------------------------------------------------
City Stats
-------------------------------------------------
Washington D.C., United States
Coordinates: 38.907192 N, 77.036871 W
Population: 4,955,139
Avg. Air Pollution (PM2.5): 9

Atlanta, United States
Coordinates: 33.748995 N, 84.387982 W
Population: 5,142,140
Avg. Air Pollution (PM2.5): 11

Ankara, Turkey
Coordinates: 39.933363 N, 32.859742 E
Population: 4,749,968
Avg. Air Pollution (PM2.5): 19

Alexandria, Egypt
Coordinates: 31.200092 N, 29.918739 E
Population: 4,777,677
Avg. Air Pollution (PM2.5): 30

Abidjan, Cote d'Ivoire
Coordinates: 5.359952 N, 4.008256 W
Population: 4,859,798
Avg. Air Pollution (PM2.5): 37
```

## Information on included data sets

The following files are included with the program:

* `city_data_100.txt`
* `city_data_10.txt`

The first consists of the world's 100 most populated cities, and the second is the top 10.

### Population data
Population data comes from [an article on worldatlas.com](https://www.worldatlas.com/citypops.htm), which cites the United Nations[World's Cities Data Booklet](http://www.un.org/en/development/desa/population/publications/pdf/urbanization/the_worlds_cities_in_2016_data_booklet.pdf) as its source.

Population numberes include surrounding metropolitan area.

### Air quality data
The air quality number represents the **average annual PM<sub>2.5</sub> particles** *(concentration of fine particle matter less than 2.5 microns in diameter)*.

Most of the the air pollution data comes from [a database](https://www.who.int/airpollution/data/aap_air_quality_database_2018_v14.xlsx?ua=1) downloaded from [the World Health Organization's website](https://www.who.int/airpollution/data/cities/en/). However, there was not PM<sub>2.5</sub> data for all 100 most populated cities, so the set was supplemented with data from [Plume Labs](https://air.plumelabs.com/).



---
<sub>*All code written by @jessiicalynch for Spring 2019 CSC-250 Final*</sub>
