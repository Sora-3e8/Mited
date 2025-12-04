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
#include <iostream>
#include <QApplication>

class GLCanvas : public QOpenGLWidget 
{

  public:
    GLCanvas(QWidget *parent) : QOpenGLWidget(parent){};

  protected:
    void initializeGL() override;
    void paintGL() override;

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
