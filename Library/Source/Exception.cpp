//
//  Exception.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"

namespace Zep {
    Exception::Exception(std::string const &message) : runtime_error(message) { }
}
