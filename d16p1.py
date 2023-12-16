from typing import List

directions = {
    'l': [0, -1],
    'r': [0, 1],
    'u': [-1, 0],
    'd': [1, 0],
}

count = 0
def traverse(grid: List[List[str]], vis: List[List[bool]], splits: List[List[bool]], i: int, j: int, dir: str):
    global count

    while 0 <= i and i < len(grid) and 0 <= j  and j < len(grid[0]):
        if not vis[i][j]:
            count += 1
        vis[i][j] = True
            
        if grid[i][j] == '|' and (dir == 'l' or dir == 'r'):
            if splits[i][j]:
                return
            splits[i][j] = True
            traverse(grid, vis, splits, i - 1, j, 'u')
            dir = 'd'
        elif (grid[i][j] == '-' and (dir == 'u' or dir == 'd')):
            if splits[i][j]:
                return
            splits[i][j] = True
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


if __name__ == '__main__:
    with open('input.txt') as fin:
        grid = [list(i) for i  in fin.read().strip().split('\n')]
    
        vis = [[False] * len(grid[0]) for _ in range(len(grid))]
        splits = [[False] * len(grid[0]) for _ in range(len(grid))]
    
        traverse(grid, vis, splits, 0, 0, 'r')
    
        print(count)
