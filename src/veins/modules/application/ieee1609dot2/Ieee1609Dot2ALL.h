/***************************************/
/*                                     */
/* IEEE 1609.2 APPLICATION LAYER LOGIC */
/*                                     */
/***************************************/

#pragma once

#include <omnetpp.h>

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2.h"


namespace veins {


class VEINS_API Ieee1609Dot2ALL : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;

protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;
    Ieee1609Dot2* ieee1609Dot2;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void onBSM(DemoSafetyMessage* bsm) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

    Ieee1609Dot2Data* createUnsecureDataFromString(const char *msg);
    Ieee1609Dot2Data* createEncryptedDataFromString(const char *msg);
    Ieee1609Dot2Data* createSignedDataFromString(const char *msg);
};

}
