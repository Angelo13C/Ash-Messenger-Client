#pragma once

#include <QDebug>

#include <functional>

#include "dtpa.h"
#include "dtparequest.h"

class DTPAReceiverManager
{
public:
    DTPAReceiverManager();

    void callRequestCommand(DTPARequest *request, bool *deleteRequest);

    /* SINGLETON */
    static DTPAReceiverManager* getInstance();

    typedef std::function<void(DTPARequest *, bool *)> funcCommand;
    void signCommandFunction(DTPARequest::Command command, funcCommand function);
private:
    QMap<DTPARequest::Command, funcCommand> _commandFunctions;
};

