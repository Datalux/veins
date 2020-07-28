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

cplusplus 
{{
 #include "CertificateId_m.h"   
}}

class noncobject CertificateId;


packet ToBeSignedCertificate {
 	CertificateId id;
 	char cracaId[3]; //should be HashedId3
 	uint16_t crlSeries; // CrlSeries
 	string validityPeriod; //ValidityPeriod
 	string region; // GeographicRegion OPTIONAL
 	string assuranceLevel; // SubjectAssurance OPTIONAL
 	string appPermission; // SeuquenceOfPsidSsp OPTIONAL
 	string certIssuePermission; //SequenceOfPsidGroupPermissions OPTIONAL 
 	string certRequestPermission; //SequenceOfPsidGroupPermissions OPTIONAL
 	string canRequestRollover; // NULL OPTIONAL
 	string encryptionKey; // PublicEncryptionKey OPTIONAL
 	string verifyKeyIndicator; //VerificationKeyIndicator
 	    
}