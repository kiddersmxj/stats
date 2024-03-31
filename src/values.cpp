#include "../inc/values.hpp"

namespace fs = std::filesystem;

Values::Values() {
    Refresh();
}

Values::~Values() {
}

void Values::Refresh() {
    for (const auto & File : fs::directory_iterator(StatsDir)) {
        std::ifstream JFile(File.path());
        nlohmann::ordered_json JStats = nlohmann::ordered_json::parse(JFile);
        int i(0);
        for(auto W: JStats) {
            k::T WE = { .Year = W["WE"].at(0), .Month = W["WE"].at(1), .Day = W["WE"].at(2) };

            int j(1);
            std::vector<Value> Values;
            for(int Number: W["number"]) {
                Value Value = { .Number = Number, .DayNum = j, .WE = WE, .Type = W["type"] };
                Values.push_back(Value);
                j++;
            }

            Week Week = { .Values = Values, .Cond = {W["weekcondition"]}, .WE = WE };
            /* std::cout << Week.WE.Year << "-" << Week.WE.Month << "-" << Week.WE.Day << std::endl; */
            /* std::cout << i << "-" << W["total"] << " " << Week.Values.at(0).Number << " " */
            /*     << Week.Cond.Condition << std::endl; */
            i++;
            Weeks.push_back(Week);
        }
    }
}

int Values::GetDay(k::T Time) {
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

