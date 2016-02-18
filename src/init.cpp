#include <lua.hpp>
#include <init.hh>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

/* the Lua interpreter */
lua_State *L;
unordered_map<string,int> datapoints;

int main (int argc, char *arcv[])
{
    init_datapoints();
    menu();
    return 0;
}

void menu(void) {
    int choice;
    do {
        cout << "Lua example menu\n";
        cout << "Please make your selection\n";
        cout << "============================\n\n";
        cout << "1 - Run program" << endl;
        cout << "2 - Print array" << endl;
        cout << "3 - Reset array" << endl;
        cout << "4 - Quit" << endl << endl;
        cout << "Selection: ";
        cin >> choice;

        switch(choice) {
            case 1:
                char* program;
                program = read_program_file();
                do_string(program);
                break;
            case 2:
                print_array_content();
                break;
            case 3:
                init_datapoints();
                break;
        }
    }while(choice != 4);
}

void print_array_content(void) {
    cout << "datapoints array contains: " << endl << endl;
    for (auto& dp: datapoints) {
        cout << dp.first << ": " << dp.second << endl;
    }
    cout << endl;
}

void init_datapoints(void) {
    datapoints["FB1.IN1"] = 0;
    datapoints["FB1.IN2"]=0;
    datapoints["FB1.IN3"]=0;
    datapoints["FB1.OUT1"]=0;
    datapoints["FB1.OUT2"]=0;
    datapoints["FB1.OUT3"]=0;
    datapoints["FB2.IN1"]=0;
    datapoints["FB2.IN2"]=0;
    datapoints["FB2.IN3"]=0;
    datapoints["FB2.OUT1"]=0;
    datapoints["FB2.OUT3"]=0;
}

void do_string(char* program) {
    cout << "********************\n";
    cout << endl << endl;
    cout << "Executing program" << endl;
    cout << program << endl << endl;
    L = luaL_newstate();
    lua_register(L,"get_value",get_value);
    lua_register(L,"set_value",set_value);
    luaL_openlibs(L);
    luaL_dostring(L,program);
    lua_close(L);
    cout << "********************" << endl << endl;
}

int get_value(lua_State *L) {
    int out = -9999;
    string address = lua_tostring(L,1);
    cerr << "-- read datapoint for address: " << address << endl;
    unordered_map<string,int>::const_iterator got = datapoints.find (address);
    if( got == datapoints.end() ) {
        cout << "--- address: " << address << " not found" << endl;
    }
    else {
        out = got->second;
        cout << "--- value in address: " << address << " is " << out << endl;
    }
    lua_pushnumber(L,out);  // return value
    return 1;               // number of return values
}

int set_value(lua_State *L) {
    string address = lua_tostring(L,1);
    string string_value = lua_tostring(L,2);
    int value = atoi(string_value.c_str());
    datapoints[address] = value;
    cout << "--- set value " << value << " in address: " << address << endl;
    lua_pushnumber(L,true);
    return 1;
}

void report_errors(lua_State *L, int status) {
    if ( status != 0 ) {
        cerr << "-- " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1); // remove error message
    }
}

char* read_program_file(void) {
    ifstream    file;
    size_t      size;
    char*       inBuf;

    file.open("stl.lua",std::ifstream::in);
    file.seekg(0,ios::end);     // get file size
    size = file.tellg();
    cout << "Size of the file: " << size << endl;
    file.seekg(0);

    inBuf = new char[size];
    file.read(inBuf,size);
    file.close();
    return inBuf;
}
