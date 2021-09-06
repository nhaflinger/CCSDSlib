#!/usr/bin/env python3

from ccsdslib import CCSDS
from ccsdslib import CCSDSprimaryHeader

#xtce_file = "/home/dcreel/repos/ccsdslib/data/xtce.xml"
xtce_file = "/home/dcreel/repos/lemma/xtce.xml"
root_node = "SpaceSystem"

c = CCSDS()
c.xmlPacketDesc(xtce_file, root_node)

primary_header = CCSDSprimaryHeader()
primary_header.packet_version = c.xtceVersion()
primary_header.packet_type = c.xtceType()
primary_header.packet_sechdrflag = c.xtceSecHdrFlag()
primary_header.apid = c.xtceAPID()
primary_header.packet_count = 0
primary_header.packet_length = 64

#packet_file = "/home/dcreel/repos/ccsdslib/data/testpacket.ccsds"
#packet_fields = c.loadPacketFile(packet_file)

packet_fields = c.packetFields()

#for packet in packet_fields:
    #print(packet)

field_map = {'EpochUSNO' : '0', 'w_B.x' : '0', 'w_B.y' : '0', 'w_B.z' : '0', 'X_E.x' : '0', 'X_E.y' : '0', 'X_E.z' : '0', 'q_B2L.x' : '0', 'q_B2L.y' : '0', 'q_B2L.z' : '0', 'q_B2L.w' : '0'}

packed_bytes = c.encodePacketBytes(primary_header, packet_fields, field_map)
