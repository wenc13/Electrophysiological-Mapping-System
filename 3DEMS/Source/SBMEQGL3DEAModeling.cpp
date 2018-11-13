#include "SBMEQGL3DEAModeling.h"
#include "SBMENDIAuxiliary.h"

#include <QTextStream>

#define GL_PI 3.1415f

void Normalise(float vector[3])
{
    float length;
    length = (float)sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
    if (length == 0.0)
        length = 1.0;
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}

void Normal(float v[3][3], float out[3])
{
    float v1[3], v2[3];
    static const int x = 0, y = 1, z = 2;
    v1[x] = v[0][x] - v[1][x];
    v1[y] = v[0][y] - v[1][y];
    v1[z] = v[0][z] - v[1][z];
    v2[x] = v[1][x] - v[2][x];
    v2[y] = v[1][y] - v[2][y];
    v2[z] = v[1][z] - v[2][z];
    out[x] = v1[y] * v2[z] - v1[z] * v2[y];
    out[y] = v1[z] * v2[x] - v1[x] * v2[z];
    out[z] = v1[x] * v2[y] - v1[y] * v2[x];
    Normalise(out);
}

bool NormalCorrect(float v[3][3], float vector[3])
{
    float center[3];
    for (int i = 0; i < 3; i++)
    {
        center[i] = (v[0][i] + v[1][i] + v[2][i]) / 3;
    }
    if ((center[0] * vector[0] + center[1] * vector[1] + center[2] * vector[2]) < 0)
        return true;
    return false;
}

SBMEQGL3DEAModeling::SBMEQGL3DEAModeling(QWidget *parent, ViewType viewtype)
    : QGLWidget(parent)
{
	//setMinimumSize(200, 200);
	m_pDeformationModel = NULL;
	m_pColorMappingBar = NULL;
	m_pModelFile = NULL;

	m_ViewType = viewtype;
    
	m_translationX = 0.0;
    m_translationY = 0.0;
    m_translationZ = 0.0;
    m_rotationX    = 0.0;
    m_rotationY    = 0.0;
    m_rotationZ    = 0.0;
	m_scaling      = 1.0;

    m_bIsExtendedVolume      = true;
    m_bIsLargerSymbol        = true;
	m_bIsColoring            = true;
    m_bIsColored             = false;
	m_bViewInModel           = false;
	m_bViewOnlySampledPoints = true;
	m_bPerspective           = true;

    m_nSystemType            = AURORA_SYSTEM;
    m_nHandlesEnabled        = 0;
    m_nCurrentActiveHandle   = -1;
	m_nPupilDistance         = 66;
    m_nFocusDistance         = 100;
    m_nFovy                  = 60;
    
    m_fColoringRadius        = 5;

    for (int i = 0; i < NO_HANDLES; i++)
    {
        m_HandlesEnbaledFlag[i] = false;
        m_HandleModel[i]        = 0;
		m_HandleColors[i]       = Qt::blue;
    }
}

void SBMEQGL3DEAModeling::SetSystemType(int nSystemType)
{
    m_nSystemType = nSystemType;
    updateGL();
}

void SBMEQGL3DEAModeling::Set3DEAModel(SBMEDeformModel *pModel)
{
    m_pDeformationModel = pModel;
    updateGL();
}

void SBMEQGL3DEAModeling::SetColorMappingBar(SBMEColorMappingBar *bar )
{
    m_pColorMappingBar = bar;
}

void SBMEQGL3DEAModeling::SetModelFile(QFile *modleFile)
{
    m_pModelFile = modleFile;
}

void SBMEQGL3DEAModeling::SetTranslation(GLfloat TranslationX, GLfloat TranslationY, GLfloat TranslationZ)
{
    m_translationX = TranslationX;
    m_translationY = TranslationY;
    m_translationZ = TranslationZ;
    updateGL();
}

void SBMEQGL3DEAModeling::SetColored(bool isColored)
{
    m_bIsColored = isColored;
    updateGL();
}

void SBMEQGL3DEAModeling::SetHandlesEnabled(int handlesEnabled)
{
    m_nHandlesEnabled = handlesEnabled;
    updateGL();
}

void SBMEQGL3DEAModeling::SetHandlesEnabledFlag(int index, bool bEnabled)
{
    m_HandlesEnbaledFlag[index] = bEnabled;
    updateGL();
}

void SBMEQGL3DEAModeling::SetCurrentActiveHandle(int idx)
{
    m_nCurrentActiveHandle = idx;
}

void SBMEQGL3DEAModeling::SetHandleColor(int idx, QColor color)
{
    m_HandleColors[idx] = color;
    updateGL();
}

