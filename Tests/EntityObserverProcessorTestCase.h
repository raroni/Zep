//
//  EntityObserverProcessorTestCase.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef Zep_EntityObserverProcessorTestCase_h
#define Zep_EntityObserverProcessorTestCase_h

#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Simulation/EntityObserverProcessor.h"

namespace EntityObserverProcessorTestCase {
    class Bouncy : public Zep::Component { };
    class Juicy : public Zep::Component { };
    
    class DummyProcessor : public Zep::EntityObserverProcessor {
        void onAdded(Zep::EntityID id) {
            ids.push_back(id);
        }
        Zep::ComponentMask createComponentMask() {
            return database->getComponentMask<Bouncy>();
        }
    public:
        std::vector<Zep::EntityID> ids;
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
            assertEqual(0, dummy.ids[0]);
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
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EntityObserverProcessor";
            add(new AdditionMatchTest());
            add(new AdditionMissTest());
        }
    };
}

#endif
