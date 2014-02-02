#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Simulation/EntityIDDestruction.h"
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
    
    class AdditionEventTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            void receive(const Zep::EntityIDAddition &addition) {
                lastReceivedID = addition.getID();
            }
        };
    public:
        AdditionEventTest() {
            name = "AdditionEvent";
        }
        void run() {
            DummyReceiver dummyReceiver;
            Zep::EventManager eventManager;
            eventManager.subscribe<Zep::EntityIDAddition>(dummyReceiver);
            Zep::Database database(eventManager);
            database.initialize();
            Zep::EntityID entityID1 = database.createEntityID();
            assertEqual(-1, dummyReceiver.lastReceivedID);
            database.update();
            assertEqual(entityID1, dummyReceiver.lastReceivedID);
            database.createEntityID();
            Zep::EntityID entityID3 = database.createEntityID();
            assertEqual(entityID1, dummyReceiver.lastReceivedID);
            database.update();
            assertEqual(entityID3, dummyReceiver.lastReceivedID);
        }
    };
    
    class DestructionEventTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            void receive(const Zep::EntityIDDestruction &destruction) {
                lastReceivedID = destruction.getID();
            }
        };
    public:
        DestructionEventTest() {
            name = "DestructionEvent";
        }
        void run() {
            DummyReceiver dummyReceiver;
            Zep::EventManager eventManager;
            eventManager.subscribe<Zep::EntityIDDestruction>(dummyReceiver);
            Zep::Database database(eventManager);
            database.initialize();
            Zep::EntityID id = database.createEntityID();
            database.update();
            database.destroy(id);
            assertEqual(-1, dummyReceiver.lastReceivedID);
            database.update();
            assertEqual(id, dummyReceiver.lastReceivedID);
        }
    };
    
    class EntityIDReuseTest : public Vincent::Test {
    public:
        EntityIDReuseTest() {
            name = "EntityIDReuse";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            Zep::EntityID firstID = database.createEntityID();
            database.update();
            database.destroy(firstID);
            database.update();
            Zep::EntityID secondID = database.createEntityID();
            assertEqual(firstID, secondID);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "Database";
            add(new CreateEntityIDTest());
            add(new CreateComponentTest());
            add(new AdditionEventTest());
            add(new DestructionEventTest());
            add(new EntityIDReuseTest());
        }
    };
}
