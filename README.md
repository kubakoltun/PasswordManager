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

To start a program it is recommended to run a compile of all the scripts and then run the program itself.
``` bash
# Compile all .cpp files in the current folder
g++ *.cpp -o password_manager

# Run the program
./password_manager
```

On startup, the program reads and decrypts the encrypted file.
Users can view, add, remove, sort or search passwords.
Before closing, data is re-encrypted and saved with additional random noise.
Your passwords never appear in plain text outside the program’s runtime.

### TODO

There is a bug in viewing the results, primerly on editting the password. The line numbers come from a file. Not really an issue i guess. The anoying thing is when you search the password it does not show you the actual password just the tag you were searching by.
Also better cypher would be nice, maybe at least a bit shifting (>>) insted of the ROT.
Polish commands - to be replaced.
