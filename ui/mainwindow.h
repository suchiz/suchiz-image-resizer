#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QListWidgetItem>
#include <QMainWindow>
#include <core/resizetool.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_addButton_clicked();

  void on_removeButton_clicked();

  void on_selectedItemsList_itemChanged(QListWidgetItem *item);

  void on_resizeButton_clicked();

private:
  Ui::MainWindow *ui;
  ResizeTool m_resizeTool;
  QList<uint16_t> m_idsToRemove = QList<uint16_t>();
};
#endif // MAINWINDOW_H
