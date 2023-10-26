// FileViewer.cpp

#include "FileViewer.h"

using namespace std;

void FileViewer::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    system(clear_command);

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  open  search  go  quit\n";
    cout << short_separator << endl;
}

void FileViewer::execute_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            buffer_.move_to_next_page();
            break;
        }

        case 'o': {
            cout << "file name: ";
            string file_name;
            buffer_.file_number = 0;
            getline(cin, file_name);
            if (!buffer_.open(file_name)) {
                error_message_ = "Could not open " + file_name;
            }
            else {
                buffer_.file_number++;
                buffer_.history.push_back(file_name);
            }
            if (buffer_.find_links() != 0) {
                error_message_ = "Found a link! ";
            }
            break;
        }

        case 'p': {
            buffer_.move_to_previous_page();
            break;
        }

        case 'q': {
            done = true;
            break;
        }
        case 'g': {
            int linkNumber = 0;
            cout << "link number:  ";
                cin >> linkNumber;
            break;
        }
        case 's': {
            cout << "string: ";
            string search_term;
            getline(cin, search_term);
            bool found_line = buffer_.search(search_term);
            if (found_line == false) {
                error_message_ = "String " + search_term + " was not found";
            }
            }
        case'b': {
            if (!(buffer_.history.empty())) {
                int i = (buffer_.history.size());
                if (i > 2) {
                    buffer_.open(buffer_.history[(i + (buffer_.file_number - 2)) - buffer_.file_number]);
                    i--;
                            }
                            else
                            {
                                buffer_.open(buffer_.history[i - buffer_.file_number]);
                            }
            break;
        }
    }
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);

    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}


