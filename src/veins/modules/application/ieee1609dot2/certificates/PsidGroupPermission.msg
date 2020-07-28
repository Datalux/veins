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
 #include "SubjectPermission_m.h"   
}}

class noncobject SubjectPermission;

packet PsidGroupPermission {
    string appPermission;
    int minChainDepth = 1; // 0 for enrolment certs
    int chainDepthRange = 0; // max depth = min + range
    int eeType = 0; // 0 = app (default), 1 = enrol  
    
}