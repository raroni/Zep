//
//  EntityObserverProcessorTestCase.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef Zep_EntityObserverProcessorTestCase_h
#define Zep_EntityObserverProcessorTestCase_h

#include <unordered_set>
#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Database/EntityObserverProcessor.h"

namespace EntityObserverProcessorTestCase {
    class Bouncy : public Zep::Component { };
    class Juicy : public Zep::Component { };
    
    class DummyProcessor : public Zep::EntityObserverProcessor {
        void onAdded(Zep::EntityID id) {
            ids.insert(id);
        }
        void onRemoved(Zep::EntityID id) {
            ids.erase(id);
        }
        bool match(Zep::EntityID id) {
            return database->hasComponent<Bouncy>(id);
        }
    public:
        std::unordered_set<Zep::EntityID> ids;
        void update(int timeDelta) { }
    };
    
    class AdditionMatchTest : public Vincent::Test {
    public:
        AdditionMatchTest() {
            name = "AdditionMatch";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            
            DummyProcessor dummy;
            dummy.setEventManager(eventManager);
            dummy.setDatabase(database);
            dummy.initialize();
            
            Zep::EntityID id = database.createEntityID();
            database.createComponent<Bouncy>(id);
            database.update();
            
            assert(1 == dummy.ids.size());
            assert(dummy.ids.find(0) != dummy.ids.end());
        }
    };
    
    class AdditionMissTest : public Vincent::Test {
    public:
        AdditionMissTest() {
            name = "AdditionMiss";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            
            DummyProcessor dummy;
            dummy.setEventManager(eventManager);
            dummy.setDatabase(database);
            dummy.initialize();
            
            Zep::EntityID id = database.createEntityID();
            database.createComponent<Juicy>(id);
            database.update();
            
            assert(0 == dummy.ids.size());
        }
    };
    
    class DestructionMatchTest : public Vincent::Test {
    public:
        DestructionMatchTest() {
            name = "DestructionMatch";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            
            DummyProcessor dummy;
            dummy.setEventManager(eventManager);
            dummy.setDatabase(database);
            dummy.initialize();
            
            Zep::EntityID id = database.createEntityID();
            database.createComponent<Bouncy>(id);
            database.update();
            
            assert(1 == dummy.ids.size());
            assert(dummy.ids.find(0) != dummy.ids.end());
            
            database.destroy(id);
            database.update();
            
            assert(0 == dummy.ids.size());
        }
    };
    
    class DestructionMissTest : public Vincent::Test {
    public:
        DestructionMissTest() {
            name = "DestructionMiss";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            
            DummyProcessor dummy;
            dummy.setEventManager(eventManager);
            dummy.setDatabase(database);
            dummy.initialize();
            
            Zep::EntityID entityID1 = database.createEntityID();
            Zep::EntityID entityID2 = database.createEntityID();
            database.createComponent<Bouncy>(entityID1);
            database.update();
                        
            database.destroy(entityID2);
            database.update();
            
            assert(1 == dummy.ids.size());
        }
    };
    
    class ChangeMatchTest : public Vincent::Test {
    public:
        ChangeMatchTest() {
            name = "ChangeMatch";
        }
        void run() {
            Zep::EventManager eventManager;
            Zep::Database database(eventManager);
            database.initialize();
            
            DummyProcessor dummy;
            dummy.setEventManager(eventManager);
            dummy.setDatabase(database);
            dummy.initialize();
            
            Zep::EntityID entityID1 = database.createEntityID();
            database.createComponent<Juicy>(entityID1);
            database.update();
            assert(0 == dummy.ids.size());

            database.createComponent<Bouncy>(entityID1);
            database.update();
            assert(1 == dummy.ids.size());
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EntityObserverProcessor";
            add(new AdditionMatchTest());
            add(new AdditionMissTest());
            add(new DestructionMatchTest());
            add(new DestructionMissTest());
            add(new ChangeMatchTest());
        }
    };
}

#endif
