
def findPermutation(s: str):
    if len(s) == 1:
        if s[0] == 'I':
            return [1,2]
        else:
            return [2,1]
    p1 = 0
    counts = []
    res = []
    while p1 < len(s):
        count = 0
        curr_letter = s[p1]
        while p1 < len(s) and curr_letter == s[p1]:
            count += 1
            p1 += 1
        counts.append(count)
    
    if s[0] == 'I':
        res.append(1)
        highest = 1
        I_now = True
    else:
        res.append(1 + counts[0])
        highest = 1 + counts[0]
        I_now = False

    for idx,i in enumerate(counts):
        if I_now:
            res,highest = I(idx,counts,res,highest)
            I_now = False
            highest = res[-1]
        
        else:
            res,highest = D(idx,counts,res,highest)
            I_now = True
            
    return res
def I(idx,counts,res,highest):
    how_many = counts[idx]
    start = highest
    if idx == len(counts) - 1:

        for i in range(how_many):
            start += 1
            res.append(start)
            highest = max(start,highest)
        return res,highest
    else:
        for i in range(how_many - 1):
            start += 1
            res.append(start)
            highest = max(start,highest)
        if idx + 1 <= len(counts) - 1:
            print(highest + 1 + counts[idx + 1],'begin d')
            res.append(highest + 1 + counts[idx + 1])
            highest = max(highest + 1 + counts[idx + 1],highest)
    
    return res, highest

        
def D(idx,counts,res,highest):
    how_many = counts[idx]
    start = highest
    for i in range(how_many):
        start -= 1
        res.append(start)
    return res,highest
print(Solution().findPermutation('IIDDIIDD'))
