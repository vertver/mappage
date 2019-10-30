/*
 * Отрисовка векторных объектов на карте с помощью Canvas.
 * Стандартный подход, предполагающий использование MapViewItem, при большом количестве
 * отрисовываемых объектов (моделей) работает слишком медленно.
 *
 * TODO
 * Не удалось добиться скроллинга без артефактов при малом увеличении: т.е. когда
 * канвас по долготе охватывает весь Земной шар. В качестве временного решения
 * при горизонтальном скроллинге используется принудительная перерисовка.
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScreen>

#include "PolylineModel.h"
#include "trace.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto screens = QGuiApplication::screens();
    SDL_TRACE_ARGS("N of screens", screens.size());

    for (int i = 0, sz = screens.size(); i < sz; ++i) {
        auto screen = screens[i];
        auto rect = screen->geometry();
        SDL_TRACE_ARGS("screen", i, "size", rect.width(), rect.height());
    }

    qmlRegisterType<PolylineModel>("Polyline", 1, 0, "PolylineModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

