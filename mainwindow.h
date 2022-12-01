#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QFontDatabase>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_Bold_stateChanged(int arg1);
    void on_checkBox_Itailic_stateChanged(int arg1);
    void on_checkBox_Underline_stateChanged(int arg1);
    void on_checkBox_Chinese_stateChanged(int arg1);
    void on_spinBox_FontSize_textChanged(const QString &arg1);
    void on_pushButton_About_clicked();

    void on_plainTextEdit_Input_textChanged();


private:
    Ui::MainWindow  *ui;
    QStringList     fontFamilies;

    QString getHTML();
    void    getFontFamilies();
    void    initGUI();
    void    initAPP();
};
#endif // MAINWINDOW_H
