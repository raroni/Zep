//
//  ComponentList.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__ComponentList__
#define __Zep__ComponentList__

#include <cstring>
#include "Zep/Simulation/ComponentListInterface.h"

namespace Zep {
    template <class T>
    class ComponentList : public ComponentListInterface {
        T* data;
        size_t size = 0;
    public:
        ComponentList() {
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
        ~ComponentList() {
            delete[] data;
        }
    };
}

#endif
