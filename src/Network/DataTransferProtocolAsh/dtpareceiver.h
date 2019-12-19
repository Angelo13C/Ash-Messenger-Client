#pragma once

#include "dtparequest.h"

namespace DTPAReceiver
{
DTPARequest fragmentToRequest(QString fragment);

QList<DTPARequest> packetToRequests(QString packet);

static QVector<DTPARequest> _cachedRequests;
void addToCachedRequests(DTPARequest request);
void removeFromCachedRequests(DTPARequest *request);

}

