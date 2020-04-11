/***************************************/
/*                                     */
/* IEEE 1609.2 APPLICATION LAYER LOGIC */
/*                                     */
/***************************************/

#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2ALL.h"
#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2.h"
#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2Message_m.h"



//#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::Ieee1609Dot2ALL);

void Ieee1609Dot2ALL::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    ieee1609Dot2 = new Ieee1609Dot2();

    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
}

void Ieee1609Dot2ALL::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}

void Ieee1609Dot2ALL::onWSM(BaseFrame1609_4* frame)
{
    Ieee1609Dot2Message* wsm = check_and_cast<Ieee1609Dot2Message*>(frame);
    const char* data = ieee1609Dot2->processSPDU(wsm);

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(data, 9999);
    if (!sentMessage) {
        sentMessage = true;
        // repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
    }
}

void Ieee1609Dot2ALL::handleSelfMsg(cMessage* msg)
{
    if (Ieee1609Dot2Message* wsm = dynamic_cast<Ieee1609Dot2Message*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void Ieee1609Dot2ALL::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().setTagArg("i", 1, "red");
            sentMessage = true;

            Ieee1609Dot2Message* wsm = new Ieee1609Dot2Message();
            populateWSM(wsm);

            wsm->setData(*(ieee1609Dot2->createSPDU(ContentChoiceType::UNSECURE_DATA, mobility->getRoadId().c_str())));


            // host is standing still due to crash
            if (dataOnSch) {
                startService(Channel::sch2, 42, "Traffic Information Service");
                // started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
            }
            else {
                // send right away on CCH, because channel switching is disabled
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
