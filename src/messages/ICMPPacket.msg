message ICMPPacket {
    string srcIP;
    string dstIP;
    int seqNum;
    bool isEchoRequest; // true = request, false = reply
}