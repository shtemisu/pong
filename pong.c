#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 25
#define WIDTH 80
#define middleOfField 40

void drawFieldBall(int ballX, int ballY, int leftRocket, int rightRocket,
                   int first_player_score, int second_player_score) {
  system("clear");
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (y == 0 || y == HEIGHT - 1) {
        printf("-");
      } else if (x == 0 || x == WIDTH - 1) {
        printf("#");
      } else if (y == ballY && x == ballX) {
        printf("O");
      } else if (x == middleOfField) {
        printf("|");
      } else if (x == 2 && (y == leftRocket + 1 || y == leftRocket ||
                            y == leftRocket - 1)) {
        printf("]");
      } else if (x == 77 && (y == rightRocket + 1 || y == rightRocket ||
                             y == rightRocket - 1)) {
        printf("[");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf(" Player-1: %d", first_player_score);
  printf(" Player-2: %d\n\n", second_player_score);
}

int check_direction(int dir, int ballY) {
  if (ballY == 1 && dir == 1)
    return 2;
  if (ballY == 1 && dir == 4)
    return 3;
  if (ballY == 23 && dir == 2)
    return 1;
  if (ballY == 23 && dir == 3)
    return 4;

  return -1;
}

int moveToBallY(int dir, int ballY) {
  if (dir == 1) {
    return --ballY;
  } else if (dir == 2) {
    return ++ballY;
  } else if (dir == 3) {
    return ++ballY;
  } else if (dir == 4) {
    return --ballY;
  }
  return -1;
}

int moveToBallX(int dir, int ballX) {
  if (dir == 1) {
    return ++ballX;

  } else if (dir == 2) {
    return ++ballX;

  } else if (dir == 3) {
    return --ballX;

  } else if (dir == 4) {
    return --ballX;
  }
  return -1;
}

int check_rocket(int leftRocket, int rightRocket, int ballX, int ballY,
                 int dir) {
  if (ballX == 3 &&
      (ballY == leftRocket || ballY == leftRocket + 1 ||
       ballY == leftRocket - 1) &&
      dir == 3) {
    return 2;
  } else if (ballX == 3 &&
             (ballY == leftRocket || ballY == leftRocket + 1 ||
              ballY == leftRocket - 1) &&
             dir == 4) {
    return 1;
  } else if (ballX == 76 &&
             (ballY == rightRocket || ballY == rightRocket + 1 ||
              ballY == rightRocket - 1) &&
             dir == 2) {
    return 3;
  } else if (ballX == 76 &&
             (ballY == rightRocket || ballY == rightRocket + 1 ||
              ballY == rightRocket - 1) &&
             dir == 1) {
    return 4;
  } else if (ballX == 76 && ballY == rightRocket + 2) {
    return 3;
  } else if (ballX == 76 && ballY == rightRocket - 2) {
    return 4;
  } else if (ballX == 3 && ballY == leftRocket + 2) {
    return 2;
  } else if (ballX == 3 && ballY == leftRocket - 2) {
    return 1;
  }
  return -1;
}

int check_border(int ballX) {
  if (ballX <= 1) {
    return 1;
  }
  if (ballX >= 78) {
    return 2;
  }
  return 0;
}

int main() {
  int rightRocket = HEIGHT / 2;
  int leftRocket = HEIGHT / 2;
  int ballX = 40;
  int ballY = 12;
  int scoreOne = 0;
  int scoreTwo = 0;
  int dir = 1;

  while (scoreOne < 21 && scoreTwo < 21) {
    if (check_border(ballX) == 1) {
      scoreTwo++;
      ballX = 40;
      ballY = 12;
      dir = 2;
    } else if (check_border(ballX) == 2) {
      scoreOne++;
      ballX = 40;
      ballY = 12;
      dir = 4;
    }
    if (check_direction(dir, ballY) != -1) {
      dir = check_direction(dir, ballY);
    }
    if (check_rocket(leftRocket, rightRocket, ballX, ballY, dir) != -1) {
      dir = check_rocket(leftRocket, rightRocket, ballX, ballY, dir);
    }
    drawFieldBall(ballX, ballY, leftRocket, rightRocket, scoreOne, scoreTwo);
    ballX = moveToBallX(dir, ballX);
    ballY = moveToBallY(dir, ballY);

    char key = getchar();
    if (key == 'a' && leftRocket > 2) {
      leftRocket--;
    }
    if (key == 'z' && leftRocket < HEIGHT - 3) {
      leftRocket++;
    }
    if (key == 'k' && rightRocket > 2) {
      rightRocket--;
    }
    if (key == 'm' && rightRocket < HEIGHT - 3) {
      rightRocket++;
    }
    if (key == 'q') {
      printf("Game Over Early!\n");
      break;
    }
    if (key == ' ') {
      rightRocket += 0;
      leftRocket += 0;
    }
  }
  if (scoreOne == 21 || scoreTwo == 21) {
    drawFieldBall(-1, -1, leftRocket, rightRocket, scoreOne, scoreTwo);
  }
  if (scoreOne == 21)
    printf("Game over!\nPlayer 1 won!\n");
  if (scoreTwo == 21)
    printf("Game over!\nPlayer 2 won!\n");

  return 0;
}
