Pass or block CAN msgs (with CAN id translation if needed) between multiple pairs of input and output socket connections. A file defining the CAN ids is checked and tables built and loaded to 'calloc'd memory, for run-time uses.

These routines would were primarily for 'hub-server' use, but applicable to emc-master and can-server-bridge (RPi with CAN hat).

A matrix approach creates a N*N array of small structs with pointers, sizes, and type of associated table. The array is accessed as a two dimensional array with input connection and output connection numbers as indices. Given the in:out pair and CAN msg, a return of copy or no-copy is returned, and if the CAN id needs translation the CAN msg is updated to the translated CAN id.
