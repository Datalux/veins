//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// TODO generated message class
//

cplusplus 
{{
#include "../messages_type/ContentChoiceType_m.h"
#include "../messages_type/ContentUnsecuredData_m.h"
#include "../messages_type/ContentEncryptedData_m.h"
#include "../messages_type/ContentSignedCertificateRequest_m.h"
#include "../messages_type/ContentSignedData_m.h"

}}


enum ContentChoiceType;
class ContentUnsecuredData;
class ContentEncryptedData;
class ContentSignedCertificateRequest;
class ContentSignedData;

packet Ieee1609Dot2Content {
	//char unsecuredData[8]; //should be Opaque
    //SignedData signedData;
    //EncryptedData encryptedData;
    //char signedCertificateRequest[8]; //should be Opaque
    //ContentChoice contentChoices;
    int contentType @enum(ContentChoiceType);
    ContentUnsecuredData unsecuredData;
    ContentEncryptedData encryptedData;
    ContentSignedCertificateRequest signedCertificateRequest;
    ContentSignedData signedData;
}
