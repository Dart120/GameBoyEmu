def simulation(maxi,stones):
    tabu = set()
    # forward_pass
    p1 = 0
    print(maxi)
    while p1 < len(stones) - 1:
        start = stones[p1]
        if (stones[p1 + 1] - start) > maxi:
            return False
        while p1 < len(stones) - 1 and (stones[p1 + 1] - start) <= maxi:
            p1 += 1
        
        tabu.add(p1)
        
   
    # print(tabu,maxi)
    # exit()
    res = []
    for idx,i in enumerate(stones):
        if idx not in tabu:
            res.append(i)
    for i in range(1,len(res)):
        if abs(res[i] - res[i-1]) > maxi:
            return False
    return True
print(simulation(5,[0,2,5,6,7]))