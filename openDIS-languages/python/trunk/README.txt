A partially completed student project by SS Pollock, John Weaver, et al.

This is a partial implementation of a Python ESPDU. It still does not
correctly serialize itself. Things to be aware of:

1. The use of the "!" in the pack() format string forces the binary
   encoding to be network byte order, which is what we want. 

2. The number of args and data values don't quite match up. They should.

