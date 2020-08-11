/***************************************/
/*                                     */
/* IEEE 1609.2 APPLICATION LAYER LOGIC */
/*                                     */
/***************************************/

#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2ALL.h"
#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2.h"
#include "veins/modules/application/ieee1609dot2/messages_type/Ieee1609Dot2Message_m.h"



//#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::Ieee1609Dot2ALL);

void Ieee1609Dot2ALL::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    ieee1609Dot2 = new Ieee1609Dot2();

}

Ieee1609Dot2Data* Ieee1609Dot2ALL::createUnsecureDataFromString(const char* msg){
    Ieee1609Dot2Data* data = new Ieee1609Dot2Data();
    data->setProtocolVersion(3);

    Ieee1609Dot2Content* content = new Ieee1609Dot2Content();
    content->setContentType(ContentChoiceType::UNSECURE_DATA);

    ContentUnsecuredData* contentUnsecuredData = new ContentUnsecuredData();
    UnsecuredData* unsecuredData = new UnsecuredData();
    unsecuredData->setUnsecuredData(msg);

    contentUnsecuredData->setUnsecuredData(*unsecuredData);
    content->setUnsecuredData(*contentUnsecuredData);

    data->setContent(*content);
    return data;

}

Ieee1609Dot2Data* Ieee1609Dot2ALL::createEncryptedDataFromString(const char* msg){
    Ieee1609Dot2Data* data = new Ieee1609Dot2Data();
    data->setProtocolVersion(3);

    Ieee1609Dot2Content* content = new Ieee1609Dot2Content();
    content->setContentType(ContentChoiceType::ENCRYPTED_DATA);

    ContentEncryptedData* contentEncryptedData = new ContentEncryptedData();
    EncryptedData* encryptedData = new EncryptedData();
    encryptedData->setCiphertext(msg);
    encryptedData->setRecipients("");

    contentEncryptedData->setEncryptedData(*encryptedData);
    content->setEncryptedData(*contentEncryptedData);

    data->setContent(*content);
    return data;
}

Ieee1609Dot2Data* Ieee1609Dot2ALL::createSignedDataFromString(const char* msg){
    Ieee1609Dot2Data* data = new Ieee1609Dot2Data();
    data->setProtocolVersion(3);

    Ieee1609Dot2Content* content = new Ieee1609Dot2Content();
    content->setContentType(ContentChoiceType::SIGNED_DATA);

    ContentSignedData* contentSignedData = new ContentSignedData();
    SignedData* signedData = new SignedData();

    // initialize signedData

    contentSignedData->setSignedData(*signedData);
    content->setSignedData(*contentSignedData);

    data->setContent(*content);
    return data;
}

void Ieee1609Dot2ALL::onWSA(DemoServiceAdvertisment* wsa)
{

}

void Ieee1609Dot2ALL::onWSM(BaseFrame1609_4* frame)
{
    Ieee1609Dot2Message* wsm = check_and_cast<Ieee1609Dot2Message*>(frame);
    std::string returnedData = ieee1609Dot2->processSPDU(wsm);
}

void Ieee1609Dot2ALL::onBSM(DemoSafetyMessage* bsm){

}

void Ieee1609Dot2ALL::handleSelfMsg(cMessage* msg)
{

}

void Ieee1609Dot2ALL::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

}
