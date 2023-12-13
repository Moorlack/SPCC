#include "question.h"

question::question(const std::string& text, unsigned points)
    : text{text}, Points{points} {}

question& question::ansAdd(const Ans& answer) {
    ans.emplace_back(answer);
    return *this;
}
