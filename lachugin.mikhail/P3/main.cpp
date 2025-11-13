#include <iostream>
#include <fstream>
namespace lachugin {

  int **make(int rows, int cols);

  int **make(int r, int c)
  {
    int **mtx = new int *[r];
    for (size_t i = 0; i < r; i++){
      mtx[i] = new int[c];

    }
    return mtx;
  }

  int **dynmtx(std::ifstream& fin,size_t rows, size_t cols) {
    int **result = nullptr;
    result = make(rows, cols);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        fin >> result[i][j];
      }
    }
    fin.close();
    return result;
  };

  int *LFT_BOT_CLK (int **mtx, size_t rows, size_t cols) {
    size_t d = 1;
    size_t k = 0;
    size_t n = 0;
    while (d < rows * cols) {
      for (int i = (rows-1)-n; i >= 0+n; i--) {   // up
        mtx[i][0+n] -= d;
        d++;
      }

      k++;


      for (int i = 0+k; i < cols-n; i++) { // right
        mtx[0+n][i] -= d;
        d++;
      }

      for (int i = 0+k; i < rows-n; i++) {   // down
        mtx[i][0-n] -= d;
        d++;
      }


      n++;

      for (int i = (cols-1)-n; i >= 0+n; i--) {   // left
        mtx[(rows-1)-n][i] -= d;
        d++;
      }
    }
  }







}

int main(int argc, char ** argv) {
  if (argc < 4 ) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if ( argc > 4 ) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int prmt = 0;
  try{
    prmt = std::stoi(argv[1]);
  } catch (const std::invalid_argument& e){
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if ( prmt > 2 || prmt < 1 ){
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  if (!fin.is_open()) {
     std::cerr << "Error opening file\n";
    return 1;
  }
  size_t rows = 0, cols = 0;
  fin >> rows >> cols;
  if (fin.fail()) {
    std::cerr <<  "Error reading file\n";
    return 1;
  }
  int *var1 = nullptr;
  if (prmt == 2) {
    int **mtx = nullptr;
    mtx = lachugin::dynmtx(fin, rows, cols);

  }
}
