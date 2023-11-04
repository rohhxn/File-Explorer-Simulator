#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct FileSystemEntry {
    string name;
    bool isFile;
    vector<FileSystemEntry*> children;

    FileSystemEntry(const string& name, bool isFile) : name(name), isFile(isFile) {}
};

class FileSystemExplorer {
private:
    FileSystemEntry* root;
    FileSystemEntry* currentDir;

public:
    FileSystemExplorer() {
        root = new FileSystemEntry("Root", false);
        currentDir = root;
    }

    void insertEntry(FileSystemEntry* parent, const string& name, bool isFile) {
        if (parent) {
            FileSystemEntry* newEntry = new FileSystemEntry(name, isFile);
            parent->children.push_back(newEntry);
        }
    }

    void listContents(FileSystemEntry* dir) {
        if (dir) {
            cout << "Contents of " << dir->name << ":\n";
            for (const auto& child : dir->children) {
                cout << (child->isFile ? "File: " : "Directory: ") << child->name << endl;
            }
        }
    }

    FileSystemEntry* findEntry(FileSystemEntry* dir, const string& name) {
        if (dir) {
            for (const auto& child : dir->children) {
                if (child->name == name) {
                    return child;
                }
            }
        }
        return nullptr;
    }

    void printDirectoryStructure(FileSystemEntry* dir, int depth = 0) {
        if (dir) {
            for (int i = 0; i < depth; ++i) {
                cout << " ";
            }
            cout << "|-- " << dir->name << endl;
            for (const auto& child : dir->children) {
                printDirectoryStructure(child, depth + 1);
            }
        }
    }

    void run() {
        while (true) {
            cout << "Current Directory: " << currentDir->name << endl;
            cout << "Menu:\n";
            cout << "1. Create Directory\n2. Create File\n3. List Contents\n4. Change Directory\n5. Print Directory Structure\n6. Exit\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                cout << "Enter directory name: ";
                string name;
                cin >> name;
                insertEntry(currentDir, name, false);
            } else if (choice == 2) {
                cout << "Enter file name: ";
                string name;
                cin >> name;
                insertEntry(currentDir, name, true);
            } else if (choice == 3) {
                listContents(currentDir);
            } else if (choice == 4) {
                cout << "Enter directory name to change to: ";
                string name;
                cin >> name;
                FileSystemEntry* foundEntry = findEntry(currentDir, name);
                if (foundEntry && !foundEntry->isFile) {
                    currentDir = foundEntry;
                } else {
                    cout << "Directory not found or invalid choice." << endl;
                }
            } else if (choice == 5) {
                cout << "Directory Structure:\n";
                printDirectoryStructure(root, 0);
            } else if (choice == 6) {
                break;
            }
        }
    }
};

int main() {
    FileSystemExplorer explorer;
    explorer.run();
    return 0;
}
