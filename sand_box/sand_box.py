def add_accessible(world, x, y, z):
    count = 0
    if world[x][y][z + 1]:
        count += 1
    if world[x][y][z - 1]:
        count += 1
    if world[x + 1][y][z]:
        count += 1
    if world[x - 1][y][z]:
        count += 1
    if world[x][y - 1][z]:
        count += 1
    if world[x][y + 1][z]:
        count += 1

    if count > 0 and count != 6:
        world[x][y][z] = 1
        return True
    else:
        return False


def space_neighbor(world, pack):
    x, y, z = pack
    sn = []
    b = False
    if world[x][y][z + 1] == 0:
        if z + 1 == 101:
            b = True
        sn.append((x, y, z + 1))
    if world[x][y][z - 1] == 0:
        sn.append((x, y, z - 1))
    if world[x + 1][y][z] == 0:
        if x + 1 == 101:
            b = True
        sn.append((x + 1, y, z))
    if world[x - 1][y][z] == 0:
        if x - 1 == 0:
            b = True
        sn.append((x - 1, y, z))
    if world[x][y - 1][z] == 0:
        if y - 1 == 0:
            b = True
        sn.append((x, y - 1, z))
    if world[x][y + 1][z] == 0:
        if y + 1 == 101:
            b = True
        sn.append((x, y + 1, z))

    return sn, b


def far_reachable(world, x, y, z):
    pass_list = [(x, y, z)]
    tmp = []
    while True:
        for ele in pass_list:
            tmp, b = space_neighbor(world, ele)
            if b:
                return True
            if len(tmp) == 0:
                return False
        pass_list = tmp


def main():
    n_samples = int(raw_input())
    first = 1
    while n_samples:
        n_samples -= 1
        world = [[[0 for x in range(102)] for x in range(102)] for x in range(102)]
        for y in range(0, 102):
            for z in range(0, 102):
                world[z][y][0] = 1
        n_tests = int(raw_input())

        fuck = 0
        while n_tests:
            x, y, z = map(int, raw_input().split(' '))
            if (not add_accessible(world, x, y, z)) or (not far_reachable(world, x, y, z)):
                fuck += 1
            n_tests -= 1
        if first == 1:
            first = 0
            if fuck == 0:
                print 'Yes',
            else:
                print 'No',
        else:
            if fuck == 0:
                print ''
                print 'Yes',
            else:
                print ''
                print 'No',


if __name__ == '__main__':
    main()

