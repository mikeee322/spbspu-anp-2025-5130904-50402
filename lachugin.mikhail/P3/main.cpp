#include <iostream>
#include <fstream>
namespace lachugin {

  double circle( int **mtx,long long i, long long j);
  int **dynmtx(int r, int c);
  void staticmtx (std::ifstream& fin,int (&arr)[1000][1000] ,size_t r, size_t c);
  int *convert_int(int **a, size_t r, size_t c, int prmt);
  double *convert_dbl(double **a, size_t r, size_t c, int prmt);
  int *LFT_BOT_CLK (int **mtx, size_t rows, size_t cols, int prmt);
  double *BLT_SMT_MTR (int **mtx, size_t rows, size_t cols, int prmt);
  int **make(std::ifstream& fin,size_t rows, size_t cols, int prmt);

  int *convert_int(int **a, size_t r, size_t c, int prmt) {
    int *result = nullptr;
    if (prmt == 2) {
      result = new int[r*c];
    }
    else {
      int arr[10000];
      result = &arr[0];
    }
    size_t start = 0;
    for (size_t i = 0; i < r; i++) {
      for (size_t j = 0; j < c; j++) {
        result [start] = a[i][j];
        start++;
      }
    }
    return result;
  }

  double *convert_dbl(double **a, size_t r, size_t c, int prmt) {
    double *result = nullptr;
    if (prmt == 2) {
      result = new double[r*c];
    }
    else {
      double arr[10000];
      result = &arr[0];
    }
    size_t start = 0;
    for (size_t i = 0; i < r; i++) {
      for (size_t j = 0; j < c; j++) {
        result [start] = a[i][j];
        start++;
      }
    }
    return result;
  }

  int **dynmtx(size_t r, size_t c){
    int **mtx = nullptr;
    try {
      mtx = new int *[r];
    } catch (const std::bad_alloc &e) {
      throw;
    }
    for (size_t i = 0; i < r; i++){
      mtx[i] = new int[c];
    }
    return mtx;
  }

  int **make(std::ifstream& fin,size_t rows, size_t cols, int prmt, int **mtx) {
    int **result = nullptr;
    if (prmt == 2) {
      result = dynmtx(rows, cols);
    }
    if (prmt == 1) {
      result = mtx;
    }
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        fin >> result[i][j];
        if (fin.eof()) {
          throw std::logic_error("Not enough data\n");
        }
        if (fin.fail()) {
          throw std::logic_error("Can't read\n");
        }
      }
    }
    fin.close();
    return result;
  };

  void staticmtx (std::ifstream& fin,int (&arr)[1000][1000] ,size_t r, size_t c) {
    for (size_t i = 0; i < r; i++) {
      for (size_t j = 0; j < c; j++) {
        fin >> arr[i][j];
      }
    }
    fin.close();
  }

  int *LFT_BOT_CLK (int **mtx, size_t rows, size_t cols, int prmt) {
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
    result = convert_int(mtx, rows, cols, prmt);
    return result;
  }

  double **fopy (double **a, int **mtx, size_t r, size_t c) {
    for (size_t i = 0; i < r; i++) {
      for (size_t j = 0; j < c; j++) {
        a[i][j] = mtx[i][j];
      }
    }
    return a;
  }

  double *BLT_SMT_MTR (int **mtx, size_t rows, size_t cols, int prmt) {
    double **a = nullptr;
    a = fopy(a, mtx, rows, cols);

    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        a[i][j] = circle(mtx, i, j);
      }
    }
    double *result = nullptr;
    result = convert_dbl(a, rows, cols, prmt);
    return result;
  }

  double circle(int **mtx,int i, int j) {
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
    if (i-1>=0) {
      k++;
      sum += mtx[i-1][j];
    }
    double result = static_cast<double>(sum)/k;
    return result;
  }

  std::ostream &output(std::ostream &output, const int *var1, size_t rows, size_t cols, const double *var2) {
    output << rows << ' ' << cols << ' ';
    for (size_t i = 0; i < rows * cols; ++i) {
      output << var1[i] << ' ';
    }
    for (size_t i = 0; i < rows * cols; ++i) {
      output << var2[i] << ' ';
    }
    output << '\n';
    return output;
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
  double *var2 = nullptr;

  if (prmt == 2) {
    int **mtx = nullptr;
    int **zero = nullptr;
    mtx = lachugin::make(fin, rows, cols, prmt, zero);
    delete [] zero;
    var1 = lachugin::LFT_BOT_CLK(mtx, rows, cols, prmt);
    var2 = lachugin::BLT_SMT_MTR(mtx, rows, cols, prmt);
    delete [] mtx;
  }
  if (prmt == 1) {
    int arr[100][100];
    int* pointers[100];
    for (size_t i = 0; i < rows; i++) {
      pointers[i] = arr[i];
    }
    int **mtx = nullptr;
    mtx = lachugin::make(fin, rows, cols, prmt, pointers);
    var1 = lachugin::LFT_BOT_CLK(mtx, rows, cols, prmt);
    var2 = lachugin::BLT_SMT_MTR(mtx, rows, cols, prmt);
    delete [] mtx;
  }
  std::ofstream fout(argv[3]);
  lachugin::output(fout, var1, rows, cols, var2) << '\n';
}
