
Right now, almost all of the functionality is implemented: all the functionality remains from the first week, and now the program saves state using protobufs to write messages to a local file (I designate the name in the file because
I don't think I'm supposed to allow bankcli to take any command-line arguments), and all the accounts have balances that can be updated by applying transactions to them. One thing that isn't so great is that I leak a very small amount of
memory (less than 1% of the memory my application uses), but I have some more pressing program structure issues I want
to tackle before I address that.


