#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Database/EntityIDAddition.h"
#include "Zep/Database/EntityIDDestruction.h"
#include "Zep/Database/EntityChange.h"
#include "Zep/Database/Database.h"
#include "Zep/Events/EventBus.h"

namespace DatabaseTestCase {
    struct Health : public Zep::Aspect { };
    struct Position : public Zep::Aspect { };
    struct Jetpack : public Zep::Aspect {
        int thrust = 1234;
    };
    
    class EntityIDCreationTest : public Vincent::Test {
    public:
        EntityIDCreationTest() {
            name = "EntityIDCreation";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            auto func = [&database] () {
              database.createEntityID();
            };
            assertThrows<Zep::Exception>(func);
            database.initialize();
            assertEqual(0, database.createEntityID());
            assertEqual(1, database.createEntityID());
        }
    };
    
    class AspectCreationTest : public Vincent::Test {
    public:
        AspectCreationTest() {
            name = "AspectCreation";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            auto func = [&database] () {
              database.createAspect<Jetpack>(0);
            };
            assertThrows<Zep::Exception>(func);
            database.initialize();
            Zep::EntityID entityID = database.createEntityID();
            Jetpack &jetpack = database.createAspect<Jetpack>(entityID);
            assertEqual(1234, jetpack.thrust);
        }
    };
    
    class HasAspectByTemplateTest : public Vincent::Test {
    public:
        HasAspectByTemplateTest() {
            name = "HasAspectByTemplate";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            Zep::EntityID id = database.createEntityID();
            database.createAspect<Jetpack>(id);
            assert(!database.hasAspect<Jetpack>(id));
            database.update();
            assert(database.hasAspect<Jetpack>(id));
        }
    };
    
    class HasAspectByIDTest : public Vincent::Test {
    public:
        HasAspectByIDTest() {
            name = "HasAspectByID";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            auto aspectID = database.getAspectTypeID<Jetpack>();
            Zep::EntityID id = database.createEntityID();
            database.createAspect<Jetpack>(id);
            assert(!database.hasAspect(id, aspectID));
            database.update();
            assert(database.hasAspect(id, aspectID));
            assert(false);
        }
    };
    
