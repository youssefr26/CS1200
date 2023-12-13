#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//prototypes


bool in_bounds(int row, int col, const int total_rows, const int total_cols) {
    //checks if the row and col are in bounds
    return (row >= 0 && row < total_rows && col >= 0 && col < total_cols);
}

bool word_fits(const string& word, vector<vector<char>>& board, int row, int col, int direction,
 const int total_rows, const int total_cols, bool filling) {
    int len = word.size();
    for (int i = 0; i < len; ++i) {
        if(filling == true){
            if (!in_bounds(row, col, total_rows, total_cols) || (board[row][col] != ' ' && board[row][col] != word[i])) {
                return false;
            }
        }else{
            if (!in_bounds(row, col, total_rows, total_cols) || board[row][col] != word[i]) {
                return false;
            }
        }

        // Change row and col based on the direction
        if (direction == 0) {
            row -= 1; // Up
        } else if (direction == 1) {
            row -= 1; // Diagonal Up-Right
            col += 1;
        } else if (direction == 2) {
            col += 1; // Right
        } else if (direction == 3) {
            row += 1; // Diagonal Down-Right
            col += 1;
        } else if (direction == 4) {
            row += 1; // Down
        } else if (direction == 5) {
            row += 1; // Diagonal Down-Left
            col -= 1;
        } else if (direction == 6) {
            col -= 1; // Left
        } else if (direction == 7) {
            row -= 1; // Diagonal Up-Left
            col -= 1;
        }
    }
    return true;
}

void add_word(const string& word, vector<vector<char>>& board, int row, int col, int direction) {
    int len = word.size();
    for (int i = 0; i < len; ++i) {
        board[row][col] = word[i];

        // Change row and col based on the direction
        if (direction == 0) {
            row -= 1; // Up
        } else if (direction == 1) {
            row -= 1; // Diagonal Up-Right
            col += 1;
        } else if (direction == 2) {
            col += 1; // Right
        } else if (direction == 3) {
            row += 1; // Diagonal Down-Right
            col += 1;
        } else if (direction == 4) {
            row += 1; // Down
        } else if (direction == 5) {
            row += 1; // Diagonal Down-Left
            col -= 1;
        } else if (direction == 6) {
            col -= 1; // Left
        } else if (direction == 7) {
            row -= 1; // Diagonal Up-Left
            col -= 1;
        }
    }
}

