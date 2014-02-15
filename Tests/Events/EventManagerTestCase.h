#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventManager.h"

namespace EventManagerTestCase {
    class Explosion : public Zep::Event { };
    class Collision : public Zep::Event { };
    
    struct DummyObserver {
        int counter = 0;
        void receive(const Explosion &event) {
            counter++;
        }
    };
    
    class SubscriptionTest : public Vincent::Test {
    public:
        SubscriptionTest() {
            name = "Subscription";
        }
        void run() {
            Zep::EventManager manager;
            DummyObserver observer;
            auto subscription = manager.subscribe<Explosion>(observer);
            manager.emit<Explosion>();
            assertEqual(1, observer.counter);
            manager.emit<Explosion>();
            assertEqual(2, observer.counter);
            subscription.cancel();
            manager.emit<Explosion>();
            assertEqual(2, observer.counter);
        }
    };
    
    class VariousEventTypesTest : public Vincent::Test {
    public:
        VariousEventTypesTest() {
            name = "VariousEventTypes";
        }
        void run() {
            Zep::EventManager manager;
            DummyObserver observer;
            auto subscription = manager.subscribe<Explosion>(observer);
            manager.emit<Explosion>();
            assertEqual(1, observer.counter);
            manager.emit<Collision>();
            assertEqual(1, observer.counter);
            subscription.cancel();
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventManager";
            add(new SubscriptionTest());
            add(new VariousEventTypesTest());
        }
    };
}
