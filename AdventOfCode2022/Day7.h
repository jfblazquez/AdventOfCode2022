#pragma once
#include<memory>
#include <map>
#include <string>
#include "BaseDay.h"

struct Inode;
using pInode = std::shared_ptr<Inode>;

struct Inode {
    Inode(int _inode, bool _directory, int _size) : inode(_inode), directory(_directory), size(_size) {}
    int inode{};
    bool directory;
    int size{};
    std::map<std::string, pInode> sub;
};

pInode GetCreateDirectory(pInode parent, const std::string& directory);
pInode CreateFile(pInode parent, const std::string& name, int size);
int GetTotalSize(pInode inode);

class Day7 :
    public BaseDay {
public:
    Day7();
    int puzzle1();
    int puzzle2();
private:

    /// parse stack and movements
    void fillData();

    /// save all sizes in allDirsSize (recursive) call allDirsSize.clear() before
    void lsRDirectorySize(pInode inode);

    pInode root{};
    int rootSize{};
    std::vector<int> allDirsSize;
};

