#ifndef  EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H

typedef struct BusLine {
    int line_number, distance, duration;
} BusLine;

/** The bubble sort function sorts the BusLine struct by the distance, From
 * the lowest to the biggest using the Bubble sort algorithm. */
void bubble_sort (BusLine *start, BusLine *end);

/** The quick sort function sorts the BusLine struct by the duration, From
 * the lowest to the bigger using the quick sort algorithm.*/
void quick_sort (BusLine *start, BusLine *end);

/** The partition function is a helper function the quick sort.
 It takes the last BusLine of the array as a pivot and  partition it
 according to it. Put on "right" of the partition all the BusLines whose
 duration is lower than the pivot's and to the "left" the BusLines
 which duration is bigger than the pivot's and in the end return the pivot.
 */
BusLine *partition (BusLine *start, BusLine *end);

#endif