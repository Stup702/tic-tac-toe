#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define EMPTY '.'
#define INVALID_MOVE 69

// ANSI color codes
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

char cells[9];
char human, computer;

void print_board() {
    system("clear");
    printf("\n");
    for (int i = 0; i < 9; i++) {
        char ch = cells[i];
        if (ch == human)
            printf(" %s%c%s ", GREEN, ch, RESET);
        else if (ch == computer)
            printf(" %s%c%s ", RED, ch, RESET);
        else
            printf(" %c ", ch);

        if ((i + 1) % 3 == 0) {
            if (i != 8) printf("\n---|---|---\n");
            else printf("\n\n");
        } else {
            printf("|");
        }
    }
}

void reset_board() {
    for (int i = 0; i < 9; i++) cells[i] = EMPTY;
}

bool is_draw() {
    for (int i = 0; i < 9; i++) {
        if (cells[i] == EMPTY) return false;
    }
    return true;
}

bool check_winner(char player) {
    const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (int i = 0; i < 8; i++) {
        if (cells[wins[i][0]] == player &&
            cells[wins[i][1]] == player &&
            cells[wins[i][2]] == player) return true;
    }
    return false;
}

int get_winning_move(char player) {
    for (int i = 0; i < 9; i++) {
        if (cells[i] == EMPTY) {
            cells[i] = player;
            bool win = check_winner(player);
            cells[i] = EMPTY;
            if (win) return i;
        }
    }
    return INVALID_MOVE;
}

int the_one_and_only(char player) {
    if (cells[1] == player) {
        if (cells[0] == EMPTY) return 0;
        if (cells[2] == EMPTY) return 2;
    }
    if (cells[3] == player) {
        if (cells[0] == EMPTY) return 0;
        if (cells[6] == EMPTY) return 6;
    }
    if (cells[5] == player) {
        if (cells[2] == EMPTY) return 2;
        if (cells[8] == EMPTY) return 8;
    }
    if (cells[7] == player) {
        if (cells[6] == EMPTY) return 6;
        if (cells[8] == EMPTY) return 8;
    }
    return INVALID_MOVE;
}

int get_random_move() {
    int options[9], count = 0;
    for (int i = 0; i < 9; i++) {
        if (cells[i] == EMPTY) options[count++] = i;
    }
    return count > 0 ? options[rand() % count] : INVALID_MOVE;
}

int get_best_move() {
    int move = get_winning_move(computer);
    if (move != INVALID_MOVE) return move;

    move = get_winning_move(human);
    if (move != INVALID_MOVE) return move;

    move = the_one_and_only(human);
    if (move != INVALID_MOVE) return move;

    if (cells[4] == EMPTY) return 4; // center

    int corners[] = {0,2,6,8};
    for (int i = 0; i < 4; i++) {
        if (cells[corners[i]] == EMPTY) return corners[i];
    }

    return get_random_move();
}

void player_turn() {
    int move;
    while (true) {
        printf("Enter your move (0-8): ");
        if (scanf("%d", &move) == 1 && move >= 0 && move <= 8 && cells[move] == EMPTY) break;
        printf("Invalid move. Try again.\n");
    }
    cells[move] = human;
}

void computer_turn() {
    int move = get_best_move();
    if (move != INVALID_MOVE) cells[move] = computer;
    printf("Computer played at position %d\n", move);
}

void play_game() {
    reset_board();
    char turn;
    printf("Do you want to go first? (y/n): ");
    scanf(" %c", &turn);
    bool human_first = (turn == 'y');

    print_board();
    for (int i = 0; i < 9; i++) {
        if ((i % 2 == 0) == human_first) {
            player_turn();
        } else {
            computer_turn();
        }
        print_board();

        if (check_winner(human)) {
            printf(GREEN "You win!\n" RESET);
            return;
        } else if (check_winner(computer)) {
            printf(RED "Computer wins!\n" RESET);
            return;
        } else if (is_draw()) {
            printf(YELLOW "It's a draw. So, you lose.\n" RESET);
            return;
        }
    }
}

int main() {
    srand(time(NULL));
    printf(CYAN "\n=== WELCOME TO ANIMESH'S CHALLENGE ===\n" RESET);
    printf("Beat the unbeatable Tic Tac Toe AI!\n");
    printf(YELLOW "⚠️  Draw = Loss. You win ONLY if you win.\n\n" RESET);

    while (1) {
        char choice;
        printf("Choose your symbol (x/o): ");
        scanf(" %c", &human);
        if (human == 'x' || human == 'o') {
            computer = (human == 'x') ? 'o' : 'x';
            play_game();
        } else {
            printf("Invalid symbol. Try again.\n");
            continue;
        }

        printf("Play again? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y') break;
    }

    return 0;
}