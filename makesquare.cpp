#include <iostream>
#include <vector>

typedef std::vector<std::vector<bool>> Grid;

const int length {25}; //version 2 type (25x25)
char white_symbol= '#', black_symbol =' ';
Grid Board;

void write_on_board(Grid& Board, int length);
void print_line(int length, char symbol );
Grid square_module(int length);
void past_grid(Grid& LargeGrid, const Grid& SmallGrid,
                size_t start_row, size_t start_col);

void print_board(const Grid& Board);

int main(void)
{
    write_on_board(Board, length);
    Board[5][6] = 1;
    print_board(Board);
}

void write_on_board(Grid& Board, int length){
    Board.resize(length, std::vector<bool>(length));
    for (int i{0}; i<length; ++i){
        for (int j{0}; j<length; ++j){
            Board[j][i] = 0;
        };
    };
    // square modules in corners
    Grid square {square_module(7)};
    past_grid(Board, square, 0, 0);
    past_grid(Board, square, 0, length-7);
    past_grid(Board, square, length-7, 0);
    Grid align_square {square_module(5)};
    past_grid(Board, align_square, 16, 16);

    // 
}

Grid square_module(int square_length) {
    Grid square{};

    square.resize(square_length,std::vector<bool>(square_length));
    square[0].flip();
    square[square_length-1].flip();

    switch (square_length){
    case 7:
        for (int i{1}; i<square_length-1;++i){
            square[i][0].flip();
            square[i][square_length-1].flip();
        };
        for (int row: {2,3,4}){
            for (int col: {2,3,4}){
                square[row][col].flip();
            };
        };
        break;
    case 5:
        for (int i{1}; i<square_length-1;++i){
            square[i][0].flip();
            square[i][square_length-1].flip();
        };
        square[2][2].flip();
        break;
    };

    return square;
}

void past_grid(Grid& LargeGrid, const Grid& SmallGrid,
                size_t start_row, size_t start_col){
    size_t small_lenth{SmallGrid.size()};
    for (int i{0};i < small_lenth; ++i){
        for (int j{0};j < small_lenth; ++j){
            LargeGrid[start_row + i][start_col + j] = SmallGrid[i][j];
        };
    };    
}

void print_line(int box_length, char symbol = white_symbol) {
    for (int i = 0; i <= box_length; ++i) std::cout << symbol << ' ';
    std::cout << symbol << std::endl;
}

void print_board(const Grid& Board){
    size_t box_length { Board[0].size()};

    // std::cout << std::string(box_length,'x') << '\n';
    print_line(box_length);
    for (size_t i = 0; i < Board.size(); ++i) {
        std::cout << white_symbol << ' ';
        for (const bool value : Board[i]){    
            std::cout << (value?black_symbol:white_symbol) << ' ';
        }
    std::cout << white_symbol<< '\n';
    };
    // std::cout << std::string(box_length*2+3,'x') << std::endl;
    print_line(box_length);
    std::cout << '\n';
}

// std::cout << '-' << std::string(2*length+2, '-') << '\n';
// for (int i = 0; i < length; ++i)
// {
//     std::cout << "| ";
//     for (int j = 0; j < length; ++j)
//     {
//         if (array[i][j]==1)
//         std::cout << '*' << ' ';
//         else
//         std::cout << ' ' << ' ';
//     }
//     std::cout << "|\n";
// }
// std::cout << '-' << std::string(2*length+2, '-') << '\n';
// std::cout << std::endl;