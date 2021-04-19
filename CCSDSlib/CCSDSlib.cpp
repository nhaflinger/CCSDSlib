#include "CCSDSlib.h"
#include <stdio.h>
#include <string.h>

using namespace rapidxml;
using namespace std;

namespace CCSDSlib
{
	CCSDS::CCSDS() :
		m_xtce_apid(0),
		m_xtce_sec_hdr_flag(0),
		m_xtce_version(0),
		m_xtce_type(0)
	{
		m_primary_header.packet_version = 0;
		m_primary_header.packet_type = 0;
		m_primary_header.sec_hdr_flag = 0;
		m_primary_header.apid = 0;
		m_primary_header.seq_flags = 0;
		m_primary_header.packet_count_or_name = 0;
		m_primary_header.packet_length = 0;

		m_secondary_header.seconds = 0;
		m_secondary_header.subseconds = 0;

		m_command_header.packet_length = 0;
		m_command_header.packet_type = 0;
		m_command_header.packet_seq_count = 0;
	}

	CCSDS::~CCSDS()
	{
	}

	void CCSDS::newPacketField(string name, string data_type, int bit_length, int bit_offset, int byte_order)
	{
		PacketField packet_field = PacketField(name, data_type, bit_length, bit_offset, byte_order);
		m_packet_fields.push_back(packet_field);
	}

