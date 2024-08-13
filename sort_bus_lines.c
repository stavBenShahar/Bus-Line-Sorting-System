#include "sort_bus_lines.h"

void swap(BusLine *a, BusLine *b) {
  BusLine temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(BusLine *start, BusLine *end) {
  for (BusLine *i = start; i < end - 1; i++) {
    int swapped = 0;
    for (BusLine *j = start; j < end - 1 - (i - start); j++) {
      if (j->distance > (j + 1)->distance) {
        swap(j, j + 1);
        swapped = 1;
      }
    }
    if (!swapped) break;
  }
}

void quick_sort(BusLine *start, BusLine *end) {
  if (start < end - 1) {
    BusLine *pivot = partition(start, end);
    quick_sort(start, pivot);
    quick_sort(pivot + 1, end);
  }
}

BusLine *partition(BusLine *start, BusLine *end) {
  BusLine *pivot = end - 1;
  BusLine *i = start - 1;

  for (BusLine *j = start; j < pivot; j++) {
    if (j->duration <= pivot->duration) {
      i++;
      swap(i, j);
    }
  }
  swap(i + 1, pivot);
  return i + 1;
}
