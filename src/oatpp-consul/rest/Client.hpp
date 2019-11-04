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
  
/**
 *  oatpp::consul::rest::Client provides consul rest API calls for Simple and Async oatpp API. <br>
 *  For more convenient methods see &id:oatpp::consul::Client;. <br>
 *  See Rest Client full declaration on github: [rest/Client.hpp](https://github.com/oatpp/oatpp-consul/blob/master/src/oatpp-consul/rest/Client.hpp);
 */
class Client : public oatpp::web::client::ApiClient {
private:
  constexpr static const char* HTTP_GET = "GET";
  constexpr static const char* HTTP_PUT = "PUT";
  constexpr static const char* HTTP_DELETE = "DELETE";
public:
#include OATPP_CODEGEN_BEGIN(ApiClient)
  
  API_CLIENT_INIT(Client)
  
  //---------------------------------------------------------------------------------------------------
  // KV

  API_CALL(HTTP_GET, "v1/kv/{key}", kvGet, PATH(String, key))
  API_CALL(HTTP_GET, "v1/kv/{key}", kvGetInDC, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  API_CALL(HTTP_GET, "v1/kv/{key}?raw", kvGetRaw, PATH(String, key))
  API_CALL(HTTP_GET, "v1/kv/{key}?raw&dc={dc}", kvGetRawInDC, PATH(String, key), PATH(String, datacenter, "dc"))

  API_CALL(HTTP_PUT, "v1/kv/{key}", kvPut, PATH(String, key), BODY_STRING(String, data))
  API_CALL(HTTP_PUT, "v1/kv/{key}", kvPutInDC, PATH(String, key), BODY_STRING(String, data), QUERY(String, datacenter, "dc"))
  
  API_CALL(HTTP_DELETE, "v1/kv/{key}", kvDelete, PATH(String, key))
  API_CALL(HTTP_DELETE, "v1/kv/{key}", kvDeleteInDC, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  API_CALL_ASYNC(HTTP_GET, "v1/kv/{key}", kvGetAsync, PATH(String, key))
  API_CALL_ASYNC(HTTP_GET, "v1/kv/{key}", kvGetInDCAsync, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  API_CALL_ASYNC(HTTP_GET, "v1/kv/{key}?raw", kvGetRawAsync, PATH(String, key))
  API_CALL_ASYNC(HTTP_GET, "v1/kv/{key}?raw&dc={dc}", kvGetRawInDCAsync, PATH(String, key), PATH(String, datacenter, "dc"))
  
  API_CALL_ASYNC(HTTP_PUT, "v1/kv/{key}", kvPutAsync, PATH(String, key), BODY_STRING(String, data))
  API_CALL_ASYNC(HTTP_PUT, "v1/kv/{key}", kvPutInDCAsync, PATH(String, key), BODY_STRING(String, data), QUERY(String, datacenter, "dc"))
  
  API_CALL_ASYNC(HTTP_DELETE, "v1/kv/{key}", kvDeleteAsync, PATH(String, key))
  API_CALL_ASYNC(HTTP_DELETE, "v1/kv/{key}", kvDeleteInDCAsync, PATH(String, key), QUERY(String, datacenter, "dc"))
  
  
  //---------------------------------------------------------------------------------------------------
  // AgentChecks
  
  API_CALL(HTTP_GET, "v1/agent/checks", agentGetChecks)
  API_CALL(HTTP_PUT, "v1/agent/check/register", agentCheckRegister, BODY_DTO(AgentCheckRegisterPayload::ObjectWrapper, payload))
  API_CALL(HTTP_PUT, "v1/agent/check/deregister/{checkId}", agentCheckDeregister, PATH(String, checkId))
  
  API_CALL_ASYNC(HTTP_GET, "v1/agent/checks", agentGetChecksAsync)
  API_CALL_ASYNC(HTTP_PUT, "v1/agent/check/register", agentCheckRegisterAsync, BODY_DTO(AgentCheckRegisterPayload::ObjectWrapper, payload))
  API_CALL_ASYNC(HTTP_PUT, "v1/agent/check/deregister/{checkId}", agentCheckDeregisterAsync, PATH(String, checkId))
  
  //---------------------------------------------------------------------------------------------------
  // AgentService
  
  API_CALL(HTTP_GET, "v1/agent/services", agentGetServices)
  API_CALL(HTTP_PUT, "v1/agent/service/register", agentServiceRegister, BODY_DTO(AgentServiceRegisterPayload::ObjectWrapper, payload))
  API_CALL(HTTP_PUT, "v1/agent/service/deregister/{serviceId}", agentServiceDeregister, PATH(String, serviceId))
  
  API_CALL_ASYNC(HTTP_GET, "v1/agent/services", agentGetServicesAsync)
  API_CALL_ASYNC(HTTP_PUT, "v1/agent/service/register", agentServiceRegisterAsync, BODY_DTO(AgentServiceRegisterPayload::ObjectWrapper, payload))
  API_CALL_ASYNC(HTTP_PUT, "v1/agent/service/deregister/{serviceId}", agentServiceDeregisterAsync, PATH(String, serviceId))
  
  
#include OATPP_CODEGEN_END(ApiClient)
};
  
}}}

#endif /* oatpp_consul_rest_Client_hpp */
