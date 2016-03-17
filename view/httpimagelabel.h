#ifndef HTTPIMAGELABEL_H
#define HTTPIMAGELABEL_H

#include <QLabel>

class HttpImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HttpImageLabel(QWidget *parent = 0);
    void setHttpImage(const QString &url);

signals:

public slots:
};

#endif // HTTPIMAGELABEL_H
