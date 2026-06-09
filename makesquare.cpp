#include <iostream>
#include <vector>

typedef std::vector<bool> vec;
typedef std::vector<std::vector<bool>> grid;

class gridclass {
public:
gridclass(){}
gridclass(int length){
    mlength = length;
    EmptyGrid();
}
void SetLength(int length){
    mlength = length;
    EmptyGrid();
}
std::vector<std::vector<bool>> GetBody(){
    return body;
}

private:
int mlength{0};
std::vector<std::vector<bool>> body;

void EmptyGrid(){
    body.resize(mlength, std::vector<bool>(mlength));
    for (int i{0}; i<mlength; ++i){
        for (int j{0}; j<mlength; ++j){
            body[j][i] = 0;
        };
    };
}

};

const int klength {25}; 
// I will start with only version 2 (25x25 modules)
// in the future I can adapt for larger versions
constexpr char kWhite_symbol= '#', kBlack_symbol =' ';

void write_on_board(grid& Board, int length);
void print_line(int length, char symbol );
grid finder_pattern(int length);
void paste_on_grid(grid& LargeGrid, const grid& SmallGrid,
                size_t start_row, size_t start_col);

void print_board(const grid& Board);

int main(void)
{
    grid Board;

    write_on_board(Board, klength);

    print_board(Board);
}

void write_on_board(grid& Board, int length){
    Board.resize(length, std::vector<bool>(length));
    for (int i{0}; i<length; ++i){
        for (int j{0}; j<length; ++j){
            Board[j][i] = 0;
        };
    };
    // square modules in corners
    grid finder_square {finder_pattern(7)};
    paste_on_grid(Board, finder_square, 0, 0);
    paste_on_grid(Board, finder_square, 0, length-7);
    paste_on_grid(Board, finder_square, length-7, 0);
    grid align_square {finder_pattern(5)};
    paste_on_grid(Board, align_square, 16, 16);

    // timing pattern
    vec timing {};
    timing.resize(9); 
    
}

grid finder_pattern(int square_length) {
    grid square{};

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

void paste_on_grid(grid& LargeGrid, const grid& SmallGrid,
                size_t start_row, size_t start_col){
    size_t small_row_length{SmallGrid.size()};
    size_t small_col_length{SmallGrid.size()};
    for (int i{0};i < small_row_length; ++i){
        for (int j{0};j < small_col_length; ++j){
            LargeGrid[start_row + i][start_col + j] =
             SmallGrid[i][j];
        };
    };    
}

void print_line(int box_length, char symbol = kWhite_symbol) {
    std::string line;
    line.reserve((box_length + 1) * 2 );

    for (int i = 0; i <= box_length + 1; ++i) {
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