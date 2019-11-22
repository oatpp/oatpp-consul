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

#include "Client.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

namespace oatpp { namespace consul {
  
Client::Client(const std::shared_ptr<oatpp::web::client::RequestExecutor>& requestExecutor, const std::shared_ptr<ObjectMapper>& objectMapper)
  : m_restClient(rest::Client::createShared(requestExecutor, objectMapper))
  , m_objectMapper(objectMapper)
{}

std::shared_ptr<Client::ObjectMapper> Client::createDefaultObjectMapper() {

  auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
  serializerConfig->includeNullFields = false;

  auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
  deserializerConfig->allowUnknownFields = true;
  
  return oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);

}

std::shared_ptr<oatpp::data::mapping::ObjectMapper> Client::getObjectMapper() const {
  return m_objectMapper;
}
  
rest::KVMetadata::ObjectWrapper Client::kvGetMetadata(const oatpp::String& key) const {
  auto response = m_restClient->kvGet(key);
  if(response->getStatusCode() == 200){
    auto list = response->readBodyToDto<List<rest::KVMetadata::ObjectWrapper>>(m_objectMapper.get());
    if(list && list->count() > 0) {
      return list->getFirst();
    }
  }
  throw Error("[oatpp::consul::client::kvGetMetadata()]: Error", response->getStatusCode());
}

rest::KVMetadata::ObjectWrapper Client::kvGetMetadataInDC(const oatpp::String& key, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvGetInDC(key, datacenter);
  if(response->getStatusCode() == 200){
    auto list = response->readBodyToDto<List<rest::KVMetadata::ObjectWrapper>>(m_objectMapper.get());
    if(list && list->count() > 0) {
      return list->getFirst();
    }
  }
  throw Error("[oatpp::consul::client::kvGetMetadataInDC()]: Error", response->getStatusCode());
}

oatpp::String Client::kvGet(const oatpp::String& key) const {
  auto response = m_restClient->kvGetRaw(key);
  if(response->getStatusCode() == 200){
    return response->readBodyToString();
  }
  throw Error("[oatpp::consul::client::kvGet()]: Error", response->getStatusCode());
}

oatpp::String Client::kvGetInDC(const oatpp::String& key, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvGetRawInDC(key, datacenter);
  if(response->getStatusCode() == 200){
    return response->readBodyToString();
  }
  throw Error("[oatpp::consul::client::kvGetInDC()]: Error", response->getStatusCode());
}
  

bool Client::kvPut(const oatpp::String& key, const oatpp::String& value) const {
  auto response = m_restClient->kvPut(key, value);
  if(response->getStatusCode() == 200){
    auto body = response->readBodyToString();
    return body && body == "true";
  }
  throw Error("[oatpp::consul::client::kvPut()]: Error", response->getStatusCode());
}

bool Client::kvPutInDC(const oatpp::String& key, const oatpp::String& value, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvPutInDC(key, value, datacenter);
  if(response->getStatusCode() == 200){
    auto body = response->readBodyToString();
    return body && body == "true";
  }
  throw Error("[oatpp::consul::client::kvPutInDC()]: Error", response->getStatusCode());
}

bool Client::kvDelete(const oatpp::String& key) const {
  auto response = m_restClient->kvDelete(key);
  if(response->getStatusCode() == 200){
    auto body = response->readBodyToString();
    return body && body == "true";
  }
  throw Error("[oatpp::consul::client::kvDelete()]: Error", response->getStatusCode());
}

bool Client::kvDeleteInDC(const oatpp::String& key, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvDeleteInDC(key, datacenter);
  if(response->getStatusCode() == 200){
    auto body = response->readBodyToString();
    return body && body == "true";
  }
  throw Error("[oatpp::consul::client::kvDeleteInDC()]: Error", response->getStatusCode());
}
  
}}
