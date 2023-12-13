#include "questionstest.h"
#include "mainwindow.h"

#include <QApplication>

questionstest questionsTest();

int main(int argc, char *argv[]) {
    QApplication ar(argc, argv);
    const auto test = questionsTest();
    auto mw = mainwindow(&test);
    mw.show();
    return ar.exec();
}

questionstest questionsTest() {
    using namespace std::chrono_literals;

    return questionstest(10s)
        .questionAdd(
            question("Яка столиця Франції?", 1)
                .ansAdd({"Лондон", false})
                .ansAdd({"Берлін", false})
                .ansAdd({"Париж", true})
                .ansAdd({"Мадрид", false})
            )
        .questionAdd(
            question("Хто написав п'єсу 'Ромео і Джульєтта'?", 2)
                .ansAdd({"Чарльз Діккенс", false})
                .ansAdd({"Вільям Шекспір", true})
                .ansAdd({"Джейн Остін", false})
                .ansAdd({"Лев Толстой", false})
            )
        .questionAdd(
            question("Яким хімічним символом позначається золото?", 1)
                .ansAdd({"Зо", false})
                .ansAdd({"Ау", true})
                .ansAdd({"Аг", false})
                .ansAdd({"Пт", false})
            )
        .questionAdd(
            question("Яка планета відома як 'Червона планета'?", 2)
                .ansAdd({"Венера", false})
                .ansAdd({"Марс", true})
                .ansAdd({"Юпітер", false})
                .ansAdd({"Нептун", false})
            )
        .questionAdd(
            question("Хто автор серії книг 'Гаррі Поттер'?", 3)
                .ansAdd({"Дж.Р.Р. Толкін", false})
                .ansAdd({"Джордж Орвелл", false})
                .ansAdd({"Дж.К. Роулінг", true})
                .ansAdd({"Агата Крісті", false})
            );
}

