
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2.h"
#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2Message_m.h"

#include "veins/modules/application/ieee1609dot2/ContentUnsecuredData_m.h"
#include "veins/modules/application/ieee1609dot2/ContentSignedData_m.h"
#include "veins/modules/application/ieee1609dot2/ContentEncryptedData_m.h"
#include "veins/modules/application/ieee1609dot2/ContentSignedCertificateRequest_m.h"

#include "veins/modules/application/ieee1609dot2/ContentChoiceType_m.h"


using namespace veins;

std::string Ieee1609Dot2::processSPDU(Ieee1609Dot2Message* spdu)
{
    if(spdu->getData().getProtocolVersion() != 3){
        delete(spdu);
        return nullptr;
    } else {
        int checkType = spdu->getData().getContent().getContentType();

        switch (checkType) {
            case ContentChoiceType::UNSECURE_DATA:
            {
                ContentUnsecuredData unsecuredData = spdu->getData().getContent().getUnsecuredData();
                return unsecuredData.getUnsecuredData().getUnsecuredData();
            }
            case ContentChoiceType::SIGNED_DATA:
            {
                ContentSignedData signedData = spdu->getData().getContent().getSignedData();
                return std::to_string(signedData.getSignedData().getSignature());

            }
            case ContentChoiceType::ENCRYPTED_DATA:
            {
                ContentEncryptedData contentEncryptedData = spdu->getData().getContent().getEncryptedData();
                EncryptedData encryptedData = contentEncryptedData.getEncryptedData();
                Ieee1609Dot2::DecryptionResult* decrypted = SecEncryptedDataDecryptionRequest(encryptedData, 0, "");
                return decrypted->data;
            }
            case ContentChoiceType::SIGNED_CERTIFICATE_REQUEST:
            {
                ContentSignedCertificateRequest signedCertificateRequest = spdu->getData().getContent().getSignedCertificateRequest();
                delete(spdu);
                return signedCertificateRequest.getSignedCertificateRequest();
            }
        }
    }
}

Ieee1609Dot2Data* Ieee1609Dot2::createSPDU(int type, Ieee1609Dot2Data* data)
{

    Ieee1609Dot2Data* spdu = new Ieee1609Dot2Data();
    spdu->setProtocolVersion(3);

    switch(type){
    case ContentChoiceType::UNSECURE_DATA:
    {
        spdu->setContent(data->getContent());
        break;
    }
    case ContentChoiceType::SIGNED_DATA:
    {
        spdu->setContent(data->getContent());
        break;
    }

    case ContentChoiceType::ENCRYPTED_DATA:
        {
            Ieee1609Dot2Content* content = new Ieee1609Dot2Content();
            content->setContentType(ContentChoiceType::ENCRYPTED_DATA);
            ContentEncryptedData* contentEncryptedData = new ContentEncryptedData();

            EncryptedData* encryptedData = SecEncryptedDataRequest(
                    data,
                    data->getContent().getContentType(),
                    0,
                    0,
                    std::vector<CertificateBase>(),
                    "",
                    "",
                    0
                    );

            contentEncryptedData->setEncryptedData(*encryptedData);
            content->setEncryptedData(*contentEncryptedData);
            spdu->setContent(*content);

            break;
        }
    case ContentChoiceType::SIGNED_CERTIFICATE_REQUEST:
    {
        Ieee1609Dot2Content* content = new Ieee1609Dot2Content();
        content->setContentType(ContentChoiceType::SIGNED_CERTIFICATE_REQUEST);

        ContentSignedCertificateRequest* contentSigendCertificateRequest = new ContentSignedCertificateRequest();
        contentSigendCertificateRequest->setSignedCertificateRequest("signedCertificateRequest");

        content->setSignedCertificateRequest(*contentSigendCertificateRequest);
        spdu->setContent(*content);
    }
    }

    //data->setContent(*content);

    return spdu;
}

void Ieee1609Dot2::SecSecureDataPreprocessingRequest(
        Ieee1609Dot2Data* data,
        int sdeeID,
        int psid,
        bool useP2PCD
        )
{
    int inputType = data->getContent().getContentType();
    if(inputType == ContentChoiceType::SIGNED_DATA){
        //TODO 9.3.11.1.4
    }

}

SignedData* Ieee1609Dot2::SecSignedDataRequest(
                int cryptomaterialHandle,
                Ieee1609Dot2Data* data,
                int dataType,
                std::string externalDataType,
                int externalDataHashAlgorithm,
                int psid,
                bool setGenerationTime,
                bool setGenerationLocation,
                int time,
                int signerIdentifierType,
                int signerIdentifierCertificateChainLenght,
                int maximumCertificateChainLength,
                int ecPointFormat,
                bool useP2PCD,
                int sdeeID
                )
{
    SignedData *signedData = new SignedData();
    signedData->setHashID(HashAlgorithm::SHA256);

    ToBeSignedData *tbsData = new ToBeSignedData();
    SignedDataPayload *signedDataPayload = new SignedDataPayload();
    signedDataPayload->setData(data);
    signedDataPayload->setExtDataHash("extDataHash");
    tbsData->setPayload(*signedDataPayload);
    HeaderInfo* headerInfo = new HeaderInfo(); //empty HeaderInfo
    tbsData->setHeaderInfo(*headerInfo);

    SignerIdentifier* signerIdentifier = new SignerIdentifier(); //empty SignerIdentifier
    signedData->setSigner(*signerIdentifier);

    Signature signature = 0; //empty Signature
    signedData->setSignature(signature);

    return signedData;
}



EncryptedData* Ieee1609Dot2::SecEncryptedDataRequest(
            Ieee1609Dot2Data* data,
            int dataType,
            int dataEncryptionKeyType,
            int symmetricCHM,
            std::vector<CertificateBase> recipientCertificates,
            std::string signedDataRecipientInfo,
            std::string responseEncryptionKey,
            int ecPointFormat
            )
{
    EncryptedData* encryptedData = new EncryptedData();
    encryptedData->setCiphertext(data->getContent().getUnsecuredData().getUnsecuredData().getUnsecuredData());
    encryptedData->setRecipients("recipients");
    return encryptedData;
}

EncryptedData* Ieee1609Dot2::SecEncryptedDataConfirm(
            int resultCode,
            Ieee1609Dot2Data* data,
            std::string signedDataRecipientInfo
            )
{

}

Ieee1609Dot2::DecryptionResult* Ieee1609Dot2::SecEncryptedDataDecryptionRequest(
        EncryptedData data,
        int cryptomaterialHandle,
        std::string signedDataRecipientInfo
        )
{
    Ieee1609Dot2::DecryptionResult *result;
    result->restultCode = DecryptionResultCode::SUCCESS;
    result->data = data.getCiphertext();

    return result;
    }


