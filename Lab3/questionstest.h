#ifndef LAB_3_TQUESTIONSTEST_H
#define LAB_3_TQUESTIONSTEST_H

#include "question.h"

#include <chrono>
#include <optional>

class questionstest {
public:
    explicit questionstest(const std::optional<std::chrono::seconds>& seconds);
    questionstest& questionAdd(const question& question);

    std::optional<std::chrono::seconds> seconds;
    std::vector<question> questions;
};

#endif //LAB_3_TQUESTIONSTEST_H
