#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <QWidget>
#include <QTextEdit>
#include <setting.h>

class TextInput : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextInput(QTextEdit *parent = nullptr);
    QFile* getSetFile();
    QFont* getSetFont();
    void setSetFile(QString );

private:
    Setting widgetSet;
signals:

};

#endif // TEXTINPUT_H
