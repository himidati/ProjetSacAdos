#pragma once

#include <string>
#include<iostream>

using namespace std;

struct Item {
    int value;
    int weight;
};

void convertFile(const string& inputFileName);
