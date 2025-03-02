/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/28/25
 * Stores dependencies of files in BST.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// parse dependencies
void parseDependencies(struct tree_node *node, char *dependencies[], int *dep_count) {
    FILE *file = fopen(node->data.name, "r");
    if (!file) return;
    char line[63]; //assuming max len of 63 chars
    *dep_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "#include \"")) {
            char *start = strchr(line, '"') + 1;
            char *end = strchr(start, '"');
            if (start && end) {
                *end = '\0';
                dependencies[(*dep_count)++] = strdup(start);
            }
        }
    }
    fclose(file);
}

// print dependencies
void printDependencies(struct tree_node *root, char *filename) {
    struct tree_node *node = find(filename, root);
    if (!node) {
        printf("%s not found\n", filename);
        return;
    }
    char *dependencies[100];
    int dep_count = 0;
    parseDependencies(node, dependencies, &dep_count);
    printf("%s has the following dependencies\n", filename);
    for (int i = 0; i < dep_count; i++) {
        printf("  %s\n", dependencies[i]);
        free(dependencies[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    struct tree_node *root = NULL;
    for (int i = 1; i < argc; i++) {
        root = insert(argv[i], root);
    }
    
    // command loop
    char command[63];
    while (1) {
        printf("$ ");
        if (!fgets(command, sizeof(command), stdin)) break;
        command[strcspn(command, "\n")] = 0; // account for newline
        if (strcmp(command, "quit") == 0) break;
        else if (strcmp(command, "list") == 0) printSorted(root);
        else printDependencies(root, command);
    }
    clear(root);
    return 0;
}