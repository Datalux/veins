/*
 * SignedDataPayload.cc
 *
 *  Created on: Apr 14, 2020
 *      Author: giuseppe
 */

#include <veins/modules/application/ieee1609dot2/SignedDataPayload.h>

SignedDataPayload::SignedDataPayload() {
    // TODO Auto-generated constructor stub

}

SignedDataPayload::~SignedDataPayload() {
    // TODO Auto-generated destructor stub
}


Ieee1609Dot2Data * SignedDataPayload::getData()
{
    return this->data;
}

void SignedDataPayload::setData(Ieee1609Dot2Data * data)
{
    this->data = data;
}

