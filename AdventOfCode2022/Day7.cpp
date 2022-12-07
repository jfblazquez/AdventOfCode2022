#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

using namespace std;

#include "Day7.h"

Day7::Day7() {
	day = 7;
	filename = "input/day7.txt";
}

int newInode() {
    static int inodeidx = 0;
    return inodeidx++;
}

int Day7::puzzle1() {
    root = GetCreateDirectory(nullptr, "__ROOT__");
    fillData();
    rootSize = GetTotalSize(root);
    allDirsSize.push_back(rootSize);
    std::cout << "__ROOT__ : " << rootSize << "\n";
    lsRDirectorySize(root);
    std::sort(allDirsSize.begin(), allDirsSize.end());
    int result = 0;
    constexpr int dirAtMost = 100000;
    for (int it : allDirsSize) {
        if (it <= dirAtMost) {
            result += it;
        }
    }
    return result;
}

int Day7::puzzle2() {
    if (allDirsSize.empty()) {
        //need allDirsSize calculated
        puzzle1();
    }
    constexpr int maxFsSpace = 70000000;
    constexpr int needFsSpace = 30000000;
    int currentFsSpace = maxFsSpace - rootSize;
    int minSizeFolderToDel = needFsSpace - currentFsSpace;
    if (minSizeFolderToDel <= 0) {
        std::cout << "No need to del any folder\n";
        return 0;
    }
    int result = 0;
    for (int it : allDirsSize) {
        if (it >= minSizeFolderToDel) {
            result = it;
            break;
        }
    }
    return result;
}

void Day7::fillData()
{
    long all{};
    pInode current = root;
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    while (getline(ifs, line)) {
        if (line[0] == '$') {
            if (line == "$ ls") {
                continue; //ignore ls...all output from commands is only ls
            }
            else if (line == "$ cd ..") {
                current = current->sub[".."];
            }
            else if (line == "$ cd /") {
                current = root;
            }
            else if (line.substr(0, 5) == "$ cd ") {
                std::string dir = line.substr(5);
                current = GetCreateDirectory(current, dir);
            }
            else {
                assert(false && "Not valid command");
            }
        }
        else {
            //new sub for current inode
            //dir a
            //14848514 b.txt
            if (line.substr(0, 4) == "dir ") {
                std::string newDir = line.substr(4);
                GetCreateDirectory(current, newDir);
            }
            else {
                //<size> <name>
                auto splitstr = utils::string::split(line, ' ');
                constexpr size_t sizeIdx = 0;
                constexpr size_t nameIdx = 1;                                
                int size = std::stoi(splitstr[sizeIdx]);
                all += size;
                std::string name = splitstr[nameIdx];
                CreateFile(current, name, size);
            }
        }
    }
    //std::cout << "All files : " << all << std::endl;
}

void Day7::lsRDirectorySize(pInode inode) {
    if (!inode->directory) {
        std::cout << "Not a directory\n";
        return;
    }

    for (auto& it : inode->sub) {
        if (it.first != ".." && it.second->directory) {
            int size = GetTotalSize(it.second);
            //std::cout << it.first << " : " << size << "\n";
            allDirsSize.push_back(size);
            lsRDirectorySize(it.second);
        }
    }
}
pInode GetCreateDirectory(pInode parent, const std::string& directory) {
    if (parent) {
        //Check if exist and return
        auto it = parent->sub.find(directory);
        if (it != parent->sub.end()) {
            return it->second;
        }
    }
    auto newNode = std::make_shared<Inode>(newInode(), true, 0);
    if (parent) {
        parent->sub[directory] = newNode;
        newNode->sub[".."] = parent;
    }
    else {
        newNode->sub[".."] = newNode;
    }
    return newNode;
}

pInode CreateFile(pInode parent, const std::string& name, int size) {
    auto newNode = std::make_shared<Inode>(newInode(), false, size);
    if (parent) {
        parent->sub[name] = newNode;
    }
    return newNode;

}

int GetTotalSize(pInode inode) {
    if (!inode) {
        return 0;
    }

    if (!inode->directory) {
        return inode->size;
    }

    int sum = 0;
    for (auto& it : inode->sub) {
        if (it.first != "..") {
            sum += GetTotalSize(it.second);
        }
    }
    return sum;
}