    class AdditionEventTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            void handle(const Zep::EntityIDAddition &addition) {
                lastReceivedID = addition.getID();
            }
        };
    public:
        AdditionEventTest() {
            name = "AdditionEvent";
        }
        void run() {
            DummyReceiver dummyReceiver;
            Zep::EventBus eventBus;
            eventBus.subscribe<Zep::EntityIDAddition>(dummyReceiver);
            Zep::Database database(eventBus);
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
            void handle(const Zep::EntityIDDestruction &destruction) {
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
            Zep::EventBus eventBus;
            eventBus.subscribe<Zep::EntityIDDestruction>(dummyReceiver);
            Zep::Database database(eventBus);
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
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            Zep::EntityID firstID = database.createEntityID();
            database.update();
            database.destroy(firstID);
            database.update();
            Zep::EntityID secondID = database.createEntityID();
            assertEqual(firstID, secondID);
        }
    };
    
    class ChangeEventByAspectCreationTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            int events = 0;
            void handle(const Zep::EntityChange &change) {
                lastReceivedID = change.getID();
                events++;
            }
        };
    public:
        ChangeEventByAspectCreationTest() {
            name = "ChangeEventByAspectCreation";
        }
        void run() {
            DummyReceiver dummy;
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            auto id = database.createEntityID();
            database.update();
            
            eventBus.subscribe<Zep::EntityChange>(dummy);
            database.createAspect<Jetpack>(id);
            database.update();
            assertEqual(id, dummy.lastReceivedID);
            
            database.update();
            assertEqual(1, dummy.events);
        }
    };
    
    class ChangeEventByAspectDestructionTest : public Vincent::Test {
        class DummyReceiver {
        public:
            int lastReceivedID = -1;
            int events = 0;
            void handle(const Zep::EntityChange &change) {
                lastReceivedID = change.getID();
                events++;
            }
        };
    public:
        ChangeEventByAspectDestructionTest() {
            name = "ChangeEventByAspectDestruction";
        }
        void run() {
            DummyReceiver dummy;
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            auto id = database.createEntityID();
            database.createAspect<Jetpack>(id);
            database.update();
            
            eventBus.subscribe<Zep::EntityChange>(dummy);
            database.destroy<Jetpack>(id);
            database.update();
            assertEqual(id, dummy.lastReceivedID);
            
            database.update();
            assertEqual(1, dummy.events);
        }
    };
    
    struct AspectDestructionTest : public Vincent::Test {
        AspectDestructionTest() {
            name = "AspectDestruction";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            auto id = database.createEntityID();
            database.createAspect<Jetpack>(id);
            database.update();
            
            database.destroy<Jetpack>(id);
            assert(database.hasAspect<Jetpack>(id));
            database.update();
            assert(!database.hasAspect<Jetpack>(id));
        }
    };
    
    struct SingleAspectMaskGenerationTest : public Vincent::Test {
        SingleAspectMaskGenerationTest() {
            name = "SingleAspectMaskGeneration";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            
            Zep::AspectMask jetpackMask = database.getAspectMask<Jetpack>();
            assert(jetpackMask.count() == 1);
        }
    };
    
    struct MultiAspectMaskGenerationTest : public Vincent::Test {
        MultiAspectMaskGenerationTest() {
            name = "MultiAspectMaskGeneration";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            
            Zep::AspectMask jetpackMask = database.getAspectMask<Jetpack>();
            Zep::AspectMask healthMask = database.getAspectMask<Health>();
            Zep::AspectMask positionMask = database.getAspectMask<Position>();
            
            Zep::AspectMask manualCombinedMask = jetpackMask | healthMask | positionMask;
            
            Zep::AspectMask generatedCombinedMask = database.getAspectMask<Jetpack, Health, Position>();
            
            assert(manualCombinedMask == generatedCombinedMask);
        }
    };
    
    class HasAspectsTest : public Vincent::Test {
    public:
        HasAspectsTest() {
            name = "HasAspect";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            
            Zep::AspectMask mask = database.getAspectMask<Jetpack, Health>();
            
            Zep::EntityID id = database.createEntityID();
            database.createAspect<Jetpack>(id);
            database.update();
            assert(!database.hasAspects(id, mask));
            
            database.createAspect<Health>(id);
            database.update();
            assert(database.hasAspects(id, mask));
            
            database.createAspect<Position>(id);
            database.update();
            assert(database.hasAspects(id, mask));
        }
    };
    
    class FastAspectRetrivalTest : public Vincent::Test {
    public:
        FastAspectRetrivalTest() {
            name = "FastAspectRetrival";
        }
        void run() {
            Zep::EventBus eventBus;
            Zep::Database database(eventBus);
            database.initialize();
            
            Zep::AspectTypeID typeID = database.getAspectTypeID<Jetpack>();
            Zep::EntityID id = database.createEntityID();
            auto &createdJetpack = database.createAspect<Jetpack>(id);
            auto &retrivedJetpack = database.getAspect<Jetpack>(id, typeID);
            assert(&createdJetpack == &retrivedJetpack);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "Database";
            add(new EntityIDCreationTest());
            add(new AspectCreationTest());
            add(new AdditionEventTest());
            add(new DestructionEventTest());
            add(new EntityIDReuseTest());
            add(new AspectDestructionTest());
            add(new ChangeEventByAspectCreationTest());
            add(new ChangeEventByAspectDestructionTest());
            add(new SingleAspectMaskGenerationTest());
            add(new MultiAspectMaskGenerationTest());
            add(new HasAspectByTemplateTest());
            add(new HasAspectByIDTest());
            add(new HasAspectsTest());
            add(new FastAspectRetrivalTest());
        }
    };
}
