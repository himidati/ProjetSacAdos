#pragma once

#include<filesystem>
#include <string>
#include<iostream>

using namespace std;
namespace fs=filesystem;

struct Item {
    int value;
    int weight;
};

vector<string> recupererTousFichier(string const & folder);
void convertFile(const string& inputFileName);
void convertInstanceType3(string const & inputfile);
void genereFichierSolution(string const & inputfile);
void validationCoherence(string const & inputfile);
void parseInstances(string const & txtfile);
void converInstanceType2(string const  & inputfile);