#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_INPUT 60
#define MIN_DURATION 10
#define MAX_DURATION 100
#define MAX_DISTANCE 1000
#define MAX_LINE_NUMBER 999
#define ZERO 0

#define ARG_ERROR_MSG "USAGE: Too many arguments, expected only 1!\n"
#define COMMAND_ERROR_MSG "USAGE: Invalid argument name!\n"
#define NUM_LINES_ERROR_MSG "ERROR: Number of lines needs to be positive.\n"
#define BUS_NUM_ERROR_MSG "ERROR: Bus number should be between 1-999!\n"
#define DISTANCE_ERROR_MSG "ERROR: Distance should be an integer between 0-1000\n"
#define DURATION_ERROR_MSG "ERROR: Duration should be an integer between 10-100.\n"
#define NUMBER_LINES_MSG "Enter the number of lines: "
#define LINES_INFO_MSG "Enter line info (bus number,distance,duration): "

enum { VALID_ARGS = 2, CMD_INDEX = 1 };
enum { BUS_NUM_INDEX = 0, DISTANCE_INDEX = 1, DURATION_INDEX = 2 };

int validate_command(int argc, char *argv[]);
int get_number_of_lines();
void get_all_lines_info(int num_lines, BusLine *lines);
void get_bus_info(int bus_info[]);
int validate_bus_info(const int bus_info[]);
int handle_command(char *argv[], int num_lines);
int handle_test_command(int num_lines);
int start_tests(BusLine *start, BusLine *end, int num_lines);
int execute_sort(char *argv[], int num_lines);
void run_bubble_test(BusLine *sorted, BusLine *original, int num_lines);
void run_quick_test(BusLine *sorted, BusLine *original, int num_lines);
void print_results(BusLine *start, BusLine *end);

