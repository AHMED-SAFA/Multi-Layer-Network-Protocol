message ARPPacket {
    string srcIP;
    string dstIP;
    string srcMAC;
    string dstMAC;
    bool isRequest; // true = request, false = reply
}