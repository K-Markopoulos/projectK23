#include <iostream>
#include <string>
#include <cstddef>
#include "../inc/utils.hpp"

using namespace std;

/** -----------------------------------------------------
 * split a string based on the delimeter
 *
 * @params line, string to split
 * @params delim, character used as delimeter
 */
vector<string> split(const string line, const char delim){
  vector<string> sections;
  string delims = string() + delim + "\n\0";
  size_t pos_start = 0, pos_end = -1;
  while((pos_end = line.find_first_of(delims, pos_end + 1)) != string::npos){
    sections.emplace_back(line.substr(pos_start, pos_end - pos_start));
    pos_start = pos_end + 1;
  }
  sections.emplace_back(line.substr(pos_start));
  return sections;
}

/** -----------------------------------------------------
 * Checks if file exists
 *
 * @params name, name of file
 * @params true if exists, else false
 */
bool file_exists(const string& name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}
