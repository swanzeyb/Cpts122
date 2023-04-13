
#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

using std::string;
using std::ostream;
using std::time_t;
using std::strftime;
using std::localtime;

class DateTime {
public:
    DateTime() {
        char rn[11];
        time_t unix = time(0);
        strftime(rn, 11, "%m/%d/%Y", localtime(&unix));
        
        // We gotta convert it to a string
        string rnfr(rn);
        dateTime_ = rnfr;
    }
    ~DateTime() {}

    string toString() {
        return dateTime_;
    }

    friend ostream& operator<<(ostream& os, const DateTime& dt) {
        os << dt.dateTime_;
        return os;
    }

private:
    string dateTime_;
};
