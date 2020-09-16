//
// Created by penguin on 9/15/20.
//

#ifndef PLAYGROUND_CONSTANTS_H
#define PLAYGROUND_CONSTANTS_H

namespace Constants {
constexpr const char* const ProcDirectory = "/proc/";
constexpr const char* const CmdlineFilename = "/cmdline";
constexpr const char* const CpuinfoFilename = "cpuinfo";
constexpr const char* const StatusFilename = "/status";
constexpr const char* const StatFilename = "stat";
constexpr const char* const UptimeFilename = "uptime";
constexpr const char* const MemInfoFilename = "meminfo";
constexpr const char* const VersionFilename = "/version";
constexpr const char* const OSRealesePath = "/etc/os-release";
constexpr const char* const PasswordPath = "/etc/passwd";

enum class CPUStates : int {
  S_USER = 1,
  S_NICE,
  S_SYSTEM,
  S_IDLE,
  S_IOWAIT,
  S_IRQ,
  S_SOFTIRQ,
  S_STEAL,
  S_GUEST,
  S_GUEST_NICE
};

}  // namespace Constants

#endif  // PLAYGROUND_CONSTANTS_H
