#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class NoiseModuleScene;
class NoiseModule;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);


public slots:
    void itemInserted(NoiseModule *);
    void itemSelected(NoiseModule *);

private slots:
    void on_pushButton_released();


private:
    Ui::MainWindow *ui;
    NoiseModuleScene *nmScene;

};

#endif // MAINWINDOW_H
