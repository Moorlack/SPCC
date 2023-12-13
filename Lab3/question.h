#ifndef LAB_3_TQUESTION_H
#define LAB_3_TQUESTION_H

#include <string>
#include <vector>

struct Ans {
    std::string text;
    bool correct = false;
};

class question {
public:
    explicit question(const std::string& text, unsigned points);
    question& ansAdd(const Ans& answer);

    unsigned Points = 0;
    std::string text;
    std::vector<Ans> ans;
};


#endif //LAB_3_TQUESTION_H
