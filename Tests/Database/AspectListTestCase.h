#include "vincent/test_case.h"
#include "vincent/test.h"
#include "Zep/Database/AspectList.h"

namespace AspectListTestCase {
    struct Jetpack : public Zep::Aspect {
        int thrust = 1234;
    };
    
    class GetAndResizeTest : public Vincent::Test {
    public:
        GetAndResizeTest() {
            name = "GetAndReisze";
        }
        void run() {
            Zep::AspectList<Jetpack> jetpack;
            jetpack.resize(5);
            jetpack[2].thrust = 42;
            
            jetpack.resize(10);
            
            assertEqual(42, jetpack[2].thrust);
        }
    };
    
    class Case : public Vincent::TestCase {
    public:
        Case() {
            name = "AspectList";
            add(new GetAndResizeTest());
        }
    };
}
