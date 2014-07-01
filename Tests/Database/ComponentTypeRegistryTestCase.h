#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Database/ComponentTypeRegistry.h"

namespace ComponentTypeRegistryTestCase {
    struct Jetpack : public Zep::Component { };
    struct Lens : public Zep::Component { };
    struct Bouncy : public Zep::Component { };
    
    class GetTest : public Vincent::Test {
    public:
        GetTest() {
            name = "Get";
        }
        void run() {
            Zep::ComponentTypeRegistry registry(32);
            assertEqual(0, registry.getID<Jetpack>());
            assertEqual(0, registry.getID<Jetpack>());
            assertEqual(1, registry.getID<Lens>());
            assertEqual(0, registry.getID<Jetpack>());
            assertEqual(1, registry.getID<Lens>());
        }
    };
    
    class OverflowTest : public Vincent::Test {
    public:
        OverflowTest() {
            name = "Overflow";
        }
        void run() {
            Zep::ComponentTypeRegistry registry(2);
            assertEqual(0, registry.getID<Jetpack>());
            assertEqual(1, registry.getID<Lens>());
            
            auto func = [&registry] () {
                registry.getID<Bouncy>();
            };
            
            assertThrows<Zep::Exception>(func);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "ComponentTypeRegistry";
            add(new GetTest());
            add(new OverflowTest());
        }
    };
}
