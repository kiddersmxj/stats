#ifndef K_GRAPHS
#define K_GRAPHS

#include "config.hpp"
#include "values.hpp"

#include "ftxui/screen/color.hpp"  // for colour

typedef struct {
    std::string Name;
    std::vector<Week> Vs;
    ftxui::Color Colour;
} Graph;

/* typedef struct { */
/*     int x; */
/*     int y; */
/*     Value V; */
/* } Point; */

class Graphs {
    public:
        Graphs();
        Graphs(Values &Values);
        ~Graphs();
        std::vector<Graph> Get();
    private:
        std::vector<Point> GenPoints(std::vector<Value> &Values);
        std::vector<Graph> Gs;
        void Refresh();
        void Save();
        int GetDay(k::T Time);
};

#endif

// Copyright (c) 2024, Maxamilian Kidd-May
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

