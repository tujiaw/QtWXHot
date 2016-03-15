#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "article.h"

namespace Ui {
class Dialog;
}

class ArticleNet;
class QListWidgetItem;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void slotReturn();
    void slotUpdateArticleList(const ArticleResult &data);
    void slotListWidgetItemClicked(QListWidgetItem *item);

private:
    Ui::Dialog *ui;
    ArticleNet *m_articleNet;
};

#endif // DIALOG_H
