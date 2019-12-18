#pragma once

#include <QObject>

#include <QSslSocket>

#include <functional>

#include "dtpa.h"
#include "dtparequest.h"

class DTPASender : public QObject
{
Q_OBJECT

public:
    explicit DTPASender(QObject *parent = nullptr);

    static DTPASender *getInstance();
    void setSocket(QSslSocket *socket);

    QString getPacketFromQueue();
    void sendPacket();
    DTPARequest *getHighestPriorityRequest(int *outRequestIndex);
    int16_t getValidRequestID();

    typedef std::function<void(DTPARequest *, int)> funcRequestAnswer;
    void callRequestAnswer(DTPARequest *request);
    typedef std::function<void(DTPARequest *)> funcRequestEnd;
    void callRequestEnd(DTPARequest *request);
    void sendRequest(DTPARequest *request, funcRequestAnswer funcAnswer = nullptr, funcRequestEnd funcEnd = nullptr);

    bool queueEmpty();
private:
    QMap<int, funcRequestAnswer> _funcNeedAnswerRequest;
    QMap<int, funcRequestEnd> _funcEndRequest;

private:
    QList<DTPARequest *> _requestQueue;
    bool _requestIDs[10000] = {false};

    QSslSocket *_socket;
};


