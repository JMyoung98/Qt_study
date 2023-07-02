#include <QApplication>
#include "CustomWidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    CustomWidget *widget = new CustomWidget(0);
    QObject::connect(widget,SIGNAL(widgetClicked()),&app,SLOT(quit()));
    widget->show(); 		/* 위젯의 화면 표시 */

    return app.exec();
}
