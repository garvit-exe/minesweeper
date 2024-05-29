#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Minefield
{
private:
    int r, c;                   // r,c - number of rows,columns
    int num_mines;              // total number of mines
    bool is_mine[128][128];     // true if mine is at (i,j), false otherwise
    bool is_swept[128][128];    // true if swept, false otherwise
    bool is_q_marked[128][128]; // true if q_marked, false otherwise
    bool is_flagged[128][128];  // true if flagged, false otherwise
    short number[128][128];     // stores total number of mines in the eight surrounding tiles
    char state[128][128];       // stores info which can be revealed to player
    bool loss;                  // becomes true when game is lost, false till then
    int num_swept = 0;          // holds number of swept tiles
    int num_flagged = 0;        // holds number of flags used
    // legend
    char flag_char = 'F';
    char q_mark_char = '?';
    char unswept_char = ' ';
    char swept_char = 'o';
    char mine_char = '*';

    void sweep_util(int i, int j, int s) // a utility function which just accepts a zero location and flood fills all the zeros
    {
        if (i < 0 || i >= r || j < 0 || j >= c)
        {
            return;
        }

        if (number[i][j] != 0)
        {
            return;
        }

        number[i][j] = s;         // changing the zeros to s (which helps us to identify the zeros which have opened)   s is purely a placeholder
        state[i][j] = swept_char; // changing the state array which is printed at the end
        sweep_util(i - 1, j, s);
        sweep_util(i + 1, j, s);
        sweep_util(i, j - 1, s);
        sweep_util(i, j + 1, s);
        sweep_util(i - 1, j - 1, s);
        sweep_util(i + 1, j + 1, s);
        sweep_util(i + 1, j - 1, s);
        sweep_util(i - 1, j + 1, s);
    }
    void set_field(int i_ex, int j_ex) // mutator
    {

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                number[i][j] = 0;
                is_mine[i][j] = false;
            }
        }

        for (int i = 0; i < num_mines;)
        {

            int l = rand() % r;
            int m = rand() % c;
            if (is_mine[l][m] == true || (l == i_ex && m == j_ex))
                continue;
            else
            {
                i++;
                is_mine[l][m] = true;
                number[l][m] = -1;

                if (l == 0 && m == 0) // checking top left corner
                {

                    number[1][0] += 1;

                    number[1][1] += 1;

                    number[0][1] += 1;
                }
                else if (l == 0 && m == c - 1) // checking top right corner
                {
                    number[0][c - 2] += 1;
                    number[1][c - 2] += 1;
                    number[1][c - 1] += 1;
                }
                else if (l == r - 1 && m == 0) // checking bottom left corner
                {
                    number[r - 2][0] += 1;
                    number[r - 2][1] += 1;
                    number[r - 1][1] += 1;
                }
                else if (l == r - 1 && m == c - 1) // checking bottom right corner
                {
                    number[r - 1][c - 2] += 1;
                    number[r - 2][c - 2] += 1;
                    number[r - 2][c - 1] += 1;
                }
                else if (l == 0) // checking upper boundary tiles
                {
                    number[l][m - 1] += 1;
                    number[l][m + 1] += 1;
                    number[l + 1][m - 1] += 1;
                    number[l + 1][m] += 1;
                    number[l + 1][m + 1] += 1;
                }
                else if (m == 0) // checking left boundary tiles
                {
                    number[l - 1][m] += 1;
                    number[l - 1][m + 1] += 1;
                    number[l][m + 1] += 1;
                    number[l + 1][m] += 1;
                    number[l + 1][m + 1] += 1;
                }
                else if (m == c - 1) // checking right boundary tiles
                {
                    number[l - 1][m - 1] += 1;
                    number[l - 1][m] += 1;
                    number[l][m - 1] += 1;
                    number[l + 1][m - 1] += 1;
                    number[l + 1][m] += 1;
                }
                else if (l == r - 1) // checking lower boundary tiles
                {
                    number[l - 1][m - 1] += 1;
                    number[l - 1][m] += 1;
                    number[l - 1][m + 1] += 1;
                    number[l][m - 1] += 1;
                    number[l][m + 1] += 1;
                }
                else
                {
                    number[l - 1][m - 1] += 1;
                    number[l - 1][m] += 1;
                    number[l - 1][m + 1] += 1;
                    number[l][m - 1] += 1;
                    number[l][m + 1] += 1;
                    number[l + 1][m - 1] += 1;
                    number[l + 1][m] += 1;
                    number[l + 1][m + 1] += 1;
                }
            }
        }

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (is_mine[i][j] == true)
                {
                    number[i][j] = -1;
                }
            }
        }
    }

