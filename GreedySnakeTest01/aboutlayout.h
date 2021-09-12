#ifndef OTHERLAYOUT_H
#define OTHERLAYOUT_H
#include <QObject>
#include <QMainWindow>
#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QLabel>
#include <QDebug>
class aboutLayout : public QDialog
{
    Q_OBJECT
public:
    explicit aboutLayout(QWidget *parent = 0);
};
#endif // OTHERLAYOUT_H
