#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include <QMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getFontFamilies();
    initGUI();
    initAPP();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAPP()
{
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());//窗口居中显示
//    ui->textBrowser_Output->installEventFilter(this);   //为textBrowser安装事件过滤器
}

//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//    if (obj != ui->textBrowser_Output || event->type() != QEvent::Wheel)
//        return QWidget::eventFilter(obj, event);

//    auto *wheelEvent = static_cast<QWheelEvent *>(event);
//    if (!(wheelEvent->modifiers() & Qt::ControlModifier))
//        return false;

//    if (wheelEvent->inverted())//远离操作者，即放大
//        ui->textBrowser_Output->zoomIn();
//    else
//        ui->textBrowser_Output->zoomOut();

//    //可以向ui->spinBox_FontSize发送信号emit xxx

//return true;
//}

void MainWindow::initGUI()
{
    auto *pVLayout_main = new QVBoxLayout;

    auto *pHLayout_Input1 = new QHBoxLayout;
    pHLayout_Input1->addWidget(ui->label_Input);
    pHLayout_Input1->addWidget(ui->pushButton_About);
    ui->pushButton_About->setFixedWidth(30);

    pVLayout_main->addLayout(pHLayout_Input1);          //#V0
    pVLayout_main->addWidget(ui->plainTextEdit_Input);  //#V1

    //字体属性设置
    auto *pHLayout_FontAttribute = new QHBoxLayout;
    pHLayout_FontAttribute->addWidget(ui->checkBox_Bold);
    pHLayout_FontAttribute->addWidget(ui->checkBox_Itailic);
    pHLayout_FontAttribute->addWidget(ui->checkBox_Underline);
    pHLayout_FontAttribute->addWidget(ui->checkBox_Chinese);
    auto *pGroupBox_FontAttribute = new QGroupBox(tr("字体属性"));
    pGroupBox_FontAttribute->setStyleSheet("QGroupBox{font-size:14px}");
    pGroupBox_FontAttribute->setLayout(pHLayout_FontAttribute);
    pHLayout_FontAttribute->setContentsMargins(40,8,40,8);

    //字体大小设置
    auto *pHLayout_FontSize = new QHBoxLayout;
    pHLayout_FontSize->addWidget(ui->label_FontSize);
    pHLayout_FontSize->addWidget(ui->spinBox_FontSize);
    auto *pGroupBox_FontSize = new QGroupBox(tr("字体大小"));
    pGroupBox_FontSize->setStyleSheet("QGroupBox{font-size:14px}");
    pGroupBox_FontSize->setLayout(pHLayout_FontSize);

    pHLayout_FontSize->setContentsMargins(30,8,30,8);

    //字体属性、字体大小水平布局
    auto *pHLayout_Font = new QHBoxLayout;
    pHLayout_Font->addWidget(pGroupBox_FontAttribute);
    pHLayout_Font->addWidget(pGroupBox_FontSize);
    pHLayout_Font->setStretch(0,4);
    pHLayout_Font->setStretch(1,1);

    pVLayout_main->addLayout(pHLayout_Font);                //#V2

    pVLayout_main->addSpacing(9);
    pVLayout_main->addWidget(ui->textBrowser_Output);       //#V3

    pVLayout_main->setStretch(0, 1);
    pVLayout_main->setStretch(1, 2);
    pVLayout_main->setStretch(2, 1);
    pVLayout_main->setStretch(4, 15);

    centralWidget()->setLayout(pVLayout_main);
    centralWidget()->setContentsMargins(8,8,8,8);
}

QString MainWindow::getHTML()
{
    auto textString =  ui->plainTextEdit_Input->toPlainText();

//    QString sHTML(tr(""
//                     "<!DOCTYPE html>"
//                     "<html>"
//                     "<head> "
//                     "<meta charset=&quot;utf-8&quot;>"
//                     "<title>五星出东方利中国</title>"
//                     "</head>"
//                     "<body>"
//                     ""));

    QString sHTML("");

    int index = 0;
    for (const QString &family : fontFamilies)
    {
        QString sParagraph =
                tr("<p style=\"font-family:%1;color:%2;font-size:%3px\">%4：%5</p>").arg(family).arg(index%2==0?"Black":"Green").arg(ui->spinBox_FontSize->value()).arg(family).arg(textString);

        if (ui->checkBox_Bold->isChecked())//字体加粗
            sParagraph = tr("<b>%1</b>").arg(sParagraph);

        if (ui->checkBox_Itailic->isChecked())//字体倾斜
            sParagraph = tr("<i>%1</i>").arg(sParagraph);

        if (ui->checkBox_Underline->isChecked())//字体下划线
            sParagraph = tr("<u>%1</u>").arg(sParagraph);

        sHTML += sParagraph;
        index++;
    }


//    sHTML +=tr(""
//               "</body>"
//               "</html>"
//               "");

    return sHTML;
}

void MainWindow::getFontFamilies()
{
    fontFamilies = ui->checkBox_Chinese->isChecked()?QFontDatabase::families(QFontDatabase::SimplifiedChinese):QFontDatabase::families();
}

void MainWindow::on_checkBox_Bold_stateChanged(int arg1)
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
        return;

    auto sParagraph = getHTML();
    if (ui->checkBox_Bold->isChecked())//字体加粗
        sParagraph = tr("<b>%1</b>").arg(sParagraph);
    else
    {
        sParagraph.replace(QRegularExpression("<b>"), "");
        sParagraph.replace(QRegularExpression("</b>"), "");
    }

    ui->textBrowser_Output->setHtml(getHTML());
}

void MainWindow::on_checkBox_Itailic_stateChanged(int arg1)
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
        return;

    ui->textBrowser_Output->setFontItalic(ui->checkBox_Itailic->isChecked());
    ui->textBrowser_Output->setHtml(getHTML());
}

void MainWindow::on_checkBox_Underline_stateChanged(int arg1)
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
        return;

    ui->textBrowser_Output->setFontUnderline(ui->checkBox_Underline->isChecked());
    ui->textBrowser_Output->setHtml(getHTML());
}

void MainWindow::on_checkBox_Chinese_stateChanged(int arg1)
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
        return;

    fontFamilies = ui->checkBox_Chinese->isChecked()?QFontDatabase::families(QFontDatabase::SimplifiedChinese):QFontDatabase::families();
    ui->textBrowser_Output->setHtml(getHTML());
}

void MainWindow::on_spinBox_FontSize_textChanged(const QString &arg1)
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
        return;

    auto sParagraph = getHTML();
    sParagraph.replace(QRegularExpression("font-size:[0-9]+px"), tr("font-size:%1px").arg(ui->spinBox_FontSize->value()));
    ui->textBrowser_Output->setHtml(sParagraph);
}

void MainWindow::on_pushButton_About_clicked()
{
    QMessageBox::information(this, tr("关于…"),
                             tr("天女散花字体秀(FontShow)，以可视化方式辅助各类设计人员进行字体选择。\n\r"
                                "小工具用后即扔，免费、绿色、无公害。\n\r"
                                "———五星出东方利中国系列出品。\n\r"
                                "邮件地址：P299792458@qq.com"));
}

void MainWindow::on_plainTextEdit_Input_textChanged()
{
    if (ui->plainTextEdit_Input->toPlainText().length() == 0)
    {
        ui->textBrowser_Output->clear();
        return;
    }

    auto shtml = getHTML();
    ui->textBrowser_Output->setHtml(shtml);
}
