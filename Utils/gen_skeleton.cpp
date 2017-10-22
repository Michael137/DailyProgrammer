#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

enum class gStatus {
  Initialized,
  Progressing,
  Success,
  Error
};

#define DELIMITER "/"

struct CppComment {
  std::string comment_start,
              comment_line,
              comment_end;

  CppComment() : comment_start("/*"), comment_line("**"), comment_end("*/") {};
  ~CppComment() {};
};

class FileGenerator {
public:
  FileGenerator() : filename_(), path_(), sbuffer_(), status_(gStatus::Initialized) {}
  FileGenerator(std::string absolute_path_) {
    std::size_t pos = absolute_path_.find_last_of(DELIMITER);
    path_ = absolute_path_.substr(0, pos);
    filename_ = absolute_path_.substr(pos + 1);

    sbuffer_ << "";
    status_ = gStatus::Initialized;
  }

  FileGenerator(std::string path, std::string filename) : path_(path), filename_(filename), sbuffer_(), status_(gStatus::Initialized) {}

  bool Success() {  return status_ == gStatus::Success; }

  void GenerateFile() {
    CppComment cmt;
    sbuffer_ << cmt.comment_start << std::endl;
    sbuffer_ << cmt.comment_line << " " << "URL: " << std::endl;
    sbuffer_ << cmt.comment_line << " " << "Name: " << std::endl;
    sbuffer_ << cmt.comment_line << " " << "Run Instructions: " << std::endl;
    sbuffer_ << cmt.comment_line << " " << "Description: " << std::endl;
    sbuffer_ << cmt.comment_line << " " << "Input: " << std::endl;
    sbuffer_ << cmt.comment_line << " " << "Output: " << std::endl;
    sbuffer_ << cmt.comment_end << std::endl;

    std::ofstream ostrm(path_ + DELIMITER + filename_ + ".cpp");

    ostrm << sbuffer_.str();
    ostrm.close();

    status_ = gStatus::Success;
  }

private:
  std::string filename_,
              path_;

  std::stringstream sbuffer_;
  gStatus status_;
};

int main(int argc, char const *argv[]) {
  std::unique_ptr<FileGenerator> gen_p = nullptr;

  switch (argc) {
#ifdef DEBUG
    case 1: {
      std::cout << "Debug mode: creating header with '/test/path/to/file.test'." << std::endl;
      gen_p = std::make_unique<FileGenerator>("/test/file", "path");
      break;
    }
#endif
    case 2: {
      gen_p = std::make_unique<FileGenerator>(argv[1]);
      break;
    }
    case 3: {
      gen_p = std::make_unique<FileGenerator>(argv[1], argv[2]);
      break;
    }
    default:
      std::cout << "Incorrect number of input arguments supplied. Exiting..." << std::endl;
      exit(1);
  }

  gen_p->GenerateFile();

  if(gen_p->Success())
    std::cout << "Created file successfully...Exiting..." << '\n';
  else
    std::cout << "A problem has occurred during file creation...Exiting..." << '\n';

  return 0;
}
