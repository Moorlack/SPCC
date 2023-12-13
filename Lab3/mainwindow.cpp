#include "mainwindow.h"
#include "questionstest.h"

static constexpr int winWidth = 800;
static constexpr int winHeight = 600;

static constexpr int startWidth = 200;
static constexpr int startHeight = 50;
const QString mainwindow::timeText = "Часу лишилось:";
const QString mainwindow::backText= "Назад";
const QString mainwindow::nextText= "Вперед";
const QString mainwindow::finishText= "Завершити";
const QString mainwindow::startText= "Розпочати";

mainwindow::mainwindow(const questionstest* test, QWidget *parent)
    : QWidget{parent}, mpTest{test} {

    resize(winWidth, winHeight);

    startbuttonCreate();
    questionCreate();

    mpResult = new QLabel(this);
    mpResult->hide();

    mvGivenAns.resize(test->questions.size());
    for(auto i = 0; i < test->questions.size(); ++i) {
        mvGivenAns[i].assign(test->questions[i].ans.size(), false);
    }

    mpQuestionNum->hide();
    mpQuestiontxt->hide();
    mpAnsCont->hide();
    mpScroll->hide();
    mpNext->hide();
    mpBack->hide();
    mpFinish->hide();
    mpTimeLabel->hide();
    mpTimeLeft->hide();

}

void mainwindow::startbuttonCreate() {
    mpStart = new QPushButton(this);
    mpStart->setFixedWidth(startWidth);
    mpStart->setFixedHeight(startHeight);
    mpStart->setText(startText);
    mpStart->move((winWidth - startWidth) / 2, (winHeight - startHeight) / 2);
    QObject::connect(mpStart, &QPushButton::clicked, this, &mainwindow::onStart);
}

void mainwindow::questionCreate() {
    QVBoxLayout* mainLayout;
    if (this->layout() == nullptr) {
        mainLayout = new QVBoxLayout(this);
        this->setLayout(mainLayout);
    } else {
        mainLayout = qobject_cast<QVBoxLayout*>(this->layout());
    }
    QHBoxLayout* infoLayout = new QHBoxLayout();
    mpQuestionNum = new QLabel(this);
    mpTimeLabel = new QLabel(mainwindow::timeText, this);
    mpTimeLeft = new QLabel("0", this);
    infoLayout->addWidget(mpQuestionNum);
    infoLayout->addWidget(mpTimeLabel);
    infoLayout->addWidget(mpTimeLeft);
    infoLayout->addStretch();
    mainLayout->addLayout(infoLayout);
    mpQuestiontxt = new QLabel(this);
    mainLayout->addWidget(mpQuestiontxt);
    mpAnsCont = new QWidget();
    mpAns = new QVBoxLayout(mpAnsCont);
    mpScroll = new QScrollArea(this);
    mpScroll->setWidget(mpAnsCont);
    mpScroll->setWidgetResizable(true);
    mainLayout->addWidget(mpScroll);
    mpAns->setSpacing(2);
    mpAnsCont->setMaximumHeight(mpTest->questions.size() * 50);
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    mpBack = new QPushButton(backText, this);
    QObject::connect(mpBack, &QPushButton::clicked, this, &mainwindow::onBack);
    bottomLayout->addWidget(mpBack);
    mpNext = new QPushButton(nextText, this);
    QObject::connect(mpNext, &QPushButton::clicked, this, &mainwindow::onNext);
    bottomLayout->addWidget(mpNext);
    mpFinish = new QPushButton(finishText, this);
    QObject::connect(mpFinish, &QPushButton::clicked, this, &mainwindow::onFinish);
    bottomLayout->addWidget(mpFinish);
    mainLayout->addLayout(bottomLayout);
    questionUpdate();
}
void mainwindow::questionUpdate() {
    if(mpTest->questions.empty()) return;
    const auto& question = mpTest->questions[muCurrQuestion];
    mpQuestionNum->setText(
        "Номер питання: " + QString::number(muCurrQuestion+1) + ". Бали за питання: " + QString::number(question.Points)+ ".");
    mpQuestiontxt->setText(QString::fromStdString(question.text));
    qDeleteAll(mvAns);
    mvAns.clear();
    for(const auto& answer : question.ans) {
        auto checkbox = new QCheckBox(QString::fromStdString(answer.text));
        QObject::connect(checkbox, &QCheckBox::stateChanged, this, &mainwindow::answerSave);
        mvAns.push_back(checkbox);
        mpAns->addWidget(checkbox);
    }
    mpAnsCont->setLayout(mpAns);
}

