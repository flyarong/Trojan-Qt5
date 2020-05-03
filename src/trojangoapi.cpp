#include "trojangoapi.h"
#include "logger.h"
#include "confighelper.h"
#if defined (Q_OS_WIN)
#include <QCoreApplication>
#endif

using namespace api;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

TrojanGoAPI::TrojanGoAPI()
{
    thread = new QThread();
    this->moveToThread(thread);
    connect(thread, SIGNAL(started()), this, SLOT(run()));
}


TrojanGoAPI::~TrojanGoAPI()
{
    stop();
    thread->wait();
    thread = nullptr;
    delete thread;
}

void TrojanGoAPI::setPassword(QString pass)
{
    password = pass;
}

void TrojanGoAPI::start()
{
    running = true;
    thread->start();
}

void TrojanGoAPI::run()
{
#ifdef Q_OS_WIN
    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
#else
    QDir configDir = QDir::homePath() + "/.config/trojan-qt5";
    QString configFile = configDir.absolutePath() + "/config.ini";
#endif

    ConfigHelper *conf = new ConfigHelper(configFile);

    QString address = QString("127.0.0.1:%1").arg(conf->getTrojanAPIPort());

    while (running) {

        Channel = grpc::CreateChannel(address.toStdString(), grpc::InsecureChannelCredentials());
        TrojanClientService service;
        Stub = service.NewStub(Channel);
        GetTrafficResponse reply;
        GetTrafficRequest request;
        User = new ::api::User;
        User->set_password(password.toUtf8().data());
        request.set_allocated_user(User);
        ClientContext context;
        Status status = Stub->GetTraffic(&context, request, &reply);

        if (!status.ok()) {
            Logger::error(QString("Trojan API Request failed: %1 (%2)").arg(status.error_code()).arg(QString::fromStdString(status.error_message())));
        }

        quint64 up = reply.speed_current().upload_speed();
        quint64 down = reply.speed_current().download_speed();

        if (up >= 0 && down >= 0)
            emit OnDataReady(up, down);

        QThread::msleep(1000); // sleep one second
    }

    thread->exit();
}

void TrojanGoAPI::stop()
{
    running = false;
}
