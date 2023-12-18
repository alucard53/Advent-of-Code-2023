// Converted the input into the grid for day 10 lol

import java.io.*;
import java.util.*;

class Entry {
    char dir;
    int count;
    String color;

    Entry(char dir, int count, String color) {
        this.dir = dir;
        this.count = count;
        this.color = color;
    }

    public String toString() {
        return dir + " "+ Integer.toString(count) + " " + color;
    }
}

public class d18p1 {

    static boolean inGrid(char[][] grid, int i, int j) {
        return 0 <= i && i < grid.length && 0 <= j && j < grid[0].length;
    }

    static int isCorner(char[][] grid, int i, int j) {
        boolean north = inGrid(grid, i - 1, j) && grid[i - 1][j] != '.';
        boolean south = inGrid(grid, i + 1, j) && grid[i + 1][j] != '.';
        boolean west = inGrid(grid, i, j - 1) && grid[i][j - 1] != '.';
        boolean east = inGrid(grid, i, j + 1) && grid[i][j + 1] != '.';
        if (north && east) {
            return 1;
        }
        if (east && south) {
            return 2;
        }
        if (south && west) {
            return 3;
        }
        if (west && north) {
            return 4;
        }
        return 0;
    }

    public static void main(String args[]) throws Exception {
        FileInputStream fis = new FileInputStream("input.txt");
        Scanner in = new Scanner(fis);

        ArrayList<Entry> plan =  new ArrayList<>();

        int i = 0, j = 0;
        int start_i = 0, start_j = 0;
        int m = 0, n = 0;
        while (in.hasNext()) {
            char dir = in.next().charAt(0);
            int count =in.nextInt();
            String color = in.nextLine();

            switch (dir) {
                case 'U':
                    i -= count;
                    break;
                case 'D':
                    i += count;
                    break;
                case 'L':
                    j -= count;
                    break;
                case 'R':
                    j += count;
                    break;
            }
            if (i < 0) {
                start_i += -i;
                m += -i + 1;
                i = 0;
            }
            else if (j < 0) {
                start_j += -j;
                n += -j + 1;
                j = 0;
            } else {
                m = Math.max(i + 1, m);
                n = Math.max(j + 1, n);
            }

            plan.add(new Entry(dir, count, color));
        }
        in.close();
        fis.close();

        char[][] grid = new char[m][n];
        for (char[] row : grid) {
            Arrays.fill(row, '.');
        }
        i = start_i; j = start_j;

        for (var p : plan) {
            int count = p.count;
            switch (p.dir) {
                case 'U':
                    while (count-- > 0) {
                        grid[i--][j] = '#';
                    }
                    break;
                case 'D':
                    while (count-- > 0) {
                        grid[i++][j] = '#';
                    }
                    break;
                case 'L':
                    while (count-- > 0) {
                        grid[i][j--] = '#';
                    }
                    break;
                case 'R':
                    while (count-- > 0) {
                        grid[i][j++] = '#';
                    }
                    break;
            }
        }

        i = start_i; j = start_j;
        for (var p : plan) {
            int count = p.count;
            switch (p.dir) {
                case 'U':
                    while (count-- > 0) {
                        int c = isCorner(grid, i, j);
                        if (c == 0) {
                            grid[i][j] = '|';
                        } else if (c == 1) {
                            grid[i][j] = 'L';
                        } else {
                            grid[i][j] = 'J';
                        }
                        i--;
                    }
                    break;
                case 'D':
                    while (count-- > 0) {
                        int c = isCorner(grid, i, j);
                        if (isCorner(grid, i, j) == 0) {
                            grid[i][j] = '|';
                        } else if (c == 2) {
                            grid[i][j] = 'F';
                        } else {
                            grid[i][j] = '7';
                        }
                        i++;
                    }
                    break;
                case 'L':
                    while (count-- > 0) {
                        int c = isCorner(grid, i, j);
                        if (c == 0) {
                            grid[i][j] = '-';
                        } else if (c == 4) {
                            grid[i][j] = 'J';
                        } else  {
                            grid[i][j] = '7';
                        }
                        j--;
                    }
                    break;
                case 'R':
                    while (count-- > 0) {
                        int c = isCorner(grid, i, j);
                        if (c == 0) {
                            grid[i][j] = '-';
                        } else if (c == 2) {
                            grid[i][j] = 'F';
                        } else {
                            grid[i][j] = 'L';
                        }
                        j++;
                    }
                    break;
            }
        }
        for (char[] row : grid) {
            for (char point : row) {
                System.out.print(point);
            }
            System.out.println();
        }
    }
}