void mainwindow::answerSave() {
    for(auto i = 0; i < mvAns.size(); ++i) {
        mvGivenAns[muCurrQuestion][i] = mvAns[i]->isChecked();
    }
}

void mainwindow::answerLoad() {
    for(auto i = 0; i < mvAns.size(); ++i) {
        mvAns[i]->blockSignals(true);
        mvAns[i]->setChecked(mvGivenAns[muCurrQuestion][i]);
        mvAns[i]->blockSignals(false);
    }
}

void mainwindow::testFinish() {
    mpQuestionNum->hide();
    mpQuestiontxt->hide();
    mpAnsCont->hide();
    mpScroll->hide();
    mpNext->hide();
    mpBack->hide();
    mpFinish->hide();
    mpTimeLabel->hide();
    mpTimeLeft->hide();

    auto totalPoints = 0u;
    for(auto i = 0; i < mvGivenAns.size(); ++i) {
        auto isCorrect = true;
        for(auto j = 0; j < mvGivenAns[i].size(); ++j) {
            if(mvGivenAns[i][j] != mpTest->questions[i].ans[j].correct) {
                isCorrect = false;
                break;
            }
        }
        if(isCorrect) {
            totalPoints += mpTest->questions[i].Points;
        }
    }
    mpResult->setText("Набрані бали: " + QString::number(totalPoints));
    mpResult->show();
}

void mainwindow::clockUpdate() {
    const auto time = std::chrono::system_clock::now();
    const auto between = std::chrono::system_clock::to_time_t(time) - mxStartTime;
    const auto betweenPoint = std::chrono::system_clock::from_time_t(between);
    const auto secs = std::chrono::time_point_cast<std::chrono::seconds>(betweenPoint);
    const auto seconds = secs.time_since_epoch();

    const auto left = mpTest->seconds.value() - seconds;
    mpTimeLeft->setText(QString::number(left.count()));
}

void mainwindow::onStart() {
    mpStart->hide();

    if(mpTest->seconds) {
        const auto time = std::chrono::system_clock::now();
        mxStartTime = std::chrono::system_clock::to_time_t(time);
        std::chrono::milliseconds millisec = std::chrono::duration_cast<std::chrono::milliseconds>(mpTest->seconds.value());
        QTimer::singleShot(millisec.count(), this, &mainwindow::onFinish);
        mpTimer = new QTimer(this);
        QObject::connect(mpTimer, &QTimer::timeout, this, &mainwindow::clockUpdate);
        mpTimer->start(1000);
        clockUpdate();
    }


    if(mpTest->questions.empty()) {
        testFinish();
        return;
    }

    mpQuestionNum->show();
    mpQuestiontxt->show();
    mpAnsCont->show();
    mpScroll->show();
    mpNext->show();
    mpBack->show();
    mpFinish->show();
    mpTimeLabel->show();
    mpTimeLeft->show();
    mpFinish->setDisabled(true);
    mpBack->setDisabled(true);
}

void mainwindow::onNext() {
    answerSave();

    muCurrQuestion++;

    questionUpdate();
    answerLoad();

    mpBack->setDisabled(false);
    if(muCurrQuestion == mpTest->questions.size() - 1) {
        mpNext->setDisabled(true);
        mpFinish->setDisabled(false);
    }
}

void mainwindow::onBack() {
    answerSave();

    muCurrQuestion--;

    questionUpdate();
    answerLoad();

    if(muCurrQuestion==0) {
        mpBack->setDisabled(true);
    }
    mpNext->setDisabled(false);
    mpFinish->setDisabled(true);
}

void mainwindow::onFinish() {
    testFinish();
}

