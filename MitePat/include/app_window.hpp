#pragma once
#include <Qt>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QDockWidget>
#include <QBoxLayout>
#include <QToolBar>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <iostream>
#include <QApplication>
#include <QMatrix4x4>
#include <QSurfaceFormat>

class GLCanvas : public QOpenGLWidget 
{

  public:
    GLCanvas(QWidget *parent) : QOpenGLWidget(parent){
        // QSurfaceFormat format;
        // format.setVersion(4, 1); // Set your desired OpenGL version
        // format.setProfile(QSurfaceFormat::CompatibilityProfile);
        // setFormat(format);
    };

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

};

class AppWindow : public QMainWindow {
  public:
      AppWindow();
      ~AppWindow() override;
      GLCanvas *canvas;
      bool prepareShaders();
      void closeApp();
  private:
      void toolbars_init();
      void docks_init();

      QDockWidget *projfiles_dock;
      QDockWidget *tag_tooldock;
      QToolBar *top_toolbar;
      QToolBar *bottom_toolbar;
};
