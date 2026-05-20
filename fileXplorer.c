#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <direct.h>

    void list_files(const char *path) {
        WIN32_FIND_DATA findData;
        char searchPath[1024];
        snprintf(searchPath, sizeof(searchPath), "%s\\*", path);
        HANDLE hFind = FindFirstFile(searchPath, &findData);

        if (hFind == INVALID_HANDLE_VALUE) return;

        printf("\n--- Contents of %s ---\n", path);
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("[DIR]  %s\n", findData.cFileName);
            } else {
                printf("[FILE] %s\n", findData.cFileName);
            }
        } while (FindNextFile(hFind, &findData) != 0);

        FindClose(hFind);
    }

    int main() {
        char path[1024];
        char command[1024];

        getcwd(path, sizeof(path));
        printf("v0.03.2\n");
        printf("Welcome to fileXplorer on Windows!\n");
        printf("Enter 'cd <dirname>' to move, or 'exit' (use man to print out all the commands): \n");
        list_files(path);
        while (1) {
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = 0;

            if (strcmp(command, "exit") == 0) break;

            if (strcmp(command, "man") == 0) {
                printf("cd - Move directories\n");
                printf("exit - Exit the program\n");
                printf("ls - List files in directory\n");
                continue;
            }

            if (strcmp(command, "ls") == 0) {
                list_files(path);
                continue;
            }

            if (strncmp(command, "cd ", 3) == 0) {
                char *new_dir = command + 3;
                if (chdir(new_dir) == 0) {
                    getcwd(path, sizeof(path)); // update current path
                } else {
                    printf("Directory change failed");
                }
            }
        }
    }
#else
    #include <stdio.h>
    #include <dirent.h>
    #include <string.h>
    #include <unistd.h>

    void list_files(const char *path) {
        struct dirent *entry;
        DIR *dir = opendir(path);

        if (dir == NULL) {
            perror("Unable to read directory, directory is NULL");
            return;
        }

        printf("\n--- Contents of %s ---\n", path);
        while ((entry = readdir(dir)) != NULL) {
            // distinguish between directories and files
            const char *type = (entry->d_type == DT_DIR) ? "[DIR] " : "[FILE]";
            printf("%s %s\n", type, entry->d_name);
        }
        closedir(dir);
    }

    int main() {
        char path[1024] = ".";
        char command[1024];

        getcwd(path, sizeof(path));
        printf("v0.03.2\n");
        printf("Welcome to fileXplorer on Linux/macOS!\n");
        printf("Enter 'cd <dirname>' to move, or 'exit' (use man to print out all the commands): \n");
        list_files(path);
        while (1) {
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = 0;

            if (strcmp(command, "exit") == 0) break;

            if (strcmp(command, "man") == 0) {
                printf("cd - Move directories\n");
                printf("exit - Exit the program\n");
                printf("ls - List files in directory\n");
                continue;
            }

            if (strcmp(command, "ls") == 0) {
                list_files(path);
                continue;
            }

            if (strncmp(command, "cd ", 3) == 0) {
                char *new_dir = command + 3;
                if (chdir(new_dir) == 0) {
                    getcwd(path, sizeof(path)); // update current path
                } else {
                    printf("Directory change failed");
                }
            }
        }
        return 0;
    }
#endif