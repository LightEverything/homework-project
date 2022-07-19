#include "textinput.h"

TextInput::TextInput(QTextEdit *parent) : QTextEdit(parent)
{
}

QFile* TextInput::getSetFile()
{
    return &this->widgetSet.file;
}

QFont* TextInput::getSetFont()
{
    return &this->widgetSet.font;
}

void TextInput::setSetFile(QString str)
{
    this->widgetSet.file.setFileName(str);
}
