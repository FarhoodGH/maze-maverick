// Developers: @FatemehHasani & @FarhoodGhanbari

#include <iostream>
#include <fstream> //کار با فایل
#include <string>
#include <cstdlib> //تولید اعداد رندم
#include <ncurses.h> //امکان تغییر رنگ و اندازه متن در ترمینال
#include <vector> 
#include <sstream> //استفاده از stringstream
using namespace std;

void upload_maze(const string& matrixName)
{
    int rows, columns;
    
    cout << "Enter the number of rows in the maze: ";
    cin >> rows;

    cout << "Enter the number of columns in the maze: ";
    cin >> columns;

    cout << "Enter the matrix elements: " << endl;

    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) 
    {
        matrix[i] = new int[columns];
        for (int j = 0; j < columns; ++j) 
        {
            cin >> matrix[i][j];
        }
    }

    ofstream file;
    file.open("Maps.txt", ios ::app);
    file << matrixName << endl;
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file << endl;

    for (int i = 0; i < rows; ++i) 
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    file.close();
}
void printMatrixFromFile(vector<vector<int>>& maze , const string& matrixName) 
{
    ifstream file("Maps.txt");
    string line;
    bool matrixFound = false;

    while (getline(file, line)) 
    {
        if (line == matrixName) 
        {
            matrixFound = true;
            break;
        }
    }
    if(matrixFound)
    {
        while (getline(file, line))
        {
            vector<int> row;
            istringstream iss(line);//تعداد مشخصی از کاراکتر ها رو دریافت میکنه
            int element;
            while (iss >> element)
            {
                row.push_back(element);
            }
            maze.push_back(row);
        }
    }
    else
    {
        cout << "\nMatrix not found!\n" << endl;
    }

    file.close();
}
void generateMaze(vector<vector<int>>& maze, int rows, int cols) 
{
    maze = vector<vector<int>>(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            int randomNumber = rand() % 7 - 3;  // تولید عدد رندم از -3 تا 3
            maze[i][j] = randomNumber;
        }
    }

    maze[rows - 1][cols - 1] = 1 ; // جهت راحتی کار
}

void drawMazeWithoutPlayer(const vector<vector<int>>& maze) 
{
    for (int i = 0; i < maze.size(); i++) 
    {
        for (int j = 0; j < maze[i].size(); j++) 
        {
            if (maze[i][j] == 0) 
            {
                attron(COLOR_PAIR(1));  // تبدیل به رنگ قرمز
                mvaddch(i, j * 2, '0');  // قرار دادن صفر بعنوان مانع
                attroff(COLOR_PAIR(1));  // اتمام تغییر رنگ
            } 
            else 
            {
                attron(COLOR_PAIR(2));  // تبدیل به رنگ سبز
                mvprintw(i, j * 2, "%2d", maze[i][j]);  // چاپ maze
                attroff(COLOR_PAIR(2));  // اتمام تغییر رنگ
            }
        }
    }
    refresh();  // پاک کردن صفحه
}
void drawMaze(vector<vector<int>>& maze, int playerRow, int playerCol) 
{
    for (int i = 0; i < maze.size(); i++) 
    {
        for (int j = 0; j < maze[i].size(); j++) 
        {
            if (i == playerRow && j == playerCol) 
            {
                attron(COLOR_PAIR(3));  // تغییر رنگ به آبی
                mvaddch(i, j * 2, 'P');  // نشان دادن جایگاه بازیکن با p
                attroff(COLOR_PAIR(3));  // اتمام تغییر رنگ
            } 
            else 
            {
                if (maze[i][j] == 0) 
                {
                    attron(COLOR_PAIR(1));  // تفییر رنگ به قرمز
                    mvaddch(i, j * 2, '0');  // قرار دادن صفر بعنوان مانع
                    attroff(COLOR_PAIR(1));  // اتمام تغییر رنگ
                } else {
                    attron(COLOR_PAIR(2));  // تغییر رنگ به سبز
                    mvprintw(i, j * 2, "%2d", maze[i][j]);  // چاپ maze
                    attroff(COLOR_PAIR(2));  // اتمام تغییر رنگ
                }
            }
        }
    }
    refresh();  
}

