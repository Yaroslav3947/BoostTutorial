#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>


void print(const boost::system::error_code& e,
    boost::asio::steady_timer* timer, int* count) {
    std::cout << "Print\n";

    if (*count < 5) {
        std::cout << *count << '\n';
        (*count)++;
        timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(1));
        timer->async_wait(boost::bind(print, boost::asio::placeholders::error, timer, count));
    }
}
int main() {
    boost::asio::io_context io;
    int count(0);
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(1));

    timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));

    io.run();

    std::cout << "Final count is " << count << "\n";

    return 0;
}