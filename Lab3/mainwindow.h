#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QLayout>
#include <QCheckBox>
#include <QTimer>

#include <vector>

class questionstest;

class mainwindow : public QWidget {
    Q_OBJECT
public:
    explicit mainwindow(const questionstest* test, QWidget *parent = nullptr);

signals:

private:
    void questionCreate();
    void startbuttonCreate();

private:
    void questionUpdate();
    void answerSave();
    void answerLoad();
    void testFinish();
    void clockUpdate();

private slots:
    void onStart();
    void onNext();
    void onBack();
    void onFinish();

private:
    QWidget* mpAnsCont = nullptr;
    QScrollArea* mpScroll = nullptr;
    QPushButton* mpNext = nullptr;
    QPushButton* mpBack = nullptr;
    QPushButton* mpFinish = nullptr;
    QPushButton* mpStart = nullptr;
    QLabel* mpQuestionNum = nullptr;
    QLabel* mpQuestiontxt = nullptr;
    QVBoxLayout* mpAns = nullptr;
    QLabel* mpTimeLabel = nullptr;
    QLabel* mpTimeLeft = nullptr;
    QLabel* mpResult = nullptr;

private:
    QList<QCheckBox*> mvAns;

private:
    QTimer* mpTimer = nullptr;

private:
    const questionstest* mpTest;

private:
    std::vector<std::vector<bool>> mvGivenAns;
    unsigned muCurrQuestion = 0;
    std::time_t mxStartTime;

private:
    static const QString timeText;
    static const QString backText;
    static const QString nextText;
    static const QString finishText;
    static const QString startText;
};

#endif // MAINWINDOW_H
