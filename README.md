# Simple OS


## Hello this is small and simple OS kernel with memory manager, Interrupts, raw Keyboard Driver and Bootloader

> [!IMPORTANT]
> To build this system, you must use Linux (or WSL if you're on Windows).
---
### **Installing Dependencies**

#### Ubuntu
```sh
sudo apt install gcc gcc-i686-linux-gnu nasm build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu
```
#### Fedora
```sh
sudo dnf install gcc gcc-i686-linux-gnu nasm build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu
```
#### ArchLinux <3
```sh
sudo pacman -Syu gcc gcc-i686-linux-gnu nasm build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu
```
or use 
```sh
sudo yay <package_name>
```
---
### **Installing essential-build**

#### Build
```sh
mkdir -p ~/i686-elf
cd ~/i686-elf

wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz

tar -xzf binutils-2.41.tar.gz
tar -xzf gcc-13.2.0.tar.gz

mkdir build-binutils && cd build-binutils
../binutils-2.41/configure --target=i686-elf --prefix="$HOME/i686-elf" --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install
cd ..

cd gcc-13.2.0
./contrib/download_prerequisites
cd ..

mkdir build-gcc && cd build-gcc
../gcc-13.2.0/configure --target=i686-elf --prefix="$HOME/i686-elf" --disable-nls --enable-languages=c --without-headers
make all-gcc -j$(nproc)
make install-gcc
cd ..
```

#### Or download a pre-built version

```sh
wget https://github.com/Alex9600t/gcc-i686/releases/download/rel_1/i686-elf-toolchain.tar.gz
tar -xf i686-elf-toolchain.tar.gz
sudo mkdir -p /usr/local/i686_essential-build && sudo cp -r i686-elf /usr/local/i686_essential-build/ && export PATH="$PATH:/usr/local/i686_essential-build/i686-elf/bin" && echo 'export PATH="$PATH:/usr/local/i686_essential-build/i686-elf/bin"' >> ~/.zshrc ; echo 'export PATH="$PATH:/usr/local/i686_essential-build/i686-elf/bin"' >> ~/.bashrc
```
---
### **Verification**

```sh
i686-elf-gcc -v
i686-elf-ld -v
```
---
### Build

```sh
git clone https://github.com/L1stak/Simple-OS.git
cd Simple-OS

make
make run
```
---
> [!IMPORTANT]
> If you encounter any issues, don’t hesitate to open an issue.  
> (Or, if you're too shy, feel free to send your problems to `/dev/zero`)


> [!NOTE]
> Thank you for checking out and running the code! :3
