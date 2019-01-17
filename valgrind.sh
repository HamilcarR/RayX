
#!/bin/bash
valgrind --error-limit=no --leak-check=full --tool=memcheck --show-leak-kinds=all --track-origins=yes --show-reachable=yes $1

