//
// Created by Fady on 1/7/2018.
//

#ifndef WET2_EXCEPTIONS_H
#define WET2_EXCEPTIONS_H

#include <stdexcept>

namespace DataStructure {

    class DataStructureException {};

    class Invalid_Input : public DataStructureException {};

    class Fail : public DataStructureException {};

    // class UNEXPECTED :public DataStructureException();
}


#endif //WET2_EXCEPTIONS_H
