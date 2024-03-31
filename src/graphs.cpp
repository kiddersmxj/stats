#include "../inc/graphs.hpp"

Graphs::Graphs() {
}

Graphs::Graphs(Values &Values) {
    for(auto V: Values.GetTotals()) {
        std::cout << V.WE.Date << " - " << V.Number << std::endl;
    }
}

Graphs::~Graphs() {
}

std::vector<Point> Graphs::GenPoints(std::vector<Value> &Values) {
    std::vector<Point> Points;
    for(auto Value: Values) {

    }
    return Points;
}

int Graphs::GetDay(k::T Time) {
	int _day = Time.Day;
	int month = Time.Month;
	int year = Time.Year;

    std::vector<int> days={31,28,31,30,31,30,31,31,30,31,30,31};        
    std::vector<int> dates = { 4, 5, 6, 7, 1, 2, 3 };        

    int d = _day;        
    for(int i = 0; i < month-1; i++) d += days[i];        
    if ( ( ( year%4 == 0 && year%100 != 0) || year%400 == 0) && month > 2) d++;        
        for(int i = 1971; i < year; i++) {
            if ( ( i%4 == 0 && i%100 != 0) || i%400 == 0) d += 366;
            else d += 365;
        }
        
    int result = dates[ ( d%7 + 3 ) % 7];
    return result;
}


// Copyright (c) 2024, Maxamilian Kidd-May
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

