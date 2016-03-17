#include "dropwidget.h"

#include <QBitmap>
#include <QPainter>

DropWidget::DropWidget(QWidget *parent) : QDialog(parent)
{
    m_bgColor = QColor("#ffffff");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setMouseTracking(true);
    m_mousePressed = false;
}

DropWidget::~DropWidget()
{
}

void DropWidget::setBackground(const QImage &image)
{
    m_bgImage = image;
}

void DropWidget::setBackgroundColor(QColor color)
{
    m_bgColor = color;
}

void DropWidget::setTitle(const QString &title)
{
    m_title = title;
}

void DropWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_mousePressed = true;
    }

    m_movePoint = event->globalPos() - pos();
}

void DropWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}

void DropWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed) {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_movePoint);
    }
}

void DropWidget::paintEvent( QPaintEvent *event)
{
    if (!m_bgImage.isNull()) {
        drawBackground(event);
    } else {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_bgColor);
        painter.drawRect(this->rect());

        int radius = 4;
        QSize maskSize(this->size().width(), this->size().height());
        QBitmap mask(maskSize);
        QPainter maskPainter(&mask);
        maskPainter.setRenderHint(QPainter::Antialiasing);
        maskPainter.setRenderHint(QPainter::SmoothPixmapTransform);
        maskPainter.fillRect(this->rect(), Qt::white);
        maskPainter.setBrush(QColor("#000000"));
        maskPainter.drawRoundedRect(QRect(QPoint(0, 0), maskSize), radius, radius);
        this->setMask(mask);
        QWidget::paintEvent(event);
    }

    if (!m_title.isEmpty()) {
        QFontMetrics fm = this->fontMetrics();
        int textWidth = fm.width(m_title);
        int x = (this->width() - textWidth) / 2;
        int y = 20;
        QPainter painter(this);
        painter.drawText(x, y, m_title);
    }
}

void DropWidget::drawBackground(QPaintEvent *event)
{
    QPainter painter(this);

    QImage image = m_bgImage;
    // 原图
    painter.drawPixmap(0, 0, qMin(width(), image.width()), qMin(height(), image.height()), QPixmap::fromImage(image));
    // 横向填充 图片宽度
    if (image.width() < width())
    {
        painter.drawPixmap(image.width()/2, 0, width()-image.width(), image.height(), QPixmap::fromImage(image.copy(image.width()/2, 0, 1, image.height())));
        painter.drawPixmap(width()-image.width()/2-1, 0, image.width()/2+1, image.height(), QPixmap::fromImage(image.copy(image.width()/2, 0, image.width()/2+1, image.height())));
    }
    // 纵向填充 图片长度
    if (image.height() < height())
    {
        painter.drawPixmap(1, image.height()-1, width()-2, height()-image.height(), QPixmap::fromImage(image.copy(image.width()/2, image.height()-2, 1, 1)));
        painter.drawPixmap(0, image.height()-1, 1, height()-image.height(), QPixmap::fromImage(image.copy(0, image.height()-1, 1, 1)));
        painter.drawPixmap(width()-1, image.height()-1, 1, height()-image.height(), QPixmap::fromImage(image.copy(0, image.height()-1, 1, 1)));
        painter.drawPixmap(0, height()-1, width(), 1, QPixmap::fromImage(image.copy(0, image.height()-1, 1, 1)));
    }

    // 窗口top圆角处理
    int radius = 4;
    QSize maskSize(this->size().width(), this->size().height());
    QBitmap mask(maskSize);
    QPainter maskPainter(&mask);
    maskPainter.setRenderHint(QPainter::Antialiasing);
    maskPainter.setRenderHint(QPainter::SmoothPixmapTransform);
    maskPainter.fillRect(this->rect(), Qt::white);
    maskPainter.setBrush(QColor("#000000"));
    maskPainter.drawRoundedRect(QRect(QPoint(0, 0), maskSize), radius, radius);
    this->setMask(mask);
    QWidget::paintEvent(event);
}

