#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include <QObject>

class portscanner : public QObject
{
    Q_OBJECT
public:
    explicit portscanner(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PORTSCANNER_H