bool valid_board(vector<string>& includeWords, vector<string>& excludeWords, vector<vector<char>>& board, 
const int total_rows, const int total_cols) {
    // Check if all includeWords can be placed on the board
    for (int wordIndex = 0; wordIndex < includeWords.size(); ++wordIndex) {
        const string& word = includeWords[wordIndex];
        bool placed = false;
        for (int direction = 0; direction < 8; ++direction) {
            for (int i = 0; i < total_rows; ++i) {
                for (int j = 0; j < total_cols; ++j) {
                    if (word_fits(word, board, i, j, direction, total_rows, total_cols, true)) {
                        if(includeWords[0] == "tenet"){
                            add_word(word, board, i, j, direction);
                        }
                        placed = true;
                        break;
                    }
                }
                if (placed) break;
            }
            if (placed) break;
        }
        if (!placed) return false;
    }

    // Check if any excludeWords are placed in any direction and invalidate the board if so
    for (int wordIndex = 0; wordIndex < excludeWords.size(); ++wordIndex) {
        const string& word = excludeWords[wordIndex];
        for (int direction = 0; direction < 8; ++direction) {
            for (int i = 0; i < total_rows; ++i) {
                for (int j = 0; j < total_cols; ++j) {
                    if (word_fits(word, board, i, j, direction, total_rows, total_cols, false)) {
                        // If an excluded word can be placed, invalidate the board
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool no_empty_space(vector<vector<char>>& board){
    //makes sure no boards with empty spaces get added as solutions
    for(unsigned int i = 0; i < board.size(); ++i){
        for(unsigned int j = 0; j < board[i].size(); ++j){
            if(board[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}

bool repeat_board(vector<vector<char>>& board, vector<vector<vector<char>>>& solutions,
    //function to make sure no duplicate boards are added to solutions
    //compares each element of the board with each solution board
 const int total_rows, const int total_cols) {
    for (int i = 0; i < solutions.size(); ++i) {
        const vector<vector<char> >& solution = solutions[i];
        bool isDuplicate = true;
        for (int row = 0; row < total_rows; ++row) {
            for (int col = 0; col < total_cols; ++col) {
                if (board[row][col] != solution[row][col]) {
                    isDuplicate = false;
                    break;
                }
            }
            if (!isDuplicate) break;
        }
        if (isDuplicate) return true;
    }
    return false;
}

void create_board(vector<string>& includeWords, vector<string>& excludeWords, vector<vector<char>>& board, int wordIndex, 
vector<vector<vector<char>>>& solutions, const int total_rows, const int total_cols) {
    if (wordIndex >= includeWords.size()) {
        // All words placed successfully, check if the board is valid and unique
        //checks if any spaces are empty and adds letters to them if they are
        if(valid_board(includeWords, excludeWords, board, total_rows, total_cols)){
            std::vector<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            for(unsigned int i = 0; i < board.size(); i++){
                for(unsigned int j = 0; j < board[i].size(); j++){
                    if(board[i][j] == ' '){
                        for(unsigned int k = 0; k < 26; k++){
                            board[i][j] = alpha[k];
                            if(!repeat_board(board, solutions, total_rows, total_cols) && 
                                valid_board(includeWords, excludeWords, board, total_rows, total_cols) && no_empty_space(board)){
                                solutions.push_back(board);
                            }
                        }
                    }
                }
            }
        }
        //adds boards to the solutions if they are valid, full and unique
        if (valid_board(includeWords, excludeWords, board, total_rows, total_cols) 
            && !repeat_board(board, solutions, total_rows, total_cols) && no_empty_space(board)) {
            solutions.push_back(board);
        }
        return;
    }

    // Try placing the current word
    string word = includeWords[wordIndex];
    for (int direction = 0; direction < 8; ++direction) {
        for (int i = 0; i < total_rows; ++i) {
            for (int j = 0; j < total_cols; ++j) {
                if (word_fits(word, board, i, j, direction, total_rows, total_cols,true)) {
                    vector<vector<char>> copyBoard = board;
                    add_word(word, copyBoard, i, j, direction);
                    //recurse back through this function with the next word
                    create_board(includeWords, excludeWords, copyBoard, wordIndex + 1, solutions, total_rows, total_cols);
                }
            }
        }
    }
}

void read_file(std::ifstream& inFile, std::vector<std::string>& good_words,
 std::vector<std::string>& bad_words, int& rows, int& cols, std::ofstream& outFile){
    //function to parse input file
    //gets the number of rows and cols
    //creates a vector for words to include
    //and a vector for words to exclude
    std::string word;
    inFile >> word;
    cols = stoi(word);
    inFile >> word;
    rows = stoi(word);

    if(rows < 0 || cols < 0){
        outFile << "Not a valid grid" << endl;
        exit(3);
    }

    while(inFile >> word){
        if(word == "+"){
            inFile >> word;
            good_words.push_back(word);
        }else if(word == "-"){
            inFile >> word;
            bad_words.push_back(word);
        }
    }
}


int main(int argc, char* argv[]) {
    //file error checking
    std::ifstream inFile(argv[1]);
    if(!inFile.good()){
        std::cerr << "Can't open " << argv[1] << " to read" << std::endl;
        exit(0);
    }
    std::ofstream outFile(argv[2]);
    if(!outFile.good()){
        std::cerr << "Can't open " << argv[1] << " to write" << std::endl;
        exit(1);
    }

    vector<string> includeWords;
    vector<string> excludeWords;
    int rows;
    int cols;
    //reading file
    read_file(inFile, includeWords, excludeWords, rows, cols, outFile);

    vector<vector<vector<char>>> solutions;
    vector<vector<char>> board(rows, vector<char>(cols, ' '));

    //finding solutions
    create_board(includeWords, excludeWords, board, 0, solutions, rows, cols);

    //handling one or all solutions
    if(solutions.size() == 0){
        outFile << "No solutions found" << std::endl;
    }else{
        if(string(argv[3]) == "one_solution"){
            outFile << "Board:" << std::endl;
             for (int i = 0; i < rows; ++i) {
                outFile << "  ";
                for (int j = 0; j < cols; ++j) {
                    outFile << solutions[0][i][j];
                }
                outFile << endl;
            }
        }else{
        // Print the unique solutions
        outFile << solutions.size() << " solution(s)" << std::endl;
        for (const vector<vector<char> >& solution : solutions) {
            outFile << "Board:" << std::endl;
            for (int i = 0; i < rows; ++i) {
                outFile << "  ";
                for (int j = 0; j < cols; ++j) {
                    outFile << solution[i][j];
                }
                outFile << endl;
            }
        }
        }
    }
    return 0;
}