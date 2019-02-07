# oatpp-consul [![Build Status](https://dev.azure.com/lganzzzo/lganzzzo/_apis/build/status/oatpp.oatpp-consul?branchName=master)](https://dev.azure.com/lganzzzo/lganzzzo/_build/latest?definitionId=7&branchName=master)
oatpp client for consul

- [oatpp::consul::Client](https://github.com/oatpp/oatpp-consul/blob/master/Client.hpp) - Simple consul-KV API.
- [oatpp::consul::rest::Client](https://github.com/oatpp/oatpp-consul/blob/master/rest/Client.hpp) - oatpp retrofit-like client for consul. Currently provides consul KV, Agent-Checks, Agent-Services API.

More about oatpp see [https://oatpp.io/](https://oatpp.io/)  
More about consul API see [https://www.consul.io/api/index.html](https://www.consul.io/api/index.html)

## Example

For full example project see: [oatpp-consul example](https://github.com/oatpp/example-consul)

### KV

```c++

#include "oatpp-consul/Client.hpp"

...
  
  /* request executor should be previously initialized */
  auto client = oatpp::consul::Client::createShared(requestExecutor);

  /* put value */
  client->kvPut("key1", "value1");
 
  /* get value */
  auto value = client->kvGet("key1");
  
  /* print value */
  OATPP_LOGD("consul", "value='%s'", value->c_str());
  
  /* get kv metadata */
  auto meta = client->kvGetMetadata("key1");
  
  /* decode and pring value from metadata */
  OATPP_LOGD("consul", "value='%s'", meta->getValueDecoded()->c_str());

...

```

### Register Service

```c++

#include "oatpp-consul/Client.hpp"

...
  
  /* request executor should be previously initialized */
  auto client = oatpp::consul::Client::createShared(requestExecutor);
  
  /* get oatpp::consul::rest::Client */
  auto restClient = client->getRestClient();
  
  auto checkPayload = oatpp::consul::rest::AgentCheckRegisterPayload::createShared();
  checkPayload->id = "service_check_id";
  checkPayload->name = "service_check_name";
  checkPayload->notes = "Check on the MyService/Health endpoint";
  checkPayload->http = "http://localhost:8000/check/health";
  checkPayload->method = "GET";
  checkPayload->interval = "30s";
  checkPayload->timeout = "15s";
  
  auto payload = oatpp::consul::rest::AgentServiceRegisterPayload::createShared();
  payload->id = "service_id";
  payload->name = "service_name";
  payload->port = 8000;
  payload->check = checkPayload;
  
  /* make API call */
  auto response = restClient->agentServiceRegister(payload);
  
  OATPP_LOGD("consul", "response='%s'", response->readBodyToString()->c_str());
  
...
```

