#include "vincent/test_case.h"
#include "vincent/test.h"

namespace DatabaseTestCase {
  class CreateEntityIDTest : public Vincent::Test {
  public:
    CreateEntityIDTest() {
      name = "CreateEntityID";
    }
    void run() {
      assertEqual(3, 3);
    }
  };

  class Case : public Vincent::TestCase {
  public:
    Case() {
      name = "Database";
      add(new CreateEntityIDTest());
    }
  };
}
