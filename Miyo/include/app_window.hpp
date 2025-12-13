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
#include <QEnterEvent>
#include <QList>
#include <QDebug>
#include <cmath>

class GLCanvas : public QOpenGLWidget, protected QOpenGLFunctions 
{

  public:
    GLCanvas(QWidget *parent) : QOpenGLWidget(parent)
      {
            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            format.setVersion(3, 3);
            format.setProfile(QSurfaceFormat::CoreProfile);
            setFormat(format);
      };
    QOpenGLShaderProgram SHADER_PROGRAM;
    QOpenGLVertexArrayObject m_vao;

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    bool prepareShaders();
    void prepareRect();
    void enterEvent(QEnterEvent *event) override {  };
    void leaveEvent(QEvent *event) override {  };
    void focusInEvent(QFocusEvent *event) override {};

};

class AppWindow : public QMainWindow {
  public:
      AppWindow();
      ~AppWindow() override;
      GLCanvas *canvas;
  protected:
      void enterEvent(QEnterEvent *event) override {  };
      void leaveEvent(QEvent *event) override {  };
      void focusInEvent(QFocusEvent *event) override {};


  private:
      void toolbars_init();
      void docks_init();
      QDockWidget *projfiles_dock;
      QDockWidget *tag_tooldock;
      QToolBar *top_toolbar;
      QToolBar *bottom_toolbar;
};
