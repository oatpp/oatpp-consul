/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi, <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_consul_rest_DTOs_hpp
#define oatpp_consul_rest_DTOs_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO codegen */
#include OATPP_CODEGEN_BEGIN(DTO)

namespace oatpp { namespace consul { namespace rest {
  
class KVMetadata : public oatpp::data::mapping::type::Object {
  
  DTO_INIT(KVMetadata, Object)

  DTO_FIELD(String, key, "Key");
  DTO_FIELD(String, value, "Value");
  
  DTO_FIELD(String, session, "Session");
  
  DTO_FIELD(Int32, createIndex, "CreateIndex");
  DTO_FIELD(Int32, modifyIndex, "ModifyIndex");
  DTO_FIELD(Int32, lockIndex, "LockIndex");
  
  DTO_FIELD(Int32, flags, "Flags");
  
};
  
class AgentCheckRegisterPayload : public oatpp::data::mapping::type::Object {
  
  DTO_INIT(AgentCheckRegisterPayload, Object)
  
  DTO_FIELD(String, name, "Name");
  DTO_FIELD(String, id, "ID");
  DTO_FIELD(String, interval, "Interval");
  DTO_FIELD(String, notes, "Notes");
  DTO_FIELD(String, deregisterCriticalServiceAfter, "DeregisterCriticalServiceAfter");
  
  DTO_FIELD(List<String>::ObjectWrapper, args, "Args");
  
  DTO_FIELD(String, dockerContainerID, "DockerContainerID");
  
  DTO_FIELD(String, grpc, "GRPC");
  DTO_FIELD(String, grpcUseTLS, "GRPCUseTLS");
  
  DTO_FIELD(String, http, "HTTP");
  DTO_FIELD(String, method, "Method");
  
  //DTO_FIELD(Map<String, List<String>::ObjectWrapper>::ObjectWrapper, header, "Header");
  
  DTO_FIELD(String, timeout, "Timeout");
  DTO_FIELD(Boolean, tlsSkipVerify, "TLSSkipVerify");
  DTO_FIELD(String, tcp, "TCP");
  DTO_FIELD(String, ttl, "TTL");
  DTO_FIELD(String, serviceID, "ServiceID");
  DTO_FIELD(String, status, "Status");
  
};
  
}}}

/* End DTO codegen */
#include OATPP_CODEGEN_END(DTO)

#endif /* oatpp_consul_rest_DTOs_hpp */
