#include "app_window.hpp"
#include "shaders.h"

QOpenGLShaderProgram *SHADER_PROGRAM;

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


bool AppWindow::prepareShaders()
{
  SHADER_PROGRAM = new QOpenGLShaderProgram(this);
  QOpenGLShader *vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex, SHADER_PROGRAM);
  QOpenGLShader *fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment, SHADER_PROGRAM);
  
  if ( !vertex_shader->compileSourceCode(MITED_SHADERS::vertex) )
  {
    std::cout << "Vertex compile:\n" << vertex_shader->log().toStdString() << std::endl;
    delete vertex_shader;
    return false;
  }

  if( !fragment_shader->compileSourceCode(MITED_SHADERS::fragment))
  {
    std::cout << "Fragment compile:\n" << vertex_shader->log().toStdString() << std::endl;
    delete vertex_shader;
    delete fragment_shader;
    return false;
  }

  SHADER_PROGRAM->addShader(vertex_shader);
  SHADER_PROGRAM->addShader(fragment_shader);

  if(!SHADER_PROGRAM->link())
  {
    std::cout << "Linker: \n" << SHADER_PROGRAM->log().toStdString() << std::endl;
    delete vertex_shader;
    delete fragment_shader;
    return false;
  }
  return true;
}

void GLCanvas::initializeGL()
{
  AppWindow *win = ((AppWindow*)parentWidget());
  QCoreApplication *app = QApplication::instance();
  // Set up the rendering context, load shaders and other resources, etc.:
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  if( win->prepareShaders() ) { SHADER_PROGRAM->bind(); } else {QMetaObject::invokeMethod(app, "quit", Qt::QueuedConnection);}
}

void GLCanvas::paintGL()
{
  // Draw the scene:
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClear(GL_COLOR_BUFFER_BIT);
}




