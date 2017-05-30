

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplashScreen>


#include <Quarter/Quarter.h>
#include <Quarter/QuarterWidget.h>
#include <Inventor/nodes/SoNodes.h>


int
main(int n_app_args, char **app_arg)
{
  //  Initialize an application.
  QApplication application(n_app_args, app_arg);

  //  Create the main window.
  QMainWindow * mainWindow = new QMainWindow();

  // Initialize Quarter (and Inventor).
  SIM::Coin3D::Quarter::Quarter::init();

  SoSeparator * root = new SoSeparator();
  root->ref();

  if (n_app_args == 1)
    {
      //  Make a scene containing a red sphere.
      SoMaterial * material = new SoMaterial();
      material->diffuseColor.setValue(1.0F, 0.0F, 0.0F); // Red
      SoSphere * sphere = new SoSphere();
      root->addChild(material);
      root->addChild(sphere);
    }
  else
    {
      //  Make a scene with the contents of the Inventor file.
      SoFile * file = new SoFile();
      file->name.setValue(app_arg[1]);
      root->addChild(file);
    }

  //  Create the viewer.
  SIM::Coin3D::Quarter::QuarterWidget * viewer = new SIM::Coin3D::Quarter::QuarterWidget(mainWindow);
  QColor backgroundColor;
  backgroundColor.setRgbF(0.7, 0.7, 0.9);
  viewer->setBackgroundColor(backgroundColor);
  viewer->setNavigationModeFile();
  viewer->setSceneGraph(root);
  viewer->show();
  mainWindow->setCentralWidget(viewer);
  mainWindow->resize(800, 600);
  mainWindow->show();

  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));

  auto ok = application.exec();

  root->removeAllChildren();
  root->unref();
  delete viewer;

  SIM::Coin3D::Quarter::Quarter::clean();

  return ok;
}