int main()
{
    int a = 0;
    while(a == 0)
    {
    cout << "menu :\n" << "*Create a New Map :\n" << "1 : Easy\n" << "2 : Hard\n" << "3 : Exit\n";
    cout << "Select the desired level :\n";
    int level;
    cin >> level;
    switch (level)
    {
        case 1 :
        cout << "Let's go to the next step!\n";
        break;
        case 2 :
        cout << "Not available at the moment!";
        exit(0);
        break;
        case 3:
        exit(0);
        break;
    }
    
    
    cout << "\n**Playground" << "\n" << "1 : Choose from Existing Maps\n"  << "2 : Exit\n";
    cout << "\nEnter the number of your choice :";
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
        break;
        case 2:
        exit(0);
        break;
    }
    
    cout << "\n***Solve a Maze:\n" << "1 : Choose from Existing Maps\n" << "2 : Import a Custom Map\n" << "3 : Exit\n";
    cout << "Enter the number of your choice :" << endl;
    int choice_2;
    cin >> choice_2;
    switch (choice_2)
    {
        case 1 :
        {
            initscr();  
            start_color();  // شروع تغببر رنگ
            init_pair(1, COLOR_RED, COLOR_BLACK);  
            init_pair(2, COLOR_GREEN, COLOR_BLACK);
            init_pair(3, COLOR_BLUE, COLOR_BLACK);  

            int rows, cols;
            cout << "Enter the number of rows in the maze:\n";
            cin >> rows;
            cout << "Enter the number of columns in the maze:\n";
            cin >> cols;
            
            vector<vector<int>> maze;
            generateMaze(maze, rows, cols);

            int playerRow = 0;  
            int playerCol = 0;
            int moveCount = 0;
            int moveLimit = rows + cols - 2;
            int sumOfNumbers = maze[0][0];  

            char input;

            while (true) 
            {
                clear(); 
                drawMazeWithoutPlayer(maze);
                drawMaze(maze, playerRow, playerCol);
                if (playerRow == rows - 1 && playerCol == cols - 1) 
                {
                    maze[rows - 1][cols - 1] = sumOfNumbers;
                    clear();
                    drawMaze(maze, playerRow, playerCol);
                    cout << endl << "Congratulations! You won the game!" << endl;
                    cout << "The value of the last maze block is " << sumOfNumbers - 1 << endl;
                    refresh();
                    break;
                }
                if (moveCount >= moveLimit) 
                {
                    cout << endl << "You've reached the move limit. Game over!" << endl;
                    break;
                }
                input = getch();  // ورودی گرفتن از کاربر
                switch (input) 
                {
                    case 'w':
                        if (playerRow > 0) 
                        {
                            sumOfNumbers += maze[playerRow - 1][playerCol];  
                            if (maze[playerRow - 1][playerCol] != 0) 
                            {
                                playerRow--;
                                moveCount++;
                            }
                        }
                        break;
                    case 's':
                        if (playerRow < rows - 1) 
                        {
                            sumOfNumbers += maze[playerRow + 1][playerCol];  
                            if (maze[playerRow + 1][playerCol] != 0) 
                            {
                                playerRow++;
                                moveCount++;
                            }
                        }
                        break;
                    case 'a':
                        if (playerCol > 0) 
                        {
                            sumOfNumbers += maze[playerRow][playerCol - 1];  
                            if (maze[playerRow][playerCol - 1] != 0) 
                            {
                                playerCol--;
                                moveCount++;
                            }
                        }
                        break;
                    case 'd':
                        if (playerCol < cols - 1) 
                        {
                            sumOfNumbers += maze[playerRow][playerCol + 1];  
                            if (maze[playerRow][playerCol + 1] != 0) 
                            {
                                playerCol++;
                                moveCount++;
                            }
                        }
                        break;
                }
            }
        }
        break;
        case 2 :
        {
            cout << "Enter your desired name :\n";
            string Name;
            cin >> Name;
            upload_maze(Name);
            cout << "\nYour maze has been loaded!\n";
            vector<vector<int>> maze;
            printMatrixFromFile(maze , Name);
            initscr();  
            start_color();  
            init_pair(1, COLOR_RED, COLOR_BLACK);  
            init_pair(2, COLOR_GREEN, COLOR_BLACK);   
            init_pair(3, COLOR_BLUE, COLOR_BLACK);  

            int rows, cols;
            printw("Enter the number of rows in the maze: ");
            scanw("%d", &rows);
            printw("Enter the number of columns in the maze: ");
            scanw("%d", &cols);
            
            
            int playerRow = 0;  
            int playerCol = 0;
            int moveCount = 0;
            int moveLimit = rows + cols - 2;
            int sumOfNumbers = maze[0][0];  

            char input;
            while (true) 
            {
                clear();  
                drawMazeWithoutPlayer(maze);
                drawMaze(maze, playerRow, playerCol);
                if (playerRow == rows - 1 && playerCol == cols - 1) 
                {
                    maze[rows - 1][cols - 1] = sumOfNumbers;
                    clear();
                    drawMaze(maze, playerRow, playerCol);
                    cout << endl << "Congratulations! You won the game!" << endl;
                    cout << "The value of the last maze block is " << sumOfNumbers - 1 << endl;
                    refresh();
                    break;
                }
                if (moveCount >= moveLimit) 
                {
                    cout << endl << "You've reached the move limit. Game over!" << endl;
                    break;
                }
                input = getch();  
                switch (input) 
                {
                    case 'w':
                        if (playerRow > 0) 
                        {
                            sumOfNumbers += maze[playerRow - 1][playerCol];  
                            if (maze[playerRow - 1][playerCol] != 0) 
                            {
                                playerRow--;
                                moveCount++;
                            }
                        }
                        break;
                    case 's':
                        if (playerRow < rows - 1) 
                        {
                            sumOfNumbers += maze[playerRow + 1][playerCol]; 
                            if (maze[playerRow + 1][playerCol] != 0) 
                            {
                                playerRow++;
                                moveCount++;
                            }
                        }
                        break;
                    case 'a':
                        if (playerCol > 0) 
                        {
                            sumOfNumbers += maze[playerRow][playerCol - 1];  
                            if (maze[playerRow][playerCol - 1] != 0) 
                            {
                                playerCol--;
                                moveCount++;
                            }
                        }
                        break;
                    case 'd':
                        if (playerCol < cols - 1) 
                        {
                            sumOfNumbers += maze[playerRow][playerCol + 1]; 
                            if (maze[playerRow][playerCol + 1] != 0) 
                            {
                                playerCol++;
                                moveCount++;
                            }
                        }
                        break;
                }
            }
        }
        
        break;
        case 3 :
        exit(0);
        break;
    }
    cout << "\nDo you want to play again? \n" << "1 : Yes\n" << "2 : No\n";
    int choice_3;
    cout << "\nEnter the number of your choice :\n";
    cin >> choice_3;
    switch (choice_3)
    {
        case 1 :
        a = 0;
        break;
        case 2 :
        exit(0);
        break;
    }
    }
    return 0;
    }