void SBMEQGL3DEAModeling::SetHandleModel(int idx, int model)
{
    m_HandleModel[idx] = model;
    updateGL();
}

void SBMEQGL3DEAModeling::SetHandleXfms(int index, Position3d translation, QuatRotation rotation)
{
    m_HandleXfms[index].translation.x = translation.x;
    m_HandleXfms[index].translation.y = translation.y;
    m_HandleXfms[index].translation.z = translation.z;
    GLfloat q0, qx, qy, qz;
    q0 = rotation.q0;
    qx = rotation.qx;
    qy = rotation.qy;
    qz = rotation.qz;
    m_HandleXfms[index].rotation.q0 = rotation.q0;
    m_HandleXfms[index].rotation.qx = rotation.qx;
    m_HandleXfms[index].rotation.qy = rotation.qy;
    m_HandleXfms[index].rotation.qz = rotation.qz;
    m_HandleDirection[index].directionx = -2 * (qy * qz - q0 * qx);
    m_HandleDirection[index].directiony = -2 * (qx * qz + q0 * qy);
    m_HandleDirection[index].directionz = q0 * q0 - qx * qx - qy * qy + qz * qz;
    updateGL();
}

void SBMEQGL3DEAModeling::SetHandleView(bool isLargerSymbol)
{
    m_bIsLargerSymbol = isLargerSymbol;
    updateGL();
}

void SBMEQGL3DEAModeling::SetVolumeView(bool isExtendedVolume)
{
    m_bIsExtendedVolume = isExtendedVolume;
    updateGL();
}

void SBMEQGL3DEAModeling::SetViewSampledPointsOnly(bool isOnlyViewSampledPoints)
{
    m_bViewOnlySampledPoints = isOnlyViewSampledPoints;
    updateGL();
}

void SBMEQGL3DEAModeling::ViewInOrOutModel(bool isViewIn)
{
    m_bViewInModel = isViewIn;
    updateGL();
}

void SBMEQGL3DEAModeling::PerspectiveOrOrtho(bool isPespective)
{
    m_bPerspective = isPespective;
    SetProjection(width(), height());
    updateGL();
}

bool SBMEQGL3DEAModeling::GetCurrentPoint(float *pointx, float *pointy, float *pointz)
{
    if (m_nCurrentActiveHandle == -1)
        return false;
    else
    {
        *pointx = m_HandleXfms[m_nCurrentActiveHandle].translation.x;
        *pointy = m_HandleXfms[m_nCurrentActiveHandle].translation.y;
        *pointz = m_HandleXfms[m_nCurrentActiveHandle].translation.z;
        return true;
    }
}

void SBMEQGL3DEAModeling::mousePressEvent(QMouseEvent *event)
{
    if ((m_ViewType != LeftView) && (m_ViewType != RightView))
        m_LastPos = event->pos();
}

void SBMEQGL3DEAModeling::mouseMoveEvent(QMouseEvent *event)
{
    if ((m_ViewType != LeftView) && (m_ViewType != RightView))
    {
        GLfloat dx = GLfloat(event->x() - m_LastPos.x()) / width();
        GLfloat dy = GLfloat(event->y() - m_LastPos.y()) / height();

        if (event->buttons() && Qt::LeftButton)
        {
            m_rotationX -= 180 * dy;
            m_rotationY -= 180 * dx;
        }
        else if (event->buttons() && Qt::RightButton)
            m_rotationZ -= 180 * dx;
        updateGL();
        m_LastPos = event->pos();
        emit m_signalRefreshLeftRightView(m_scaling, m_rotationX, m_rotationY, m_rotationZ);
    }
}

void SBMEQGL3DEAModeling::mouseDoubleClickEvent(QMouseEvent *event)
{
    if ((m_ViewType == MainView))
    {
        double x, y, z;
        if (m_nCurrentActiveHandle != -1)
        {
            static int i = 0;
            x = m_HandleXfms[m_nCurrentActiveHandle].translation.x;
            y = m_HandleXfms[m_nCurrentActiveHandle].translation.y;
            z = m_HandleXfms[m_nCurrentActiveHandle].translation.z;
            m_pDeformationModel->InsertPoint(x, y, z);
            i++;
            if (m_pModelFile != NULL)
            {
                QString str = QString("%1,%2,%3\n").arg(x, 0, 'f', 6).arg(y, 0, 'f', 6).arg(z, 0, 'f', 6);
                QTextStream out(m_pModelFile);
                out.seek(m_pModelFile->size());
                out<<str;
            }
            double centerPoint[3];
            m_pDeformationModel->GetCenter(centerPoint);
            SetTranslation(centerPoint[0], centerPoint[1], centerPoint[2]);
            m_bIsColored = false;
            emit m_signalNewPointSampled();
            updateGL();
        }
    }
}

