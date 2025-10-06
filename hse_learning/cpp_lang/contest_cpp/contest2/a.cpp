#include <iostream>
#include <ctime>

using namespace std;

int main() {
    int d, m, y;
    cin >> d >> m >> y;

    tm date = {};
    date.tm_mday = d;
    date.tm_mon = m - 1;
    date.tm_year = y - 1900;

    time_t t = mktime(&date) + 2 * 24 * 60 * 60;
    tm *res = localtime(&t);

    cout << res->tm_mday << " " << res->tm_mon + 1 << " " << res->tm_year + 1900 << endl;

    return 0;
}
