elf-parser
===
This parses the elf format file. It dumps the elf header and the section info in the elf file.

To implement this, elf-parser uses the header file 'elf.h'. In the header file, the struct ```Elfxx_Ehdr``` and ```Elfxx_Shdr``` are used.

## how to use
```c
$ make
$ ./elf_parser elf_format_file
```