int main(int argc, char *argv[]) {
  if (validate_command(argc, argv) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  int num_lines = get_number_of_lines();
  if (num_lines <= 0) {
    fprintf(stdout, "%s", NUM_LINES_ERROR_MSG);
    return EXIT_FAILURE;
  }

  if (handle_command(argv, num_lines) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int validate_command(int argc, char *argv[]) {
  if (argc != VALID_ARGS) {
    fprintf(stdout, "%s", ARG_ERROR_MSG);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[CMD_INDEX], "test") != 0 &&
      strcmp(argv[CMD_INDEX], "bubble") != 0 &&
      strcmp(argv[CMD_INDEX], "quick") != 0) {
    fprintf(stdout, "%s", COMMAND_ERROR_MSG);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int get_number_of_lines() {
  char input[MAX_USER_INPUT];
  fprintf(stdout, "%s", NUMBER_LINES_MSG);
  fgets(input, MAX_USER_INPUT, stdin);

  int num_lines;
  sscanf(input, "%d", &num_lines);
  return num_lines;
}

void get_all_lines_info(int num_lines, BusLine *lines) {
  for (int i = 0; i < num_lines; i++) {
    int bus_info[3];
    get_bus_info(bus_info);

    if (validate_bus_info(bus_info) == EXIT_SUCCESS) {
      lines[i].line_number = bus_info[BUS_NUM_INDEX];
      lines[i].distance = bus_info[DISTANCE_INDEX];
      lines[i].duration = bus_info[DURATION_INDEX];
    } else {
      i--; // Invalid input, ask again
    }
  }
}

void get_bus_info(int bus_info[]) {
  fprintf(stdout, "%s", LINES_INFO_MSG);
  char input[MAX_USER_INPUT];
  fgets(input, MAX_USER_INPUT, stdin);
  sscanf(input, "%d,%d,%d", &bus_info[BUS_NUM_INDEX], &bus_info[DISTANCE_INDEX], &bus_info[DURATION_INDEX]);
}

int validate_bus_info(const int bus_info[]) {
  if (bus_info[BUS_NUM_INDEX] <= 0 || bus_info[BUS_NUM_INDEX] > MAX_LINE_NUMBER) {
    fprintf(stdout, "%s", BUS_NUM_ERROR_MSG);
    return EXIT_FAILURE;
  }
  if (bus_info[DISTANCE_INDEX] < 0 || bus_info[DISTANCE_INDEX] > MAX_DISTANCE) {
    fprintf(stdout, "%s", DISTANCE_ERROR_MSG);
    return EXIT_FAILURE;
  }
  if (bus_info[DURATION_INDEX] < MIN_DURATION || bus_info[DURATION_INDEX] > MAX_DURATION) {
    fprintf(stdout, "%s", DURATION_ERROR_MSG);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int handle_command(char *argv[], int num_lines) {
  if (strcmp(argv[CMD_INDEX], "test") == 0) {
    return handle_test_command(num_lines);
  } else {
    return execute_sort(argv, num_lines);
  }
}

int handle_test_command(int num_lines) {
  BusLine *lines = malloc(sizeof(BusLine) * num_lines);
  if (!lines) {
    return EXIT_FAILURE;
  }

  get_all_lines_info(num_lines, lines);
  BusLine *end = lines + num_lines;

  int result = start_tests(lines, end, num_lines);

  free(lines);
  return result;
}

int start_tests(BusLine *start, BusLine *end, int num_lines) {
  BusLine *original = malloc(sizeof(BusLine) * num_lines);
  if (!original) {
    return EXIT_FAILURE;
  }

  memcpy(original, start, sizeof(BusLine) * num_lines);

  run_bubble_test(start, original, num_lines);
  memcpy(start, original, sizeof(BusLine) * num_lines);
  run_quick_test(start, original, num_lines);

  free(original);
  return EXIT_SUCCESS;
}

int execute_sort(char *argv[], int num_lines) {
  BusLine *lines = malloc(sizeof(BusLine) * num_lines);
  if (!lines) {
    return EXIT_FAILURE;
  }

  get_all_lines_info(num_lines, lines);
  BusLine *end = lines + num_lines;

  if (strcmp(argv[CMD_INDEX], "bubble") == 0) {
    bubble_sort(lines, end);
  } else {
    quick_sort(lines, end);
  }

  print_results(lines, end);
  free(lines);
  return EXIT_SUCCESS;
}

void run_bubble_test(BusLine *sorted, BusLine *original, int num_lines) {
  bubble_sort(sorted, sorted + num_lines);

  if (is_sorted_by_distance(sorted, sorted + num_lines)) {
    fprintf(stdout, "TEST 1 PASSED: Sorted by distance!\n");
  } else {
    fprintf(stdout, "TEST 1 FAILED: Not sorted!\n");
  }

  if (is_equal(sorted, sorted + num_lines, original, original + num_lines)) {
    fprintf(stdout, "TEST 2 PASSED: The array is the same!\n");
  } else {
    fprintf(stdout, "TEST 2 FAILED: The array isn't the same!\n");
  }
}

void run_quick_test(BusLine *sorted, BusLine *original, int num_lines) {
  quick_sort(sorted, sorted + num_lines);

  if (is_sorted_by_duration(sorted, sorted + num_lines)) {
    fprintf(stdout, "TEST 3 PASSED: Sorted by duration!\n");
  } else {
    fprintf(stdout, "TEST 3 FAILED: Not sorted!\n");
  }

  if (is_equal(sorted, sorted + num_lines, original, original + num_lines)) {
    fprintf(stdout, "TEST 4 PASSED: The array is the same!\n");
  } else {
    fprintf(stdout, "TEST 4 FAILED: The array isn't the same!\n");
  }
}

void print_results(BusLine *start, BusLine *end) {
  for (BusLine *curr = start; curr < end; curr++) {
    fprintf(stdout, "%d,%d,%d\n", curr->line_number, curr->distance, curr->duration);
  }
}
