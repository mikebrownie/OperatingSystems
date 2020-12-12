
#SET THESE BEFORE USING
disk_size = 5000
size = 10
#size = length of posistions array

def FCFS(curr, posisitions):
    print("FCFS called, starting from: {}\n".format(curr))
    print("Posistions recieved: {}\n".format(posisitions))
    distance = 0
    for x in posisitions:
        print("FCFS: next job at {}, distance to go {}\n".format(x,  abs(x-curr)))
        distance += abs(x-curr)
        curr = x
    return distance

def SSTF(curr, arr):
    posisitions = arr[:] # copy parameters to not modify
    distance = 0
    print("SSTF called, starting from: {}\n".format(curr))
    print("Posistions recieved: {}\n".format(posisitions))

    while(len(posisitions) !=0): 
        #For each current pos, find minumum next posistion
        neighbors = []
        for x in posisitions:
            neighbors.append( (abs(x-curr), x) )
        next_pos = min(neighbors)
        print("SSTF: next job at {}, distance to go {}\n".format(next_pos[1], next_pos[0]))
        posisitions.remove(next_pos[1])
        curr = next_pos[1]
        distance += next_pos[0]
    return distance

def CSCAN(curr, posisitions, direction):
    print("CSCAN called, starting from: {}\n".format(curr))
    print("Posistions recieved: {}\n".format(posisitions))
    seek_count = 0
    distance, cur_track = 0, 0
    distance = 0
    left = []
    right = []
    seek_sequence = []
 
    # Appending end values
    # which has to be visited
    # before reversing the direction
    left.append(0)
    right.append(disk_size - 1)
 
    for x in posisitions:
        if (x < curr):
            left.append(x)
        if (x > curr):
            right.append(x)

 
    # Sorting left and right vectors
    left.sort()
    right.sort()

    # Run the while loop two times.
    # one by one scanning right
    # and left of the curr
    run = 2
    while (run != 0):
        if (direction == "left"):
            for l in left:
                cur_track = l
 
                # Appending current track to 
                # seek sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - curr)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now the new curr
                curr = cur_track
             
            direction = "right"
     
        elif (direction == "right"):
            for r in right:
                cur_track = r
                # Appending current track to seek 
                # sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - curr)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now new curr
                curr = cur_track
             
            direction = "left"
        run -= 1
    print("Seek Sequence is: ", seek_sequence)
    return seek_count
   
def SCAN(curr, posisitions, direction):
    print("SCAN called, starting from: {}\n".format(curr))
    print("Posistions recieved: {}\n".format(posisitions))
    seek_count = 0
    distance, cur_track = 0, 0
    distance = 0
    left = []
    right = []
    seek_sequence = []
 
    # Appending end values
    # which has to be visited
    # before reversing the direction
    if (direction == "left"):
        left.append(0)
    elif (direction == "right"):
        right.append(disk_size - 1)
 
    for x in posisitions:
        if (x < curr):
            left.append(x)
        if (x > curr):
            right.append(x)

 
   
    run = 2
    while (run > 0):
        if (direction == "left"):
            # Sorting left and right vectors
            left.sort(reverse=True)
            
            for l in left:
                cur_track = l

                # Appending current track to 
                # seek sequence
                seek_sequence.append(cur_track)
                # Calculate absolute distance
                distance = abs(cur_track - curr)

                # Increase the total count
                seek_count += distance

                # Accessed track is now the new curr
                curr = cur_track
             
            direction = "right"

        elif (direction == "right"):
            right.sort()
            for r in right:
                cur_track = r

                # Appending current track to seek 
                # sequence
                seek_sequence.append(cur_track)

                # Calculate absolute distance
                distance = abs(cur_track - curr)

                # Increase the total count
                seek_count += distance

                # Accessed track is now new curr
                curr = cur_track
            
            direction = "left"
        run-=1
    
    print("Seek Sequence is: ", seek_sequence)
    return seek_count
    
def LOOK(head, arr, direction):
    print("LOOK called, starting from: {}\n".format(head))
    print("Posistions recieved: {}\n".format(arr))
    seek_count = 0
    distance, cur_track = 0, 0
    left = []
    right = []
    seek_sequence = []
 
    for pos in arr:
        if (pos < head):
            left.append(pos)
        if (pos > head):
            right.append(pos)
 
    # Sorting left and right vectors
    right.sort()
    left.sort(reverse = True)

    run = 2
    while (run != 0):
        if (direction == "left"):
            for l in left:
                cur_track = l
                # Appending current track to 
                # seek sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - head)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now the new head
                head = cur_track
             
            direction = "right"
     
        elif (direction == "right"):
            for r in right:
                cur_track = r
                 
                # Appending current track to seek 
                # sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - head)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now new head
                head = cur_track
             
            direction = "left"
         
        run -= 1
    print("Seek Sequence is: ", seek_sequence)
    return seek_count
    
def CLOOK(head, arr, direction):
    print("CLOOK called, starting from: {}\n".format(head))
    print("Posistions recieved: {}\n".format(arr))
    seek_count = 0
    distance, cur_track = 0, 0
    left = []
    right = []
    seek_sequence = []
 
    for pos in arr:
        if (pos < head):
            left.append(pos)
        if (pos > head):
            right.append(pos)
 
    # Sorting left and right vectors
    right.sort()
    left.sort()

 
        # Run the while loop two times.
    # one by one scanning right
    # and left of the head
    run = 2
    while (run != 0):
        if (direction == "left"):
            for l in left:
                cur_track = l
                # Appending current track to 
                # seek sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - head)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now the new head
                head = cur_track
             
            direction = "right"
     
        elif (direction == "right"):
            for r in right:
                cur_track = r
                 
                # Appending current track to seek 
                # sequence
                seek_sequence.append(cur_track)
 
                # Calculate absolute distance
                distance = abs(cur_track - head)
 
                # Increase the total count
                seek_count += distance
 
                # Accessed track is now new head
                head = cur_track
             
            direction = "left"
         
        run -= 1
 
    print("Seek Sequence is: ", seek_sequence)
    return seek_count
        
        
def main():
    #Just uncomment whichever one you want to use
    #Don't forget to update $posistions and $curr
    
    curr = 2150
    posisitions = [2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681]
    distance = FCFS(curr, posisitions)
    print("FCFC traveled a distnace of : ", distance)
    print("\n==========================================================================================\n")
    distance = SSTF(curr, posisitions)
    print("SSTF traveled a distance of : ", distance)
    print("\n==========================================================================================\n")

    direction = "right" #which direction we travel first
   
    distance = CSCAN(curr, posisitions, direction)
    print("CSCAN traveled a distance of : ", distance)
    print("\n==========================================================================================\n")
    distance = SCAN(curr, posisitions, direction)
    print("SCAN traveled a distance of : ", distance)
    print("\n==========================================================================================\n")
    distance = LOOK(curr, posisitions, 'right')
    print("LOOK traveled a distance of : ", distance)
    print("\n==========================================================================================\n")
    distance = CLOOK(curr, posisitions, 'right')
    print("CLOOK traveled a distance of : ", distance)
    print("\n==========================================================================================\n")

    

    


if __name__ == '__main__':
    main()
