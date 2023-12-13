#include "questionstest.h"

questionstest::questionstest(const std::optional<std::chrono::seconds>& seconds) : seconds{seconds} {}

questionstest& questionstest::questionAdd(const question& question) {
    questions.emplace_back(question);
    return *this;
}
