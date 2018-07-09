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
  
Client::Client(const std::shared_ptr<oatpp::web::client::RequestExecutor>& requestExecutor) {
  
  auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
  serializerConfig->includeNullFields = false;
  
  auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
  deserializerConfig->allowUnknownFields = false;
  
  m_objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
  
  m_restClient = rest::Client::createShared(requestExecutor, m_objectMapper);
  
}
  
rest::KVMetadata::ObjectWrapper Client::kvGetMetadata(const oatpp::String& key) const {
  auto response = m_restClient->kvGet(key);
  if(response->statusCode == 200){
    auto list = response->readBodyToDto<List<rest::KVMetadata::ObjectWrapper>>(m_objectMapper);
    if(list && list->count() > 0) {
      return list->getFirst();
    }
  }
  return nullptr;
}

rest::KVMetadata::ObjectWrapper Client::kvGetMetadataInDC(const oatpp::String& key, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvGetInDC(key, datacenter);
  if(response->statusCode == 200){
    auto list = response->readBodyToDto<List<rest::KVMetadata::ObjectWrapper>>(m_objectMapper);
    if(list && list->count() > 0) {
      return list->getFirst();
    }
  }
  return nullptr;
}

oatpp::String Client::kvGet(const oatpp::String& key) const {
  auto response = m_restClient->kvGetRaw(key);
  if(response->statusCode == 200){
    return response->readBodyToString();
  }
  return nullptr;
}

oatpp::String Client::kvGetInDC(const oatpp::String& key, const oatpp::String& datacenter) const {
  auto response = m_restClient->kvGetRawInDC(key, datacenter);
  if(response->statusCode == 200){
    return response->readBodyToString();
  }
  return nullptr;
}
  
}}
