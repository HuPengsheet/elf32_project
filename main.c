#include<stdio.h>
#include<stdlib.h>
#include"elf.h"    


#define FILE_NAME  "a.out"

//Elf32_Ehdr   ELF32位的ELFheader结构体定义，共64个字节
//Elf32_Shdr     ELF32位的节表项结构体定义，共64个字节

unsigned int get_file_size(const char* name);

int main(){

    //获取文件大小
    unsigned int file_size = get_file_size(FILE_NAME);
    //printf("文件的大小为%u\n",file_size);


    void* elf_file = malloc(file_size);
        if (elf_file == NULL) {
        printf("分配内存失败！\n");
        return 1;
    }


    FILE* file_ptr = fopen(FILE_NAME,"r");
    fread(elf_file, file_size, 1, file_ptr);
    fclose(file_ptr);

    Elf32_Ehdr* elf_header = elf_file;
   
    //printf("节表的偏移地址%u\n",elf_header->e_shoff);
    
    //遍历，打印节表，节表结构Elf32_Shdr
    //节表的偏移elf_header->e_shoff，节表的数量 elf_header->e_shnum
    for(int i =0;i<elf_header->e_shnum;i++){
            Elf32_Shdr* section= elf_file+ elf_header->e_shoff+i*elf_header->e_shentsize;
            printf("节表的名字%u\n",section->sh_name);
    }

    // 关闭文件，释放分配的内存
   
    free(elf_file);
    return 0;
}



unsigned int get_file_size(const char* name){

    FILE* file_ptr = fopen(name,"r");
    if(file_ptr==NULL) {
        printf("文件打开失败，请检查你的文件名是否输入正确\n");
        return 0;
    }

    //把文件指针移动到，文件的末尾
    //SEEK_END表示文件的末尾，0表示偏移量为0
    if(fseek(file_ptr,0,SEEK_END)!=0){
        printf("文件指针设置错误，请仔细检查！！");
        return 0;
    }

    unsigned int  file_size = ftell(file_ptr);
    fclose(file_ptr);
    return file_size;  
}