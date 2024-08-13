#define EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**This test checks that the struct was sorted by distance correctly
 * using a for loop to go over each object and compare it to the
 * one after him*/
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**This test checks that the struct was sorted by duration correctly
 * using a for loop to go over each object and compare it to the
 * one after him*/
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**This test check that during the sorting functions no new objects were
 * added to the struct and both structs are still the same their
 * only difference is the way they are sorted */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
