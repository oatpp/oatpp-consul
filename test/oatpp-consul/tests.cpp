
#include "oatpp-consul/Client.hpp"

#include "oatpp-test/UnitTest.hpp"

#include "oatpp/Environment.hpp"

#include <iostream>
#include <mutex>

namespace {

class Logger : public oatpp::Logger {
private:
  std::mutex m_lock;
public:

  void log(v_uint32 priority, const std::string& tag, const std::string& message) override {
    std::lock_guard<std::mutex> lock(m_lock);
    std::cout << tag << ":" << message << "\n";
  }

};

class Test : public oatpp::test::UnitTest {
public:
  Test() : oatpp::test::UnitTest("MyTag")
  {}

  void onRun() override {

    auto client = oatpp::consul::Client::createShared(nullptr);

    // TODO write correct  tests
    
  }
};

void runTests() {
  OATPP_RUN_TEST(Test);
}

}

int main() {

  oatpp::Environment::init();

  runTests();

  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::Environment::getObjectsCount() == 0);

  oatpp::Environment::destroy();

  return 0;
}
