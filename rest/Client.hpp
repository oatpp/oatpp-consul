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

#ifndef oatpp_consul_rest_Client_hpp
#define oatpp_consul_rest_Client_hpp

#include "DTOs.hpp"

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace oatpp { namespace consul { namespace rest {
  
class Client : public oatpp::web::client::ApiClient {
private:
  constexpr static const char* GET = "GET";
  constexpr static const char* PUT = "PUT";
  constexpr static const char* DELETE = "DELETE";
public:
#include OATPP_CODEGEN_BEGIN(ApiClient)
  
  API_CLIENT_INIT(Client)
  
  //---------------------------------------------------------------------------------------------------
  // KV
  
  API_CALL(GET, "v1/kv/{key}", getKV, PATH(String, key))
  API_CALL(GET, "v1/kv/{key}", getKVInDC, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  API_CALL(PUT, "v1/kv/{key}", putKV, PATH(String, key), BODY_STRING(String, data))
  API_CALL(PUT, "v1/kv/{key}", putKVInDC, PATH(String, key), QUERY(String, datacenter, "dc"), BODY_STRING(String, data))
  
  API_CALL(DELETE, "v1/kv/{key}", deleteKV, PATH(String, key))
  API_CALL(DELETE, "v1/kv/{key}", deleteKVInDC, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  
  //---------------------------------------------------------------------------------------------------
  // AgentChecks
  
  API_CALL(GET, "v1/agent/checks", getAgentChecks)
  
  API_CALL(PUT, "v1/agent/check/register", putAgentChecksRegister, BODY_DTO(AgentCheckRegisterPayload::ObjectWrapper, payload))
  
  
#include OATPP_CODEGEN_END(ApiClient)
};
  
}}}

#endif /* oatpp_consul_rest_Client_hpp */
