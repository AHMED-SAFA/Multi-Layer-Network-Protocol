package multilayernetwork;
simple HTTPServer
{
    parameters:
        string ipAddr = default("192.168.0.20");
        string macAddr = default("AA:BB:CC:DD:EE:20");
    gates:
        input in;
        output out;
}