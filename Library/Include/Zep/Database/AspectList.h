//
//  AspectList.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__AspectList__
#define __Zep__AspectList__

#include <cstring>
#include "Zep/Database/AspectListInterface.h"

namespace Zep {
    template <class T>
    class AspectList : public AspectListInterface {
        T* data;
        size_t size = 0;
    public:
        AspectList() {
            data = new T[size];
        }
        T& operator[](int index) {
            return data[index];
        }
        void resize(size_t newSize) {
            T* newData = new T[newSize];
            std::memcpy(newData, data, size);
            delete[] data;
            data = newData;
            size = newSize;
        }
        ~AspectList() {
            delete[] data;
        }
    };
}

#endif
