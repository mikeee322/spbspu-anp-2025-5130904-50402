#include <iostream>
#include <fstream>
namespace lachugin {
  int *convert(const int **a, size_t r, size_t c);
  double circle( int **mtx,long long i, long long j);
  int **dynmtx(int r, int c);
  int **staticmtx(size_t rows);
  int *LFT_BOT_CLK (int **mtx, size_t rows, size_t cols);
  int *BLT_SMT_MTR (int **mtx, size_t rows, size_t cols);
  int **make(std::ifstream& fin,size_t rows, size_t cols, int prmt);

  int *convert(int **a, size_t r, size_t c) {

    int *result = new int[r*c];
    size_t start = 0;
    while (start < r * c) {
      for (size_t i = start; i < start + c; i++) {
        for (size_t j = 0; j < c; j++) {
          result [start] = a[i][j];
          start++;
        }
      }
    }
    return result;
  }



  int **dynmtx(size_t r, size_t c) {
    int **mtx = new int *[r];
    for (size_t i = 0; i < r; i++){
      mtx[i] = new int[c];
    }
    return mtx;
  }

  int **make(std::ifstream& fin,size_t rows, size_t cols, int prmt) {
    int **result = nullptr;
    if (prmt == 1) {
      result = staticmtx(rows);
    }
    if (prmt == 2) {
      result = dynmtx(rows, cols);
    }
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        fin >> result[i][j];
      }
    }
    fin.close();
    return result;
  };

  int **staticmtx(size_t rows) {
    int mtx[100][100];
    int *row_ptrs[rows];
    for(int i = 0; i < rows; i++) {
      row_ptrs[i] = mtx[i];
    }
    return row_ptrs;

  }

  int *LFT_BOT_CLK (int **mtx, size_t rows, size_t cols) {
    size_t d = 1;
    size_t k = 0;
    size_t n = 0;
    while (d < rows * cols) {
      for (unsigned long long i = (rows-1)-n; i >= 0+n; i--) {   // up
        mtx[i][0+n] -= d;
        d++;
      }
      if (d == rows * cols) {
        break;
      }
      k++;
      for (unsigned long long i = 0+k; i < cols-n; i++) { // right
        mtx[0+n][i] -= d;
        d++;
      }
      if (d == rows * cols) {
        break;
      }
      for (unsigned long long  i= 0+k; i < rows-n; i++) {   // down
        mtx[i][0-n] -= d;
        d++;
      }
      if (d == rows * cols) {
        break;
      }
      n++;
      for (unsigned long long  i = (cols-1)-n; i >= 0+n; i--) {   // left
        mtx[(rows-1)-n][i] -= d;
        d++;
      }
    }
    int *result = nullptr;
    result = convert(mtx, rows, cols);
    return result;
  }

  int *BLT_SMT_MTR (int **mtx, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        mtx[i][j] = circle(mtx, i, j);
      }
    }
    int *result = nullptr;
    result = convert(mtx, rows, cols);
    return result;
  }

  double circle(int **mtx,long long i, long long j) {
    size_t k = 0;
    size_t sum = 0;
    if (i-1 >= 0&& j-1 >= 0) {
      k++;
      sum += mtx[i-1][j-1];
    } else if (j-1 >= 0) {
      k++;
      sum += mtx[i][j-1];
    } else if (i+1 >=0 && j-1 >= 0) {
      k++;
      sum += mtx[i+1][j-1];
    } else if (i+1 >= 0) {
      k++;
      sum += mtx[i+1][j];
    } else if (i+1 >= 0 && j+1 >= 0) {
      k++;
      sum += mtx[i+1][j+1];
    } else if (j+1 >= 0) {
      k++;
      sum += mtx[i][j+1];
    } else if (j+1 >= 0 && i-1 >= 0) {
      k++;
      sum += mtx[i-1][j+1];
    }
    return static_cast<double>(sum)/static_cast<double>(k);
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
  int *var2 = nullptr;
  if (prmt == 2) {
    int **mtx = nullptr;
    mtx = lachugin::make(fin, rows, cols, prmt);
    var1 = lachugin::LFT_BOT_CLK(mtx, rows, cols);
    var2 = lachugin::BLT_SMT_MTR(mtx, rows, cols);
  }
  if (prmt == 1) {
    int **mtx = nullptr;
    mtx = lachugin::make(fin, rows, cols, prmt);
    var1 = lachugin::LFT_BOT_CLK(mtx, rows, cols);
    var2 = lachugin::BLT_SMT_MTR(mtx, rows, cols);
  }
}
