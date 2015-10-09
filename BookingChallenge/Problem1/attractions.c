#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*#define DEBUG*/
/*
Problem Statement

Destinations often have lots of attractions or landmarks that travelers want to visit – usually more than they
can visit during their stay. What most travelers end up doing is optimizing their time by only visiting the
attractions that are closest to where they’re staying.

Travelers ask you to help them to arrange holiday, so they can visit as many attractions as possible. Your task
is to calculate the time it takes from the hotel to the attractions by preferred transport for the given amount
of time. transport can be only be one of the followings: foot, bike or metro.

Notes:

You should consider the following average speed for the different transport options: metro, 20km/h; bike, 15km/h;
and foot, 5km/h For distances in the problem you should use the 'Law of Cosines for Spherical Trigonometry'.
Here how it is implemented as pseudo-code.

function distance_between(point1, point2) {
    var EARTH_RADIUS = 6371;//in km
    var point1_lat_in_radians  = degree2radians( point1.latitude );
    var point2_lat_in_radians  = degree2radians( point2.latitude );
    var point1_long_in_radians  = degree2radians( point1.longitude );
    var point2_long_in_radians  = degree2radians( point2.longitude );

    return acos( sin( point1_lat_in_radians ) * sin( point2_lat_in_radians ) +
                 cos( point1_lat_in_radians ) * cos( point2_lat_in_radians ) *
                 cos( point2_long_in_radians - point1_long_in_radians) ) * EARTH_RADIUS;
}

When calculating distance, always round it up or down to 2 decimal points precision. Example: 2.3467 should be
rounded to 2.35 while 3.4522 should be rounded to 3.45 All values of integer type should be considered as 4-bytes
integer.

Assume value of pi is 3.14159265359.

Input Format

The first line contains an integer N, which represents the number of attractions that follows. After that are N
lines each containing three space-separated numbers that represent the ID (integer), the latitude (double) and
the longitude (double) of the attraction.

After the attractions there will be another line containing an integer M, which represents the number of test
cases that follows. After that are M lines each containing four space-separated values – the first and second
are the latitude (double) and longitude (double) of the hotel the guest is staying at, the third value shows
their preferred transport option and the fourth represents how long they are willing to travel in minutes
starting from the hotel.

Output Format

The output is precisely M lines, each containing a list of space-separated attraction IDs. Each line represents
the attractions that are possible to reach from the guest’s hotel in the specified amount of time and using the
preferred transport option. In each line the attraction IDs should be sorted by distance starting with the
closest one. When two attractions are the same distance away, they should be sorted by ID.

M is no greater than 200. N is no greater than 200.
*/

#define EARTH_RADIUS 6371;    /* In kilometers */
#define PI  3.14159265359       /* Pi */
#define SPEED_BY_METRO  20  /* Km/hr */
#define SPEED_BY_BIKE   15  /* Km/hr */
#define SPEED_BY_FOOT   5   /* Km/hr */
#define MINUTES_PER_HOUR 60 /* Number of minutes in an hour */

/* Linked List structural element definition */
struct listElement {
    int id;                     /* Id of the attraction */
    double  distance;           /* Distance to the attraction */
    struct listElement *next;   /* Pointer to the next element in the list */
};

/* Allow the elements of the linked list to be referred to as nodes */
typedef struct listElement node;

/* Define the head as the top of the linked list, and initialize it as NULL */
node *head = NULL;

void displayNodes(); /* Function prototype */

