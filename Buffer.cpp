// Buffer.cpp

#include "Buffer.h"

using namespace std;

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
        if (i < v_lines_.size())
            cout << std::setw(6) << i+1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file)
        return false;

    v_lines_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.

    string line;
    while (getline(file, line))
        v_lines_.push_back(line);

    file_name_ = new_file_name;
    ix_top_line_ = 0;
    return true;
}
bool Buffer::search(const std::string& s) {
    for (int i = ix_top_line_; i < v_lines_.size(); i++) {
        if (v_lines_[i].find(s) != string::npos) { // if the line of the vector not returning 'not a postition'
            ix_top_line_ = i;
            return true;
        }
    }
    return false;
}
//void Buffer::link_search(const int& linkno) {
//    for (int i = ix_top_line_; i < v_lines_.size(); i++) {
//        if (v_lines_[i].find() != string::npos) {
//            ix_top_line_ = i;
//        }
//        return;
//
//    }
//}
int Buffer::find_links() {
    int count = 0;
    for (int i = ix_top_line_; i < v_lines_.size(); i++) {
        if (v_lines_[i].find("<a ")) {
            ++count;
        }
    }
    return count;
}