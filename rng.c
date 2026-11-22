//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	RNG table of pre-defined integers.
//

#include <stdio.h>
#include "rng.h"

int rngcall() {
    int numbers[] = {
        0, 16, 25, 44,
        104, 33, 42, 2,
        12,  99, 13, 243,
	255, 77, 67, 9
    };

    // Count the amount of values.
    int total_num = sizeof(numbers) / sizeof(numbers[0]);

    static int index = 0;

    int current_value = numbers[index];
    index = (index + 1) % total_num;

    return current_value;
}
