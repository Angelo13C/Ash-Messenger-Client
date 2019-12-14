#pragma once

#include <QVector>
#include <QList>

#include "dtpa.h"
#include "dtpasender.h"
#include "dtparequest.h"
#include "dtpaform.h"
#include "dtpareceivermanager.h"

namespace DTPAReceiver
{
DTPARequest fragmentToRequest(QString fragment);

QList<DTPARequest> packetToRequests(QString packet);

static QVector<DTPARequest> _cachedRequests;
void addToCachedRequests(DTPARequest request);
void removeFromCachedRequests(DTPARequest *request);

}

