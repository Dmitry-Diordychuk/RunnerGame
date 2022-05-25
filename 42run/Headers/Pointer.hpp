//
// Created by ebona on 25.05.2022.
//

#ifndef INC_42RUN_POINTER_HPP
#define INC_42RUN_POINTER_HPP

#include <memory>

namespace ft
{
    using namespace std;

    template <typename T>
    using Ref = shared_ptr<T>;

    template <typename T>
    using Scope = unique_ptr<T>;
}

#endif //INC_42RUN_POINTER_HPP
