/*
 * SignedDataPayload.h
 *
 *  Created on: Apr 14, 2020
 *      Author: giuseppe
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_IEEE1609DOT2_SIGNEDDATAPAYLOAD_H_
#define SRC_VEINS_MODULES_APPLICATION_IEEE1609DOT2_SIGNEDDATAPAYLOAD_H_

#include "veins/modules/application/ieee1609dot2/SignedDataPayload_m.h"
//#include "veins/modules/application/ieee1609dot2/Ieee1609Dot2Data_m.h"

class Ieee1609Dot2Data;

class SignedDataPayload : public SignedDataPayload_Base {
    Ieee1609Dot2Data* data;
public:
    SignedDataPayload();
    virtual ~SignedDataPayload();
    SignedDataPayload& operator=(const SignedDataPayload& other) {SignedDataPayload_Base::operator=(other); return *this;}
    virtual SignedDataPayload *dup() const {return new SignedDataPayload(*this);}

    Ieee1609Dot2Data * getData();
    void setData(Ieee1609Dot2Data * data);



};

#endif /* SRC_VEINS_MODULES_APPLICATION_IEEE1609DOT2_SIGNEDDATAPAYLOAD_H_ */
