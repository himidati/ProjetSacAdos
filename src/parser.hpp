#pragma once

#include <string>
#include<iostream>

using namespace std;

// Structure pour stocker les valeurs et les poids
struct Item {
    int value;
    int weight;
};


string convertFile(const string& inputFileName);

bool toCSV(const string & inputFileName);
