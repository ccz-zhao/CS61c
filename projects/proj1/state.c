#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

#define     MAX_LEN   100000

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int x, unsigned int y, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_x(unsigned int cur_x, char c);
static unsigned int get_next_y(unsigned int cur_y, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);


/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  int i;
  unsigned int default_row = 18;
  unsigned int default_col = 21;
  char *outer = "####################\n";
  char *inner = "#                  #\n";
  snake_t *snake = malloc(sizeof(snake_t));
  game_state_t *state = malloc(sizeof(game_state_t));
  char **board = malloc(default_row*sizeof(char*));

  for (i = 0; i < default_row; ++i)
    board[i] = malloc(default_col*sizeof(char));

  // setup board
  strcpy(board[0], outer);
  strcpy(board[17], outer);
  for (i = 1; i < 17; ++i) {
    strcpy(board[i], inner);
  }
  
  board[2][2] = 'd';
  board[2][3] = '>';
  board[2][4] = 'D';
  board[2][9] = '*';

  // setup snake
  snake->tail_x = 2;
  snake->tail_y = 2;
  snake->head_x = 4;
  snake->head_y = 2;
  snake->live = true;

  // setup state
  state->num_rows = 18;
  state->num_snakes = 1;
  state->snakes = snake;
  state->board = board;

  return state;
}


/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  // free board
  int i;
  for (i = 0; i < state->num_rows; ++i) {
    free(state->board[i]);
  }
  free(state->board);

  // free snakes
  free(state->snakes);

  // free state
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  int i;
  for (i = 0; i < state->num_rows; ++i) {
    fprintf(fp, "%s", state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}


/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int x, unsigned int y) {
  return state->board[y][x];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int x, unsigned int y, char ch) {
  state->board[y][x] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c == 'w' || c == 'a' || c == 's' || c == 'd')
    return true;
  else  
    return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'x')
    return true;
  else  
    return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<>vWASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if (is_head(c) || is_tail(c) || c == '>' || c == '<' || c == '^' || c == 'v')
    return true;
  else 
    return false;
}

/*
  Converts a character in the snake's body ("^<>v")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  if (c == '^') 
    return 'w';
  if (c == '<') 
    return 'a';
  if (c == '>') 
    return 'd';
  if (c == 'v') 
    return 's';
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<>v").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  if (c == 'W') 
    return '^';
  if (c == 'A') 
    return '<';
  if (c == 'D') 
    return '>';
  if (c == 'S') 
    return 'v';
  return '?';
}

/*
  Returns cur_x + 1 if c is '>' or 'd' or 'D'.
  Returns cur_x - 1 if c is '<' or 'a' or 'A'.
  Returns cur_x otherwise.
*/
static unsigned int get_next_x(unsigned int cur_x, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D')
    return cur_x + 1;
  else if (c == '<' || c == 'a' || c == 'A')
    return cur_x - 1;
  else
    return cur_x;
}

/*
  Returns cur_y + 1 if c is '^' or 'w' or 'W'.
  Returns cur_y - 1 if c is 'v' or 's' or 'S'.
  Returns cur_y otherwise.
*/
static unsigned int get_next_y(unsigned int cur_y, char c) {
  // TODO: Implement this function.
  if (c == '^' || c == 'w' || c == 'W')
    return cur_y - 1;
  else if (c == 'v' || c == 's' || c == 'S')
    return cur_y + 1;
  else
    return cur_y;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  char head_c, next_c;
  unsigned int head_x, head_y, next_x, next_y;

  head_x = (state->snakes+snum)->head_x;
  head_y = (state->snakes+snum)->head_y;
  head_c = get_board_at(state, head_x, head_y);

  next_x = get_next_x(head_x, head_c);
  next_y = get_next_y(head_y, head_c);
  next_c = get_board_at(state, next_x, next_y);

  return next_c;
}


/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the x and y coordinates of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  char head_c;
  unsigned int head_x, head_y, next_x, next_y;

  head_x = (state->snakes+snum)->head_x;
  head_y = (state->snakes+snum)->head_y;
  head_c = get_board_at(state, head_x, head_y);
  next_x = get_next_x(head_x, head_c);
  next_y = get_next_y(head_y, head_c);

  // update snake struct
  (state->snakes+snum)->head_x = next_x;
  (state->snakes+snum)->head_y = next_y;

  // update board
  set_board_at(state, next_x, next_y, head_c);
  set_board_at(state, head_x, head_y, head_to_body(head_c));
  
  return;
}


/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^v<>) into a tail character (wasd)

  ...in the snake struct: update the x and y coordinates of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  char tail_c, next_c;
  unsigned int tail_x, tail_y, next_x, next_y;

  tail_x = (state->snakes+snum)->tail_x;
  tail_y = (state->snakes+snum)->tail_y;
  tail_c = get_board_at(state, tail_x, tail_y);
  
  next_x = get_next_x(tail_x, tail_c);
  next_y = get_next_y(tail_y, tail_c);
  next_c = get_board_at(state, next_x, next_y);
  // update snake struct
  (state->snakes+snum)->tail_x = next_x;
  (state->snakes+snum)->tail_y = next_y;

  // update board
  set_board_at(state, next_x, next_y, body_to_tail(next_c));
  set_board_at(state, tail_x, tail_y, ' ');

  return;
}

