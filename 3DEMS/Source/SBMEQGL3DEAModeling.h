#ifndef SBMEQGL3DEAMODELING_H
#define SBMEQGL3DEAMODELING_H

#include <QGLWidget>
#include <QFile>
#include <QMouseEvent>
#include <QWheelEvent>

#include "SBMENDIDef.h"
#include "SBMEMacroDefinition.h"
#include "SBMEDeformModel.h"
#include "SBMEColorMappingBar.h"

#include "GL/glut.h"

typedef struct HandleDirectionStruct
{
    GLfloat directionx;
    GLfloat directiony;
    GLfloat directionz;
} HandleDirection;

class SBMEQGL3DEAModeling : public QGLWidget
{
    Q_OBJECT

public:
    enum ViewType{MainView, AddView, LeftView, RightView};
    SBMEQGL3DEAModeling(QWidget *parent = 0, ViewType viewtype = MainView);

	void SetSystemType(int nSystemType);
	void Set3DEAModel(SBMEDeformModel *pModel);
	void SetColorMappingBar(SBMEColorMappingBar *bar);
    void SetModelFile(QFile *modleFile);
    void SetTranslation(GLfloat TranslationX, GLfloat TranslationY, GLfloat TranslationZ); 
    void SetColored(bool isColored);
    
    void SetHandlesEnabled(int handlesEnabled);
    void SetHandlesEnabledFlag(int index, bool bEnabled);
    void SetCurrentActiveHandle(int idx);
    void SetHandleColor(int idx, QColor color);
    void SetHandleModel(int idx, int model);
    void SetHandleXfms(int index, Position3d translation, QuatRotation rotation);
    void SetHandleView(bool isLargerSymbol);
	
	void SetVolumeView(bool isExtendedVolume);
    void SetViewSampledPointsOnly(bool isOnlyViewSampledPoints);
    void ViewInOrOutModel(bool isViewIn);
    void PerspectiveOrOrtho(bool isPespective);
    bool GetCurrentPoint(float *pointx, float *pointy, float *pointz);

protected:
	void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
	
	void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
	SBMEDeformModel     *m_pDeformationModel;
    SBMEColorMappingBar *m_pColorMappingBar;
	QFile *m_pModelFile;

	ViewType m_ViewType;

	QPoint m_LastPos;

    GLfloat m_translationX;
    GLfloat m_translationY;
    GLfloat m_translationZ;
    GLfloat m_rotationX;
    GLfloat m_rotationY;
    GLfloat m_rotationZ;
	GLfloat m_scaling;

    bool m_bIsExtendedVolume;
    bool m_bIsLargerSymbol;
    bool m_bIsColoring;
    bool m_bIsColored;
    bool m_bViewInModel;
    bool m_bViewOnlySampledPoints;
    bool m_bPerspective;
    
    int  m_nSystemType;
    int  m_nHandlesEnabled;
    int  m_nCurrentActiveHandle;
    int  m_nPupilDistance;
    int  m_nFocusDistance;
    int  m_nFovy;

	float m_fColoringRadius;

    bool   m_HandlesEnbaledFlag[NO_HANDLES];
	int    m_HandleModel[NO_HANDLES];
	QColor m_HandleColors[NO_HANDLES];

	QuatTransformation m_HandleXfms[NO_HANDLES];
    HandleDirection    m_HandleDirection[NO_HANDLES];
    
	int  m_GridPointColor[SBME_MAX_GRID_POINTS];
    int  m_CapturedPointsColor[SBME_MAX_GRID_POINTS];
    
    void SetProjection(int width, int height);
	void Coloring();
	void DrawVolume();
    void DrawCoordinate();
	void Draw3DModel();
    void DrawHandle();
    void DrawCatheter(int idx);
    void DrawDefaultCatheter(int idx);
    void DrawLineCatheter(int idx);
    void DrawSpiralCatheter(int idx);
    void DrawSphereCatheter(int idx);

signals:
	void m_signalRefreshLeftRightView(GLfloat scaling, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
    void m_signalNewPointSampled();

private slots:
	void m_slotRefreshWithMainView(GLfloat scaling, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
    void m_slotRefreshModel();
	void m_slotRefreshWithFocalDistance(int FD);
    void m_slotRefreshWithPupilDistance(int PD);
    void m_slotRefreshWithFovy(int Fovy);
    void m_slotRefreshWithColorBar();
    void m_slotRefreshWithColoringFlag(bool iscoloring);
    void m_slotRefreshWithColoringRadius(float ColoringRadius);
};

#endif // SBMEQGL3DEAMODELING_H