void SBMEQGL3DEAModeling::wheelEvent(QWheelEvent *event)
{
    if ((m_ViewType != LeftView) && (m_ViewType != RightView))
    {
        double numDegrees = event->delta() / 8.0;
        double numSteps = numDegrees / 15.0;
        m_scaling *= std::pow(1.125, numSteps);
        updateGL();
        emit m_signalRefreshLeftRightView(m_scaling, m_rotationX, m_rotationY, m_rotationZ);
    }
}

void SBMEQGL3DEAModeling::initializeGL()
{
    //qglClearColor(Qt::black);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                  //修改于2015/06/15
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //修改于2015/06/15
    glShadeModel(GL_FLAT);                                 //单色模式
    glEnable(GL_DEPTH_TEST);                               //启用深度缓冲区
    glEnable(GL_CULL_FACE);                                //启用剔除功能
}

void SBMEQGL3DEAModeling::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    SetProjection(width, height);
}

void SBMEQGL3DEAModeling::paintGL()
{
    SetProjection(this->width(), this->height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    switch (m_ViewType)
    {
    case LeftView:
        gluLookAt(-m_nPupilDistance / 2, 0, m_nFocusDistance, 0, 0, -1, 0, 1, 0);
        break;
    case RightView:
        gluLookAt(m_nPupilDistance / 2, 0, m_nFocusDistance, 0, 0, -1, 0, 1, 0);
        break;
    default:
        gluLookAt(0, 0, m_nFocusDistance, 0, 0, -1, 0, 1, 0);
        break;
    }
    
	glRotatef(m_rotationX, 1.0, 0.0, 0.0);
    glRotatef(m_rotationY, 0.0, 1.0, 0.0);
    glRotatef(m_rotationZ, 0.0, 0.0, 1.0);
    glScalef(m_scaling, m_scaling, m_scaling);

    DrawCoordinate();
	Draw3DModel();
	DrawHandle();
    
	if (m_ViewType == AddView)
        DrawVolume();
    glPopMatrix();
}

void SBMEQGL3DEAModeling::SetProjection(int width, int height)
{
    if (height == 0)
        height = 1;

    GLfloat aspect = GLdouble(width) / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (m_ViewType == AddView)
    {
        if (m_nSystemType == AURORA_SYSTEM)
        {
            //修改于2015/06/21
			if (aspect >= 1)
                glOrtho(-600 * aspect, 600 * aspect, -400, 800, -800, 800);    //正投影，此区域足以涵盖NDI系统的Volume
            else
                glOrtho(-600, 600, -400 / aspect, 800 / aspect, -800, 800);
        }
        else
        {
            //原始代码，未调试
			if (aspect >= 1)
                glOrtho(-1500 * aspect, 1500 * aspect, -1500, 1500, -100, 5000);    //正投影，此区域足以涵盖NDI系统的Volume
            else
                glOrtho(-1500, 1500, -1500 / aspect, 1500 / aspect, -100, 5000);
        }
    }
    else
    {
        if (m_bPerspective)
            gluPerspective(m_nFovy, aspect, 10, 3000);
        else
        {
            if (aspect >= 1)
                glOrtho(-200 * aspect, 200 * aspect, -200, 200, 0, 3000);    //正投影，此区域足以涵盖心脏区域
            else
                glOrtho(-200, 200, -200 / aspect, 200 / aspect, 0, 3000);
        }
    }
}

void SBMEQGL3DEAModeling::Coloring()
{
    if (m_bIsColored)
        return;

    double x1, y1, z1, x2, y2, z2;
    double weight = 0;
    int color = 0;

    for (int i = 0; i < m_pDeformationModel->GetGridPointsNum(); i++)
    {
        weight = 0;
        color = 0;
        x1 = m_pDeformationModel->GetGridPointsPoint(i)[0];
        y1 = m_pDeformationModel->GetGridPointsPoint(i)[1];
        z1 = m_pDeformationModel->GetGridPointsPoint(i)[2];
        for (int j = 0; j != m_pDeformationModel->GetPoints3DNum(); j++)
        {
            x2 = m_pDeformationModel->GetPoints3DPoint(j)[0];
            y2 = m_pDeformationModel->GetPoints3DPoint(j)[1];
            z2 = m_pDeformationModel->GetPoints3DPoint(j)[2];
            double distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
            if (distance < m_fColoringRadius)
            {
                weight += (m_fColoringRadius - distance) / m_fColoringRadius;
                color += m_CapturedPointsColor[j] * (m_fColoringRadius-distance) / m_fColoringRadius;
            }
        }
        if (weight == 0)
        {
            weight = 1;
        }
        m_GridPointColor[i] = color / weight;
    }
    m_bIsColored = true;
}

void SBMEQGL3DEAModeling::DrawVolume()
{
    //以下注释部分为原始代码，新代码修改于2015/06/21
	/*
	if (m_nSystemType == -1)
        return;

    glLineWidth(1);
    qglColor(Qt::blue);
    if (m_nSystemType == AURORA_SYSTEM)
    {
        GLfloat deepth[2] = {50, m_bIsExtendedVolume ? 660 : 550};
        GLfloat width = m_bIsExtendedVolume ? 980 : 500;
        GLfloat height = 500;
        GLfloat VolumePoints[2][4][3];
        for (int i = 0; i < 2; i++)
        {
            VolumePoints[i][0][0] = -width / 2;
            VolumePoints[i][0][1] = height / 2;
            VolumePoints[i][0][2] = -deepth[i];
            VolumePoints[i][1][0] = width / 2;
            VolumePoints[i][1][1] = height / 2;
            VolumePoints[i][1][2] = -deepth[i];
            VolumePoints[i][2][0] = width / 2;
            VolumePoints[i][2][1] = -height / 2;
            VolumePoints[i][2][2] = -deepth[i];
            VolumePoints[i][3][0] = -width / 2;
            VolumePoints[i][3][1] = -height / 2;
            VolumePoints[i][3][2] = -deepth[i];
        }
        for (int i = 0; i < 2; i++)
        {
            glBegin(GL_LINE_LOOP);
            for (int j = 3; j >= 0; j--)
                glVertex3f(VolumePoints[i][j][0], VolumePoints[i][j][1], VolumePoints[i][j][2]);
            glEnd();
        }
        for (int j = 0; j < 4; j++)
        {
            glBegin(GL_LINES);
            for (int i = 0; i < 2; i++)
                glVertex3f(VolumePoints[i][j][0], VolumePoints[i][j][1], VolumePoints[i][j][2]);
            glEnd();
        }
    }
    else
    {
        static const GLfloat deepth[4] = {950, 1532, 2400, 3000};
        static const GLfloat width[4] = {480, 1144, 1566, 1856};
        static const GLfloat height[4] = {448, 796, 1312, 1470};
        GLfloat VolumePoints[4][4][3];
        for (int i = 0; i < 4; i++)
        {
            VolumePoints[i][0][0] = -width[i] / 2;
            VolumePoints[i][0][1] = height[i] / 2;
            VolumePoints[i][0][2] = -deepth[i];
            VolumePoints[i][1][0] = width[i] / 2;
            VolumePoints[i][1][1] = height[i] / 2;
            VolumePoints[i][1][2] = -deepth[i];
            VolumePoints[i][2][0] = width[i] / 2;
            VolumePoints[i][2][1] = -height[i] / 2;
            VolumePoints[i][2][2] = -deepth[i];
            VolumePoints[i][3][0] = -width[i] / 2;
            VolumePoints[i][3][1] = -height[i] / 2;
            VolumePoints[i][3][2] = -deepth[i];
        }

        for (int i = 0; i < (m_bIsExtendedVolume ? 4 : 3); ++i)
        {
            glBegin(GL_LINE_LOOP);
            for (int j = 3; j >= 0; j--)
                glVertex3f(VolumePoints[i][j][0], VolumePoints[i][j][1], VolumePoints[i][j][2]);
            glEnd();
        }
        for (int j = 0; j < 4; j++)
        {
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < (m_bIsExtendedVolume ? 4 : 3); ++i)
                glVertex3f(VolumePoints[i][j][0], VolumePoints[i][j][1], VolumePoints[i][j][2]);
            glEnd();
        }
    }
	*/

	//新代码
	if (m_nSystemType == -1)
        return;
    glLineWidth(1);
    glColor4f(0.0f, 0.0f, 1.0f, 0.0f);

    if (m_nSystemType == AURORA_SYSTEM)
    {
        glBegin(GL_LINE_LOOP);
		for(GLfloat fVaule = 0; fVaule <= 2.0f * GL_PI; fVaule += 0.005f)
			glVertex3f(250.0f * cos(fVaule), 41.0f, 250.0f * sin(fVaule));
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-250.0f, 0.0f + 41.0f, 0.0f);
		glVertex3f(-250.0f, 50.0f * sqrt(119.0f) + 41.0f, 0.0f);
		glVertex3f(250.0f, 0.0f + 41.0f, 0.0f);
		glVertex3f(250.0f, 50.0f * sqrt(119.0f) + 41.0f, 0.0f);
		glVertex3f(0.0f, 0.0f + 41.0f, 250.0f);
		glVertex3f(0.0f, 50.0f * sqrt(119.0f) + 41.0f, 250.0f);
		glVertex3f(0.0f, 0.0f + 41.0f, -250.0f);
		glVertex3f(0.0f, 50.0f * sqrt(119.0f) + 41.0f, -250.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
		for(GLfloat fVaule = 0; fVaule <= 2.0f * GL_PI; fVaule += 0.005f)
			glVertex3f(250.0f * cos(fVaule), 50.0f * sqrt(119.0f) + 41.0f, 250.0f * sin(fVaule));
		glEnd();
		
		if (m_bIsExtendedVolume)
		{
			glBegin(GL_LINE_STRIP);
			for(GLfloat fVaule = atan(50.0f * sqrt(119.0f) / 250.0f); fVaule <= GL_PI - atan(50.0f * sqrt(119.0f) / 250.0f); fVaule += 0.005f)
				glVertex3f(600.0f * cos(fVaule), 600.0f * sin(fVaule) + 41.0f, 0.0f);
			glEnd();

			glBegin(GL_LINE_STRIP);
			for(GLfloat fVaule = atan(50.0f * sqrt(119.0f) / 250.0f); fVaule <= GL_PI - atan(50.0f * sqrt(119.0f) / 250.0f); fVaule += 0.005f)
				glVertex3f(0.0F, 600.0f * sin(fVaule) + 41.0f, 600.0f * cos(fVaule));
			glEnd();
		}

		glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(500.0f, 0.0f, 500.0f);
		glVertex3f(-500.0f, 0.0f, 500.0f);
		glVertex3f(-500.0f, 0.0f, -500.0f);
		glVertex3f(500.0f, 0.0f, -500.0f);
		glEnd();

		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
    }
    else
    {
        //此分支语句用于扩展Polaris定位系统，可参考原始代码
    }
}

void SBMEQGL3DEAModeling::DrawCoordinate()    //相机坐标系模型
{
    //以下注释部分为原始代码，新代码修改于2015/06/21
	/*
	glPushMatrix();    //在坐标系平移变换之前务必压栈保存当前转换矩阵，最后再出栈。
    float scale = 1;
    if (m_nSystemType == AURORA_SYSTEM)
        scale = 0.35;
    if (m_ViewType != AddView)    //注意先平移再旋转
    {
        glTranslatef(-170, 170, -70);
        scale = 0.08;
    }
    glRotatef(m_rotationX, 1.0, 0.0, 0.0);
    glRotatef(m_rotationY, 0.0, 1.0, 0.0);
    glRotatef(m_rotationZ, 0.0, 0.0, 1.0);

    glLineWidth(3);
    qglColor(Qt::white);
    //glutSolidSphere(30 * scale, 15, 15);
	
    glBegin(GL_LINES);

    qglColor(Qt::red);
    glVertex3f(0, 0, 0);
    glVertex3f(-300 * scale, 0, 0);
    glVertex3f(-300 * scale, 0, 0);
    glVertex3f(-250 * scale, 50 * scale, 0);
    glVertex3f(-300 * scale, 0, 0);
    glVertex3f(-250 * scale, -50 * scale, 0);
    glVertex3f(-350 * scale, 0, 0);
    glVertex3f(-380 * scale, 30 * scale, 0);
    glVertex3f(-350 * scale, 0, 0);
    glVertex3f(-320 * scale, 30 * scale, 0);
    glVertex3f(-350 * scale, 0, 0);
    glVertex3f(-350 * scale, -50 * scale, 0);
    
	qglColor(Qt::green);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -300 * scale, 0);
    glVertex3f(0, -300 * scale, 0);
    glVertex3f(-50 * scale, -250 * scale, 0);
    glVertex3f(0, -300 * scale, 0);
    glVertex3f(50 * scale, -250 * scale, 0);
    glVertex3f(-30 * scale, -320 * scale, 0);
    glVertex3f(30 * scale, -380 * scale, 0);
    glVertex3f(30 * scale, -320 * scale, 0);
    glVertex3f(-30 * scale, -380 * scale, 0);
    
	qglColor(Qt::blue);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 300 * scale);
    glVertex3f(0, 0, 300 * scale);
    glVertex3f(-50 * scale, 0, 250 * scale);
    glVertex3f(0, 0, 300 * scale);
    glVertex3f(50 * scale, 0, 250 * scale);
    glVertex3f(-30 * scale, 0, 360 * scale);
    glVertex3f(30 * scale, 0, 360 * scale);
    glVertex3f(30 * scale, 0, 360 * scale);
    glVertex3f(-30 * scale, 0, 310 * scale);
    glVertex3f(-30 * scale, 0, 310 * scale);
    glVertex3f(30 * scale, 0, 310 * scale);

    glEnd();
    glPopMatrix();
	*/

	//新代码
	float scale = 0.2;
	if (m_ViewType == AddView)
		scale = 1;

	glLineWidth(2);
    glBegin(GL_LINES);

    qglColor(Qt::red);
    glVertex3f(0,          0,            0);
    glVertex3f(0,          0, -300 * scale);
    glVertex3f(0,          0, -300 * scale);
	glVertex3f( 25* scale, 0, -250 * scale);
	glVertex3f(0,          0, -300 * scale);
	glVertex3f(-25* scale, 0, -250 * scale);

	glVertex3f( 50 * scale,  25 * scale, -300 * scale);
	glVertex3f(100 * scale, -25 * scale, -300 * scale);
	glVertex3f(100 * scale,  25 * scale, -300 * scale);
	glVertex3f( 50 * scale, -25 * scale, -300 * scale);
    
	qglColor(Qt::green);
    glVertex3f(0,            0,           0);
    glVertex3f(-300 * scale, 0,           0);
    glVertex3f(-300 * scale, 0,           0);
    glVertex3f(-250 * scale, 0,  25 * scale);
	glVertex3f(-300 * scale, 0,           0);
	glVertex3f(-250 * scale, 0, -25 * scale);

	glVertex3f(-275 * scale,  -50 * scale, 0);
	glVertex3f(-300 * scale,  -75 * scale, 0);
	glVertex3f(-325 * scale,  -50 * scale, 0);
	glVertex3f(-300 * scale,  -75 * scale, 0);
	glVertex3f(-300 * scale,  -75 * scale, 0);
	glVertex3f(-300 * scale, -100 * scale, 0);
    
	qglColor(Qt::blue);
    glVertex3f(0,                      0, 0);
    glVertex3f(0,           -300 * scale, 0);
    glVertex3f(0,           -300 * scale, 0);
    glVertex3f(-25 * scale, -250 * scale, 0);
    glVertex3f(0,           -300 * scale, 0);
    glVertex3f( 25 * scale, -250 * scale, 0);

	glVertex3f( 50 * scale, -300 * scale, 0);
	glVertex3f(100 * scale, -300 * scale, 0);
	glVertex3f(100 * scale, -300 * scale, 0);
	glVertex3f( 50 * scale, -350 * scale, 0);
	glVertex3f( 50 * scale, -350 * scale, 0);
	glVertex3f(100 * scale, -350 * scale, 0);

    glEnd();
}

void SBMEQGL3DEAModeling::Draw3DModel()
{
	float x, y, z;

	//testing
	//int a = m_pDeformationModel->GetPoints3DNum();
	//int b = a;
	//testing

    for (int i = 0; i != m_pDeformationModel->GetPoints3DNum(); i++)
    {
        if (m_pColorMappingBar != NULL)
        {
            QColor Color = m_pColorMappingBar->ColorMapping(i, m_pDeformationModel->GetPoints3DNum());
            m_CapturedPointsColor[i] = i * 255 / m_pDeformationModel->GetPoints3DNum();
            qglColor(Color);
        }
        //glPushMatrix();
        x = m_pDeformationModel->GetPoints3DPoint(i)[0] - m_translationX;
        y = m_pDeformationModel->GetPoints3DPoint(i)[1] - m_translationY;
        z = m_pDeformationModel->GetPoints3DPoint(i)[2] - m_translationZ;
        //glTranslatef(-y, -x, z);
        //glutSolidSphere(0.5f, 10, 10);
        //glPopMatrix();

		//修改于2015/06/22
		glPointSize(3);
	    glBegin(GL_POINTS);
	    glVertex3f(-y, -z, -x);
	    glEnd();
		glPointSize(1);
    }

    if (m_bViewOnlySampledPoints)
        return;

    qglColor(Qt::blue);

    int num = m_pDeformationModel->GetGridPointsNum();
    for (int i = 0; i<num; i++)
    {
        //glPushMatrix();
        x = m_pDeformationModel->GetGridPointsPoint(i)[0] - m_translationX;
        y = m_pDeformationModel->GetGridPointsPoint(i)[1] - m_translationY;
        z = m_pDeformationModel->GetGridPointsPoint(i)[2] - m_translationZ;
        //glTranslatef(-y, -x, z);
        //glutSolidSphere(0.05f, 5, 5);
        //glPopMatrix();
		
		//修改于2015/06/22
	    glBegin(GL_POINTS);
	    glVertex3f(-y, -z, -x);
	    glEnd();
    }
    
	if (m_bIsColoring)
        Coloring();

    glBegin(GL_TRIANGLES);
    float trianglepoints[3][3];
    float normal[3] = {-1, -1, -1};
    for (int i = 0; i < m_pDeformationModel->GetTriangleNum(); i++)
    {
        glPushMatrix();
        int trianglepointsindex[3];
        m_pDeformationModel->GetTrianglePointIndex(i, trianglepointsindex);
        for (int j = 0; j < 3; j++)
        {
            //trianglepoints[j][0] = -(m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[1] - m_translationY);
            //trianglepoints[j][1] = -(m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[0] - m_translationX);
            //trianglepoints[j][2] = m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[2] - m_translationZ;

			//修改于2015/06/22
			trianglepoints[j][0] = -(m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[1] - m_translationY);
            trianglepoints[j][1] = -(m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[2] - m_translationZ);
            trianglepoints[j][2] = -(m_pDeformationModel->GetGridPointsPoint(trianglepointsindex[j])[0] - m_translationX);
        }
        int color = (m_GridPointColor[trianglepointsindex[0]] + m_GridPointColor[trianglepointsindex[1]] + m_GridPointColor[trianglepointsindex[2]]) / 3;
        if ((m_pColorMappingBar != NULL) && (m_bIsColoring))
        {
            QColor TriangleColor = m_pColorMappingBar->ColorMapping(color, 256);
            qglColor(TriangleColor);
        }
        else
            qglColor(Qt::blue);
        Normal(trianglepoints, normal);
        int pointorder[3];
        if (m_bViewInModel)
        {
            if (!NormalCorrect(trianglepoints, normal))
            {
                pointorder[0] = 2;
                pointorder[1] = 1;
                pointorder[2] = 0;
            }
            else
            {
                pointorder[0] = 0;
                pointorder[1] = 1;
                pointorder[2] = 2;
            }
        }
        else
        {
            if (NormalCorrect(trianglepoints, normal))
            {
                pointorder[0] = 2;
                pointorder[1] = 1;
                pointorder[2] = 0;
            }
            else
            {
                pointorder[0] = 0;
                pointorder[1] = 1;
                pointorder[2] = 2;
            }
        }
        glVertex3fv(trianglepoints[pointorder[0]]);
        glVertex3fv(trianglepoints[pointorder[1]]);
        glVertex3fv(trianglepoints[pointorder[2]]);
        glPopMatrix();
    }
    glEnd();
}

void SBMEQGL3DEAModeling::DrawHandle()
{
    for (int i = 0; i < m_nHandlesEnabled; i++)
    {
        if (m_HandlesEnbaledFlag[i])
        {
            glPushMatrix();
            qglColor(m_HandleColors[i]);
            glTranslatef(-(m_HandleXfms[i].translation.y - m_translationY),
                         -(m_HandleXfms[i].translation.x - m_translationX),
                           m_HandleXfms[i].translation.z - m_translationZ);

            if (m_ViewType == AddView);
                //glutSolidSphere(m_bIsLargerSymbol ? 15 : 15, 15, 15);
            else;
                //glutSolidSphere(m_bIsLargerSymbol ? 2 : 1, 15, 15);
            DrawCatheter(i);
            glPopMatrix();
        }
    }
}

void SBMEQGL3DEAModeling::DrawCatheter(int idx)
{
    switch (m_HandleModel[idx])
    {
    case 0:
        DrawDefaultCatheter(idx);
        break;
    case 1:
        DrawLineCatheter(idx);
        break;
    case 2:
        DrawSpiralCatheter(idx);
        break;
    case 3:
        DrawSphereCatheter(idx);
        break;
    }
}

void SBMEQGL3DEAModeling::DrawDefaultCatheter(int idx)
{
    qglColor(Qt::white);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    if (m_ViewType == AddView)
        glVertex3f(-m_HandleDirection[idx].directionx * 100, -m_HandleDirection[idx].directiony * 100, -m_HandleDirection[idx].directionz * 100);
    else
        glVertex3f(-m_HandleDirection[idx].directionx * 20, -m_HandleDirection[idx].directiony * 20, -m_HandleDirection[idx].directionz * 20);
    glEnd();
}

void SBMEQGL3DEAModeling::DrawLineCatheter(int idx)
{
    qglColor(Qt::blue);
    glLineWidth(15);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(-m_HandleDirection[idx].directionx * 4, -m_HandleDirection[idx].directiony * 4, -m_HandleDirection[idx].directionz * 4);
    qglColor(Qt::white);
    glVertex3f(-m_HandleDirection[idx].directionx * 8, -m_HandleDirection[idx].directiony * 8, -m_HandleDirection[idx].directionz * 8);
    qglColor(Qt::blue);
    glVertex3f(-m_HandleDirection[idx].directionx * 12, -m_HandleDirection[idx].directiony * 12, -m_HandleDirection[idx].directionz * 12);
    qglColor(Qt::white);
    glVertex3f(-m_HandleDirection[idx].directionx * 20, -m_HandleDirection[idx].directiony * 20, -m_HandleDirection[idx].directionz * 20);
    glEnd();
}

void SBMEQGL3DEAModeling::DrawSpiralCatheter(int idx)
{
    DrawDefaultCatheter(idx);
    int NumOfElectrode = 16;
    int electroderate = 2;
    int Radius = 10;
    GLfloat deepth = 2;
    int color = 0;
    GLfloat angle;
    Position3d pnt, pnt2;
    pnt.z = 0;
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NumOfElectrode; i++)
    {
        qglColor(Qt::white);
        angle = 2 * GL_PI * i / NumOfElectrode;
        pnt.x = Radius * sin(angle);
        pnt.y = Radius * cos(angle);
        pnt.z = deepth * i / NumOfElectrode;
        QuatRotatePoint(&m_HandleXfms[idx].rotation, &pnt, &pnt2);
        glVertex3f(-pnt2.y, -pnt2.x, pnt2.z);
        qglColor(Qt::blue);
        angle += 2 * GL_PI / NumOfElectrode / (electroderate + 1);
        pnt.x = Radius * sin(angle);
        pnt.y = Radius * cos(angle);
        pnt.z += deepth / NumOfElectrode / (electroderate + 1);
        QuatRotatePoint(&m_HandleXfms[idx].rotation, &pnt, &pnt2);
        glVertex3f(-pnt2.y, -pnt2.x, pnt2.z);
    }
    glEnd();
}

