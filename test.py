from queue import PriorityQueue

# create an empty priority queue
q = PriorityQueue()

# add some numbers with priorities
q.put(0,2)
q.put(1,4)
q.put(2,1)
q.put(3,2)
q.put(4,5)


# remove and print the items in priority order
while not q.empty():
    item = q.get()
    print(item)
