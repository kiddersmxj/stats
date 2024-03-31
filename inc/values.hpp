#ifndef K_VALUES
#define K_VALUES

#include "condition.hpp"
#include "config.hpp"

#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>
#define NLOHMANN_JSON_PRESERVE_ORDER
using json = nlohmann::json_abi_v3_11_2::json;

typedef struct {
    int Number;
    int DayNum;
    k::T WE;
    std::string Type;
} Value;

typedef struct {
    int x;
    int y;
    Value V;
} Point;

typedef struct {
    std::vector<Value> Values;
    Condition Cond;
    k::T WE;
    std::string Type;
    int Total;
} Week;

class Values {
    public:
        Values();
        ~Values();
        void Refresh();
        std::vector<Value> GetTotals();
        std::vector<Week> GetWeeks();
        int ExtrapolateHeight(int &Input, int &Lowest, int &Highest, int &Height);
        int ExtrapolateWidth(int &Input, int Size, int &Height);
        int Reverse(int &Input, int &Height);
    private:
        std::vector<Value> Totals;
        std::vector<Week> Weeks;
        int GetDay(k::T Time);
};

#endif

// Copyright (c) 2024, Maxamilian Kidd-May
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

