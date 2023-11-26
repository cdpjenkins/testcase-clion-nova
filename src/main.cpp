#include <vector>
#include <string>
#include <ranges>
#include <numeric>
#include <cstdint>
#include <iostream>

std::vector<int> parse_elves(const std::vector<std::string> &input) {
    using namespace std::string_literals;

    // The following code compiles and runs OK but the calls to the | operator are reported as an error (and underlined
    // in red in CLion Nove
    // CLion 2023.3 EAP (Nova)
    // Build #CL-233.12287, built on November 23, 2023
    //
    // The ""s string literal is also reported as being in error (but again cpmpiles and runs fine)
    auto elves = input
                 | std::views::lazy_split(""s)
                 | std::views::transform([](const auto& elf) -> uint64_t {
        auto to_unsigned = [](const auto& in) { return std::stoull(in); };
        auto rng = elf | std::views::transform(to_unsigned) | std::views::common;
        return std::reduce(rng.begin(), rng.end());
    });

    return (std::vector<int>) {elves.begin(), elves.end()};
}

int main() {
    std::vector<std::string> day01_test_input{
        "1000",
        "2000",
        "3000",
        "",
        "4000",
        "",
        "5000",
        "6000",
        "",
        "7000",
        "8000",
        "9000",
        "",
        "10000"
    };

    auto elves = parse_elves(day01_test_input);

    for (int elf : elves) {
        std::cout << elf << std::endl;
    }
}
