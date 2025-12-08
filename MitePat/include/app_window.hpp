#pragma once
#include <Qt>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QDockWidget>
#include <QBoxLayout>
#include <QToolBar>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <iostream>
#include <QApplication>
#include <QMatrix4x4>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QList>
#include <QDebug>

class GLCanvas : public QOpenGLWidget, protected QOpenGLFunctions 
{

  public:
    GLCanvas(QWidget *parent) : QOpenGLWidget(parent){};
    QOpenGLShaderProgram SHADER_PROGRAM;

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    bool prepareShaders();
    void prepareRect();

};

class AppWindow : public QMainWindow {
  public:
      AppWindow();
      ~AppWindow() override;
      GLCanvas *canvas;

  private:
      void toolbars_init();
      void docks_init();
      QDockWidget *projfiles_dock;
      QDockWidget *tag_tooldock;
      QToolBar *top_toolbar;
      QToolBar *bottom_toolbar;
};
