#ifndef NETWORKINGHACKER_H
#define NETWORKINGHACKER_H

#include <Hacker.h>
#include "EVERYTHING.h"
#include "Level.h"

/**
 * @brief Class representing a Networking Hacker, derived from Hacker.
 */
class NetworkingHacker : public Hacker {
private:
    std::string specialization; /**< The specialization of the Networking Hacker */

public:
    /**
     * @brief Constructor for NetworkingHacker with specialization.
     *
     * @param specialization The specialization of the Networking Hacker.
     */
    NetworkingHacker(const std::string &specialization);

    /**
     * @brief Default constructor for NetworkingHacker.
     */
    NetworkingHacker();

    /**
     * @brief Copy constructor for NetworkingHacker.
     *
     * @param other The other NetworkingHacker object to copy from.
     */
    NetworkingHacker(const NetworkingHacker &other) = default;

    /**
     * @brief Performs network penetration testing.
     */
    void hack() override {
        std::cout << "Performing network penetration testing..." << std::endl;
        std::cout << "Scanning ports 80, 443, 8080..." << std::endl;
        std::cout << "Port scan complete. Open ports found!" << std::endl;
    }

    /**
     * @brief Displays information about the Networking Hacker.
     */
    void display() const override {
        std::cout << "Networking Hacker specializing in analyzing networks!" << std::endl;
    }

    /**
     * @brief Clones the NetworkingHacker object.
     *
     * @return Hacker* A new clone of the current NetworkingHacker object.
     */
    Hacker* clone() const override {
        return new NetworkingHacker(*this);
    }

    /**
     * @brief Destructor for NetworkingHacker.
     */
    ~NetworkingHacker() = default;

    /**
     * @brief Simulates a port scan on a target.
     *
     * @param target The target to perform the port scan on.
     * @param ports The ports to scan.
     * @param level The level associated with the port scan.
     */
    static void SimulatePortScan(const std::string &target, const std::vector<int> &ports, const Level &level);

    /**
     * @brief Intercepts network packets.
     *
     * @param packets The network packets to intercept.
     */
    static void InterceptPackets(const std::vector<std::string> &packets);

    /**
     * @brief Spoofs a request to a target IP with a message.
     *
     * @param targetIP The target IP address to spoof the request to.
     * @param message The message to send with the spoofed request.
     */
    static void SpoofRequest(const std::string &targetIP, const std::string &message);

    /**
     * @brief Captures traffic logs.
     *
     * @param trafficLogs The traffic logs to capture.
     */
    static void CaptureTraffic(const std::vector<std::string> &trafficLogs);

};

#endif
