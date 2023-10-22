#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  system("stty -icanon -echo");
  startPage();
  Ball ball = {13, 13, LEFT, NONE_Y};
  Player player_1 = {10, HEIGHT / 2, 0};
  Player player_2 = {WIDTH - 10, HEIGHT / 2, 0};
  int player_number = 1, end_game = 0;
  while (!end_game) {
    print_Screen(&ball, &player_1, &player_2);
    if (player_number == 1) {
      input(&player_1, player_number);
      player_number = 2;
    } else {
      input(&player_2, player_number);
      player_number = 1;
    }
    move_Ball(&ball, &player_1, &player_2);
    print_Screen(&ball, &player_1, &player_2);
    int goal_flag = checkGoal(ball.x, &player_1, &player_2);
    if (goal_flag != 0) {
      reset_Game(goal_flag, &player_1, &player_2, &ball);
      end_game = endGame(&player_1, &player_2);
    }
  }
  return 0;
}

void print_Board(const Ball *ball, const Player *player_1,
                 const Player *player_2) {
  for (int y = 0; y <= HEIGHT + 1; y++) {
    for (int x = 0; x <= WIDTH + 2; x++) {
      if (y == 0 || y == HEIGHT + 1) {
        printf("-");
      } else if (x == 0 || x == WIDTH + 2 || x == (WIDTH + 2) / 2 ||
                 (x == player_1->x &&
                  (y == player_1->y || y == player_1->y + 1 ||
                   y == player_1->y + 2)) ||
                 (x == player_2->x &&
                  (y == player_2->y || y == player_2->y + 1 ||
                   y == player_2->y + 2))) {
        printf("|");
      } else if (x == ball->x && y == ball->y) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void print_Score(const Player *player_1, const Player *player_2) {
  printf("\tPlayer 1 Score: %d\t\t\t", player_1->score);
  printf("Player 2 Score: %d\n", player_2->score);
}

void print_Screen(const Ball *ball, const Player *player_1,
                  const Player *player_2) {
  system("clear");
  print_Score(player_1, player_2);
  print_Board(ball, player_1, player_2);
}

void cheack_Ball_Direction(Ball *ball, const Player *player_1,
                           const Player *player_2) {
  if (ball->y == 1 && ball->direction_y == UP) {
    ball->direction_y = DOWN;
    if (ball->x == 11 && ball->direction_x == LEFT) {
      if (ball->y + 1 == player_1->y) {
        ball->direction_x = RIGHT;
      } else if (ball->y + 1 == player_1->y + 1) {
        ball->direction_x = RIGHT;
        ball->direction_y = NONE_Y;
      }
    } else if (ball->x == WIDTH - 11 && ball->direction_x == RIGHT) {
      if (ball->y + 1 == player_2->y) {
        ball->direction_x = LEFT;
      } else if (ball->y + 1 == player_2->y + 1) {
        ball->direction_x = LEFT;
        ball->direction_y = NONE_Y;
      }
    }
  } else if (ball->y == HEIGHT && ball->direction_y == DOWN) {
    ball->direction_y = UP;
    if (ball->x == 11 && ball->direction_x == LEFT) {
      if (ball->y - 1 == player_1->y + 2) {
        ball->direction_x = RIGHT;
      } else if (ball->y - 1 == player_1->y + 1) {
        ball->direction_x = RIGHT;
        ball->direction_y = NONE_Y;
      }
    } else if (ball->x == WIDTH - 11 && ball->direction_x == RIGHT) {
      if (ball->y - 1 == player_2->y + 2) {
        ball->direction_x = LEFT;
      } else if (ball->y - 1 == player_2->y + 1) {
        ball->direction_x = LEFT;
        ball->direction_y = NONE_Y;
      }
    }
  } else if ((ball->y + ball->direction_y == player_1->y &&
              (ball->x == 11 && ball->direction_x == LEFT)) ||
             ((ball->y + ball->direction_y == player_2->y) &&
              (ball->x == WIDTH - 11 && ball->direction_x == RIGHT))) {
    ball->direction_x *= -1;
    ball->direction_y = UP;
  } else if ((ball->y + ball->direction_y == (player_1->y + 1) &&
              (ball->x == 11 && ball->direction_x == LEFT)) ||
             (ball->y + ball->direction_y == (player_2->y + 1) &&
              (ball->x == WIDTH - 11 && ball->direction_x == RIGHT))) {
    ball->direction_x *= -1;
    ball->direction_y = NONE_Y;
  } else if ((ball->y + ball->direction_y == (player_1->y + 2) &&
              (ball->x == 11 && ball->direction_x == LEFT)) ||
             (ball->y + ball->direction_y == (player_2->y + 2) &&
              (ball->x == WIDTH - 11 && ball->direction_x == RIGHT))) {
    ball->direction_x *= -1;
    ball->direction_y = DOWN;
  }
}

void changing_Player_Coordinate(int *player_y, int delta) {
  if (delta == 1) {
    if (*player_y + 2 + delta <= HEIGHT)
      *player_y += delta;
  } else if (delta == -1) {
    if (*player_y + delta >= 1)
      *player_y += delta;
  }
}

void move_Ball(Ball *ball, const Player *player_1, const Player *player_2) {
  cheack_Ball_Direction(ball, player_1, player_2);
  ball->x += ball->direction_x;
  ball->y += ball->direction_y;
}

void startPage() {
  system("clear");
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 80; j++) {
      if ((j >= 12 && j <= 19) || (j >= 36 && j <= 44) ||
          (j >= 60 && j <= 67) || (i >= 4 && i <= 19 && j >= 24 && j <= 31) ||
          (i >= 4 && i <= 11 && j >= 4 && j <= 7) ||
          (i >= 15 && j >= 4 && j <= 11) ||
          (((i >= 3 && i <= 8) || (i >= 12 && i <= 19)) && j >= 72 &&
           j <= 75) ||
          (i >= 12 && i <= 15 && j >= 68 && j <= 71) ||
          ((i >= 10 || i <= 1) && j == 49) ||
          ((i >= 12 || i <= 3) && j == 50) ||
          ((i >= 14 || i <= 5) && j == 51) ||
          ((i >= 16 || i <= 7) && j == 52) ||
          ((i >= 18 || i <= 9) && j == 53) ||
          ((i >= 20 || i <= 11) && j == 54) ||
          ((i >= 22 || i <= 13) && j == 55))
        printf(" ");
      else
        printf("*");
    }
    printf("\n");
  }
  printf("\n\t\t\t\tControle rules\nPlayer 1 \t\t\t\t\t\t\t\tPlayer 2\nPress "
         "'A' to MOVE UP\t\t\t\t\t    "
         "Press 'K' to MOVE UP\nPress 'Z' to MOVE DOWN\t\t\t\t\t  Press 'M' to "
         "MOVE DOWN\nPress 'SPACE' to "
         "skip a MOVE\t\t\t    Press 'SPACE' to skip a MOVE\n");

  printf("\n\t\t\tTo start the game, press ENTER...\n\n\n");
  getchar();
}

int checkGoal(int ball_X, Player *player_1, Player *player_2) {
  int toggle_player = 0;
  if (ball_X <= 10) {
    player_2->score++;
    toggle_player = 1;
  } else if (ball_X >= 70) {
    player_1->score++;
    toggle_player = 2;
  }
  return toggle_player;
}

int endGame(const Player *player_1, const Player *player_2) {
  int end_game = 0;
  if (player_1->score == END_GAME_SCORE) {
    printf("Player number 1 is winner! Congratulations!");
    end_game = 1;
  } else if (player_2->score == END_GAME_SCORE) {
    printf("Player number 2 is winner! Congratulations!");
    end_game = 1;
  }
  getchar();
  return end_game;
}

void reset_Game(int goal_flag, Player *player_1, Player *player_2, Ball *ball) {
  player_1->y = 12;
  player_2->y = 12;
  ball->direction_y = NONE_Y;
  ball->direction_x *= -1;
  ball->y = 13;
  if (goal_flag == 1) {
    ball->x = 11;
  } else if (goal_flag == 2) {
    ball->x = WIDTH - 11;
  }
}

void input(Player *player, int player_number) {
  int delta = -99;
  while (delta == -99) {
    char user_input = getchar();
    switch (player_number) {
    case 1:
      if (user_input == 'a')
        delta = -1;
      else if (user_input == 'z')
        delta = 1;
      else if (user_input == ' ')
        delta = 0;
      break;
    case 2:
      if (user_input == 'k')
        delta = -1;
      else if (user_input == 'm')
        delta = 1;
      else if (user_input == ' ')
        delta = 0;
      break;
    }
  }
  changing_Player_Coordinate(&player->y, delta);
}