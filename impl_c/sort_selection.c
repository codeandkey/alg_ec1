/* Justin Stanley
 * Design and Analysis of Algorithms
 * Fall 2015
 * Extra Credit - C implementation of selection sort
 */

/*
 * To simplify implementation details, all implementations will read n 32-bit integers from a datafile named `input.dat`.
 * To simplify the C implementation, the program will be sorted functionally into separate parts.
 *
 * All of the file parsing and timer manipulation will be inlined into the `main` function, while the actual timed function `selection_sort` will be statically defined.
 * To see the actual implementation of the selection sort algorithm, see the function at the bottom of the file.
 * The algorithm is implemented to order a list from least to greatest value.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>

#define INPUT_FILE "input.dat"

void selection_sort(uint32_t* data, uint32_t size);

int main(int argc, char** argv) {
	uint32_t* active_list = NULL, active_list_size = 0; // active_list will be our input list.
	FILE* input_fd = fopen(INPUT_FILE, "rb");

	if (!input_fd) {
		fprintf(stderr, "Failed to open input file.\n");
		return 1;
	}

	// We use the C standard library to get the file size and bytes, and divide it into the list element size.

	fseek(input_fd, 0, SEEK_END);
	active_list_size = ftell(input_fd) / sizeof(*active_list);
	fseek(input_fd, 0, SEEK_SET);

	fprintf(stdout, "File [%s] contains %d elements.\n", INPUT_FILE, active_list_size);

	// We allocate and read the list from the file.

	active_list = malloc(active_list_size * sizeof(*active_list));

	if (!active_list) {
		fprintf(stderr, "Failed to allocate list memory.\n");
		return 1;
	}

	if (fread(active_list, sizeof(*active_list), active_list_size, input_fd) != active_list_size) {
		fprintf(stderr, "Failed to read information from file.\n");
		free(active_list);
		return 1;
	}

	fclose(input_fd);

	// The list is ready, we prepare the timer.
	// To get high-performance and high-resolution timings we will use the POSIX clock interface `clock_gettime()`

	struct timespec current_time = {0}, after_time = {0};

	if (clock_gettime(CLOCK_MONOTONIC, &current_time) < 0) {
		fprintf(stderr, "Failed to get POSIX clock information.\n");
		free(active_list);
		return 1;
	}

	// The timer is ready and counting.
	// We run the sort function.

	selection_sort(active_list, active_list_size);

	// The list is now sorted. We stop the timer.

	if (clock_gettime(CLOCK_MONOTONIC, &after_time) < 0) {
		fprintf(stderr, "Failed to get POSIX clock information.\n");
		free(active_list);
		return 1;
	}

	// To get the running time of the function, we grab the difference in nanoseconds and the difference in seconds.

	time_t dif_sec = after_time.tv_sec - current_time.tv_sec;
	long dif_nsec = after_time.tv_nsec - current_time.tv_nsec;

	double ms_difference = 1000.0 * (double) dif_sec + (double) dif_nsec / 1000000.0;

	fprintf(stdout, "Calculation complete. Time to complete : %f milliseconds.\n", ms_difference);
	fprintf(stdout, "View results? (y/N) ");

	if (tolower(getchar()) == 'y') {
		for (uint32_t i = 0; i < active_list_size; ++i) {
			fprintf(stdout, "%zu ", active_list[i]);
		}

		fprintf(stdout, "\n");
	}

	free(active_list);
	return 0;
}

void selection_sort(uint32_t* data, uint32_t size) {
	// This is a pretty short implementation.

	for (uint32_t i = 0; i < size - 1; ++i) {
		uint32_t current = 0, c_min = data[i], c_min_index = i, tmp;

		for (uint32_t k = i + 1; k < size; ++k) {
			if (data[k] < c_min) {
				c_min_index = k;
				c_min = data[k];
			}
		}

		if (c_min_index != i) {
			tmp = data[c_min_index];
			data[c_min_index] = data[i];
			data[i] = tmp;
		}
	}
}
