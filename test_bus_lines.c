#include "test_bus_lines.h"

int is_sorted_by_distance(BusLine *start, BusLine *end) {
  for (BusLine *curr = start; curr < end - 1; curr++) {
    if (curr->distance > (curr + 1)->distance) {
      return 0;
    }
  }
  return 1;
}

int is_sorted_by_duration(BusLine *start, BusLine *end) {
  for (BusLine *curr = start; curr < end - 1; curr++) {
    if (curr->duration > (curr + 1)->duration) {
      return 0;
    }
  }
  return 1;
}

int is_equal(BusLine *sorted_start, BusLine *sorted_end, BusLine *original_start, BusLine *original_end) {
  int num_lines_sorted = sorted_end - sorted_start;
  int num_lines_original = original_end - original_start;

  if (num_lines_sorted != num_lines_original) {
    return 0;
  }

  for (BusLine *orig = original_start; orig < original_end; orig++) {
    int found = 0;
    for (BusLine *sorted = sorted_start; sorted < sorted_end; sorted++) {
      if (orig->line_number == sorted->line_number &&
          orig->distance == sorted->distance &&
          orig->duration == sorted->duration) {
        found = 1;
        break;
      }
    }
    if (!found) {
      return 0;
    }
  }

