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

void
usage(const char* program)
{
	std::cout <<
		"Usage: " << program << " [options]\n" <<
		"Description: CCSDS telemetry decoder\n" <<
		"Options:\n" <<
		"    -x            XTCE packet definition\n" <<
		"    -f            CCSDS data\n" << std::endl;
}

int main(int argc, char* argv[])
{
	/* read command line arguments */
	const char* program = argv[0];
	std::string xtce_file;
	std::string ccsds_file;
	if (argc == 1)
	{
		usage(program);
		exit(0);
	}

	// parse command line
	for (int n = 1; n < argc; ++n)
	{
		std::string str1(argv[n]);
		if (str1 == "-x")
		{
			std::string str2(argv[n + 1]);
			xtce_file.assign(str2);
		}
		else if (str1 == "-f")
		{
			std::string str2(argv[n + 1]);
			ccsds_file.assign(str2);
		}
	}

	CCSDS telemetry;

	// define packet fields
	/*string nameval = "foo";
	int bitlength = 8;
	int bitoffset = 0;
	telemetry.newPacketField(nameval, "uint8_t", bitlength, bitoffset, 1);

	nameval = "bar";
	bitlength = 8;
	bitoffset = 8;
	telemetry.newPacketField(nameval, "uint8_t", bitlength, bitoffset, 1);*/

	// XTCE telemetry dictionary
	telemetry.xmlPacketDesc(xtce_file, "SpaceSystem", 1);

	// this is retrieved from XTCE file
	cout << "XTCE APID: " << telemetry.xtceAPID() << endl;
	cout << "XTCE Type: " << telemetry.xtceType() << endl;
	cout << "XTCE Version: " << telemetry.xtceVersion() << endl;
	cout << "XTCE SecHdrFlag: " << telemetry.xtceSecHdrFlag() << endl;

	//map<string, string> field_map = telemetry.loadPacketFile(ccsds_file);

	vector<char> file_bytes = loadFile(ccsds_file);
	map<string, string> field_map = telemetry.decodePacketBytes(file_bytes);

	CCSDSprimaryHeader primary_header = telemetry.primaryHeader();
	cout << "Packet apid: " << primary_header.apid << endl;

	map<string, string>::iterator it;
	for (it = field_map.begin(); it != field_map.end(); ++it)
	{
		cout << (*it).first << " " << (*it).second << endl;
	}

	// test packet encoding
	CCSDSprimaryHeader header;
	header.apid = 100;
	header.packet_version = 0;
	header.packet_type = 0;
	header.sec_hdr_flag = 0;
	header.seq_flags = 0;
	header.packet_count_or_name = 0;
	header.packet_length = 123;

	vector<PacketField> packet_fields = telemetry.packetFields();

	vector<char> packed_bytes;
	packed_bytes = telemetry.encodePacketBytes(header, packet_fields, field_map);

	// test results

	primary_header = telemetry.primaryHeader();
	cout << "Packet apid: " << primary_header.apid << endl;
	cout << "Packet type: " << primary_header.packet_type << endl;
	cout << "Packet version: " << primary_header.packet_version << endl;
	cout << "Packet sec_hdr_flag: " << primary_header.sec_hdr_flag << endl;

	field_map = telemetry.decodePacketBytes(packed_bytes);
	for (it = field_map.begin(); it != field_map.end(); ++it)
	{
		cout << (*it).first << " " << (*it).second << endl;
	}

	cout << "----------------- Command Packet -------------------------------" << endl;

	// test command encoding
	CCSDScommandHeader cheader;
	int packet_length = COMMAND_HEADER_OFFSET + COMMAND_OPCODE + COMMAND_DEVICE_NUMBER + COMMAND_DATA_STRING + COMMAND_CRC32;
	cheader.packet_type = 1;
	cheader.packet_seq_count = 0;
	cheader.packet_length = packet_length;
	CCSDScommandData cdata;
	cdata.command_opcode = 1000;
	cdata.device_number = 1;
	cdata.crc32_checksum = 1234;

	vector<char> command;
	vector<char> command_data;
	char message[COMMAND_DATA_STRING] = { 'T','h','i','s',' ','i','s',' ','t','h','e',' ','c','o','m','m','a','n','d',' ','b','y','e' };
	memcpy(cdata.command_data, message, COMMAND_DATA_STRING);
	for (int i = 0; i < COMMAND_DATA_STRING; i++)
	{
		command_data.push_back(message[i]);
	}
	command = telemetry.encodeCommand(cheader, cdata);
	
	cout << "Command packet type: " << std::to_string(command[0]).c_str() << endl;
	cout << "Command packet sequence count: " << std::to_string(command[4]).c_str() << endl;
	cout << "Command packet length: " << std::to_string(command[8]).c_str() << endl;
	cout << "Command opcode: " << std::to_string(command[12]).c_str() << endl;
	cout << "Command device number: " << std::to_string(command[16]).c_str() << endl;

	for (int j = COMMAND_HEADER_OFFSET+COMMAND_OPCODE+COMMAND_DEVICE_NUMBER; j < packet_length-COMMAND_CRC32; j++)
	{
		cout << command[j] << " ";
	}
	cout << endl;

	return 0;
}