#include "SBMEColorMappingBar.h"

SBMEColorMappingBar::SBMEColorMappingBar(QWidget* parent) :
    QWidget(parent)
{
    setFixedSize(20, 150);
    m_nValue = 255;
	m_pPix = NULL;
    GenerateColorBar();
}

SBMEColorMappingBar::~SBMEColorMappingBar()
{
    delete m_pPix;
}

QColor SBMEColorMappingBar::ColorMapping(int val,int MaxVal)
{
    int index = val * m_nValue / MaxVal;
    return m_ColorBar[index];
}

void SBMEColorMappingBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    Draw(&p);
}

void SBMEColorMappingBar::mousePressEvent(QMouseEvent *event)
{
    setVal(y2val(event->y()));
}

void SBMEColorMappingBar::mouseMoveEvent(QMouseEvent *event)
{
    setVal(y2val(event->y()));
}

int SBMEColorMappingBar::y2val(int y)
{
    int d = height() - 2 * coff - 1;
    return 255 - (y - coff) * 255 / d;
}

int SBMEColorMappingBar::val2y(int v)
{
    int d = height() - 2 * coff - 1;
    return coff + (255 - v) * d / 255;
}

void SBMEColorMappingBar::setVal(int v)
{
    if (m_nValue == v)
        return;
    m_nValue = qMax(0, qMin(v, 255));
    delete m_pPix;
    m_pPix = NULL;
    repaint();
    emit m_signalValueChanged();
}

void SBMEColorMappingBar::GenerateColorBar()
{
    int r, g, b;
    int i;
    for (i = 0; i < 256; i++)
    {
        if ((i >= 0) && (i <= 50))
        {
            r = 255;
            g = 5 * i;
            b = 0;
        }
        else if ((i >= 51) && (i <= 101))
        {
            r = 255 - 5 * (i - 51);
            g = 255;
            b = 0;
        }
        else if ((i >= 102) && (i <= 152))
        {
            r = 0;
            g = 255;
            b = 5 * (i - 102);
        }
        else if ((i >= 153) && (i <= 203))
        {
            r = 0;
            g = 255 - 5 * (i - 153);
            b = 255;
        }
        else if ((i >= 204) && (i <= 255))
        {
            r = 5 * (i - 204);
            g = 0;
            b = 255;
        }
        m_ColorBar[i] = QColor(r, g, b);
    }
}

void SBMEColorMappingBar::Draw(QPainter *p)
{
    int w = width() - 5;
    QRect r(0, foff, w, height() - 2 * foff);
    int wi = r.width() - 2;
    int hi = r.height() - 2;
    if (!m_pPix || m_pPix->height() != hi || m_pPix->width() != wi)
    {
        delete m_pPix;
        QImage img(wi, hi, QImage::Format_RGB32);
        int y;
        uint *pixel = (uint *)img.scanLine(0);
        for (y = 0; y < hi; y++)
        {
            const uint *end = pixel + wi;
            while (pixel < end)
            {
                QColor c = m_ColorBar[y2val(y + coff)];
                *pixel = c.rgb();
                ++pixel;
            }
        }
        m_pPix = new QPixmap(QPixmap::fromImage(img));
    }
    p->drawPixmap(1, coff, *m_pPix);
    const QPalette &g = palette();
    qDrawShadePanel(p, r, g, true);
    p->setPen(g.foreground().color());
    p->setBrush(g.foreground());
    QPolygon a;
    int y = val2y(m_nValue);
    a.setPoints(3, w, y, w + 5, y + 5, w + 5, y - 5);
    p->eraseRect(w, 0, 5, height());
    p->drawPolygon(a);
}
