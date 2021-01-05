#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>

using namespace std;

class Board  {
  private:
    const int size = 9;
    int board[9][9];
    int index_x = 1;
    int possible[9] = {9,9,9,9,9,9,9,9,9};

  public:
    Board(int _board[9][9] ){
      for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
          board[i][j] = _board[i][j];
          board[i][j] != 0 ? --possible[board[i][j]-1] : 0;
        }
      }
    }

    tuple<int, int, bool> findEmptyCell(){
      for(int row = 0; row < size; ++row){
        for(int col = 0; col < size; ++col){
          if(board[row][col] == 0){
            return make_tuple(row, col, true);
          }
        }
      }
      return make_tuple(0, 0, false);
    }

    bool backtracking(){
      auto x = findEmptyCell();
      int nRow = get<0>(x);
      int nCol = get<1>(x);
      bool hasEmptySpots = get<2>(x);


      if(!hasEmptySpots){
        return true;
      }

      for(int i = 0; i < 9 ; ++i){
        if(possible[i] == 0){
          continue;
        }
        if(isValid(nRow, nCol, i+1)){
          board[nRow][nCol] = i+1;
          --possible[i];

          if(backtracking()){
            return true;
          }

          board[nRow][nCol] = 0;
          ++possible[i];
        }
      }
      return false;
    }

    constexpr bool isValid(int row, int col, int num){
      int fromRow = row / 3 * 3;
      int fromCol = col / 3 * 3;

      for(int i = 0; i < 9; ++i){
        if(board[row][i] == num || 
           board[i][col] == num ||
           board[fromRow+i/3][fromCol+i%3] == num){
          return false;
        }
      }
      return true;
    }

    void print(){
      for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
          cout << board[i][j] << ' ';
        }
        cout << '\n';
      }
      cout << "-----------------\n";
    }

    void string(){
      for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
          cout << board[i][j];
        }
      }
      cout << '\n';
    }

};


int main(){
  auto start = chrono::steady_clock::now();
  vector<vector<int>> tmp_sudoku;
  int b[9][9];
  string line;


  // ------FORMAT-------
  // 0 for blank row or number 1-9 (no delimiter)
  // SUDOKUS are separated by newline.
  // Load board from cin.
  // for example in shell ./solver < puzzles.txt
  long long int lines = 0;
  while(cin >> line){
    ++lines;
    if(line.size() != 81){
      cerr << "Bad input\n";
      return -1;
    }
    vector<int> tmp;
    int index = 0;
    for(auto number : line){
      tmp.push_back(number - '0');
      ++index;
      if(index == 9){
        index = 0;
        tmp_sudoku.push_back(tmp);
        tmp.clear();
      }
    }

    for(int i = 0; i < 9; ++i){
      for(int j = 0; j < 9; ++j){
        b[i][j] = tmp_sudoku[i][j];
      }
    }
    tmp_sudoku.clear();

    Board board(b);
    if(board.backtracking()){
      board.string();
    }

    else{
      cout << "Not successfull\n";
    }


  }

  auto end = chrono::steady_clock::now();
  cerr << "Solved: " << lines << " sudokus, in " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds" << '\n';


}
