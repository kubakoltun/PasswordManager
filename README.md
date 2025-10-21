# Password Manager

A simple terminal-based password manager written in C++.
It lets you store, search, generate, and encrypt passwords, all while keeping your data private using a built-in file encryption and noise generator.

Implemented password-related functionalities:

* sorting,
* grouping,
* generating,
* strength checking,
* adding,
* deleting,
* searching,
* encrypting and decrypting,
* generating artificial noise in the main file

The program runs entirely from the terminal, with no graphical interface.


### How It Works

On startup, the program reads and decrypts the encrypted file.
Users can view, add, remove, sort or search passwords.
Before closing, data is re-encrypted and saved with additional random noise.
Your passwords never appear in plain text outside the program’s runtime.
