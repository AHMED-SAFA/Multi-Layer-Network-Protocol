package multilayernetwork;

network Network
{
    submodules:
        pc: PC;
        dnsServer: DNSServer;
        httpServer: HTTPServer;
        router: Router;

    connections:
        pc.out --> router.inPC;
        router.outPC --> pc.in;

        dnsServer.out --> router.inDNS;
        router.outDNS --> dnsServer.in;

        httpServer.out --> router.inHTTP;
        router.outHTTP --> httpServer.in;
}