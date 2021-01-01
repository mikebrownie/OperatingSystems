def NextFit(blockSize, m, processSize, n): 
      
    # Stores block id of the block  
    # allocated to a process  
  
    # Initially no block is assigned  
    # to any process  
    allocation = [-1] * n  
    j = 0
  
    # pick each process and find suitable blocks  
    # according to its size ad assign to it  
    for i in range(n): 
  
        # Do not start from beginning  
        while j < m: 
  
            if blockSize[j] >= processSize[i]: 
  
                # allocate block j to p[i] process  
                allocation[i] = j  
  
                # Reduce available memory in this block.  
                blockSize[j] -= processSize[i]  
  
                break
  
            # mod m will help in traversing the  
            # blocks from starting block after  
            # we reach the end.  
            j = (j + 1) % m 
  
    print("Process No. Process Size Block no.")  
    for i in range(n): 
        print(i + 1, "         ", processSize[i], 
                                    end = "     ") 
        if allocation[i] != -1: 
            print(allocation[i] + 1)  
        else: 
            print("Not Allocated") 
  
# Driver Code 
if __name__ == '__main__':  
    blockSize = [100, 360, 220, 300, 500] 
    processSize = [228,340, 117, 496]  
    m = len(blockSize) 
    n = len(processSize) 
  
    NextFit(blockSize, m, processSize, n) 
      
# This code is contributed by PranchalK 