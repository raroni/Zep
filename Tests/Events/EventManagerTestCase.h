#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventManager.h"

namespace EventManagerTestCase {
    class DummyEvent : public Zep::Event { };
    
    struct DummyObserver {
        int counter;
        void receive(const DummyEvent &event) {
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
            auto subscription = manager.subscribe<DummyEvent>(observer);
            manager.emit<DummyEvent>();
            assertEqual(1, observer.counter);
            manager.emit<DummyEvent>();
            assertEqual(2, observer.counter);
            delete subscription;
            manager.emit<DummyEvent>();
            assertEqual(2, observer.counter);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventManager";
            add(new SubscriptionTest());
        }
    };
}
