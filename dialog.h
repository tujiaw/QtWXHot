#ifndef DIALOG_H
#define DIALOG_H

#include "article.h"
#include "dropwidget.h"

namespace Ui {
class Dialog;
}

class ArticleNet;
class QListWidgetItem;
class SystemTray;
class Dialog : public DropWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void slotReturn();
    void slotUpdateArticleList(const ArticleResult &data);
    void slotListWidgetItemClicked(QListWidgetItem *item);

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::Dialog *ui;
    ArticleNet *m_articleNet;
    SystemTray *m_tray;
};

#endif // DIALOG_H
