#include <iostream>


using namespace std;
int arr[9][9] = {{0, 0, 2, 9, 8, 0, 5, 0, 0},
                 {4, 0, 0, 0, 7, 0, 0, 1, 3},
                 {0, 3, 9, 6, 0, 4, 0, 7, 0},
                 {2, 0, 0, 0, 5, 6, 4, 0, 0},
                 {8, 4, 0, 3, 0, 0, 2, 0, 1},
                 {9, 0, 7, 0, 0, 1, 0, 8, 6},
                 {6, 0, 0, 7, 0, 5, 1, 3, 0},
                 {0, 9, 1, 4, 0, 0, 0, 0, 5},
                 {0, 2, 0, 0, 3, 0, 6, 0, 8}};

void read_data()  //to read the game data
{
    for (int i = 0; i < 9; i++) {
        cout << "enter row number " << i + 1 << "  :  ";
        for (int j = 0; j < 9; j++)
            cin >> arr[i][j];
    }
}

void print_data() //print the array
{
    int x = 0;
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0)
            while (x < 21) {
                cout << " - ";
                x++;
            }
        cout << endl;
        x = 0;
        cout << "###############";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) cout << " | ";
            cout << " " << arr[i][j] << " ";
        }
        cout << "###############";
        cout << endl;
    }
}

bool col_Search(int number, int index)  //search if number exist in the col
{
    for (int i = 0; i < 9; i++) { if (arr[i][index] == number) return true; }
    return false;
}

bool row_search(int number, int index)  //search if number exist in the row
{
    for (int i = 0; i < 9; i++) { if (arr[index][i] == number) return true; }
    return false;
}

bool block_search(int number, int row, int col) //search if number exist in the block
{
    int i = row - (row % 3);
    int j = col - (col % 3);
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (arr[i][j] == number) return true;
            j++;
        }
        i++;
        j = j - 3;
    }
    return false;
}

//check the game
bool col_Search_check(int number, int index) {
    int flag = 0;
    for (int i = 0; i < 9; i++) {
        if (arr[i][index] == 0) {}
        else if (arr[i][index] == number) flag++;
    }
    return flag > 1;
}

bool row_search_check(int number, int index) {
    int flag = 0;
    for (int i = 0; i < 9; i++) {
        if (arr[index][i] == 0) {}
        else if (arr[index][i] == number) flag++;
    }
    return flag > 1;
}

bool block_search_check(int number, int row, int col) {
    int flag = 0;
    int i = row - (row % 3);
    int j = col - (col % 3);
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (arr[i][j] == 0) {}
            else if (arr[i][j] == number) flag++;
            j++;
        }
        i++;
        j = j - 3;
    }
    return flag > 1;
}

bool check_game() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            if (block_search_check(arr[i][j], i, j)) return true;
            if (row_search_check(arr[i][j], i)) return true;
            if (col_Search_check(arr[i][j], j)) return true;
        }
    return false;
}

bool stillzero() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (arr[i][j] == 0) return true;
    return false;
}

//----------------------------------------------------------------------------
//answer functions
//technique 1
void block_solver(int startRow, int startCol) {
    int number = 1;
    int answerFlag;
    int answerRow;
    int answerCol;
    int i = startRow;
    int j = startCol;
    int endRow = startRow + 2;
    int endCol = startCol + 2;
    if (!block_search(0, startRow, startCol)) return;
    while (number < 10) {
        if (block_search(number, startRow, startCol)) number++;
        else {
            i = startRow;
            j = startCol;
            answerFlag = 0;
            while (i <= endRow) {
                if (arr[i][j] == 0) {
                    if (col_Search(number, j) || row_search(number, i)) {}
                    else {
                        answerFlag++;
                        answerCol = j;
                        answerRow = i;
                    }
                }
                if (j == endCol) {
                    j = startCol;
                    i++;
                }
                else j++;
            }
            if (answerFlag == 1) {
                arr[answerRow][answerCol] = number;
                number = 1;
            }
            else { number++; }
        }
    }
}

//**************************************************************************************
bool matrixWay(int i, int j) {
    if (i == 8 && j == 9) return true;
    if (check_game()) return false;
    if (!stillzero()) return true;
    if (j > 8) {
        i++;
        j = 0;
    }
    int y = j;
    for (int x = i; x < 9; x++) {
        for (; y < 9; y++) {
            if (arr[x][y] == 0) {
                int number = 1;
                while (1) {
                    if (number == 10) {
                        arr[x][y] = 0;
                        return false;
                    }
                    if (!col_Search(number, y) && !row_search(number, x) && !block_search(number, x, y)) {
                        arr[x][y] = number;
                        if (matrixWay(x, y + 1)) return true;
                    }
                    number++;
                }
            }
        }
        y = 0;
    }
}

//*****************************************************************************
//by using first technique
int main1() {
    int counter = 0;
    read_data();
    if (check_game()) cout << "you entered some wrong data !! :/\n";
    else {
        print_data();
        while (stillzero()) {
            if (counter > 81) break;
            for (int i = 0; i < 9; i += 3)
                for (int j = 0; j < 9; j += 3)
                    block_solver(i, j);
            counter++;
        }
        if (counter > 81) {
            cout << "cann't answer this one ! :/\n";
            print_data();
        } else {
            cout << "****************************************************************\n";
            cout << "********************** the answer is ***************************\n";
            cout << "****************************************************************\n";
            print_data();
        }
    }
}

//using second technique pro One B|
int main() {
//    read_data();
    print_data();
    if (check_game()) cout << "you entered some wrong data !! :/\n";
    else {
        matrixWay(0, 0);
        cout << "\n\n****************************************************************\n";
        cout << "********************** the answer is ***************************\n";
        cout << "****************************************************************\n";
        print_data();
        cout << "****************************************************************\n";
        cout << "game solved B| ";
    }
}