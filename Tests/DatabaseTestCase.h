#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Simulation/Database.h"
#include "Zep/Events/EventManager.h"

namespace DatabaseTestCase {
  struct Jetpack : public Zep::Component {
    int thrust = 1234;
  };
  
  class CreateEntityIDTest : public Vincent::Test {
  public:
    CreateEntityIDTest() {
      name = "CreateEntityID";
    }
    void run() {
      Zep::EventManager eventManager;
      Zep::Database database(eventManager);
      auto func = [&database] () {
        database.createEntityID();
      };
      assertThrows<Zep::Exception>(func);
      database.initialize();
      assertEqual(0, database.createEntityID());
      assertEqual(1, database.createEntityID());
    }
  };
  
  class CreateComponentTest : public Vincent::Test {
  public:
    CreateComponentTest() {
      name = "CreateComponent";
    }
    void run() {
      Zep::EventManager eventManager;
      Zep::Database database(eventManager);
      auto func = [&database] () {
        database.createComponent<Jetpack>(0);
      };
      assertThrows<Zep::Exception>(func);
      database.initialize();
      Zep::EntityID entityID = database.createEntityID();
      Jetpack &jetpack = database.createComponent<Jetpack>(entityID);
      assertEqual(1234, jetpack.thrust);
    }
  };
  
  class Case : public Vincent::TestCase {
  public:
    Case() {
      name = "Database";
      add(new CreateEntityIDTest());
      add(new CreateComponentTest());
    }
  };
}
