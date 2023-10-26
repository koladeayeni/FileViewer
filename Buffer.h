// Buffer.h

#ifndef _Buffer_h_
#define _Buffer_h_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Buffer
{
public:
    void display() const;
    const std::string & file_name() const { return file_name_; }
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height_ = h; }
    bool search(const std::string& s);
    //void link_search(const int& linkno);
    int find_links();
    std::vector<std::string> history;
    int file_number;

private:
    std::vector<std::string> v_lines_;
    int ix_top_line_ = 0;
    std::string file_name_;
    int window_height_;
};

inline void Buffer::move_to_next_page()
{
    ix_top_line_ += window_height_;
    if (ix_top_line_ >= v_lines_.size())
        ix_top_line_ -= window_height_;
}

inline void Buffer::move_to_previous_page()
{
    ix_top_line_ -= window_height_;
    if (ix_top_line_ < 0)
        ix_top_line_ = 0;
}


#endif
