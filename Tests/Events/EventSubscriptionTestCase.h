#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventSignal.h"
#include "Zep/Events/EventSubscription.h"

namespace EventSubscriptionTestCase {
    class DeleteTest : public Vincent::Test {
    public:
        DeleteTest() {
            name = "Delete";
        }
        void run() {
            Zep::EventSignal signal;
            int id = signal.subscribe([](const Zep::Event&) { });
            auto subscription = new Zep::EventSubscription(signal, id);
            assert(1 == signal.getSubscriptionsCount());
            delete subscription;
            assert(0 == signal.getSubscriptionsCount());
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSubscription";
            add(new DeleteTest());
        }
    };
}
