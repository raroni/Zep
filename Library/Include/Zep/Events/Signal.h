//
//  Signal.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Signal__
#define __Zep__Signal__

#include <vector>

namespace Zep {
    template <typename T> class Signal;
    
    template <typename Arg, typename Ret>
    class Signal<Ret (Arg)> {
        typedef std::function<Ret (Arg)> Callback;
        std::vector<Callback> callbacks;
    public:
        void connect(Callback callback) {
            callbacks.push_back(callback);
        }
        void emit(const Arg &arg) {
            for(Callback callback : callbacks) {
                callback(arg);
            }
        }
    };

}

#endif
