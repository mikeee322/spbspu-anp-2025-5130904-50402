#include <iostream>
#include <fstream>
namespace lachugin {
  int **dynmtx(const char* input, const char* output);
  int **make(int rows, int cols);

  int **make(int r, int c)
  {
    int **mtx = new int *[r];
    for (size_t i = 0; i < r; i++){
      mtx[i] = new int[c];

    }
    return mtx;
  }

  int **dynmtx(const char* input, const char* output) {
    std::ifstream fin(input);
    if (!fin.is_open()) {
      throw std::logic_error ("Error opening file");
    }
    size_t rows = 0, cols = 0;
    fin >> rows >> cols;
    if (fin.fail()) {
      throw std::logic_error ("Error reading file");
    }
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
  }

  if (prmt == 2) {
    int **mtx = nullptr;
    mtx = lachugin::dynmtx(argv[2], argv[3]);
  }
}