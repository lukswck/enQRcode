#include <iostream>
#include <vector>

#include "grid.h"
#include "vec.h"

// Defining global variables
const size_t klength {25}; 
// I will start with only version 2 (25x25 modules)
// in the future I can adapt for larger versions
constexpr char kWhite_symbol= 'x', kBlack_symbol =' ';

void print_line(size_t length, char symbol );
grid finder_pattern(size_t length);
void paste_on_grid(grid& LargeGrid, const grid& SmallGrid,
                size_t start_row, size_t start_col);
void paste_on_grid(grid& LargeGrid, const vec& Vec,
                size_t start_row, size_t start_col, 
                char orientation );
void write_on_board(grid& Board);
void print_board(const grid& Board);

int main(void)
{
    grid Board(klength);

    write_on_board(Board);

    print_board(Board);
}

void write_on_board(grid& Board){
    size_t length{Board.size()};

    // square modules in corners
    grid finder_square {finder_pattern(7)};
    paste_on_grid(Board, finder_square, 0, 0);
    paste_on_grid(Board, finder_square, 0, length-7);
    paste_on_grid(Board, finder_square, length-7, 0);
    grid align_square {finder_pattern(5)};
    paste_on_grid(Board, align_square, 16, 16);

    // timing pattern
    vec timing(9); 
    for (size_t i{0}; i<timing.size(); i+=2) {
        timing[i].flip();
    }

    paste_on_grid(Board, timing, 8, 6, 'v');
    paste_on_grid(Board, timing, 6, 8, 'h');
}

grid finder_pattern(size_t square_length) {
    grid square(square_length);

    square[0].flip();
    square[square_length-1].flip();

    switch (square_length){
    case 7:
        for (size_t i{1}; i<square_length-1;++i){
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
        for (size_t i{1}; i<square_length-1;++i){
            square[i][0].flip();
            square[i][square_length-1].flip();
        };
        square[2][2].flip();
        break;
    };

    return square;
}

void paste_on_grid(grid& LargeGrid, const grid& SmallGrid,
                size_t start_row, size_t start_col){
    size_t small_row_length{SmallGrid.size()};
    size_t small_col_length{SmallGrid.size()};
    for (size_t i{0};i < small_row_length; ++i){
        for (size_t j{0};j < small_col_length; ++j){
            LargeGrid[start_row + i][start_col + j] =
             SmallGrid[i][j];
        };
    };    
}

void paste_on_grid(grid& LargeGrid, const vec& Vec,
                size_t start_row, size_t start_col, 
                char orientation ) {
    size_t vec_length{Vec.size()};
    if (orientation=='v') {
    for (size_t i{0};i < vec_length; ++i){
            LargeGrid[start_row + i][start_col] =
             Vec[i];
    };    
    }
    else if (orientation=='h') {
    for (size_t j{0};j < vec_length; ++j){
            LargeGrid[start_row ][start_col + j] =
             Vec[j];
    };    
    }
}

void print_line(size_t box_length, char symbol = kWhite_symbol) {
    std::string line;
    line.reserve((box_length + 1) * 2 );

    for (size_t i = 0; i <= box_length + 1; ++i) {
        line += symbol; line += ' ';
    }
    std::cout << line << std::endl;
}

void print_board(const grid& Board){
    size_t box_length { Board[0].size()};

    // std::cout << std::string(box_length,'x') << '\n';
    print_line(box_length);
    for (size_t i = 0; i < Board.size(); ++i) {
        std::cout << kWhite_symbol << ' ';
        for (const bool value : Board[i]){    
            std::cout << (value?kBlack_symbol:kWhite_symbol) << ' ';
        }
    std::cout << kWhite_symbol<< '\n';
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