/* add a new node to the sorted list of attractions by distance */
void addNode(int id, double distance) {

    /* Define some local variables */
    node    *current;   /* pointer to the current node */
    node    *previous;  /* Pointer to the previous node */
    node    *new;       /* Pointer to the node being added */

    /* Create our new node */
    new = (node *) malloc(sizeof(node));
    /* See if we were able to get memory for the node */
    if (new == NULL) {
        printf("Memory not available to create a new node.  Exiting\r\n");
        exit (EXIT_FAILURE);
    }

    /* Add the input parameters to the node */
    new->id = id;
    new->distance = distance;
    new->next = NULL;   /* Initialize it for now */

    /* See if our linked list is empty */
    if (head == NULL) {
        /* Put the new node at the head of the list */
        head = new;
        new->next = NULL;
        return;
    }

    /* See if the new node goes before the first node */
    if ((new->distance < head->distance) ||
            ((new->distance == head->distance) && (new->id < head->id)) ) {
        new->next = head;
        head = new;
        return;
    }

    /* Scan through the nodes in the linked list, to see if we can insert this node */
    current = head; /* Start at the head of the linked list */
    previous = NULL;    /* There is no previous node */
    /* Loop until there aren't any more nodes */
    while (current->next != NULL) {
        /* Is the next node past the new node? */
        if (new->distance < current->next->distance) {
            /* See if the new distance is between the current and the next node */
            if (new->distance > current->distance) {
                /* Insert the node in the linked list */
                new->next = current->next;
                current->next = new;
                return;
            } else { /* new->distance <= current->distance */
                /* This happens if the new node distance equals the current node distance */
                /* In this case, check the ids to see if we insert or append the node */
                if (new->id > current->id) { /* new->id > current->id */
                    /* Just insert it before the next id, and after the current one */
                    new->next = current->next;
                    current->next = new;
                    return;
                } else { /* new->id < current->id */
                    /* Insert the new element before the current element */
                    new->next = current;
                    previous->next = new;
                    return;
                }
            }

        } else { /* new->distance == current->next->distance */
            if (new->distance == current->next->distance) {
                /* See if we need to insert the new before the next, or keep scanning */
                if (new->id < current->next->id) {
                    /* distances are the same, ids are in order, go ahead and insert it */
                    new->next = current->next;
                    current->next = new;
                    return;
                } else {
                    /* If the distances are the same, and the new->id is > than the next id go to the next element */
                }
            }
        }

        /* If we havn't inserted the node, advance to the next node */
        previous = current;
        current = current->next;
    }

    /* If we scanned the whole list, without finding a place for the new node, insert it at the end */
    current->next = new;
    new->next = NULL;
    return;
};

/* Print out the nodes in the attractions linked list by distance */
void displayNodes() {
    /* Setup a linked list element pointer */
    node *elementPtr;

    /* Start at the head of the list */
    elementPtr = head;

    /* Loop while there are still more nodes */
    while (elementPtr) {
#ifdef DEBUG
        printf("DisplayNodes id=%d, distance=%.2lf\r\n",
            elementPtr->id, elementPtr->distance);
#else
        printf("%d ", elementPtr->id);
#endif
        /* Go to the next element in the linked list */
        elementPtr = elementPtr->next;
    }
#ifndef DEBUG
    printf("\r\n");
#endif
}

void clearNodes() {
    /* Setup a linked list element pointer */
    node *elementPtr;
    node *nextElementPtr;

    /* If there are no nodes, return */
    if (head == NULL) {
        return;
    }

    /* Start at the head of the list */
    elementPtr = head;

    /* Loop while there are still more nodes */
    while (elementPtr) {
        /* Save the next element pointer */
        nextElementPtr = elementPtr->next;

        /* Free the memory used by the node */
        free(elementPtr);

        /* Go to the next element in the linked list */
        elementPtr = nextElementPtr;
    }

    /* Set the head to NULL after all the nodes deleted */
    head = NULL;
}

typedef enum {
    METRO,
    BIKE,
    FOOT
} transportMode;

transportMode stringToEnumTransport(char * transport) {
    if (strcmp(transport, "metro") == 0) {
        return METRO;
    }
    if (strcmp(transport, "bike") == 0) {
        return BIKE;
    }
    if (strcmp(transport, "foot") == 0) {
        return FOOT;
    }
    return FOOT;
}

double minutesToAttraction(double distance, transportMode transport) {
    double result = 0;

    switch(transport) {
        case METRO:
            result = (distance/SPEED_BY_METRO) * MINUTES_PER_HOUR;
            break;
        case BIKE:
            result = (distance/SPEED_BY_BIKE) * MINUTES_PER_HOUR;
            break;
        case FOOT:
            result = (distance/SPEED_BY_FOOT) * MINUTES_PER_HOUR;
            break;
    }
    return result;
}

struct point {
    double latitude;    /* Latitude of the object */
    double longitude;   /* Longitude of the object */
};

