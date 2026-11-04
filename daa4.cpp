#include <iostream>
using namespace std;

int board[20][20];
int n;

bool isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;
    }

    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

bool solveNQueens(int row)
{
    if (row == n)
        return true;

    for (int col = 0; col < n; col++)
    {
        if (board[row][col] == 1)
            return solveNQueens(row + 1);
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col))
        {
            board[row][col] = 1;

            if (solveNQueens(row + 1))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    int r, c;

    cout << "Enter value of N: ";
    cin >> n;

    cout << "Enter row and column of first Queen (1-based): ";
    cin >> r >> c;

    if (n < 1 || n > 20 ||
        r < 1 || r > n || c < 1 || c > n)
    {
        cout << "Invalid input\n";
        return 0;
    }

    board[r - 1][c - 1] = 1;

    if (solveNQueens(0))
    {
        cout << "\nFinal N-Queens Matrix:\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    else
    {
        cout << "No solution exists for this first Queen position.\n";
    }

    return 0;
}