public:
    Minefield(int rows, int cols, int num, int i_ex, int j_ex) // constructor
    {
        r = rows;
        c = cols;
        num_mines = num;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                state[i][j] = unswept_char;
        }
        set_field(i_ex, j_ex);
    }

    void flag(int i, int j) // mutator
    {
        if (!is_swept[i][j])
        {
            clear(i, j);
            num_flagged += 1;
            is_flagged[i][j] = true;
            state[i][j] = flag_char;
        }
    }
    void q_mark(int i, int j) // mutator
    {
        if (!is_swept[i][j])
        {
            clear(i, j);
            is_q_marked[i][j] = true;
            state[i][j] = q_mark_char;
        }
    }
    void clear(int i, int j) // mutator
    {

        if (is_flagged[i][j])
        {
            is_flagged[i][j] = false;
            num_flagged -= 1;
            state[i][j] = unswept_char;
        }
        if (is_q_marked[i][j])
        {
            is_q_marked[i][j] = false;
            state[i][j] = unswept_char;
        }
    }
    void sweep_from(int i, int j) // the main function which tackles all inputs of position (which are not visited) other that flag and question mark
                                  // assuming that flag and question mark functions are called before hand only and the given position cannot have those two.
    {

        if (is_mine[i][j])
        {
            clear(i, j);
            state[i][j] = mine_char;
            loss = true;
            num_swept++;
            return;
        }
        // bomb tackled
        //  now handling numbers
        int s = -9; // placeholder

        if (number[i][j] != 0 && number[i][j] != s)
        {
            if (state[i][j] == flag_char || state[i][j] == q_mark_char)
                clear(i, j);

            state[i][j] = (char)(48 + number[i][j]);
            num_swept++;
            return;
        }

        // now handling only remaining case i.e. 0
        sweep_util(i, j, s); // this will only flood fill zeroes

        int l, m;

        num_swept = 0; // making num_swept zero becasue i will be counting it again
        // now adding boundary elements of zero flood by checking neighbours of each element. If the neighbouring element is found to be s i.e. visited zero, it's neighbor must be visible
        for (l = 0; l < r; l++)
        {
            for (m = 0; m < c; m++)
            {
                bool is_tile_flagged = false;
                bool is_tile_q_mark = false;
                if (state[l][m] == flag_char)
                    is_tile_flagged = true;
                if (state[l][m] == q_mark_char)
                    is_tile_q_mark - true;
                if (l == 0 && m == 0) // checking top left corner
                {
                    if ((number[1][0] == s || number[1][1] == s || number[0][1] == s) && number[0][0] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (l == 0 && m == c - 1) // checking top right corner
                {
                    if ((number[0][c - 2] == s || number[1][c - 2] == s || number[1][c - 1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (l == r - 1 && m == 0) // checking bottom left corner
                {
                    if ((number[r - 2][0] == s || number[r - 2][1] == s || number[r - 1][1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (l == r - 1 && m == c - 1) // checking bottom right corner
                {
                    if ((number[r - 1][c - 2] == s || number[r - 2][c - 2] == s || number[r - 2][c - 1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (l == 0) // checking upper boundary tiles
                {
                    if ((number[l][m - 1] == s || number[l][m + 1] == s || number[l + 1][m - 1] == s || number[l + 1][m] == s || number[l + 1][m + 1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (m == 0) // checking left boundary tiles
                {
                    if ((number[l - 1][m] == s || number[l - 1][m + 1] == s || number[l][m + 1] == s || number[l + 1][m] == s || number[l + 1][m + 1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (m == c - 1) // checking right boundary tiles
                {
                    if ((number[l - 1][m - 1] == s || number[l - 1][m] == s || number[l][m - 1] == s || number[l + 1][m - 1] == s || number[l + 1][m] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if (l == r - 1) // checking lower boundary tiles
                {
                    if ((number[l - 1][m - 1] == s || number[l - 1][m] == s || number[l - 1][m + 1] == s || number[l][m - 1] == s || number[l][m + 1] == s) && number[l][m] != s)
                    {

                        state[l][m] = (char)(48 + number[l][m]);
                    }
                }
                else if ((number[l - 1][m - 1] == s || number[l - 1][m] == s || number[l - 1][m + 1] == s || number[l][m - 1] == s || number[l][m + 1] == s || number[l + 1][m - 1] == s || number[l + 1][m] == s || number[l + 1][m + 1] == s) && number[l][m] != s)
                {

                    state[l][m] = (char)(48 + number[l][m]);
                }

                if (state[l][m] != unswept_char && state[l][m] != q_mark_char && state[l][m] != flag_char)
                    num_swept++;

                if (is_tile_flagged && state[l][m] != flag_char || is_tile_q_mark && state[l][m] != q_mark_char)
                {
                    clear(l, m);

                    if (number[l][m] == s)
                        state[l][m] = swept_char;
                    else
                        state[l][m] = (char)(48 + number[l][m]);
                }

            } // closing m loop
        } // closing l loop
    } // closed void sweep_from function

    bool check_win() // accessor
    {
        if (num_swept + num_mines == r * c)
            return true;
        else
            return false;
    }
    bool check_loss() // accessor
    {
        return loss;
    }
    char get_state_of(int i, int j) // accessor
    {
        return state[i][j];
    }
    int get_num_flags() // accessor
    {
        return num_flagged;
    }
    int get_num_rows() // accessor
    {
        return r;
    }
    int get_num_cols() // accessor
    {
        return c;
    }
    int get_num_swept()
    {
        return num_swept;
    }

    int get_num_of(int i, int j) { return number[i][j]; }
};

void clear()
{
    cout << "\033[2J\033[1;1H";
}
void print(Minefield m)
{
    int r = m.get_num_rows();
    int c = m.get_num_cols();
    cout << "\n";
    for (int i = 0; i < r; i++)
    {
        if (i == 0)
        {
            cout << "       ";
            for (int x = 0; x < c; x++)
            {
                if (x < 10)
                    cout << x << "   ";
                else
                    cout << x << "  ";
            }
            cout << "\n";
        }
        // if(i<10) cout<<"  "<<i<<" ";
        // else cout<<" "<<i<<" ";
        cout << "     ";
        for (int j = 0; j < c; j++)
        {
            cout << "+---";
        }
        cout << '+' << endl;
        if (i < 10)
            cout << "   " << i << " | ";
        else
            cout << "  " << i << " | ";

        // cout<<"    | ";
        for (int j = 0; j < c; j++)
        {
            cout << m.get_state_of(i, j) << " | ";
        }
        cout << "             ";
        for (int j = 0; j < c; j++)
        {
            if (m.get_num_of(i, j) >= 0)
                cout << " ";
            cout << m.get_num_of(i, j) << " ";
        }
        cout << endl;
        if (i == r - 1)
            cout << "   ";
    }
    cout << "  ";
    for (int j = 0; j < c; j++)
    {
        cout << "+---";
    }
    cout << "+";
}
int main()
{
    clear();
    char dummy;
    cout << "choose dimensions:\n";
    int r, c;
    cin >> r;
    cin >> c;
    cout << "\nchoose initial co-ordinates\n";
    int i, j;
    cin >> i;
    cin >> j;
    // determine number of mines
    Minefield m = Minefield(r, c, (r + c), i, j);
    cin >> dummy;

    char input;
    do
    {
        clear();
        print(m);
        cout << endl;
        cout << "Number of tiles swept = " << m.get_num_swept() << endl;
        cout << "Number of flags = " << m.get_num_flags() << endl;
        cout << '\n';
        cin >> input;
        if (input == 'e')
            break;
        cin >> i >> j;
        if (input == 'f')
            m.flag(i, j);
        else if (input == 'q')
            m.q_mark(i, j);
        else if (input == 's')
            m.sweep_from(i, j);
        else if (input == 'c')
            m.clear(i, j);
    } while (true);

    clear();
    cout << "End of test";
    cin >> dummy;
    return 0;
}

// Developed by Garvit Budhiraja