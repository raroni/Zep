#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Simulation/EntityIDDestruction.h"
#include "Zep/Simulation/EntityChange.h"
#include "Zep/Simulation/Database.h"
#include "Zep/Events/EventManager.h"

namespace DatabaseTestCase {
    struct Jetpack : public Zep::Component {
        int thrust = 1234;
    };
    
    class EntityIDCreationTest : public Vincent::Test {
    public:
        EntityIDCreationTest() {
            name = "EntityIDCreation";
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
    
    class ComponentCreationTest : public Vincent::Test {
    public:
        ComponentCreationTest() {
            name = "ComponentCreation";
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
    
    class HasComponentTest : public Vincent::Test {
    public:
        HasComponentTest() {
            name = "HasComponent";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            Zep::EntityID id = database.createEntityID();
            database.createComponent<Jetpack>(id);
            assert(!database.hasComponent<Jetpack>(id));
            database.update();
            assert(database.hasComponent<Jetpack>(id));
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
            int events = 0;
            int lastReceivedID = -1;
            void receive(const Zep::EntityIDDestruction &destruction) {
                lastReceivedID = destruction.getID();
                events++;
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
            assertEqual(1, dummyReceiver.events);
            database.update();
            assertEqual(1, dummyReceiver.events);
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
    
    class ChangeEventByComponentCreationTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            int events = 0;
            void receive(const Zep::EntityChange &change) {
                lastReceivedID = change.getID();
                events++;
            }
        };
    public:
        ChangeEventByComponentCreationTest() {
            name = "ChangeEventByComponentCreation";
        }
        void run() {
            DummyReceiver dummy;
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            auto id = database.createEntityID();
            database.update();
            
            eventManager.subscribe<Zep::EntityChange>(dummy);
            database.createComponent<Jetpack>(id);
            database.update();
            assertEqual(id, dummy.lastReceivedID);
            
            database.update();
            assertEqual(1, dummy.events);
        }
    };
    
    class ChangeEventByComponentDestructionTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            int events = 0;
            void receive(const Zep::EntityChange &change) {
                lastReceivedID = change.getID();
                events++;
            }
        };
    public:
        ChangeEventByComponentDestructionTest() {
            name = "ChangeEventByComponentDestruction";
        }
        void run() {
            DummyReceiver dummy;
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            auto id = database.createEntityID();
            database.createComponent<Jetpack>(id);
            database.update();
            
            eventManager.subscribe<Zep::EntityChange>(dummy);
            database.destroy<Jetpack>(id);
            database.update();
            assertEqual(id, dummy.lastReceivedID);
            
            database.update();
            assertEqual(1, dummy.events);
        }
    };
    
    struct ComponentDestructionTest : public Vincent::Test {
        ComponentDestructionTest() {
            name = "ComponentDestruction";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            auto id = database.createEntityID();
            database.createComponent<Jetpack>(id);
            database.update();
            
            database.destroy<Jetpack>(id);
            assert(database.hasComponent<Jetpack>(id));
            database.update();
            assert(!database.hasComponent<Jetpack>(id));
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "Database";
            add(new EntityIDCreationTest());
            add(new ComponentCreationTest());
            add(new HasComponentTest());
            add(new AdditionEventTest());
            add(new DestructionEventTest());
            add(new EntityIDReuseTest());
            add(new ComponentDestructionTest());
            add(new ChangeEventByComponentCreationTest());
            add(new ChangeEventByComponentDestructionTest());
        }
    };
}
