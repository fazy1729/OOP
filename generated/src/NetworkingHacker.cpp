#include "NetworkingHacker.h"
#include "Level.h"

/**
 * @brief Constructor for the NetworkingHacker class with specialization.
 *
 * This constructor initializes a NetworkingHacker object with a given specialization.
 * The specialization is passed to the base class Hacker constructor.
 *
 * @param specialization The specific area of expertise of the NetworkingHacker.
 */
NetworkingHacker::NetworkingHacker(const std::string& specialization)
    : Hacker("Network Specialist", specialization) {}

/**
 * @brief Default constructor for the NetworkingHacker class.
 *
 * Initializes the NetworkingHacker object with the default specialization of "Networking Specialist".
 */
NetworkingHacker::NetworkingHacker() : specialization("Networking Specialist") {}

/**
 * @brief Simulates a port scan on a target.
 *
 * This method simulates scanning a list of ports for a given target. It checks
 * each port's status (open or closed) based on the port configuration in the current level.
 * A simulated delay is introduced to mimic real-world network scanning.
 *
 * @param target The target IP address or hostname to scan.
 * @param ports A vector of ports to scan.
 * @param level The current level containing the port configurations.
 */
void NetworkingHacker::SimulatePortScan(const std::string &target, const std::vector<int> &ports, const Level &level) {
    std::cout << "Starting port scan on target: " << target << std::endl;

    std::vector<PortStatus> levelPorts = level.getPortsForLevel(level.getCurrentLevel());

    for (int port : ports) {
        bool isOpen = false;
        for (const auto& portStatus : levelPorts) {
            if (portStatus.port == port) {
                isOpen = portStatus.isOpen;
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate delay
        if (isOpen) {
            std::cout << "Port " << port << ": OPEN" << std::endl;
        } else {
            std::cout << "Port " << port << ": CLOSED" << std::endl;
        }
    }
    std::cout << "Port scan completed.\n";
}

/**
 * @brief Intercepts and displays network packets.
 *
 * This method simulates the interception of network packets. Each packet is displayed
 * with a simulated delay to represent real-time interception.
 *
 * @param packets A vector of strings representing intercepted packets.
 */
void NetworkingHacker::InterceptPackets(const std::vector<std::string> &packets) {
    std::cout << "Intercepting packets..." << std::endl;
    for (const auto &packet : packets) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Packet intercepted: " << packet << std::endl;
    }
    std::cout << "Packet interception completed.\n";
}

/**
 * @brief Simulates a spoofed request sent to a target.
 *
 * This method simulates the process of sending a spoofed network request to a target IP
 * with a specified message. It introduces a delay to simulate the time it would take
 * for such an action to be performed.
 *
 * @param targetIP The target IP address to which the request is sent.
 * @param message The message to be sent in the spoofed request.
 */
void NetworkingHacker::SpoofRequest(const std::string &targetIP, const std::string &message) {
    std::cout << "Spoofing request to target: " << targetIP << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Request sent with message: \"" << message << "\"" << std::endl;
    std::cout << "Spoof successful!\n";
}

/**
 * @brief Captures and analyzes network traffic logs.
 *
 * This method simulates the process of capturing network traffic logs and displaying
 * the logs with a delay. It also analyzes the captured traffic logs to extract unique IP addresses.
 *
 * @param trafficLogs A vector of traffic logs to analyze.
 */
void NetworkingHacker::CaptureTraffic(const std::vector<std::string> &trafficLogs) {
    std::cout << "Capturing network traffic..." << std::endl;
    for (const auto &log : trafficLogs) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::cout << "Traffic log: " << log << std::endl;
    }
    std::cout << "Traffic capture completed. Analyzing logs..." << std::endl;

    std::set<std::string> uniqueIPs;
    for (const auto &log : trafficLogs) {
        size_t pos = log.find("IP:");
        if (pos != std::string::npos) {
            std::string ip = log.substr(pos + 3, log.find(' ', pos + 3) - pos - 3);
            uniqueIPs.insert(ip);
        }
    }

    std::cout << "Unique IPs detected: " << std::endl;
    for (const auto &ip : uniqueIPs) {
        std::cout << "  - " << ip << std::endl;
    }
}
