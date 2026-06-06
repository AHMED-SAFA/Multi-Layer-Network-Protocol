message DNSPacket {
    string queryName;
    string answerIP;
    bool isQuery; // true = query, false = response
}