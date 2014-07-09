#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventManager.h"

namespace EventManagerTestCase {
    class Explosion : public Zep::Event { };
    class Collision : public Zep::Event { };
    
    struct DummyObserver {
        int counter = 0;
        void handle(const Explosion &event) {
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
    
    class TemplateEmissionTest : public Vincent::Test {
    public:
        TemplateEmissionTest() {
            name = "TemplateEmission";
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
    
    class InstanceEmissionTest : public Vincent::Test {
    public:
        InstanceEmissionTest() {
            name = "InstanceEmissionTest";
        }
        void run() {
            Zep::EventManager manager;
            DummyObserver observer;
            auto subscription = manager.subscribe<Explosion>(observer);
            Explosion explosion;
            manager.emit(explosion);
            assertEqual(1, observer.counter);
            Collision collision;
            manager.emit(collision);
            assertEqual(1, observer.counter);
            subscription.cancel();
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventManager";
            add(new SubscriptionTest());
            add(new TemplateEmissionTest());
            add(new InstanceEmissionTest());
        }
    };
}
