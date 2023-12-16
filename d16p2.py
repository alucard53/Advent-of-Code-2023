from typing import List, Tuple

# For later: A way to not brute force this would be to first store the paths illuminated by each of the splitters
# then traversefor each starting position until a splitter would be reached or smthn

directions = {
    'l': [0, -1],
    'r': [0, 1],
    'u': [-1, 0],
    'd': [1, 0],
}

count = 0
def traverse(grid: List[List[str]], vis: List[List[bool]], splits: set[Tuple[int, int]], i: int, j: int, dir: str):
    global count

    while 0 <= i and i < len(grid) and 0 <= j  and j < len(grid[0]):
        if not vis[i][j]:
            count += 1
        vis[i][j] = True
            
        if grid[i][j] == '|' and (dir == 'l' or dir == 'r'):
            if splits.__contains__((i, j)):
                return
            splits.add((i, j))
            traverse(grid, vis, splits, i - 1, j, 'u')
            dir = 'd'
        elif (grid[i][j] == '-' and (dir == 'u' or dir == 'd')):
            if splits.__contains__((i, j)):
                return
            splits.add((i, j))

            traverse(grid, vis, splits, i, j + 1, 'r')
            dir = 'l'
        elif grid[i][j] == '\\':
            match dir:
                case 'r':
                    dir = 'd'
                case 'l':
                    dir = 'u'
                case 'u':
                    dir = 'l'
                case 'd':
                    dir = 'r'
        elif grid[i][j] == '/':
            match dir:
                case 'r':
                    dir = 'u'
                case 'l':
                    dir = 'd'
                case 'u':
                    dir = 'r'
                case 'd':
                    dir = 'l'

        i += directions[dir][0]
        j += directions[dir][1]

if __name__ == '__main__':
    max_count = 0
    with open('input.txt') as fin:
        grid = [list(i) for i  in fin.read().strip().split('\n')]

    for j in range(len(grid[0])):
        vis = [[False] * len(grid[0]) for _ in range(len(grid))]
        splits = set()
        
        traverse(grid, vis, splits, 0, j, 'd')
        max_count = max(count, max_count)
        count = 0
    for i in range(len(grid[0])):
        vis = [[False] * len(grid[0]) for _ in range(len(grid))]
        splits = set()


        traverse(grid, vis, splits, i, 0, 'r')
        max_count = max(count, max_count)
        count = 0
    for j in range(len(grid[0])):
        vis = [[False] * len(grid[0]) for _ in range(len(grid))]
        splits = set()

        traverse(grid, vis, splits, len(grid) - 1, j, 'u')
        max_count = max(count, max_count)
        count = 0
    for i in range(len(grid[0])):
        vis = [[False] * len(grid[0]) for _ in range(len(grid))]
        splits = set()

        traverse(grid, vis, splits, i, len(grid[0]) - 1, 'l')
        max_count = max(count, max_count)
        count = 0

    print(max_count)
