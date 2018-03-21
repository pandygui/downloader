#include <DApplication>
#include <DWidgetUtil>
#include <DLog>

#include "mainwindow.h"

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);

    if (!app.setSingleInstance("deepin-downloader")) {
        return -1;
    }

    app.loadTranslator();
    app.setOrganizationName("deepin");
    app.setApplicationName("deepin-downloader");
    app.setApplicationDisplayName(QObject::tr("Deepin Downloader"));
    app.setApplicationVersion("1.0");
    app.setProductIcon(QIcon(":/images/deepin-downloader.svg"));
    app.setProductName(DApplication::translate("MainWindow", "Deepin Downloader"));
    app.setApplicationDescription(DApplication::translate("Main", "Deepin Downloader is a built-in downloading tool of deepin operating system, supporting single and batch download."));

    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    MainWindow w;
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return app.exec();
}
