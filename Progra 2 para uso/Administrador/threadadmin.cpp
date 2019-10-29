#include "threadadmin.h"

ThreadAdmin::ThreadAdmin(QObject *parent):QThread(parent)
{
    connect(this, SIGNAL(escribirServidor(QByteArray)),&socketAdmin,SLOT(escribirServidor(QByteArray)));
}

void ThreadAdmin::run()
{
    cout<<"Kuchau"<<endl;
    emit escribirServidor(QString::fromStdString("XD").toUtf8());
}
