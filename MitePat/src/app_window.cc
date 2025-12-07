#include "app_window.hpp"
#include "shaders.h"

QOpenGLShaderProgram *SHADER_PROGRAM;
QOpenGLBuffer *RECT_BUFFER;
int SHADER_VIEWMAT;

AppWindow::AppWindow()
{ 
  setWindowTitle("MitePattern");
  canvas = new GLCanvas(this);

  // QSurfaceFormat format;
  // format.setVersion(3, 3); // Set your desired OpenGL version
  // format.setProfile(QSurfaceFormat::CoreProfile);
  // format.setOption(QSurfaceFormat::DebugContext);
  // canvas->setFormat(format);
  toolbars_init();
  docks_init();

  setCentralWidget(canvas);
}

AppWindow::~AppWindow()
{
  SHADER_PROGRAM->release();
  delete SHADER_PROGRAM;
  delete RECT_BUFFER;
  delete canvas;
}

void AppWindow::closeApp()
{
  QApplication::quit();
}

void AppWindow:: toolbars_init()
{
  // | file | edit | view|      | - | o | x |
  top_toolbar = new QToolBar(this);
  top_toolbar->setMovable(false);
  top_toolbar->setFloatable(false);
  top_toolbar->setOrientation(Qt::Horizontal);

  QAction *file_action = new QAction("file",top_toolbar);
  QAction *edit_action = new QAction("edit",top_toolbar);
  QAction *show_action = new QAction("show",top_toolbar);
  top_toolbar->addAction(file_action);
  top_toolbar->addAction(edit_action);
  top_toolbar->addAction(show_action);

  addToolBar(top_toolbar);

  bottom_toolbar = new QToolBar(this);
  bottom_toolbar->setMovable(false);
  bottom_toolbar->setFloatable(false);
  bottom_toolbar->setOrientation(Qt::Horizontal);
  addToolBar(Qt::BottomToolBarArea,bottom_toolbar);

}

void AppWindow::docks_init()
{
  // Project files will go here
  projfiles_dock = new QDockWidget(this);
  projfiles_dock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
  projfiles_dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
  addDockWidget(Qt::LeftDockWidgetArea,projfiles_dock);

  // Tagging tools will go here
  tag_tooldock = new QDockWidget(this);
  tag_tooldock->setFeatures(QDockWidget::DockWidgetMovable);
  tag_tooldock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
  addDockWidget(Qt::RightDockWidgetArea,tag_tooldock);
}


bool GLCanvas::prepareShaders()
{
  SHADER_PROGRAM = new QOpenGLShaderProgram(this);
  
  bool vertex_succ = SHADER_PROGRAM->addShaderFromSourceCode(QOpenGLShader::Vertex,MITED_SHADERS::vertex);
  bool frag_succ = SHADER_PROGRAM->addShaderFromSourceCode(QOpenGLShader::Fragment,MITED_SHADERS::fragment);
  return (vertex_succ && frag_succ) ? SHADER_PROGRAM->link() : false;
}

void GLCanvas::prepareRect()
{
  int SHADER_POSBUFFER = SHADER_PROGRAM->attributeLocation("pos");
  SHADER_PROGRAM->enableAttributeArray(SHADER_POSBUFFER);
  SHADER_VIEWMAT = SHADER_PROGRAM->uniformLocation("VIEWMAT");
  
  RECT_BUFFER = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  RECT_BUFFER->setUsagePattern(QOpenGLBuffer::StaticDraw);
  RECT_BUFFER->create();
  RECT_BUFFER->bind();
  GLfloat vertices[] = { 0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.1f,0.0f,0.0f };
  RECT_BUFFER->allocate(vertices, sizeof(vertices));
  SHADER_PROGRAM->setAttributeBuffer(SHADER_POSBUFFER, GL_FLOAT, 0, 2);
  RECT_BUFFER->release();

}
void GLCanvas::initializeGL()
{
  makeCurrent();
  QCoreApplication *app = QApplication::instance();
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  std::cout << (prepareShaders() ? (SHADER_PROGRAM->bind() ? "Program bind: success" : "Program bind fail:\n" + SHADER_PROGRAM->log().toStdString() ) : "Shader compile fail:\n" + SHADER_PROGRAM->log().toStdString()) << std::endl;
  if (!SHADER_PROGRAM->isLinked()) QMetaObject::invokeMethod(app, "quit", Qt::QueuedConnection);
  prepareRect();
  std::cout << (isValid() ? "QOpenglWidget: all ok" : "QOpenGlWidget: issues detected") << std::endl;
}

void GLCanvas::paintGL()
{
  // Draw the scene
  SHADER_PROGRAM->bind();
  RECT_BUFFER->bind();
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES,0,6);
  RECT_BUFFER->release();

}

void GLCanvas::resizeGL(int w, int h)
{
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  float aspect = (float)w/(float)h;
  std::cout << "Aspect ratio:" << aspect << std::endl;
  //glViewport(0,0,w,h);
  QMatrix4x4 size_mat(1.0f/aspect,0.0f,0.0f,0.0f,
      0.0f,1.0f,0.0f,0.0f,
      0.0f,0.0f,1.0f,0.0f,
      0.0f,0.0f,0.0f,1.0f);
  //SHADER_PROGRAM->setUniformValue(SHADER_VIEWMAT, size_mat.transposed());
  update();
}