/* Convert degrees to radians */
double degrees2radians(double degrees) {
  return (degrees * PI / 180);
}

/* Law of Cosines for Spherical Trigonometry */
double distance_between(struct point point1, struct point point2) {
    double point1_lat_in_radians = degrees2radians( point1.latitude );
    double point2_lat_in_radians = degrees2radians( point2.latitude );
    double point1_long_in_radians = degrees2radians( point1.longitude );
    double point2_long_in_radians = degrees2radians( point2.longitude );

    double result = acos(sin( point1_lat_in_radians ) * sin( point2_lat_in_radians ) +
                         cos( point1_lat_in_radians ) * cos( point2_lat_in_radians ) *
                         cos( point2_long_in_radians - point1_long_in_radians) ) * EARTH_RADIUS;

    /* Round to 2 decimal places */
    result = round(result * 100) / 100;
    return result;
};

/* Define the attraction structure */
struct attraction
{
    int id; /* Attraction ID */
    struct point position;  /* Position of the attraction */
};

int main() {
    int numAttractions; /* Number of attractions */
    int attractionCtr;  /* Counter for attractions */
    int numTestCases;   /* Number of test cases */
    struct point hotelPosition;  /* Input position of the hotel */
    char transport[10];     /* Input string containing the transport method */
    transportMode transMode;    /* transport mode as an Enum */
    int minutesFromHotel;  /* Input minutes the customer is willing to travel from the hotel */
    double distToAttraction;    /* Distance in Km to the attraction */
    double minToAttraction;    /* Minutes to the attraction */
    int testCaseCtr;        /* Counter for the test cases */

    /* Read the number of attractions */
     scanf("%d", &numAttractions);
#ifdef DEBUG
     printf("Attractions = %d\r\n", numAttractions);
#endif

     /* Declare an array to store the attractions */
     struct attraction attractions[numAttractions];

     /* Read the attractions into the attractions array */
     for (attractionCtr = 0; attractionCtr < numAttractions; attractionCtr++) {
         scanf("%d %lf %lf", &attractions[attractionCtr].id,
                             &attractions[attractionCtr].position.latitude,
                             &attractions[attractionCtr].position.longitude);
#ifdef DEBUG
         printf("main: Attraction id = %d, latitude = %lf, longitude = %lf\r\n",
             attractions[attractionCtr].id,
             attractions[attractionCtr].position.latitude,
             attractions[attractionCtr].position.longitude
         );
#endif
     }

     /* Read the number of Test Cases */
     scanf("%d", &numTestCases);
#ifdef DEBUG
     printf("TestCases = %d\r\n", numTestCases);
#endif

     /* Read the TestCases */
     for (testCaseCtr = 0; testCaseCtr < numTestCases; testCaseCtr++) {
          scanf("%lf %lf %s %d",
              &hotelPosition.latitude,
              &hotelPosition.longitude,
              &transport,
              &minutesFromHotel);
          transMode = stringToEnumTransport(transport);
#ifdef DEBUG
          printf("Hotel latitude = %lf, longitude = %lf, transport = '%s', minutes = %d\r\n",
              hotelPosition.latitude,
              hotelPosition.longitude,
              transport,
              minutesFromHotel
          );
#endif

        /* Clear out the nodes in the linked list */
        clearNodes();

        /* Loop through the attractions, and calculate the distance to the hotel */
        for (attractionCtr = 0; attractionCtr < numAttractions; attractionCtr++) {
            distToAttraction = distance_between(hotelPosition, attractions[attractionCtr].position);
            minToAttraction = minutesToAttraction(distToAttraction, transMode);
#ifdef DEBUG
            printf("main2: Attraction id=%d, distance=%.2lf, minutes=%.2lf\r\n", attractions[attractionCtr].id,
                    distToAttraction,
                    minToAttraction
                    );
#endif
            /* See if we are within range of this attraction */
            if (minToAttraction <= minutesFromHotel) {
                /* Add the attraction to the sorted by distance linked list of attractions */
                addNode(attractions[attractionCtr].id, distToAttraction);
            }
        }
        /* Print out the attractions in order of distance/id */
        displayNodes();
    }

    return 0;
}
