#include "NetworkingHacker.h"
#include "Level.h"
using namespace std;

NetworkingHacker::NetworkingHacker(const std::string& specialization)
    : Hacker("Network Specialist", specialization){}

NetworkingHacker::NetworkingHacker() : specialization("Networking Specialist") {}

void NetworkingHacker::SimulatePortScan(const string &target, const vector<int> &ports, const Level &level) {
    cout << "Starting port scan on target: " << target << endl;

    vector<PortStatus> levelPorts = level.getPortsForLevel(level.getCurrentLevel());

    for (int port : ports) {
        bool isOpen = false;
        for (const auto& portStatus : levelPorts) {
            if (portStatus.port == port) {
                isOpen = portStatus.isOpen;
                break;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate delay
        if (isOpen) {
            cout << "Port " << port << ": OPEN" << endl;
        } else {
            cout << "Port " << port << ": CLOSED" << endl;
        }
    }
    cout << "Port scan completed.\n";
}

void NetworkingHacker::InterceptPackets(const vector<string> &packets) {
    cout << "Intercepting packets..." << endl;
    for (const auto &packet : packets) {
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "Packet intercepted: " << packet << endl;
    }
    cout << "Packet interception completed.\n";
}

void NetworkingHacker::SpoofRequest(const string &targetIP, const string &message) {
    cout << "Spoofing request to target: " << targetIP << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Request sent with message: \"" << message << "\"" << endl;
    cout << "Spoof successful!\n";
}

void NetworkingHacker::CaptureTraffic(const vector<string> &trafficLogs) {
    cout << "Capturing network traffic..." << endl;
    for (const auto &log : trafficLogs) {
        this_thread::sleep_for(chrono::milliseconds(150));
        cout << "Traffic log: " << log << endl;
    }
    cout << "Traffic capture completed. Analyzing logs..." << endl;

    set<string> uniqueIPs;
    for (const auto &log : trafficLogs) {
        size_t pos = log.find("IP:");
        if (pos != string::npos) {
            string ip = log.substr(pos + 3, log.find(' ', pos + 3) - pos - 3);
            uniqueIPs.insert(ip);
        }
    }

    cout << "Unique IPs detected: " << endl;
    for (const auto &ip : uniqueIPs) {
        cout << "  - " << ip << endl;
    }
}