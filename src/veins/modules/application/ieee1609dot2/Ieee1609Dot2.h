

#pragma once

#include <omnetpp.h>

#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2Message_m.h"
#include "veins/modules/application/ieee1609dot2/EncryptedData_m.h"
#include "veins/modules/application/ieee1609dot2/SignedData_m.h"
#include "veins/modules/application/ieee1609dot2/CertificateBase_m.h"

#include "veins/modules/application/ieee1609dot2/HashAlgorithm_m.h"


namespace veins {


class VEINS_API Ieee1609Dot2{

    enum DecryptionResultCode {
        SUCCESS,
        NO_DECRIPTION_KEY_AVAIBILE,
        UNSUPPORTED_CRITICAL_INFORMATION_FIELD,
        COULDNT_DECRYPT_KEY,
        COULDNT_DECRYPT_DATA,
        INVALID_FROM_FOR_PLAINTEXT
    };

    typedef struct {
        int restultCode;
        std::string data;
    } DecryptionResult;
public:
    Ieee1609Dot2() { }
    Ieee1609Dot2Data* createSPDU(int type, Ieee1609Dot2Data* data);

    //Ieee1609Dot2Data* createSPDU(int type, std::string content);

    std::string processSPDU(Ieee1609Dot2Message* spdu);

    void SecSecureDataPreprocessingRequest(
            Ieee1609Dot2Data* data,
            int sdeeID,
            int psid,
            bool useP2PCD
            );

    /* 9.3.9.1 Sec-SignedData.request */
    SignedData* SecSignedDataRequest(
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
                );

    SignedData* SecSignedDataConfirm(
            int resultCode,
            SignedData* signedData
            );

    EncryptedData* SecEncryptedDataRequest(
            Ieee1609Dot2Data* data,
            int dataType,
            int dataEncryptionKeyType,
            int symmetricCHM,
            std::vector<CertificateBase> recipientCertificates,
            std::string signedDataRecipientInfo,
            std::string responseEncryptionKey,
            int ecPointFormat
            );

    EncryptedData* SecEncryptedDataConfirm(
                int resultCode,
                Ieee1609Dot2Data* data,
                std::string signedDataRecipientInfo
                );

    DecryptionResult* SecEncryptedDataDecryptionRequest(
            EncryptedData data,
            int cryptomaterialHandle,
            std::string signedDataRecipientInfo
            );

};
}
