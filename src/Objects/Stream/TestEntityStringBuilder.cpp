#include "TestEntityStringBuilder.hpp"

#include <iostream>

#include "EntityStringBuilder.hpp"
#include "Test/TestUtils.hpp"

void TestEntityStringBuilder::TestFactoryString() {
    std::cout << "Starting TestFactoryString" << std::endl;

    EntityStringBuilder esb1(569, "SOME_TYPE", 1);
    esb1.SetArg2(5000)
            .SetArg3((Id) 568)
            .SetArg4((short) -100)
            .SetArg5(2);
    AssertEquals<std::string>("569 SOME_TYPE 1 5000 568 -100 2", esb1.Build());

    EntityStringBuilder esb2(617, "OTHER_TYPE", 6);
    esb2.SetArg2(500)
            .SetArg3((unsigned short) 1)
            .SetArg4((unsigned int) 100000);
    AssertEquals<std::string>("617 OTHER_TYPE 6 500 1 100000 0", esb2.Build());
}
