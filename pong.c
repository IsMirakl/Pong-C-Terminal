#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Для работы с функцией time
#include <unistd.h> // Для использования функции usleep

void field_generation(int LeftRocket, int RightRocket, int ball_x, int ball_y,
                      int playerScore_1, int playerScore_2) {
  for (int height = 0; height < 25; height++) {
    for (int width = 0; width < 80; width++) {
      if (height == 0 || height == 24) {
        printf("-");
      } else if (width == 40) {
        printf("|");
      } else if (((height == LeftRocket || height == LeftRocket + 1 ||
                   height == LeftRocket - 1) &&
                  width == 0) ||
                 ((height == RightRocket || height == RightRocket + 1 ||
                   height == RightRocket - 1) &&
                  width == 79)) {
        printf("|");
      } else if (height == ball_y && width == ball_x) {
        printf("o");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("Player 1: %d  Player 2: %d\n", playerScore_1, playerScore_2);
}

int playerOneTurn(char key, int Position) {
  if (key == 'a') {

    if (Position > 2) {
      Position--;
    }
  } else if (key == 'z') {
    if (Position < 22) {
      Position++;
    }
  }
  return Position;
}

int playerTwoTurn(char key, int Position) {
  if (key == 'k') {
    if (Position > 2) {
      Position--;
    }
  } else if (key == 'm') {
    if (Position < 22) {
      Position++;
    }
  }
  return Position;
}

int main() {
  char startGame;
  printf("Добро пожаловать в игру Pong !\nИгра идет до 21 очка ,кто первый"
         " набрал ,тот приз забрал)\n");
  printf("Для преждневременой остановки игры нажмите 'q'\n");
  printf("Хотите ли вы начать игру? (y/n): ");
  scanf("%c", &startGame);

  if (startGame == 'y') {
    int LeftRocket = 12;  // позиция  левой ракетки
    int RightRocket = 12; // позиция правой ракетки
    int ball_x =
        40; // Начальное положение мяча по горизонтали (по середине поля)
    int ball_y = 12; // Начальное положение мяча по вертикали (по середине поля)
    int ball_x_step = 1; // Начальное направление движения мяча по горизонтали
    int ball_y_step = 1; // Начальное направление движения мяча по вертикали
    int playerScore_1 = 0; // счет игрока
    int playerScore_2 = 0; // счет игрока

    srand(time(NULL)); // Инициализация генератора случайных чисел

    while (playerScore_1 < 21 && playerScore_2 < 21) {
      // Обновляем положение мяча и проверяем нажатие кнопок
      char key;
      key = getchar();
      if (key == 'a' || key == 'z') {
        LeftRocket = playerOneTurn(key, LeftRocket);
      } else if (key == 'k' || key == 'm') {
        RightRocket = playerTwoTurn(key, RightRocket);
      } else if (key == 'q') {
        printf("Player 1: %d\nPlayer 2: %d\n", playerScore_1, playerScore_2);
        break;
      }

      // Движение мяча
      ball_x += ball_x_step;
      ball_y += ball_y_step;

      // Обработка столкновений мяча с границами поля
      if (ball_x == 1 || ball_x == 79) {
        // Попадание в боковые стенки, зачисление очков
        if (ball_x == 1) {
          playerScore_2 += 1;
        } else {
          playerScore_1 += 1;
        }
        ball_x = 40;
        ball_y = 12;
        ball_x_step = -ball_x_step; // Изменяем направление по горизонтали
      }
      if (ball_y == 1 || ball_y == 23) {
        ball_y_step = -ball_y_step; // Изменяем направление по вертикали
      }

      // Проверка столкновения мяча с ракетками
      if ((ball_y == LeftRocket || ball_y == LeftRocket + 1 ||
           ball_y == LeftRocket - 1) &&
          ball_x == 2) {
        ball_x_step = -ball_x_step; // Изменяем направление по горизонтали
      }
      if ((ball_y == RightRocket || ball_y == RightRocket + 1 ||
           ball_y == RightRocket - 1) &&
          ball_x == 78) {
        ball_x_step = -ball_x_step; // Изменяем направление по горизонтали
      }

      if (playerScore_1 >= 21) {
        system("clear");
        printf("Игрок 1 победил\nПоздравляем его!\n");
        break;

      } else if (playerScore_2 >= 21) {
        system("clear");
        printf("Игрок 2 победил\nПоздравляем его!\n");
        break;
      }

      // Вывод обновленного поля
      system("clear"); // Очищаем экран перед выводом нового поля
      field_generation(LeftRocket, RightRocket, ball_x, ball_y, playerScore_1,
                       playerScore_2);
      usleep(100000); // Задержка для плавного обновления поля
    }
  } else {
    printf("Вы отказались начать игру ");
  }

  return 0;
}
