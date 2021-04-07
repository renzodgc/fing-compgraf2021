// Local dependencies
#include <handlers/log_handler.h>

// Print log message corresponding to log code 'code'
void log_msg(const std::string msg) {
    std::cout << msg << "\n";
}

// Print error message corresponding to error code 'code'
void error_msg(const unsigned short code) {
    switch(code) {
        case ERROR_MAIN_BAD_FORMATTING:
            std::cout << ERROR_MAIN_BAD_FORMATTING_MSG;
            break;
        default:
            return;
    }
}

// Print run message based on option 'op'
void run_msg(const unsigned short op) {

    std::string msg = "";

    if (op == 1)
        msg = "1: A";
    else if (op == 2)
        msg = "2: B";
    else return;

    std::cout << "Running option " <<  msg << "\n";
}
