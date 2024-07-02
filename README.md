# Mounter Program
## Overview
The Mounter program is designed to simplify the process of mounting exFAT and btrfs filesystems with specific options, reducing the need for manual commands and making it easier for users to perform these tasks with minimal input.

## Features
- **ExFAT Mounting:** Mount exFAT drives with current user permissions.
- **btrfs Mounting:** Mount btrfs drives with options for subvolume, compression, and noatime.

Who doesn't like typing marginally fewer characters, right?

## Compilation
To compile the program run:
```console
make
```
This will create 2 executables `mounter` and `mounter2`.

## Usage
### Command-Line Interface (CLI)
The program is executed from the command line with various options:

- To mount an exFAT drive:
```console
mounter 1 [device] [directory]
```
Example:
```console
mounter 1 /dev/sdb1 /mnt/exfat_drive
```
This mounts `/dev/sdb1` on `/mnt/exfat_drive` with current user permissions.
- To mount a btrfs drive with specific options:
```console
mounter 2 [subvol] [zstd level] [device] [directory]
```
Example:
```console
mounter 2 my_subvol 3 /dev/sdc /mnt/btrfs_drive
```
This mounts `/dev/sdc` on `/mnt/btrfs_drive` with the specified subvolume (`my_subvol`), compression level (`3`), and `noatime` option enabled.

### Help
To view help and usage instructions:
```console
mounter help
```
## Cleanup
To remove the object files and the executables run:
```console
make clean
```

## Notes
- Ensure you have necessary permissions or use `sudo` to execute the program for mounting.
-
