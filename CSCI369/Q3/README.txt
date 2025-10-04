Student Name: Edward Wagstaffe
UOW ID: 8762697
CSCI369 – Assignment (Task 3)

Requirements: 
Operating System: Kali linux with openssl and Python 3.x 


Overview:
This Python script simulates a basic ransomware attack by encrypting a file named my_secrets.txt located in the root directory of the victim's machine. It uses OpenSSL for cryptographic operations, including symmetric and asymmetric encryption. The script generates a ransom note instructing the victim to pay for decryption.
Note: This script is for educational purposes only and should not be used maliciously.

Permissions: Root privileges required (sudo)

Usage:
1. Target file

A file named my_secrets.txt must exist in the root directory (/my_secrets.txt).

For example: $> echo "Highly confidential data" | sudo tee /my_secrets.txt

Ensure permissions allow the script to modify and encrypt /my_secrets.txt


2. Execute the ransomware.py script.

For example: $> sudo python3 ransomware.py 


Expected output
[*] Generating RSA key pair...
[+] RSA key pair generated (private.pem, public.pem)
[+] Symmetric key generated and saved to key.txt
[*] Encrypting /my_secrets.txt with symmetric key...
[+] /my_secrets.txt encrypted to data_cipher.txt
[*] Encrypting key.txt with attacker public key...
[+] key.txt encrypted to key_cipher.txt
[*] Cleaning up plaintext files...
[+] Deleted key.txt
[+] Deleted /my_secrets.txt

Your file my_secrets.txt is encrypted. To decrypt it, you need to pay me $1,000 and send key_cipher.txt to me.


Files Generated

private.pem: RSA private key (kept by the attacker).
public.pem: RSA public key (used for encryption).
key.txt: Temporary file containing the symmetric key (deleted after encryption).
data_cipher.txt: Encrypted version of my_secrets.txt.
key_cipher.txt: Encrypted symmetric key (needed for decryption).

