#include <iostream>
using namespace std;

const int SIZE = 8;

void printBoard(bool board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << (board[i][j] ? " X " : " . ");
        }
        cout << endl;
    }
}

void resetBoard(bool board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = false;
}

void torre(int x, int y, bool board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        board[x][i] = true; // linha
        board[i][y] = true; // coluna
    }
    board[x][y] = false; // posição inicial não conta como destino
}

void bispo(int x, int y, bool board[SIZE][SIZE]) {
    for (int i = -SIZE; i < SIZE; i++) {
        if (x+i >= 0 && x+i < SIZE && y+i >= 0 && y+i < SIZE)
            board[x+i][y+i] = true;
        if (x+i >= 0 && x+i < SIZE && y-i >= 0 && y-i < SIZE)
            board[x+i][y-i] = true;
    }
    board[x][y] = false;
}

void rainha(int x, int y, bool board[SIZE][SIZE]) {
    torre(x, y, board);
    bool bispoBoard[SIZE][SIZE];
    resetBoard(bispoBoard);
    bispo(x, y, bispoBoard);

    // combinar com OR lógico
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = board[i][j] || bispoBoard[i][j];
}

void cavalo(int x, int y, bool board[SIZE][SIZE]) {
    int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[] = {1, 2,  2,  1, -1, -2, -2, -1};

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
            board[nx][ny] = true;
    }
}

// Exemplo com recursão simples: visitar casas em linha reta
void torreRecursiva(int x, int y, bool board[SIZE][SIZE], int dx, int dy) {
    int nx = x + dx;
    int ny = y + dy;
    if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
        board[nx][ny] = true;
        torreRecursiva(nx, ny, board, dx, dy);
    }
}

int main() {
    bool board[SIZE][SIZE];
    int x, y, opcao;

    cout << "Digite a posição inicial da peça (linha [0-7] e coluna [0-7]): ";
    cin >> x >> y;

    cout << "\nEscolha a peça:\n";
    cout << "1 - Torre\n2 - Bispo\n3 - Rainha\n4 - Cavalo\n5 - Torre Recursiva\n> ";
    cin >> opcao;

    resetBoard(board);

    switch (opcao) {
        case 1:
            torre(x, y, board);
            break;
        case 2:
            bispo(x, y, board);
            break;
        case 3:
            rainha(x, y, board);
            break;
        case 4:
            cavalo(x, y, board);
            break;
        case 5:
            torreRecursiva(x, y, board, 0, 1);  // direita
            torreRecursiva(x, y, board, 1, 0);  // abaixo
            torreRecursiva(x, y, board, 0, -1); // esquerda
            torreRecursiva(x, y, board, -1, 0); // acima
            break;
        default:
            cout << "Opção inválida!\n";
            return 1;
    }

    cout << "\nMovimentos possíveis (X = possível, . = vazio):\n";
    printBoard(board);

    return 0;
}
