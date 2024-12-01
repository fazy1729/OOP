#ifndef NETWORKINGHACKER_H
#define NETWORKINGHACKER_H

#include <Hacker.h>

#include "EVERYTHING.h"
#include "Level.h"

using namespace std;

class NetworkingHacker:public Hacker {
private:
    string specialization;
public:
    NetworkingHacker(const string &specialization);
    NetworkingHacker();
    NetworkingHacker(const NetworkingHacker &other) = default;

    void hack() override {
        cout << "Performing network penetration testing..." << endl;
        // Simulate performing a port scan on a target
        cout << "Scanning ports 80, 443, 8080..." << endl;
        // (Again, this is a simplified message, you can expand it to actual logic)
        cout << "Port scan complete. Open ports found!" << endl;
    }

    void display() const override {
        cout << "Networking Hacker specializing in analyzing networks!" << endl;
    }
    Hacker* clone() const override {
        return new NetworkingHacker(*this);  // Returnează o clonă a obiectului NetworkingHacker
    }

    ~NetworkingHacker() = default;

    static void SimulatePortScan(const std::string &target, const std::vector<int> &ports, const Level &level);
    static void InterceptPackets(const vector<string> &packets);
    static void SpoofRequest(const string &targetIP, const string &message);
    static void CaptureTraffic(const vector<string> &trafficLogs);

};

#endif