void SBMEQGL3DEAModeling::DrawSphereCatheter(int idx)
{
    DrawDefaultCatheter(idx);
    GLfloat theta, phi;
    int Radius = 10;
    Position3d pnt, pnt2;
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 8; i++)
    {
        phi = 2 * GL_PI * i / 8;
        for (int j = 0; j <= 8; j++)
        {
            qglColor(Qt::white);
            theta = 2 * GL_PI * j / 8;
            pnt.x = Radius * sin(theta) * cos(phi);
            pnt.y = Radius * sin(theta) * sin(phi);
            pnt.z = Radius * cos(theta);
            QuatRotatePoint(&m_HandleXfms[idx].rotation, &pnt, &pnt2);
            glVertex3f(-pnt2.y, -pnt2.x, pnt2.z);
            qglColor(Qt::blue);
            theta += 2 * GL_PI / 16;
            pnt.x = Radius * sin(theta) * cos(phi);
            pnt.y = Radius * sin(theta) * sin(phi);
            pnt.z = Radius * cos(theta);
            QuatRotatePoint(&m_HandleXfms[idx].rotation, &pnt, &pnt2);
            glVertex3f(-pnt2.y, -pnt2.x, pnt2.z);
        }
    }
}

void SBMEQGL3DEAModeling::m_slotRefreshWithMainView(GLfloat scaling, GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
    m_scaling = scaling;

    m_rotationX = rotationX;
    m_rotationY = rotationY;
    m_rotationZ = rotationZ;

    updateGL();
}

void SBMEQGL3DEAModeling::m_slotRefreshModel()
{
    if (m_ViewType != AddView)
    {
        double centerPoint[3];
        m_pDeformationModel->GetCenter(centerPoint);
        SetTranslation(centerPoint[0], centerPoint[1], centerPoint[2]);
    }
    m_bIsColored = false;
    updateGL();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithFocalDistance(int FD)
{
    m_nFocusDistance = FD;
    updateGL();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithPupilDistance(int PD)
{
    m_nPupilDistance = PD;
    updateGL();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithFovy(int Fovy)
{
    m_nFovy = Fovy;
    SetProjection(width(), height());
    updateGL();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithColorBar()
{
    update();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithColoringFlag(bool iscoloring)
{
    m_bIsColoring = iscoloring;
    update();
}

void SBMEQGL3DEAModeling::m_slotRefreshWithColoringRadius(float ColoringRadius)
{
    m_fColoringRadius = ColoringRadius;
    m_bIsColored = false;
    Coloring();
    update();
}
