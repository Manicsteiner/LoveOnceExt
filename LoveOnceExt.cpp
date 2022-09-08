#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream filelist("list.bin", ios::in | ios::binary);
    if (!filelist) {
        std::cout << "List file not found" << endl;
        return -1;
    }
    ifstream filedata("data.bin", ios::in | ios::binary);
    if (!filedata) {
        std::cout << "Data file not found" << endl;
        return -1;
    }
    unsigned int fileinfo[4];
    char filename[16];
    system("mkdir data");
    int filenum = 0;

    while (!filelist.eof()) {
        filelist.clear();
        filelist.seekg(80*filenum);
        if (filelist.eof()) {
            break;
        }

        filelist.read((char*)fileinfo, 16);
        //cout << fileinfo[0] << " " << fileinfo[2] << endl;
        filelist.read((char*)filename, 16);
        //cout << filename << endl;

        char* databyte = (char*)malloc(sizeof(char)*fileinfo[0]);
        filedata.clear();
        filedata.seekg(fileinfo[2]);
        filedata.read(databyte, fileinfo[0]);
        string filepath = filename;
        filepath = "data/" + filepath;
        ofstream filewrite(filepath, ios::out | ios::binary);
        filewrite.write(databyte, fileinfo[0]);
        filewrite.close();
        filenum++;
        free(databyte);
    }


    filelist.close();
    filedata.close();
    std::cout << "Complete!" << endl;
    return 0;
}