	void CCSDS::xmlPacketDesc(string file_path, string root_node, int byte_order)
	{
		xml_document<> xml_doc;
		ifstream xml_file(file_path);
		vector<char> xbuffer((istreambuf_iterator<char>(xml_file)), istreambuf_iterator<char>());
		xbuffer.push_back('\0');
		xml_doc.parse<0>(&xbuffer[0]);

		// find root node
		xml_node<>* root = xml_doc.first_node(root_node.c_str());
		m_project_name = root->first_attribute("name")->value();

		xml_node<>* param_type_set;
		xml_node<>* param_set;
		xml_node<>* container_set;

		for (xml_node<>* node = root->first_node(); node; node = node->first_node())
		{
			for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
			{
				if (!strcmp(child->name(), "ParameterTypeSet"))
				{
					param_type_set = child;
				}
				else if (!strcmp(child->name(), "ParameterSet"))
				{
					param_set = child;
				}
				else if (!strcmp(child->name(), "ContainerSet"))
				{
					container_set = child;
				}
			}
		}

		// define parameter types
		map<string, int> param_types;
		map<string, int>::iterator it = param_types.begin();
		for (xml_node<>* node = param_type_set->first_node(); node; node = node->next_sibling())
		{
			string name_val = node->first_attribute("name")->value();

			if (!strcmp(name_val.c_str(), "int8_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "uint8_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "int16_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "uint16_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "int32_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "uint32_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "bool_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "float_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "FloatDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "double_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "DoubleDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "char_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "IntegerDataEncoding"))
					{
						string size_in_bits = child->first_attribute("sizeInBits")->value();
						param_types.insert(it, { name_val, atoi(size_in_bits.c_str()) });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "vec3_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "MemberList"))
					{
						int size_in_bits = 0;
						for (xml_node<>* member = child->first_node(); member; member = member->next_sibling())
						{
							string name_val = member->first_attribute("name")->value();
							string param_type = member->first_attribute("typeRef")->value();
							param_types.insert(it, { name_val, param_types[param_type] });
							size_in_bits += param_types[param_type];
						}
						param_types.insert(it, { name_val, size_in_bits });
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "vec4_t"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "MemberList"))
					{
						int size_in_bits = 0;
						for (xml_node<>* member = child->first_node(); member; member = member->next_sibling())
						{
							string name_val = member->first_attribute("name")->value();
							string param_type = member->first_attribute("typeRef")->value();
							param_types.insert(it, { name_val, param_types[param_type] });
							size_in_bits += param_types[param_type];
						}
						param_types.insert(it, { name_val, size_in_bits });
					}
				}
			}
		}

		// determine parameters
		vector<ParamNameType> param_list;
		for (xml_node<>* node = param_set->first_node(); node; node = node->next_sibling())
		{
			ParamNameType name_type;
			name_type.name = node->first_attribute("name")->value();
			name_type.type = node->first_attribute("parameterTypeRef")->value();

			param_list.push_back(name_type);
		}

		vector<ParamNameType>::iterator im;
		for (im = param_list.begin(); im != param_list.end(); ++im)
		{
			PacketField packet_field = PacketField((*im).name, (*im).type, param_types[(*im).type], byte_order);
			m_packet_fields.push_back(packet_field); 
		}

		// determine telemetry type data;
		for (xml_node<>* node = container_set->first_node(); node; node = node->next_sibling())
		{
			string name_val = node->first_attribute("name")->value();

			if (!strcmp(name_val.c_str(), "TelemetryPacket"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "BaseContainer"))
					{
						for (xml_node<>* gchild = child->first_node(); gchild; gchild = gchild->next_sibling())
						{
							if (!strcmp(gchild->name(), "RestrictionCriteria"))
							{
								for (xml_node<>* ggchild = gchild->first_node(); ggchild; ggchild = ggchild->next_sibling())
								{
									if (!strcmp(ggchild->name(), "ComparisonList"))
									{
										for (xml_node<>* gggchild = ggchild->first_node(); gggchild; gggchild = gggchild->next_sibling())
										{
											string val = gggchild->first_attribute("value")->value();
											string type = gggchild->first_attribute("parameterRef")->value();

											if (type == "CCSDS_Packet_ID/Version")
											{
												m_xtce_version = atoi(val.c_str());
											}
											else if (type == "CCSDS_Packet_ID/Type")
											{
												if (val == "TM")
													m_xtce_type = 0;
												else
													m_xtce_type = 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else if (!strcmp(name_val.c_str(), "Spacecraft"))
			{
				for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
				{
					if (!strcmp(child->name(), "BaseContainer"))
					{
						for (xml_node<>* gchild = child->first_node(); gchild; gchild = gchild->next_sibling())
						{
							for (xml_node<>* gchild = child->first_node(); gchild; gchild = gchild->next_sibling())
							{
								if (!strcmp(gchild->name(), "RestrictionCriteria"))
								{
									for (xml_node<>* ggchild = gchild->first_node(); ggchild; ggchild = ggchild->next_sibling())
									{
										if (!strcmp(ggchild->name(), "ComparisonList"))
										{
											for (xml_node<>* gggchild = ggchild->first_node(); gggchild; gggchild = gggchild->next_sibling())
											{
												string val = gggchild->first_attribute("value")->value();
												string type = gggchild->first_attribute("parameterRef")->value();

												if (type == "CCSDS_Packet_ID/APID")
												{
													m_xtce_apid = atoi(val.c_str());
												}
												else if (type == "CCSDS_Packet_ID/SecHdrFlag")
												{
													m_xtce_sec_hdr_flag = atoi(val.c_str());
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	map<string, string> CCSDS::loadPacketFile(string file_path)
	{
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(m_packet_fields);
		map<string, string> field_map = m_packet_fixed_length.loadFile(file_path);
		m_primary_header = m_packet_fixed_length.primaryHeader();
		return field_map;
	}

	map<string, string> CCSDS::decodePacketBytes(const vector<char>& file_bytes)
	{
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(m_packet_fields);
		map<string, string> field_map = m_packet_fixed_length.decodePacket(file_bytes);
		m_primary_header = m_packet_fixed_length.primaryHeader();
		return field_map;
	}

	map<string, string> CCSDS::loadFrameFile(string file_path)
	{
		Frame frame = Frame(m_frame_data);
		map<string, string> field_map = frame.loadFile(file_path);
		return field_map;
	}

	map<string, string> CCSDS::decodeFrameBytes(const vector<char>& file_bytes)
	{
		Frame frame = Frame(m_frame_data);
		map<string, string> field_map = frame.decodeFrame(file_bytes);
		return field_map;
	}

	vector<char> CCSDS::encodePacketBytes(CCSDSprimaryHeader& header, const vector<PacketField>& packet_fields, const map<string, string>& field_map)
	{
		m_packet_fields = packet_fields;
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(packet_fields);
		m_primary_header = header;
		m_packet_fixed_length.setPrimaryHeader(header);		

		vector<char> packed_bytes = m_packet_fixed_length.encodePacket(field_map, false);

		return packed_bytes;
	}

	vector<char> CCSDS::encodePacketBytes(CCSDSprimaryHeader& header, const vector<PacketField>& packet_fields, const map<string, double>& field_map)
	{
		m_packet_fields = packet_fields;
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(packet_fields);
		m_primary_header = header;
		m_packet_fixed_length.setPrimaryHeader(header);

		map<string, string> tmap;
		map<string, double>::const_iterator it;
		for (it = field_map.begin(); it != field_map.end(); ++it)
			tmap[(*it).first] = to_string((*it).second);

		vector<char> packed_bytes = m_packet_fixed_length.encodePacket(tmap, false);
		return packed_bytes;
	}

	vector<char> CCSDS::encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const vector<PacketField>& packet_fields, const map<string, string>& field_map)
	{
		m_packet_fields = packet_fields;
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(packet_fields);
		m_primary_header = primary_header;
		m_secondary_header = secondary_header;
		m_packet_fixed_length.setPrimaryHeader(primary_header);
		m_packet_fixed_length.setSecondaryHeader(secondary_header);
		vector<char> packed_bytes = m_packet_fixed_length.encodePacket(field_map, true);
		return packed_bytes;
	}

	vector<char> CCSDS::encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const vector<PacketField>& packet_fields, const map<string, double>& field_map)
	{
		m_packet_fields = packet_fields;
		PacketFixedLength m_packet_fixed_length = PacketFixedLength();
		m_packet_fixed_length.setPacketArray(packet_fields);
		m_primary_header = primary_header;
		m_secondary_header = secondary_header;
		m_packet_fixed_length.setPrimaryHeader(primary_header);
		m_packet_fixed_length.setSecondaryHeader(secondary_header);

		map<string, string> tmap;
		map<string, double>::const_iterator it;
		for (it = field_map.begin(); it != field_map.end(); ++it)
			tmap[(*it).first] = to_string((*it).second);

		vector<char> packed_bytes = m_packet_fixed_length.encodePacket(tmap, true);
		return packed_bytes;
	}

	vector<char> CCSDS::encodeCommand(CCSDScommandHeader& command_header, CCSDScommandData& command)
	{
		CommandEncode encoder;
		encoder.setCommandHeader(command_header);
		encoder.setCommandOpcode(command.command_opcode);
		encoder.setDeviceNumber(command.device_number);
		encoder.setCommandData(command.command_data);
		encoder.setCRC32(command.crc32_checksum);
		assert(sizeof(command.command_data) >= COMMAND_DATA_STRING);
		vector<char> packed_bytes = encoder.encodeCommand();
		return packed_bytes;
	}
}