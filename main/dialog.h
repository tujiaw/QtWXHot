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
    void slotSetting();
    void slotUpdateArticleList(const ArticleResult &data);
    void slotListWidgetItemClicked(QListWidgetItem *item);
    void slotStackedCurrentChanged(int index);
    void slotBackgroundLoad(const QString &path);

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::Dialog *ui;
    ArticleNet *m_articleNet;
    SystemTray *m_tray;
    int m_fromIndex;
};

#endif // DIALOG_H
