#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Events/EventSignal.h"
#include "Zep/Events/EventSubscription.h"

namespace EventSubscriptionTestCase {
    class CancelTest : public Vincent::Test {
    public:
        CancelTest() {
            name = "Cancel";
        }
        void run() {
            Zep::EventSignal signal;
            int id = signal.subscribe([](const Zep::Event&) { });
            auto subscription = Zep::EventSubscription(signal, id);
            assert(1 == signal.getSubscriptionsCount());
            subscription.cancel();
            assert(0 == signal.getSubscriptionsCount());
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "EventSubscription";
            add(new CancelTest());
        }
    };
}
