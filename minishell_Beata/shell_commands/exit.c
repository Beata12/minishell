#include "../header_files/shell_commands.h"

int shell_exit(void) {
    exit(0);
}

int main() {
    shell_exit();
        printf("This line will never be reached\n");
    return 0;
}