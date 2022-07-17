#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QFont>

class Setting : public QObject
{
    Q_OBJECT
public:
    explicit Setting(QObject *parent = nullptr);
    QFont font;
    QFile file;

signals:

};

#endif // SETTING_H
