/**
* This will force us to create a kernel entry function,
* instead of jumping to kernel.x:0x0
*/
void dummy() { }

void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}
