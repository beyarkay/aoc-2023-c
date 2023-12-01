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
// Benchmark 1: ./bin/bench01
//   Time (mean ± σ):   659.6 µs ±  44.9 µs [User: 257.5 µs, System: 206.7 µs]
//   Range (min … max): 606.0 µs … 1224.6 µs    3794 runs
//
//   Warning: Statistical outliers were detected. Consider re-running this
//   benchmark on a quiet system without any interferences from other programs.
//   It might help to use the '--warmup' or '--prepare' options.

#include <stdio.h>
#include <stdlib.h>

int main() {
  // Setup
  FILE *file;
  char *line = NULL;
  size_t length = 0;
  ssize_t n_chars_read;

  // Get file handle
  file = fopen("input/01.txt", "r");

  // Check for errors fetching file handle
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Store the leftmost and rightmost digit as a char initially
  char left;
  char right;

  // Keep track of the count
  int count = 0;
  while ((n_chars_read = getline(&line, &length, file)) != -1) {
    // Reinitiliase left and right for each line in the file
    left = '\0';
    right = '\0';
    // Go over every character in the line
    for (int i = 0; i < n_chars_read - 1; i++) {
      // Check if the character is a digit and if we haven't yet found a
      // left/right character
      if (left == '\0' && line[i] >= '0' && line[i] <= '9') {
        left = line[i];
      }
      if (right == '\0' && line[n_chars_read - 2 - i] >= '0' &&
          line[n_chars_read - 2 - i] <= '9') {
        right = line[n_chars_read - 2 - i];
      }
      // If we've found both a left and rightmost character, we're done with
      // this line
      if (right != '\0' && left != '\0') {
        break;
      }
    }
    // Add to the count the two-digit number consisting of left as the tens
    // digit and right as the units digit
    count += (left - '0') * 10 + (right - '0');
  }
  // print out the result
  printf("\n%d", count);

  // Close out the program
  free(line);
  fclose(file);
  return 0;
}
