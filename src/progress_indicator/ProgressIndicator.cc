#include "ProgressIndicator.h"

#include <QPainter>

ProgressIndicator::ProgressIndicator(QWidget* parent)
        : QWidget(parent),
        m_angle(0),
        m_timerId(-1),
        m_delay(40),
        m_displayedWhenStopped(false),
        m_color(Qt::black),
        m_penColor(Qt::lightGray)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);
}

bool ProgressIndicator::isAnimated () const
{
    return (m_timerId != -1);
}

void ProgressIndicator::setDisplayedWhenStopped(bool state)
{
    m_displayedWhenStopped = state;

    update();
}

bool ProgressIndicator::isDisplayedWhenStopped() const
{
    return m_displayedWhenStopped;
}

void ProgressIndicator::startAnimation()
{
    m_angle = 0;

    if (m_timerId == -1)
        m_timerId = startTimer(m_delay);
}

void ProgressIndicator::stopAnimation()
{
    if (m_timerId != -1)
        killTimer(m_timerId);

    m_timerId = -1;

    update();
}

void ProgressIndicator::setAnimationDelay(int delay)
{
    if (m_timerId != -1)
        killTimer(m_timerId);

    m_delay = delay;

    if (m_timerId != -1)
        m_timerId = startTimer(m_delay);
}

void ProgressIndicator::setColor(const QColor & color)
{
    m_color = color;

    update();
}

void ProgressIndicator::setPenColor(const QColor & color)
{
    m_penColor = color;

    update();
}

QSize ProgressIndicator::sizeHint() const
{
    return QSize(20,20);
}

int ProgressIndicator::heightForWidth(int w) const
{
    return w;
}

void ProgressIndicator::timerEvent(QTimerEvent * /*event*/)
{
    m_angle = (m_angle+30)%360;

    update();
}

void ProgressIndicator::paintEvent(QPaintEvent * /*event*/)
{
    if (!m_displayedWhenStopped && !isAnimated())
        return;

    int width = qMin(this->width(), this->height());
    
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
    int outerRadius = (width-1)*0.5;
    int innerRadius = (width-1)*0.5*0.38;

    int capsuleHeight = outerRadius - innerRadius;
    int capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35;
    int capsuleRadius = capsuleWidth/2;

    for (int i=0; i<12; i++)
    {
        QColor color = m_color;
        qreal alpha = 1.0f - (i/12.0f);
        color.setAlphaF(alpha);
        
        QColor penColor = m_penColor;
        penColor.setAlphaF(alpha);
        QPen pen;
        pen.setWidth(1);
        pen.setColor(penColor);
        p.setPen(pen);
        
        p.setBrush(color);       
        p.save();
        p.translate(rect().center());
        p.rotate(m_angle - i*30.0f);
        p.drawRoundedRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
        p.restore();
    }
}
