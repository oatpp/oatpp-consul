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

#ifndef oatpp_consul_Client_hpp
#define oatpp_consul_Client_hpp

#include "rest/Client.hpp"

namespace oatpp { namespace consul {
  
/**
 *  oatpp::consul::Client provides convenience methods
 *  above oatpp::consul::rest::Client
 */
class Client {
private:
  template<class T>
  using List = oatpp::data::mapping::type::List<T>;

public:

  /**
   * Convenience typedef for &id:oatpp::web::client::RequestExecutor;.
   */
  typedef oatpp::web::client::RequestExecutor RequestExecutor;

  /**
   * Convenience typedef for &id:oatpp::data::mapping::ObjectMapper;.
   */
  typedef oatpp::data::mapping::ObjectMapper ObjectMapper;

public:

  /**
   * Client call error.
   */
  class Error : public std::runtime_error {
  private:
    oatpp::String m_message;
    v_int32 m_httpErrorCode;
  public:

    /**
     * Constructor.
     * @param message - error message.
     * @param httpErrorCode - http error code.
     */
    Error(const oatpp::String& message, v_int32 httpErrorCode)
      :std::runtime_error(message->c_str())
      , m_message(message)
    {}

    /**
     * Get error message.
     * @return - &id:oatpp::String;.
     */
    oatpp::String& getMessage() {
      return m_message;
    }

    /**
     * Get http error code.
     * @return - http error code.
     */
    v_int32 getHttpErrorCode() {
      return m_httpErrorCode;
    }
    
  };

private:
  std::shared_ptr<ObjectMapper> m_objectMapper;
  std::shared_ptr<rest::Client> m_restClient;
private:
  static std::shared_ptr<ObjectMapper> createDefaultObjectMapper();
public:
  Client(const std::shared_ptr<RequestExecutor>& requestExecutor, const std::shared_ptr<ObjectMapper>& objectMapper = createDefaultObjectMapper());
public:
  
  static std::shared_ptr<Client> createShared(const std::shared_ptr<RequestExecutor>& requestExecutor,
                                              const std::shared_ptr<ObjectMapper>& objectMapper = createDefaultObjectMapper()) {
    return std::make_shared<Client>(requestExecutor, objectMapper);
  }
  
  /**
   *  get oatpp::consul::rest::Client
   *  rest::Client provides more flexible
   */
  std::shared_ptr<rest::Client> getRestClient() {
    return m_restClient;
  }
  
  /**
   *  Get object mapper initialized in the client instance.
   */
  std::shared_ptr<oatpp::data::mapping::ObjectMapper> getObjectMapper() const;

  /**
   *  Get metadata for key containing base64 encoded value along with other fields
   *  @throws - &l:Client::Error;.
   */
  rest::KVMetadata::ObjectWrapper kvGetMetadata(const oatpp::String& key) const;
  
  /**
   *  Same as kvGetMetadata(key) but for given datacenter (DC)
   *  @throws - &l:Client::Error;.
   */
  rest::KVMetadata::ObjectWrapper kvGetMetadataInDC(const oatpp::String& key, const oatpp::String& datacenter) const;
  
  /**
   *  Get value by key
   *  @throws - &l:Client::Error;.
   */
  oatpp::String kvGet(const oatpp::String& key) const;
  
  /**
   *  Get value by key for given datacenter
   *  @throws - &l:Client::Error;.
   */
  oatpp::String kvGetInDC(const oatpp::String& key, const oatpp::String& datacenter) const;
  
  /**
   *  Get value by key and deserialize it to DTO object using given objectMapper
   *  @throws - &l:Client::Error;.
   */
  template<class Type>
  typename Type::ObjectWrapper kvGetAsDto(const oatpp::String& key, const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) const {
    auto response = m_restClient->kvGetRaw(key);
    if(response->getStatusCode() == 200) {
      return response->readBodyToDto<Type>(objectMapper);
    }
    throw Error("[oatpp::consul::client::kvGetAsDto()]: Error", response->getStatusCode());
  }
  
  /**
   *  Get value by key for given datacenter and deserialize it to DTO object using given objectMapper
   *  @throws - &l:Client::Error;.
   */
  template<class Type>
  typename Type::ObjectWrapper kvGetAsDtoInDC(const oatpp::String& key,
                                              const oatpp::String& datacenter,
                                              const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) const {
    auto response = m_restClient->kvGetRawInDC(key, datacenter);
    if(response->getStatusCode() == 200) {
      return response->readBodyToDto<Type>(objectMapper);
    }
    throw Error("[oatpp::consul::client::kvGetAsDtoInDC()]: Error", response->getStatusCode());
  }
  
  /**
   *  Put value for key
   *  @throws - &l:Client::Error;.
   */
  bool kvPut(const oatpp::String& key, const oatpp::String& value) const;
  
  /**
   *  Put value for key for given datacenter
   *  @throws - &l:Client::Error;.
   */
  bool kvPutInDC(const oatpp::String& key, const oatpp::String& value, const oatpp::String& datacenter) const;
  
  /**
   *  Delete value for key
   *  @throws - &l:Client::Error;.
   */
  bool kvDelete(const oatpp::String& key) const;
  
  /**
   *  Delete value for key for given datacenter
   *  @throws - &l:Client::Error;.
   */
  bool kvDeleteInDC(const oatpp::String& key, const oatpp::String& datacenter) const;
  
};
  
}}

#endif /* oatpp_consul_Client_hpp */
