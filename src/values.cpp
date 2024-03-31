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

            std::string Type = W["type"];
            int TotalNum = W["total"];
            Condition Cond = { .Condition = W["weekcondition"] };
            k::T WE(W["WE"].at(0), W["WE"].at(1), W["WE"].at(2), true);

            int j(1);
            std::vector<Value> Values;
            for(int Number: W["number"]) {
                Value Value = { .Number = Number, .DayNum = j, .WE = WE, .Type = Type };
                Values.push_back(Value);
                j++;
            }

            Week Week = { .Values = Values, .Cond = Cond, .WE = WE, .Total = TotalNum };
            Value Total = { .Number = TotalNum, .WE = WE, .Type = Type };
            /* std::cout << Week.WE.Year << "-" << Week.WE.Month << "-" << Week.WE.Day << std::endl; */
            /* std::cout << i << "-" << W["total"] << " " << Week.Values.at(0).Number << " " */
            /*     << Week.Cond.Condition << std::endl; */
            i++;
            Totals.push_back(Total);
            Weeks.push_back(Week);
        }
    }
}

std::vector<Value> Values::GetTotals() {
    return Totals;
}

std::vector<Week> Values::GetWeeks() {
    return Weeks;
}

int Values::ExtrapolateHeight(int &Input, int &Lowest, int &Highest, int &Height) {
    // Check if Input is within the range of Lowest and Highest
    if (Input < Lowest)
        Input = Lowest;
    else if (Input > Highest)
        Input = Highest;

    // Calculate the extrapolated value
    return (Height - ((Input - Lowest) * Height / (Highest - Lowest)));
}

int Values::ExtrapolateWidth(int &Input, int Size, int &Width) {
    int reversedInput = Size - Input - 1;
    int extrapolatedValue = (reversedInput * Width) / Size;
    return extrapolatedValue;
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

