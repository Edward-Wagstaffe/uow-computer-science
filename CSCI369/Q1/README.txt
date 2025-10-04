Student Name: Edward Wagstaffe
UOW ID: 8762697
CSCI369 – Assignment (Task 1)

Requirements: 
OS: Kali linux (attacker)
Ubuntu VM (router)
Metasploitable2 (victim)
All machines on NAT network
Python 3.x 
Scapy (pip install scapy)
Wireshark (for monitoring, optional but recommended)


Overview
This Python script performs ARP spoofing to enable a man-in-the-middle (MITM) attack by manipulating ARP tables. It tricks the victim into believing the attacker's machine is the router and the router into believing the attacker's machine is the victim, allowing the attacker to intercept network traffic.
Note: This script is for educational purposes only and should not be used maliciously.
Prerequisites


Permissions: Root privileges required (sudo)

Usage:

1. Enable IP forwarding on the attacker machine: $> echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward


2. Run the script with root privileges, specifying the victim and router IPs:sudo python3 arp_spoof.py <victim_ip> <router_ip>

For example: $> sudo python3 arp_spoof.py 10.0.2.4 10.0.2.5


The script will:
Resolve MAC addresses for the victim and router.
Start ARP spoofing to establish the MITM position.
Run until interrupted (Ctrl+C).
Restore ARP tables upon interruption.


Example Output
ARP spoofing started...
Press Ctrl+C to stop and restore ARP tables
^C
Restoring ARP tables...
ARP spoofing stopped


ARP Table Check:
On the victim or router machine, check the ARP table before and during the attack: $> arp -a

Before the attack, the router's IP should map to its legitimate MAC address. During the attack, it should map to the attacker's MAC address, indicating successful spoofing.


Wireshark: 
Launch Wireshark on the attacker machine with root privileges: $> sudo wireshark

On the eth0 interface:
Look for ARP "is-at" packets where the attacker's MAC address is associated with the router's IP (victim's perspective) and the victim's IP (router's perspective).

