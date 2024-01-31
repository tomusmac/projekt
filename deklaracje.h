#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <codecvt>


using namespace std;

struct Maraton {
    string nazwa;
    string data;
    struct Zawodnik {
        string miejsce;
        string imie;
        string id;
        string czas;
    } NowyZawodnik;
};

bool istnieje(string file);
bool porownajDaty(const Maraton& a, const Maraton& b);

