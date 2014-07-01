#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Database/EntityObserver.h"
#include "Zep/Database/EntityObserverDelegate.h"

namespace EntityObserverTestCase {
    class DummyDelegate : public Zep::EntityObserverDelegate {
    public:
        std::set<Zep::EntityID> entityIDs;
        bool nextMatch = false;
        int additions = 0;
        int removals = 0;
        
        bool match(Zep::EntityID id) {
            return nextMatch;
        }
        
        void handleAddition(Zep::EntityID id) {
            additions++;
            entityIDs.insert(id);
        }
        
        void handleRemoval(Zep::EntityID id) {
            removals++;
            entityIDs.erase(id);
        }
    };
    
    class AdditionTest : public Vincent::Test {
    public:
        AdditionTest() {
            name = "Addition";
        }
        void run() {
            Zep::EventManager eventManager;
            DummyDelegate delegate;
            delegate.nextMatch = true;
            Zep::EntityObserver entityObserver(eventManager, delegate);
            entityObserver.initialize();
            eventManager.emit<Zep::EntityIDAddition>(17);

            delegate.nextMatch = false;
            eventManager.emit<Zep::EntityIDAddition>(18);
            
            assertEqual(delegate.additions, 1);
            assert(delegate.entityIDs.size() == 1);
            assert(delegate.entityIDs.find(17) != delegate.entityIDs.end());
        }
    };
    
    class AdditionMissTest : public Vincent::Test {
    public:
        AdditionMissTest() {
            name = "AdditionMiss";
        }
        void run() {
            Zep::EventManager eventManager;
            DummyDelegate delegate;
            delegate.nextMatch = false;
            Zep::EntityObserver entityObserver(eventManager, delegate);
            entityObserver.initialize();
            eventManager.emit<Zep::EntityIDAddition>(17);
            
            assertEqual(delegate.additions, 0);
        }
    };
    
    class DestructionTest : public Vincent::Test {
    public:
        DestructionTest() {
            name = "Destruction";
        }
        void run() {
            Zep::EventManager eventManager;
            DummyDelegate delegate;
            delegate.nextMatch = true;
            Zep::EntityObserver entityObserver(eventManager, delegate);
            entityObserver.initialize();
            eventManager.emit<Zep::EntityIDAddition>(42);
            delegate.nextMatch = false;
            eventManager.emit<Zep::EntityIDDestruction>(42);
            eventManager.emit<Zep::EntityIDDestruction>(43);
            
            assert(delegate.entityIDs.size() == 0);
            assertEqual(delegate.additions, 1);
            assertEqual(delegate.removals, 1);
        }
    };
    
    class DestructionMissTest : public Vincent::Test {
    public:
        DestructionMissTest() {
            name = "DestructionMiss";
        }
        void run() {
            Zep::EventManager eventManager;
            DummyDelegate delegate;
            Zep::EntityObserver entityObserver(eventManager, delegate);
            entityObserver.initialize();
            eventManager.emit<Zep::EntityIDDestruction>(43);
            
            assertEqual(delegate.removals, 0);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EntityObserver";
            add(new AdditionTest());
            add(new AdditionMissTest());
            add(new DestructionTest());
            add(new DestructionMissTest());
        }
    };
}
