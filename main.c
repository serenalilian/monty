#include <stdio.h>
#include "monty.h"

bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - monty code interpreter
 * @argc: number of arguments
 * @argv: monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
    char content[1024];
    FILE *file;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    bus.file = file;

    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(content, sizeof(content), file))
    {
        counter++;

        /** Remove trailing newline character if present*/
        if (content[strlen(content) - 1] == '\n')
            content[strlen(content) - 1] = '\0';

        bus.content = content;
        execute(content, &stack, counter, file);
    }

    free_stack(stack);
    fclose(file);

    return (0);
}

