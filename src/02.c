// --- Day 2: Cube Conundrum ---
// https://adventofcode.com/2023/day/2
//
// You're launched high into the atmosphere! The apex of your trajectory just
// barely reaches the surface of a large island floating in the sky. You gently
// land in a fluffy pile of leaves. It's quite cold, but you don't see much
// snow. An Elf runs over to greet you.
//
// The Elf explains that you've arrived at Snow Island and apologizes for the
// lack of snow. He'll be happy to explain the situation, but it's a bit of a
// walk, so you have some time. They don't get many visitors up here; would you
// like to play a game in the meantime?
//
// As you walk, the Elf shows you a small bag and some cubes which are either
// red, green, or blue. Each time you play this game, he will hide a secret
// number of cubes of each color in the bag, and your goal is to figure out
// information about the number of cubes.
//
// To get information, once a bag has been loaded with cubes, the Elf will
// reach into the bag, grab a handful of random cubes, show them to you, and
// then put them back in the bag. He'll do this a few times per game.
//
// You play several games and record the information from each game (your
// puzzle input). Each game is listed with its ID number (like the 11 in Game
// 11: ...) followed by a semicolon-separated list of subsets of cubes that
// were revealed from the bag (like 3 red, 5 green, 4 blue).
//
// For example, the record of a few games might look like this:
//
// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green Game 2: 1 blue, 2
// green; 3 green, 4 blue, 1 red; 1 green, 1 blue Game 3: 8 green, 6 blue, 20
// red; 5 blue, 4 red, 13 green; 5 green, 1 red Game 4: 1 green, 3 red, 6 blue;
// 3 green, 6 red; 3 green, 15 blue, 14 red Game 5: 6 red, 1 blue, 3 green; 2
// blue, 1 red, 2 green
//
// In game 1, three sets of cubes are revealed from the bag (and then put back
// again). The first set is 3 blue cubes and 4 red cubes; the second set is 1
// red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green
// cubes.
//
// The Elf would first like to know which games would have been possible if the
// bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
//
// In the example above, games 1, 2, and 5 would have been possible if the bag
// had been loaded with that configuration. However, game 3 would have been
// impossible because at one point the Elf showed you 20 red cubes at once;
// similarly, game 4 would also have been impossible because the Elf showed you
// 15 blue cubes at once. If you add up the IDs of the games that would have
// been possible, you get 8.
//
// Determine which games would have been possible if the bag had been loaded
// with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum
// of the IDs of those games?

// hyperfine --warmup=5 -N --min-runs=100 ./bin/bench02
// Benchmark 1: ./bin/bench02
//   Time (mean ± σ):     615.6 µs ±  47.2 µs    [User: 222.6 µs, System: 201.4
//   µs] Range (min … max):   573.6 µs … 1292.9 µs    4363 runs
//
//   Warning: Statistical outliers were detected. Consider re-running this
//   benchmark on a quiet system without any interferences from other programs.
//   It might help to use the '--warmup' or '--prepare' options.

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  FILE *file = fopen("input/02.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char *line = NULL;
  size_t line_length = 0;
  ssize_t n_chars_read;

  int MAX_CUBES[3] = {12, 13, 14};

  int game_id_sum = 0;
  while ((n_chars_read = getline(&line, &line_length, file)) != -1) {
    int max_seen[3] = {0, 0, 0};
    int game_id = 0;
    bool seen_game_id = false;
    bool prev_was_space = false;
    char curr_colour = '\0';
    char curr_number = 0;
    // printf("%s", line);

    for (int i = 5; i < n_chars_read - 1; i++) {
      prev_was_space = line[i - 1] == ' ';
      // printf("%c  game_id: %d max: [%d %d %d] curr: %d col: %c\n", line[i],
      //        game_id, max_seen[0], max_seen[1], max_seen[2], curr_number,
      //        curr_colour);

      // Keep track of whether we're looking at the game ID or the
      // red/green/blue colour numbers
      if (line[i] == ':') {
        seen_game_id = true;
        continue;
      }

      // Figure out max colour on , or ;
      if (line[i] == ',' || line[i] == ';' || i == n_chars_read - 2) {
        // printf
        // Set the maximum of the colours
        if (curr_colour == 'r') {
          max_seen[0] = max_seen[0] > curr_number ? max_seen[0] : curr_number;
        } else if (curr_colour == 'g') {
          max_seen[1] = max_seen[1] > curr_number ? max_seen[1] : curr_number;
        } else if (curr_colour == 'b') {
          max_seen[2] = max_seen[2] > curr_number ? max_seen[2] : curr_number;
        }
        curr_colour = '\0';
        curr_number = 0;
        continue;
      }

      // printf("%c line[%d]: %c seen_game_id: %d prev_was_space: %d\n",
      // line[i], i, line[i], seen_game_id, prev_was_space);
      if (seen_game_id) {
        if (prev_was_space &&
            (line[i] == 'r' || line[i] == 'g' || line[i] == 'b')) {
          // If we're seeing a colour definition, keep track of it
          curr_colour = line[i];
        } else if (line[i] >= '0' && line[i] <= '9') {
          // If we're looking at a digit like `42 red`, then keep track of the
          // 42
          curr_number = curr_number * 10 + (line[i] - '0');
          // printf("  curr_number: %d\n", curr_number);
        }
      } else if (!seen_game_id) {
        // If we're looking at a digit like `Game 41`, then keep track of the 41
        game_id = game_id * 10 + (line[i] - '0');
        // printf("  game id: %d\n", game_id);
      }
    }

    bool is_possible = true;
    for (int i = 0; i < 3; i++) {
      if (max_seen[i] > MAX_CUBES[i]) {
        is_possible = false;
        break;
      }
    }

    if (is_possible) {
      game_id_sum += game_id;
      // printf("%d POSSIBLE    : [%d %d %d] \n\t%s", game_id, max_seen[0],
      //        max_seen[1], max_seen[2], "  ");
    } else {
      // printf("NOT POSSIBLE: [%d %d %d]", max_seen[0], max_seen[1],
      // max_seen[2]);
    }

    // printf("  game_id: %d, curr_number: %d max: [%d %d %d]\n", game_id,
    //        curr_number, max_seen[0], max_seen[1], max_seen[2]);
  }
  printf("Part 1: %d", game_id_sum);

  return 0;
}
