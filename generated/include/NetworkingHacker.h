#ifndef NETWORKINGHACKER_H
#define NETWORKINGHACKER_H

#include "EVERYTHING.h"
#include "Level.h"

using namespace std;

class NetworkingHacker {
private:
    string specialization;
public:
    NetworkingHacker(const string &specialization);
    NetworkingHacker();
    NetworkingHacker(const NetworkingHacker &other) = default;

    ~NetworkingHacker() = default;

    static void SimulatePortScan(const std::string &target, const std::vector<int> &ports, const Level &level);
    static void InterceptPackets(const vector<string> &packets);
    static void SpoofRequest(const string &targetIP, const string &message);
    static void CaptureTraffic(const vector<string> &trafficLogs);

};

#endif