static char get_next_head(game_state_t *state, unsigned int snum) {
  char head_c;
  unsigned int head_x, head_y, next_x, next_y;

  head_x = (state->snakes+snum)->head_x;
  head_y = (state->snakes+snum)->head_y;
  head_c = get_board_at(state, head_x, head_y);
  next_x = get_next_x(head_x, head_c);
  next_y = get_next_y(head_y, head_c);

  return get_board_at(state, next_x, next_y);
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  char next_head;
  unsigned int i;
  unsigned int num_snakes = state->num_snakes;
  for (i = 0; i < num_snakes; ++i) {
    if (!(state->snakes+i)->live) {
      continue;
    }
    next_head = get_next_head(state, i);
    if (next_head == ' ') {
      update_head(state, i);
      update_tail(state, i);
    }
    else if (next_head == '*') {
      update_head(state, i);
      add_food(state);
    }
    else {
      set_board_at(state, 
      (state->snakes+i)->head_x, (state->snakes+i)->head_y, 'x');
      (state->snakes+i)->live = false;
    }
  }
  return;
}


/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  int ch;
  unsigned int idx, row, row_idx;
  char **board;
  char *buff = malloc(MAX_LEN*sizeof(char));
  game_state_t *state = malloc(sizeof(game_state_t));
  FILE *fp = fopen(filename, "r");

  if (!fp) {
      fprintf(stderr, "in_filename not found!\n");
      exit(-1);
  }

  idx = 0;
  row_idx = 0;
  row = 20;
  board = malloc(row*sizeof(char*));
  
  while ((ch = fgetc(fp)) != EOF) {
    buff[idx++] = (char)ch;
    if (ch == '\n') {
      if (row_idx > row) {
        row *= 2;
        board = realloc(board, row*sizeof(char*));
      }
      buff[idx] = '\0';
      board[row_idx] = malloc((idx+1)*sizeof(char));
      strcpy(board[row_idx], buff);
      ++row_idx;
      idx = 0;
    }
  }

  state->board = board;
  state->num_rows = row_idx;

  free(buff);
  return state;
}

static char get_next_ch(game_state_t* state, unsigned int* curr_x, unsigned int* curr_y) {
  char curr_ch, next_ch;
  unsigned int next_x, next_y;

  curr_ch = get_board_at(state, *curr_x, *curr_y);
  next_x = get_next_x(*curr_x, curr_ch);
  next_y = get_next_y(*curr_y, curr_ch);
  next_ch = get_board_at(state, next_x, next_y);

  *curr_x = next_x;
  *curr_y = next_y;
  return next_ch;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail coordinates filled in,
  trace through the board to find the head coordinates, and
  fill in the head coordinates in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  char next_ch;
  unsigned int curr_x, curr_y;
  snake_t *snake = state->snakes + snum;

  curr_x = snake->tail_x;
  curr_y = snake->tail_y;
  do
  {
    next_ch = get_next_ch(state, &curr_x, &curr_y);
  } while (!is_head(next_ch));

  snake->head_x = curr_x;
  snake->head_y = curr_y;

  return;
}

static bool is_outline(const char* str) {
  int i = 0;
  while (str[i] == '#') {
    ++i;
  }
  if (str[i] == '\n')
    return true;
  else 
    return false;
}


/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  char curr_ch;
  unsigned int curr_row;
  unsigned int curr_col = 0;
  unsigned int i;
  unsigned int *tail_x = malloc(MAX_LEN*sizeof(int));
  unsigned int *tail_y = malloc(MAX_LEN*sizeof(int));
  unsigned int num_snakes = 0;
  char **board = state->board;
  snake_t *snakes;

# if 0
  while (!is_outline(board[curr_row])) {
    curr_col = 0;
    while ((curr_ch = board[curr_row][curr_col]) != '\n') {
      if (is_tail(curr_ch)) {
        tail_x[num_snakes] = curr_col;
        tail_y[num_snakes] = curr_row;
        ++num_snakes;
      }
      ++curr_col;
    }
    ++curr_row;
  }
# endif
  for (curr_row = 1; curr_row < state->num_rows; ++curr_row) {
    curr_col = 0;
    while ((curr_ch = board[curr_row][curr_col]) != '\n') {
      if (is_tail(curr_ch)) {
        tail_x[num_snakes] = curr_col;
        tail_y[num_snakes] = curr_row;
        ++num_snakes;
      }
      ++curr_col;
    }
  }

  snakes = malloc(num_snakes*(sizeof(snake_t)));
  state->snakes = snakes;
  state->num_snakes = num_snakes;

  for (i = 0; i < num_snakes; ++i) {
    snakes[i].tail_x = tail_x[i];
    snakes[i].tail_y = tail_y[i];
    find_head(state, i);
    snakes[i].live = true;
  }
  
  free(tail_x);
  free(tail_y);

  return state;
}
