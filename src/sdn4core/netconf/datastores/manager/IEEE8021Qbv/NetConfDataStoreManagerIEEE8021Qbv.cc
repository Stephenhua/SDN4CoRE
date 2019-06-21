//
// c Timo Haeckel, for HAW Hamburg
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

#include "NetConfDataStoreManagerIEEE8021Qbv.h"

#include <sdn4core/netconf/datastores/state/IEEE8021Qbv/NetConfStateDataStoreIEEE8021Qbv.h>
#include "sdn4core/netconf/datastores/config/IEEE8021Qbv/NetConfConfigDataStoreIEEE8021Qbv.h"

using namespace CoRE4INET;
using namespace std;

namespace SDN4CoRE {

Define_Module(NetConfDataStoreManagerIEEE8021Qbv);

void NetConfDataStoreManagerIEEE8021Qbv::initializeDataStores() {
    //find number of ports
    int numPorts = getParentModule()->getSubmodule("etherMAC",0)->getVectorSize();

    unordered_map<int, IEEE8021QbvGateControlList*> map;

    //find IEEE8021QbvGateControlList modules of this device
    for(int i=0; i<numPorts; i++){
        cModule* module = getParentModule()->getSubmodule("etherMAC",i)->getSubmodule("shaper")->getSubmodule("gateControlList");
        if(module){
            if(IEEE8021QbvGateControlList* gateControlListModule = dynamic_cast<IEEE8021QbvGateControlList*>(module)){
                map[i] = gateControlListModule;
            } else {
                cRuntimeError("Module found in \"^.etherMAC.shaper.gateControlList\", but is no IEEE8021QbvGateControlList");
            }
        } else {
            cRuntimeError("No Module found in \"^.etherMAC.shaper.gateControlList\"");
        }
    }

    //create the stores
    _configStores[_activeConfigName] = new NetConfConfigDataStoreIEEE8021Qbv(map);
    _stateStore = new NetConfStateDataStoreIEEE8021Qbv();

}

NetConf_RPCReplyElement* NetConfDataStoreManagerIEEE8021Qbv::handleCopyConfig(
        NetConfOperation* operation) {
    return createRPCReplyElement_Error(
            NETCONF_REPLY_ERROR_TYPE_APPLICATION,
            "Copy config not supported!",
            NETCONF_REPLY_ERROR_SEVIRITY_ERROR,"");
}

NetConf_RPCReplyElement* NetConfDataStoreManagerIEEE8021Qbv::handleDeleteConfig(
        NetConfOperation* operation) {
    return createRPCReplyElement_Error(
            NETCONF_REPLY_ERROR_TYPE_APPLICATION,
            "Delete config not supported!",
            NETCONF_REPLY_ERROR_SEVIRITY_ERROR,"");
}

}  // namespace SDN4CoRE
