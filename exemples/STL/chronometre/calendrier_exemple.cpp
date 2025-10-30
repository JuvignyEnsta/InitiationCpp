#include <chrono>
#include <iostream>

using namespace std::chrono;

void displayDate( year_month_day const& date ) {
    std::cout << "date : " << static_cast<unsigned>(date.day()) << "."
                           << static_cast<unsigned>(date.month()) << "."
                           << static_cast<int>(date.year()) << std::endl;
}

int main()
{
    year_month_day date{2022y, September, 8d};
    displayDate(date);

    const std::chrono::time_point now{std::chrono::system_clock::now()};
    std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(now)};
    displayDate( today );
    today += months(5u);
    displayDate(today);

    year_month_day date2{2023y, January, 30d};
    date2 += months(1u);
    displayDate(date2);

    return EXIT_SUCCESS;
}