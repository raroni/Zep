//
//  SafeConversion.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 09/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <limits.h>
#include "Zep/Exception.h"
#include "Zep/Misc/SafeConversion.h"

namespace Zep {
    namespace SafeConversion {
        int toInt(size_t number) {
            if(number > INT_MAX) throw Exception("Conversion overflow.");
            return (int)number;
        }
    }
}
