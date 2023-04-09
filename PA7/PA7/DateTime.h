
#include <iostream>
#include <ctime>
#include <iomanip>
using std::ostream;
using std::time_t;
using std::tm;

class DateTime {
private:
    time_t unix_time;
    tm* local_time;
public:
    DateTime() {
        // Set the current unix time
        std::time(&unix_time);

        // Convert unix time to local time
        local_time = std::localtime(&unix_time);
    }

    friend ostream& operator<<(ostream& os, const DateTime& dt) {
        os << std::put_time(dt.local_time, "%Y-%m-%d %H:%M:%S");
        return os;
    }
};
