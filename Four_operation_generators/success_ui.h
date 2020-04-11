#ifndef SUCCESS_UI_H
#define SUCCESS_UI_H

#include <QWidget>

namespace Ui {
class success_ui;
}

class success_ui : public QWidget
{
    Q_OBJECT

public:
    explicit success_ui(QWidget *parent = nullptr);
    ~success_ui();

private:
    Ui::success_ui *ui;
};

#endif // SUCCESS_UI_H
