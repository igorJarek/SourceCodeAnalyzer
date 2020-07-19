#include "App.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    App app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
