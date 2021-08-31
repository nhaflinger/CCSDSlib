#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "CCSDSlib.h"

using namespace std;
using namespace CCSDSlib;

vector<char> loadFile(string file_path)
{
        vector<char> file_bytes;

        ifstream in_file(file_path, ios::binary);
        if (in_file.good())
        {
                in_file.seekg(0, ios::end);
                int num_bytes = (int)in_file.tellg();
                cout << "Bytes in file: " << " " << num_bytes << " " << "bytes" << endl;

                in_file.seekg(0, ios::beg);
                char c = in_file.get();
                file_bytes.push_back('\0');
                while (in_file.good())
                {
                        c = in_file.get();
                        file_bytes.push_back(c);
                }
        }
        else
        {
                cout << "File does not exist!" << endl;
        }

        return file_bytes;
}

int decodeCheck(std::string ccsds_file, std::string xtce_file, int apid) 
{
    CCSDS telemetry;
        
    // XTCE telemetry dictionary
    telemetry.xmlPacketDesc(xtce_file, "SpaceSystem", 1);

    vector<char> file_bytes = loadFile(ccsds_file);
    map<string, string> field_map = telemetry.decodePacketBytes(file_bytes);

    CCSDSprimaryHeader primary_header = telemetry.primaryHeader();
    if (apid == primary_header.apid)
        return 0;

    return -1;
}


