#ifndef UNSUCCESS_UI_H
#define UNSUCCESS_UI_H

#include <QWidget>

namespace Ui {
class unsuccess_ui;
}

class unsuccess_ui : public QWidget
{
    Q_OBJECT

public:
    explicit unsuccess_ui(QWidget *parent = nullptr);
    ~unsuccess_ui();

private:
    Ui::unsuccess_ui *ui;
};

#endif // UNSUCCESS_UI_H
