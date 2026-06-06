package multilayernetwork;
simple DNSServer
{
    parameters:
        string ipAddr = default("192.168.0.10");
        string macAddr = default("AA:BB:CC:DD:EE:10");
    gates:
        input in;
        output out;
}