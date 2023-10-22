#ifndef MAIN_H
#define MAIN_H
#define WIDTH 80
#define HEIGHT 25
#define END_GAME_SCORE 5

enum Direction_x { LEFT = -1, RIGHT = 1, NONE_X = 0 };
enum Direction_y { UP = -1, DOWN = 1, NONE_Y = 0 };

typedef struct Ball {
  int x;
  int y;
  int direction_x;
  int direction_y;
} Ball;

typedef struct Player {
  const int x;
  int y;
  int score;
} Player;

void cheack_Ball_Direction(Ball *ball, const Player *player_1,
                           const Player *player_2);
void move_Ball(Ball *ball, const Player *player_1, const Player *player_2);
void print_Board(const Ball *ball, const Player *player_1,
                 const Player *player_2);
void print_Score(const Player *player_1, const Player *player_2);
void print_Screen(const Ball *ball, const Player *player_1,
                  const Player *player_2);
void changing_Player_Coordinate(int *player_y, int delta);
void input(Player *player, int player_number);
void startPage();
int checkGoal(int ball_X, Player *player_1, Player *player_2);
int endGame(const Player *player_1, const Player *player_2);
void reset_Game(int goal_flag, Player *player_1, Player *player_2, Ball *ball);

#endif