#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // 导入QQmlContext类以设置上下文属性
#include <QQmlComponent>
#include <QIcon>

#include "remotecar.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<RemoteCar>("RemoteCar", 1, 0, "RemoteCar");
    //RemoteCar remoteCarControl;
    // Embedding C++ Objects into QML with Context Properties
    //QQmlContext* ctx = engine.rootContext();
    //ctx->setContextProperty("remoteCarControl", &remoteCarControl);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/rc_car/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {},
        Qt::QueuedConnection);

    engine.load(url);

    //RemoteCar remoteCarControl;
    // Embedding C++ Objects into QML with Context Properties
    //QQmlContext* ctx = engine.rootContext();
    //ctx->setContextProperty("remoteCarControl", &remoteCarControl);
    return app.exec();
}
