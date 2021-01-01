
## Files Included:
### multilookup.c
- Thread-safe requester and resolver function prototypes
- Driver definition
- Command line reader implementation
### multilookup.h
- Requester and resolver function declarations
- Shared argument structure definition for creating Posix Threads (pthreads).
### queue.h
- Memory leak free queue implementation in C
- Queue operation declarations
### queue.c
- Function prototypes for queue operations
### performance.txt
 *Recorded multi-lookup performance for the following scenarios:*
-   1 requester thread and 1 resolver thread
-   1 requester thread and 3 resolver threads
-   3 requester threads and 1 resolver thread
-   3 requester threads and 3 resolver threads
-   5 requester threads and 5 resolver threads
1 second sleeps and 0.5 second sleeps both included.

# Man Page for Multi-Lookup
## NAME  
 multi-lookup - resolve a set of hostnames to IP addresses  
  
## SYNOPSIS  
```
./multi-lookup <# requester> <# resolver> <requester log> <resolver log> [ <data file> ... ]  
 ```
## DESCRIPTION  
  
The file names specified by <data file> are passed to the pool of requester threads which place information into a shared data area. Resolver threads read the shared data area and find the corresponding IP address.  
  ### PARAMETERS 
<# requesters> number of requestor threads to place into the thread pool.  
  
<# resolvers> number of resolver threads to place into the thread pool.  
  
<requester log> name of the file into which all the requester status information is written.  
  
<resolver log> name of the file into which all the resolver status information is written.  
  
<data file> filename to be processed. Each file contains a list of host names, one per line, that are to be resolved.



> Written with [StackEdit](https://stackedit.io/).
