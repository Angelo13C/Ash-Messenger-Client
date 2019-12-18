#include "dtpasender.h"

//Initialize the sender
DTPASender::DTPASender(QObject *parent)
{
    Q_UNUSED(parent)
}

/* SINGLETON */

DTPASender *DTPASender::getInstance()
{
    static DTPASender *instance = new DTPASender();
    return instance;
}

void DTPASender::setSocket(QSslSocket *socket)
{
    _socket = socket;
}

//Add a request to the queue of request to send
void DTPASender::sendRequest(DTPARequest *request, funcRequestAnswer funcAnswer, funcRequestEnd funcEnd)
{
    request->setID(getValidRequestID());

    //On the heap because there are bugs when retrieving it from getHighestPriorityRequest
    _requestQueue.append(new DTPARequest(*request));

    //Add to the map of the functions to call
    if(funcAnswer != nullptr)
        _funcNeedAnswerRequest.insert(request->getID(), funcAnswer);
    //Add to the map of the functions to call
    if(funcEnd != nullptr)
        _funcEndRequest.insert(request->getID(), funcEnd);

    //Send another packet if needed
    if(!DTPASender::getInstance()->queueEmpty())
        DTPASender::getInstance()->sendPacket();
}

bool DTPASender::queueEmpty()
{
    return _requestQueue.isEmpty();
}

//Get the right packet from the queue of requests
QString DTPASender::getPacketFromQueue()
{
    QString packet = "";

    //Get the fragment
    if(!_requestQueue.isEmpty())
    {
        DTPARequest *request;
        do
        {
            //Get the Request
            int requestIndex;
            request = getHighestPriorityRequest(&requestIndex);

            //If the request is ended, remove from the list and pass to the other request
            bool requestEnd;
            do
            {
                //Get the fragment of a max size of 4096 - the current packet length
                packet += request->getFragment(DTPA::REQUEST_MAX_SIZE - packet.length(), &requestEnd);

                //If the request doesn't contain forms anymore
                if(requestEnd)
                {
                    /* If the request is completely ended (if the request had got all forms
                     * completed), remove it and reset the IDs array */
                    if(request->hasBeenCompleted())
                    {
                        //If the request needs an answer or is an answer, don't set the requestID as free
                        int requestID = request->getID();
                        if(!_funcNeedAnswerRequest.contains(requestID))
                            _requestIDs[requestID] = false;

                        delete _requestQueue.at(requestIndex);
                        _requestQueue.removeAt(requestIndex);

                        break;
                    }

                    //If there's a func to call when the request is ended, call it
                    callRequestEnd(request);
                }

            }while(packet.length() < DTPA::REQUEST_MAX_SIZE - 1 && DTPA::REQUEST_MAX_SIZE - packet.length() > 3);

        }while(packet.length() < DTPA::REQUEST_MAX_SIZE - 1 && _requestQueue.length() > 0);
    }

    return packet;
}

//If there's a func to call when the request is ended, call it
void DTPASender::callRequestAnswer(DTPARequest *request)
{
    int answerToID = request->getAnswerToID();
    funcRequestAnswer func = _funcNeedAnswerRequest.value(answerToID, nullptr);
    if(func != nullptr)
    {
        int requestID = request->getID();

        //Call the function
        func(request, answerToID);

        if(request->isLastAnswer() && request->isComplete())
        {
            //Remove the request from the map
            _funcNeedAnswerRequest.remove(answerToID);

            _requestIDs[requestID] = false;
        }
    }
}

//If there's a func to call when the request is ended, call it
void DTPASender::callRequestEnd(DTPARequest *request)
{
    int requestID = request->getID();
    funcRequestEnd func = _funcEndRequest.value(requestID, nullptr);
    if(func != nullptr)
    {
        //Remove the request from the map
        _funcEndRequest.remove(requestID);
        //Call the function
        func(request);
    }
}

//Send requestes in the queue as fragment starting from the one with higher priority
void DTPASender::sendPacket()
{
    QString packet = getPacketFromQueue();

    //Send packet with socket
    _socket->write(packet.toUtf8());

    //Send another packet if needed
    if(!DTPASender::getInstance()->queueEmpty())
        DTPASender::getInstance()->sendPacket();
}

//Get the highest priority request
DTPARequest *DTPASender::getHighestPriorityRequest(int *outRequestIndex)
{
    DTPARequest *request = nullptr;

    //Get the highest priority request
    for(int i = 0; i < _requestQueue.length(); i++)
    {
        //If it's the first request or finds a request with higher priority than the currently selected
        if(!request || _requestQueue.at(i)->getPriority() > request->getPriority())
        {
            request = _requestQueue.at(i);
            *outRequestIndex = i;   //To delete the request from the list

            //If the request has the highest priority, don't continue
            if(request->getPriority() == DTPARequest::Priority::HIGHEST)
                break;
        }
    }

    return request;
}

//Get a valid id for the request
int16_t DTPASender::getValidRequestID()
{
    int16_t validID = 0;

    //Get the first unused id
    while(_requestIDs[validID])
    {
        validID++;      //from 0 to 9999
    }

    _requestIDs[validID] = true;

    return validID;
}

