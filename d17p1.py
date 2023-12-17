import sys
from typing import List
from heapq import heappush, heappop

def dijkstra(grid: List[List[int]]):
    q = []
    #            cost        i  j  dir  dir_count
    heappush(q, (grid[0][0], 0, 0, 0,   0))

    dist = [[sys.maxsize] * len(grid[0]) for _ in range(len(grid))]
    dist[0][0] = 0
    vis = [[False] * len(grid[0]) for _ in range(len(grid))]

    dirs = [
        [0, 1],  # right
        [0, -1], # left
        [-1, 0], # up
        [1, 0], # down
    ]

    while len(q) > 0:
        curr = heappop(q)
        curr_cost, i, j, dir, dir_count = curr
        vis[i][j] = True

        for d in range(4):
            if d == dir and dir_count == 3:
                continue
            m = i + dirs[d][0]
            n = j + dirs[d][1]
            if 0 <= m and m < len(grid) and 0 <= n and n < len(grid[0]) and not vis[m][n]:
                if (curr_cost + grid[m][n] < dist[m][n]):
                    dist[m][n] = curr_cost + grid[m][n]
                    heappush(q, (dist[m][n], m, n, d, dir_count + 1 if d == dir else 0))
        if i == len(grid) - 1 and j == len(grid[0]) - 1:
            break

    print(dist[len(grid) - 1][len(grid[0]) - 1])

if __name__ == '__main__':
    with open('input.txt') as fis:
        grid = [[int(cost) for cost in row] for row in fis.read().strip().split('\n')]

    dijkstra(grid)
