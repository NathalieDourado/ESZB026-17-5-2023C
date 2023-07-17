#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void makePlot();
    void realtimeDataSlot();
private:
    Ui::MainWindow *ui;
    QTimer dataTimer;
};

#endif // MAINWINDOW_H
