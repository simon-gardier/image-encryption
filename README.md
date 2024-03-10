# 🛡️ Command Line Tool for PNM Images Encryption
![Release](https://img.shields.io/badge/Release-v1.0-blueviolet?style=for-the-badge)
![Language](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge)

<div style="display: flex; justify-content: space-around; align-items: center;">
  <img src="img/decrypted.png" alt="Pixel art of a city" style="width: 40%;"/>
  <img src="img/left.png" alt="Arrow poiting from left to right" style="width: 10%;"/>
  <img src="img/encrypted.png" alt="Encrypted pixel art of a city, noisy image" style="width: 40%;"/>
</div>


Tool to encrypt/decrypt images of type PNM (PBM · PGM · PPM). The encryption is done using LFSR techniques (XOR encryption).<br>
See : https://en.wikipedia.org/wiki/Linear-feedback_shift_register
This project was made in the context of the "Complement to programming" course (INFO0947) given by Pr. Donnet

Main points of this project :

C-Language, Makefile, static libraries, encryption methods, image processing, unit testing, documentation tool (doxygen) and custom structures.

## Table of Contents
1. [Setup](#setup)
2. [Parameters](#parameters)
3. [Forbidden file name](#forbidden-file-name-for--o)
4. [Usage example](#usage-example)
5. [Documentation](#documentation)
6. [Used resources](#used-resources)
7. [Future improvements](#future-improvements)
8. [Credits](#credits)

## Setup
- Install gcc ([https://gcc.gnu.org/install/])

- Clone the repository
```console
git clone git@github.com:sgardier/CryptLFSR.git locationOfTheProgram
```
- Go to the folder of the projet
```console
cd locationOfTheProgram
```
- Run the ```make``` command at the root of the directory
```console
make
```

## Parameters
Note :

`-i` the path of the image you want to encrypt / decrypt

`-o` the path for the encrypted/decrypted image, can not contain `/\\:*?\"<>|`

`-p` a password (e.g., myPassword@!)

`-t` the tap value for the LFSR encryption (see : https://en.wikipedia.org/wiki/Linear-feedback_shift_register)

Note : 
- Only images of type P1, P2 and P3 (ppm, pnm, pgm) are supported
- All parameters are mandatory

## Forbidden file name for -o
A file name can not contain any of the following characters : `/\\:*?\"<>|`

## Usage example
Encrypt an image using password "secretpassword123"

```console
./CryptLFSR -i img/city.ppm -o city_encrypted.ppm -p veryGoodPassword -t 5
```

Decrypt the image using the encryption password 
```console
./CryptLFSR -i city_encrypted.ppm -o city_decrypted.ppm -p veryGoodPassword -t 5
```

## Documentation
Run the command
```console
make doc
```
Then open doc/html/index.html
```console
open doc/html/index.html
```

## Used resources
- Seatest : https://code.google.com/archive/p/seatest/
- Arrow image of this README : https://www.deviantart.com/s-a-r-c/art/Right-Arrow-Sticker-823590894
- DALL-E for the pixel art illustration on this README

## Future improvements
- Multithreading for the processing of the pixels matrix
- Support of the other types of pnm images

## Credits
- [Simon Gardier](https://github.com/sgardier) (Author)
