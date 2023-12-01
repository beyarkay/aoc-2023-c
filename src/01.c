//--- Day 1: Trebuchet?! ---
// https://adventofcode.com/2023/day/1
//
// Something is wrong with global snow production, and you've been selected to
// take a look. The Elves have even given you a map; on it, they've used stars
// to mark the top fifty locations that are likely to be having problems.
//
// You've been doing this long enough to know that to restore snow operations,
// you need to check all fifty stars by December 25th.
//
// Collect stars by solving puzzles. Two puzzles will be made available on each
// day in the Advent calendar; the second puzzle is unlocked when you complete
// the first. Each puzzle grants one star. Good luck!
//
// You try to ask why they can't just use a weather machine ("not powerful
// enough") and where they're even sending you ("the sky") and why your map
// looks mostly blank ("you sure ask a lot of questions") and hang on did you
// just say the sky ("of course, where do you think snow comes from") when you
// realize that the Elves are already loading you into a trebuchet ("please
// hold still, we need to strap you in").
//
// As they're making the final adjustments, they discover that their
// calibration document (your puzzle input) has been amended by a very young
// Elf who was apparently just excited to show off her art skills.
// Consequently, the Elves are having trouble reading the values on the
// document.
//
// The newly-improved calibration document consists of lines of text; each line
// originally contained a specific calibration value that the Elves now need to
// recover. On each line, the calibration value can be found by combining the
// first digit and the last digit (in that order) to form a single two-digit
// number.
//
// For example:
//
// ```
// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet
// ```
//
// In this example, the calibration values of these four lines are 12, 38, 15,
// and 77. Adding these together produces 142.
//
// Consider your entire calibration document. What is the sum of all of the
// calibration values?
//
// Benchmark 1: make run01
//   Time (mean ± σ):      50.4 ms ±   2.8 ms    [User: 33.3 ms, System: 12.2
//   ms] Range (min … max):    49.1 ms …  70.4 ms    56 runs

#include <stdio.h>
#include <stdlib.h>

int main() {
  // printf("Starting\n");
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t n_chars_read;

  file = fopen("input/01.txt", "r");

  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  int line_num = 0;
  char left = '\0';
  char right = '\0';

  int count = 0;
  while ((n_chars_read = getline(&line, &len, file)) != -1) {
    left = '\0';
    right = '\0';
    // printf("\n:: %zd %zu\n:: %s", n_chars_read, len, line);
    for (int i = 0; i < n_chars_read - 1; i++) {
      // printf("\nleft: %c right: %c", line[i], line[n_chars_read - 2 - i]);
      if (left == '\0' && line[i] >= '0' && line[i] <= '9') {
        // printf("\n  [%d  %d] %c\n", line_num, i, line[i]);
        left = line[i];
      }
      if (right == '\0' && line[n_chars_read - 2 - i] >= '0' &&
          line[n_chars_read - 2 - i] <= '9') {
        right = line[n_chars_read - 2 - i];
      }
      if (right != '\0' && left != '\0') {
        break;
      }
    }
    // printf("\n%c%c", left, right);
    count += (left - '0') * 10 + (right - '0');
  }
  printf("\n%d", count);

  free(line);

  fclose(file);

  return 0;
}
