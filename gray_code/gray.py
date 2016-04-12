def gray(N):
    if(N <= 0):
        return None
    if(N == 1):
        return [[0], [1]]
    smaller = gray(N-1)
    l = len(smaller)
    for i in range(0,l):
        chosen_line = smaller[l-i-1]
        newline = []
        for ele in chosen_line:
            newele = ele
            newline.append(newele)
        chosen_line.append(0)
        newline.append(1)
        smaller.append(newline)
    return smaller
        

g = gray(5)
for line in g:
    for ele in line:
        print ele,
    print ''
