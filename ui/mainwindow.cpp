#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->removeButton->setEnabled(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_addButton_clicked() {
  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, tr("Selectionnez vos images"), "C:/users/cedri/Downloads",
      tr("Image (*.jpg *.jpeg *.JPG *.JPEG *.png *.PNG *.webp *.jfif *.avif)"));
  ui->selectedItemsList->addItems(fileNames);
  for (int i = 0; i < ui->selectedItemsList->count(); ++i) {
    ui->selectedItemsList->item(i)->setCheckState(Qt::Unchecked);
  }
}

void MainWindow::on_removeButton_clicked() {
  QList<QListWidgetItem *> toDelete = QList<QListWidgetItem *>();
  for (int id : m_idsToRemove) {
    auto item = ui->selectedItemsList->item(id);
    if (item)
      toDelete << item;
  }

  qDeleteAll(toDelete);
  m_idsToRemove.clear();
  ui->removeButton->setEnabled(false);
  ui->selectedItemsList->repaint();
}

void MainWindow::on_selectedItemsList_itemChanged(QListWidgetItem *item) {
  int row = ui->selectedItemsList->row(item);
  if (item->checkState() == Qt::Checked) {
    m_idsToRemove << row;
  } else {
    if (m_idsToRemove.contains(row))
      m_idsToRemove.removeOne(row);
  }

  ui->removeButton->setEnabled(!m_idsToRemove.isEmpty());
}

void MainWindow::on_resizeButton_clicked() {
  int errorIndex = 0;
  while (ui->selectedItemsList->count() > 0 &&
         errorIndex < ui->selectedItemsList->count()) {
    auto item = ui->selectedItemsList->item(errorIndex);
    try {
      cv::Mat currentImage = cv::imread(item->text().toStdString(), cv::IMREAD_COLOR);
      cv::Mat resizedImage = m_resizeTool.resize(currentImage);
      QString filenameExtension = item->text().split("/").last();
      QString filename = "";
      auto splittedPoints = filenameExtension.split(".");
      for (int i = 0; i < splittedPoints.count()-1; ++i)
        filename += splittedPoints[i];
      QString filepath = QString("C:/users/cedri/Documents/ani-love/images/produits/%1.jpg").arg(filename);
      cv::imwrite(filepath.toStdString(), resizedImage);
      ui->selectedItemsList->removeItemWidget(item);
      delete item;
    } catch (...) {
      ++errorIndex;
      continue;
    }
  }
}
