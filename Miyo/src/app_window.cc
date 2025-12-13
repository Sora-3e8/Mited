#include "app_window.hpp"
#include "shaders.h"

QOpenGLShaderProgram *SHADER_PROGRAM;
QOpenGLBuffer *RECT_BUFFER;
int SHADER_VIEWMAT;

AppWindow::AppWindow()
{ 
  setWindowTitle("MitePattern");
  canvas = new GLCanvas(this);
  toolbars_init();
  docks_init();
  setCentralWidget(canvas);
}

AppWindow::~AppWindow()
{
  canvas->SHADER_PROGRAM.release();
  RECT_BUFFER->destroy();
  delete SHADER_PROGRAM;
  delete canvas;
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

void GLCanvas::prepareRect()
{
  int SHADER_POSBUFFER = SHADER_PROGRAM.attributeLocation("vertexBuffer");
  SHADER_PROGRAM.enableAttributeArray(SHADER_POSBUFFER);
  SHADER_VIEWMAT = SHADER_PROGRAM.uniformLocation("VIEWMAT");
  
  RECT_BUFFER = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  RECT_BUFFER->setUsagePattern(QOpenGLBuffer::StaticDraw);
  RECT_BUFFER->create();
  RECT_BUFFER->bind();
  GLfloat vertices[] = { 
    5.0f,5.0f,
    5.0f,-5.0f,
    -5.0f,-5.0f,

    -5.0f,-5.0f,
    -5.0f,5.0f,
    5.0f,5.0f
  };
  RECT_BUFFER->allocate(vertices, sizeof(vertices));
  SHADER_PROGRAM.setAttributeBuffer(0, GL_FLOAT, 0, 2,0);
  std::cout << "Attribute code:" << glGetError() << std::endl;

  RECT_BUFFER->release();
}

bool GLCanvas::prepareShaders()
{
  m_vao.create();
  m_vao.bind();
  SHADER_PROGRAM.create();
  bool vertex_succ = SHADER_PROGRAM.addShaderFromSourceCode(QOpenGLShader::Vertex,MITED_SHADERS::Vertex);
  bool frag_succ = SHADER_PROGRAM.addShaderFromSourceCode(QOpenGLShader::Fragment,MITED_SHADERS::Fragment);
  return (vertex_succ && frag_succ) ? SHADER_PROGRAM.link() : false;
}

void GLCanvas::initializeGL()
{
  initializeOpenGLFunctions();
  QOpenGLContext *ctx = context();
  std::cout << "Version:" <<ctx->format().majorVersion() << "." << ctx->format().minorVersion() << std::endl;
  QCoreApplication *app = QApplication::instance();
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  std::cout << (prepareShaders() ? (SHADER_PROGRAM.bind() ? "Program bind: success" : "Program bind fail:\n" + SHADER_PROGRAM.log().toStdString() ) : "Shader compile fail:\n" + SHADER_PROGRAM.log().toStdString()) << std::endl;
  if (!SHADER_PROGRAM.isLinked()) QMetaObject::invokeMethod(app, "quit", Qt::QueuedConnection);
  prepareRect();
  std::cout << (isValid() ? "QOpenglWidget: all ok" : "QOpenGlWidget: issues detected") << std::endl;
  std::cout << "Version:" << format().majorVersion() << "." << format().minorVersion() << std::endl;
}

void GLCanvas::paintGL()
{
  // Draw the scene
  //glViewport(0,0,width(),height());
  glClear(GL_COLOR_BUFFER_BIT);
  m_vao.bind();
  SHADER_PROGRAM.bind();
  glDrawArrays(GL_TRIANGLES,0,sizeof(float)*6);
  SHADER_PROGRAM.release();
  m_vao.release();
}

void GLCanvas::resizeGL(int w, int h)
{
  m_vao.bind();
  SHADER_PROGRAM.bind();
  float w_f = (float) w;
  float h_f = (float) h;
  float aspect = w_f/h_f;
  float scale = sqrt ( (w_f*w_f) + (h_f*h_f) );
  glViewport(0,0,w,h);
  QMatrix4x4 size_mat(
      1.0f/aspect,0.0f,0.0f,0.0f,
      0.0f,1.0f,0.0f,0.0f,
      0.0f,0.0f,1.0f,0.0f,
      0.0f,0.0f,0.0f,10.0f);
  SHADER_PROGRAM.setUniformValue(SHADER_VIEWMAT, size_mat.transposed());

  SHADER_PROGRAM.release();
  m_vao.release();
  update();

}





