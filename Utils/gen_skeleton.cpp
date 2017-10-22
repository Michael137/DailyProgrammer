#include <string>
#include <iostream>
#include <sstream>

#define DELIMITER "/"

class FileGenerator {
public:
  FileGenerator() : filename_(), path_() {}
  FileGenerator(std::string absolute_path_) {
    std::size_t pos = absolute_path_.find_last_of(DELIMITER);
    path_ = absolute_path_.substr(0, pos);
    filename_ = absolute_path_.substr(pos + 1);

    sbuffer_ << "";
  }

  FileGenerator(std::string path, std::string filename) : path_(path), filename_(filename), sbuffer_() {}

private:
  std::string filename_,
              path_;

  std::stringstream sbuffer_;
};

int main(int argc, char const *argv[]) {

  std::cout << "argc: " << argc << '\n';

  switch (argc) {
#ifdef DEBUG
    case 1: {
      std::cout << "Debug mode: creating header with '/test/path/to/file.test'." << std::endl;
      FileGenerator generator("/test/file", "path");
      break;
    }
#endif
    case 2: {
      FileGenerator generator(argv[1]);
      break;
    }
    case 3: {
      FileGenerator generator(argv[1], argv[2]);
      break;
    }
    default:
      std::cout << "Incorrect number of input arguments supplied. Exiting..." << std::endl;
      exit(1);
  }

  return 0;
}
