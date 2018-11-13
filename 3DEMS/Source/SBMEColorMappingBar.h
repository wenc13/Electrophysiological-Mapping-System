#ifndef SBMECOLORMAPPINGBAR_H
#define SBMECOLORMAPPINGBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qdrawutil.h>

class SBMEColorMappingBar : public QWidget
{
    Q_OBJECT

public:
    SBMEColorMappingBar(QWidget* parent=0);
    ~SBMEColorMappingBar();
    
	QColor ColorMapping(int, int);

protected:
    void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    enum {foff = 3, coff = 4};
	
	int m_nValue;
    
	QPixmap *m_pPix;
    
	QColor m_ColorBar[256];
    
    int  y2val(int);
    int  val2y(int);
    void setVal(int);
    void GenerateColorBar();
    void Draw(QPainter *painter);

signals:
    void m_signalValueChanged();
};

#endif // SBMECOLORMAPPINGBAR_H
